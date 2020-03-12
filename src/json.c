#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define JSMN_PARENT_LINKS
#include "jsmn/jsmn.h"
#include "json.h"

#define DEFAULT_TOKENS_NUMBER 8

char *token_to_str(char *json, jsmntok_t *token) {
    json[token->end] = '\0';
    return json + token->start;
}

int tokenize_json(const char *json, jsmntok_t **tokens) {
    jsmn_parser parser;

    int current_size = DEFAULT_TOKENS_NUMBER;
    *tokens = malloc(sizeof(jsmntok_t) * current_size);
    int length = strlen(json);
    jsmn_init(&parser);
    int total = 0;
    do {
        total = jsmn_parse(&parser, json, length, *tokens, current_size);
        if (total == JSMN_ERROR_NOMEM) {
            current_size = current_size * 2;
            *tokens = realloc(*tokens, sizeof(jsmntok_t) * current_size);
        }
    } while(total == JSMN_ERROR_NOMEM);

    if (total == JSMN_ERROR_INVAL) {
        free(*tokens);
        return JSMN_ERROR_INVAL;
    }

    if (total == 0 || (*tokens)[0].type != JSMN_OBJECT) {
        free(*tokens);
        return JSMN_ERROR_INVAL;
    }

    return total;
}

char *sf_return_value(char *json, const char *key) {
    jsmntok_t *tokens;
    int total = tokenize_json(json, &tokens);
    if (total <= 0) {
        return 0;
    }

    char *value = NULL;
    for (int i = 1; i < total; i++) {
        jsmntok_t *token = &tokens[i];
        if (token->parent != 0 || token->type != JSMN_STRING) {
            continue;
        }
        
        char *candidate = token_to_str(json, token);
        if (strcmp(candidate, key) != 0) {
            continue;
        }
        if (i + 1 < total) {
            jsmntok_t *peek = &tokens[i + 1];
            value = token_to_str(json, peek);
            break;
        }
    }
    free(tokens);

    return value;
}

int sf_return_code(char *json) {
    char *value = sf_return_value(json, "Ret");
    if (value == NULL) {
        return 0;
    }

    return strtol(value, NULL, 10);
}
