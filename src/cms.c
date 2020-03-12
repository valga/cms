#include <stdio.h>
#include <sysexits.h>
#include "proto.h"
#include "net.h"
#include "command.h"

#define JSON "{\"first\":\"value\",\"inner\":{\"second\":\"value\"},\"third\":\"value\"}"

int usage() {
    fprintf(stderr, "Usage: cms [USERNAME[:PASSWORD]@]IP[:PORT] COMMAND --ARGS...\n");
    return EX_USAGE;
}
 
int main(int argc, char *argv[]) {
    if (argc < 3) {
        return usage();
    }

    sf_instance cam;
    char *credentials = argv[1];
    int res = sf_parse_instance(credentials, &cam);
    if (res == 0) {
        fprintf(stderr, "Invalid instance specification \"%s\".\n", credentials);
        return EX_DATAERR;
    }

    sf_command command = sf_get_command(argv[2]);
    if (command == NULL) {
        fprintf(stderr, "Unknown command \"%s\".\n", argv[2]);
        return EX_USAGE;
    }

    sf_session session;
    int err;
    err = sf_open_session(&cam, &session);
    if (err != 0) {
        fprintf(stderr, "%s\n", session.error);
        return EX_IOERR;
    }

    err = sf_login(&session, &cam);
    if (err != 0) {
        fprintf(stderr, "%s\n", session.error);
        return EX_DATAERR;
    }
    
    err = command(&session, argc - 3, argv + 3);
    if (err != 0) {
        fprintf(stderr, "%s\n", session.error);
        return EX_DATAERR;
    }

    return EX_OK;
}
