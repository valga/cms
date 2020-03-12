#ifndef JSON_H
#define JSON_H

#define JSMN_HEADER
#include "jsmn/jsmn.h"

char *sf_return_value(char *json, const char *key);
int sf_return_code(char *json);

#endif
