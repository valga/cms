#include <string.h>
#include <stdlib.h>
#include "proto.h"
#include "crypto/md5.h"

void hash_password(const char *password, char *hash) {
    BYTE md5[MD5_BLOCK_SIZE];
    MD5_CTX ctx;
    
    md5_init(&ctx);
    md5_update(&ctx, (const unsigned char *)password, strlen(password));
    md5_final(&ctx, md5);

    for (int i = 0; i < SF_PWD_HASH_SIZE; i++) {
        char chr = (md5[2 * i] + md5[2 * i + 1]) % 62;
        if (chr > 35) {
            // a..z
            chr += 'a' - 36;
        } else if (chr > 9) {
            // A..Z
            chr += 'A' - 10;
        } else {
            // 0..9
            chr += '0';
        }

        hash[i] = chr;
    }
    
    hash[SF_PWD_HASH_SIZE] = '\0';
}
