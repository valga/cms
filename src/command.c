#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "command.h"
#include "proto.h"
#include "json.h"

#define MAX_SESSION_LENGTH 10 // 0xffffffff

int send_json_and_free(sf_session *session, sf_message **message) {
    size_t length = sizeof(**message) + (*message)->header.length - sizeof((*message)->payload);

    send(session->socket, *message, length, 0);
    free(*message);

    session->sequence++;

    return 0;
}

int receive_json_and_check_result(sf_session *session, char **json) {
    *json = sf_receive_json_response(session);
    if (*json == NULL) {
        sprintf(session->error, "Command returned an empty result.");
        return 1;
    }
    
    int ret = sf_return_code(*json);
    if (ret != SF_RET_OK) {
        free(*json);
        sprintf(session->error, "Command failed with return code %d.", ret);
        return 2;
    }

    return 0;
}

int receive_json_and_check_with_free(sf_session *session) {
    char *json;
    int result = receive_json_and_check_result(session, &json);
    if (result != 0) {
        return result;
    }
    free(json);

    return result;
}

int sf_login(sf_session *session, const sf_instance *instance) {
    session->sequence = 0;

    sf_message *message;
    char pwd_hash[SF_PWD_HASH_SIZE + 1];

    hash_password(instance->password, pwd_hash);
    message = sf_build_message(session, SF_CMD_LOGIN_REQ, sizeof(SF_LOGIN_JSON) + strlen(instance->username) + strlen(pwd_hash));
    message->header.length = sprintf(message->payload, SF_LOGIN_JSON, pwd_hash, instance->username);
    send_json_and_free(session, &message);

    return receive_json_and_check_with_free(session);
}

int generic(sf_session *session, unsigned short command, const char *key) {
    sf_message *message;
    message = sf_build_message(session, command, sizeof(SF_GENERIC_JSON) + strlen(key) + MAX_SESSION_LENGTH);
    message->header.length = sprintf(message->payload, SF_GENERIC_JSON, key, session->id);
    send_json_and_free(session, &message);

    char *json;
    json = sf_receive_json_response(session);
    if (json == NULL) {
        sprintf(session->error, "Command returned an empty result.");
        return 1;
    }

    char *value = sf_return_value(json, key);
    if (value == NULL) {
        free(json);
        sprintf(session->error, "Command returned an empty value.");
        return 2;
    }

    printf("%s\n", value);
    free(json);
    
    return 0;
}

int gettime(sf_session *session, int argc, char *argv[]) {
    return generic(session, SF_CMD_TIMEQUERY_REQ, "OPTimeQuery");
}

char *find_arg_value(const char* arg, int argc, char *argv[]) {
    char *value = NULL;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], arg) != 0) {
            continue;
        }

        if (i + 1 < argc) {
            value = argv[i + 1];
            break;
        }
    }

    return value;
}

int getconfig(sf_session *session, int argc, char *argv[]) {
    char *key = find_arg_value("--key", argc, argv);        
    if (key == NULL) {
        sprintf(session->error, "Argument --key is missing or empty.");
        return 1;
    }

    return generic(session, SF_CMD_CONFIG_GET, key);
}

int setconfig(sf_session *session, int argc, char *argv[]) {
    char *key = find_arg_value("--key", argc, argv);        
    if (key == NULL) {
        sprintf(session->error, "Argument --key is missing or empty.");
        return 1;
    }

    char *value = find_arg_value("--value", argc, argv);        
    if (value == NULL) {
        sprintf(session->error, "Argument --value is missing or empty.");
        return 1;
    }

    sf_message *message;
    message = sf_build_message(session, SF_CMD_CONFIG_SET, sizeof(SF_SET_CONFIG) + 2 * strlen(key) + strlen(value) + MAX_SESSION_LENGTH);
    message->header.length = sprintf(message->payload, SF_SET_CONFIG, key, value, key, session->id);
    
    send_json_and_free(session, &message);

    return receive_json_and_check_with_free(session);
}

int snap(sf_session *session, int argc, char *argv[]) {
    sf_message *message;
    message = sf_build_message(session, SF_CMD_NET_SNAP_REQ, sizeof(SF_SNAP_JSON) + MAX_SESSION_LENGTH);
    message->header.length = sprintf(message->payload, SF_SNAP_JSON, session->id);
    
    send_json_and_free(session, &message);

    sf_message *response = sf_receive_response(session);
    if (response == NULL) {
        sprintf(session->error, "Snap returned an empty result.");
        return 1;
    }

    if (response->header.length > 0 && response->payload[0] == '{') {
        int ret = sf_return_code(response->payload);
        free(response);
        sprintf(session->error, "Snap failed with return code %d.", ret);
        return 2;
    }

    fwrite(response->payload, sizeof(char), response->header.length, stdout);
    
    free(response);

    return 0;
}

int synctime(sf_session *session, int argc, char *argv[]) {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    sf_message *message;
    message = sf_build_message(session, SF_CMD_SYSMANAGER_REQ, sizeof(SF_SYNC_TIME_JSON) + MAX_SESSION_LENGTH);
    message->header.length = sprintf(message->payload,
        SF_SYNC_TIME_JSON, 
        timeinfo->tm_year + 1900, 
        timeinfo->tm_mon + 1, 
        timeinfo->tm_mday, 
        timeinfo->tm_hour, 
        timeinfo->tm_min, 
        timeinfo->tm_sec, 
        session->id
    );
    send_json_and_free(session, &message);

    return receive_json_and_check_with_free(session);
}

int reboot(sf_session *session, int argc, char *argv[]) {
    sf_message *message;
    message = sf_build_message(session, SF_CMD_SYSMANAGER_REQ, sizeof(SF_REBOOT_JSON) + MAX_SESSION_LENGTH);
    message->header.length = sprintf(message->payload, SF_REBOOT_JSON, session->id);
    send_json_and_free(session, &message);

    return receive_json_and_check_with_free(session);
}

sf_command sf_get_command(char *alias) {
    int len = strlen(alias);
    switch (len) {
    case 4:
        if (strcmp(alias, "snap") == 0) {
            return snap;
        }
        break;
    case 6:
        if (strcmp(alias, "reboot") == 0) {
            return reboot;
        }
        break;
    case 7:
        if (strcmp(alias, "gettime") == 0) {
            return gettime;
        }
        break;
    case 8:
        if (strcmp(alias, "synctime") == 0) {
            return synctime;
        }
    case 9:
        if (strcmp(alias, "getconfig") == 0) {
            return getconfig;
        } else if (strcmp(alias, "setconfig") == 0) {
            return setconfig;
        }
    }

    return NULL;
}


