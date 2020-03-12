#ifndef COMMAND_H
#define COMMAND_H

#include "net.h"

typedef int (*sf_command)(sf_session *session, int argc, char *argv[]);

int sf_login(sf_session *session, const sf_instance *instance);
sf_command sf_get_command(char *alias);

#endif
