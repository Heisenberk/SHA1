#ifndef SHA_H
#define SHA_H

#include <string.h>
#include "../inc/types.h"

SHA1 init_registres(SHA1 hash);
SHA1 init_16W(SHA1 hash,int rang);
SHA1 init_sha1(char* message);
void process_sha1(SHA1 hash,char* out);
void done_sha1(SHA1 hash);

#endif
