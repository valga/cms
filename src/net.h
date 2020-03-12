#ifndef NET_H
#define NET_H

#include <arpa/inet.h>
#include "proto.h"

#define DEFAULT_USERNAME "admin"
#define DEFAULT_PASSWORD ""
#define DEFAULT_PORT 34567

#define MAX_ERROR 256

typedef struct {
    char *username;
    char *password;
    struct in_addr address;
    unsigned short port;
} sf_instance;

typedef struct {
    int socket;
    unsigned int id;
    unsigned int sequence;
    char error[MAX_ERROR];
} sf_session;

int sf_parse_instance(char *str, sf_instance *result);

int sf_open_session(const sf_instance *instance, sf_session *session);

sf_message *sf_build_message(const sf_session *session, const unsigned short command, const size_t payload);

sf_message *sf_receive_response(sf_session *session);
char *sf_receive_json_response(sf_session *session);

#endif
