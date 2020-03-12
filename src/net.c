#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include "net.h"

int sf_parse_instance(char *str, sf_instance *result) {
    if (strlen(str) == 0) {
        return 0;
    }
    
    char *at_pos, *colon_pos;
    int err;
    
    at_pos = strchr(str, '@');
    if (at_pos == NULL) {
        result->username = DEFAULT_USERNAME;
        result->password = DEFAULT_PASSWORD;
        goto handle_host;
    }

    *at_pos = '\0';

    colon_pos = strchr(str, ':');
    if (colon_pos == NULL) {
        result->password = DEFAULT_PASSWORD;
        goto handle_username;
    }

    *colon_pos = '\0';
    result->password = colon_pos + 1;

handle_username:

    result->username = str;
    str = at_pos + 1;

handle_host:

    colon_pos = strchr(str, ':');
    if (colon_pos == NULL) {
        result->port = DEFAULT_PORT;
        goto handle_address;
    }

    *colon_pos = '\0';

    result->port = strtol(colon_pos + 1, NULL, 10);

handle_address:

    err = inet_aton(str, &result->address);

    return err;
}

int sf_open_session(const sf_instance *instance, sf_session *session) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);  
    if (fd == -1) {
        sprintf(session->error, "socket() failed (%d): %s.", errno, strerror(errno));
        return 1;
    }
    
    int res;
    int flag = 1;
    res = setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag));
    if (res) {
        sprintf(session->error, "setsockopt() failed (%d): %s.", errno, strerror(errno));
        close(fd);
        return 2;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(instance->port);
    addr.sin_addr = instance->address;
    res = connect(fd, (const struct sockaddr *) &addr, sizeof(addr));
    if (res == -1) {
        sprintf(session->error, "connect() failed (%d): %s.", errno, strerror(errno));
        close(fd);
        return 2;
    }

    session->socket = fd;

    return 0;
}

sf_message *sf_build_message(const sf_session *session, const unsigned short command, const size_t payload) {
    sf_message *message;
    message = malloc(sizeof(*message) + payload);
    memset(message, '\0', sizeof(*message) + payload);
    sf_header *header = &message->header;
    header->protocol = SF_PROTO_SOFIA;
    header->direction = SF_DIR_OUTGOING;
    header->session_id = session->id;
    header->sequence_number = session->sequence;
    header->command = command;

    return message;
}

sf_message *sf_receive_response(sf_session *session) {
    sf_header header;
    recv(session->socket, &header, sizeof(header), 0);
    session->id = header.session_id;

    sf_message *message;
    message = malloc(sizeof(sf_header) + sizeof(char) * header.length);
    memcpy(message, &header, sizeof(header));
    int remaining = header.length;
    char *position = message->payload;
    do {
        int received = recv(session->socket, position, remaining, 0);
        if (received == -1) {
            sprintf(session->error, "recv() failed (%d): %s.", errno, strerror(errno));
            free(message);
            return NULL;
        }
        remaining -= received;
        position += received;
    } while (remaining > 0);

    return message;
}

char *sf_receive_json_response(sf_session *session) {
    sf_header header;
    recv(session->socket, &header, sizeof(header), 0);
    session->id = header.session_id;

    char *json;
    json = malloc(sizeof(char) * (header.length + 1));
    int remaining = header.length;
    char *position = json;
    do {
        int received = recv(session->socket, position, remaining, 0);
        if (received == -1) {
            sprintf(session->error, "recv() failed (%d): %s.", errno, strerror(errno));
            free(json);
            return NULL;
        }
        remaining -= received;
        position += received;
    } while (remaining > 0);
        
    json[header.length] = '\0';
    return json;
}
