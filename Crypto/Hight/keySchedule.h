#pragma once

#include <stdint.h>
#include <stdlib.h>

uint64_t s[134] = { 0x00, };
uint64_t d[128];

//Encryption SetKeySchedule
uint64_t* encSetWK(uint64_t* K) {
    uint64_t* WK = (uint64_t*)malloc(8 * sizeof(uint64_t));
    for (int i = 0; i <= 3; i++) {
        WK[i] = K[i + 12];
    }

    for (int i = 4; i <= 7; i++) {
        WK[i] = K[i - 4];
    }

    return WK;
}

uint64_t* encSetSK(uint64_t* K) {
    uint64_t* SK = (uint64_t**)malloc(128 * sizeof(uint64_t));
    
    s[0] = 0x00;
    s[1] = 0x01;
    s[2] = 0x00;
    s[3] = 0x01;
    s[4] = 0x01;
    s[5] = 0x00;
    s[6] = 0x01;

    d[0] = s[6] << 6 | s[5] << 5 | s[4] << 4 | s[3] << 3 | s[2] << 2 | s[1] << 1 | s[0];
    for (int i = 1; i <= 127; i++) {
        s[i + 6] = s[i + 2] ^ s[i - 1];
        d[i] = s[i + 6] << 6 | s[i + 5] << 5 | s[i + 4] << 4 | s[i + 3] << 3 | s[i + 2] << 2 | s[i + 1] << 1 | s[i];
    }

    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            SK[16 * i + j] = (K[(j - i + 8) % 8] + d[16 * i + j]) % 256;
            SK[16 * i + j + 8] = (K[(j - i + 8) % 8 + 8] + d[16 * i + j + 8]) % 256;
        }                               
    }
    
    return SK;
}

//Decryption SetKeySchedule
uint64_t* decSetSK(uint64_t* K) {
    uint64_t* SK = (uint64_t*)malloc(128 * sizeof(uint64_t));
    uint64_t* encSK = encSetSK(K);

    for (int i = 0; i <= 127; i++) {
        SK[i] = encSK[127 - i];
    }

    return SK;
}


