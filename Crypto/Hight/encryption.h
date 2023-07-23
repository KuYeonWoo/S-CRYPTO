#pragma once

#include "keySchedule.h"
#include "function.h"

uint64_t** encSetX(uint64_t* P, uint64_t* K) {

    uint64_t** X = (uint64_t**)malloc(33 * sizeof(uint64_t));
    for (int i = 0; i <= 32; i++) {
        X[i] = (uint64_t*)malloc(8 * sizeof(uint64_t));
    }

    uint64_t* WK = encSetWK(K);
    uint64_t* SK = encSetSK(K);

    X[0][0] = (P[0] + WK[0]) % 256;
    X[0][1] = P[1];
    X[0][2] = P[2] ^ WK[1];
    X[0][3] = P[3];
    X[0][4] = (P[4] + WK[2]) % 256;
    X[0][5] = P[5];
    X[0][6] = P[6] ^ WK[3];
    X[0][7] = P[7];

   
    for (int i = 0; i <= 30; i++) {
        X[i + 1][0] = X[i][7] ^ ((F0(X[i][6]) + SK[4 * i + 3]) % 256);
        X[i + 1][1] = X[i][0];
        X[i + 1][2] = (X[i][1] + (F1(X[i][0]) ^ SK[4 * i])) % 256;
        X[i + 1][3] = X[i][2];
        X[i + 1][4] = X[i][3] ^ ((F0(X[i][2]) + SK[4 * i + 1]) % 256);
        X[i + 1][5] = X[i][4];
        X[i + 1][6] = (X[i][5] + (F1(X[i][4]) ^ SK[4 * i + 2])) % 256;
        X[i + 1][7] = X[i][6];

    }

    X[32][0] = X[31][0];
    X[32][1] = (X[31][1] + (F1(X[31][0]) ^ SK[124])) % 256;
    X[32][2] = X[31][2];
    X[32][3] = X[31][3] ^ (F0(X[31][2]) + SK[125]) % 256;
    X[32][4] = X[31][4];
    X[32][5] = (X[31][5] + (F1(X[31][4]) ^ SK[126])) % 256;
    X[32][6] = X[31][6];
    X[32][7] = X[31][7] ^ (F0(X[31][6]) + SK[127]) % 256;

    ////WK Ãâ·Â
    //for (int i = 0; i <= 7; i++) {
    //    printf("%llx ", WK[i]);
    //}
    //printf("\n\n");

    ////round
    //for (int i = 0; i <= 32; i++) {
    //    printf("[round %d]: ", i);
    //    for (int j = 0; j <= 7; j++) {
    //        printf("%llx ", X[i][j]);
    //    }
    //    printf("\n");
    //}
    //printf("\n");

    ////SK
    //for (int i = 0; i <= 127; i++) {
    //    printf("SK%d: %llx, ", i, SK[i]);
    //    if ((i-3) % 4 == 0)
    //        printf("\n");
    //}
    //printf("\n\n");


    return X;
}


uint64_t* encryption(uint64_t* P, uint64_t* K) {
    uint64_t pt[8];
    uint64_t key[16];
    for (int i = 0; i <= 7; i++) {
        pt[i] = P[7 - i];
    }
    for (int i = 0; i <= 15; i++) {
        key[i] = K[15 - i];
    }
     
    uint64_t** X = encSetX(pt, key);
    uint64_t* WK = encSetWK(key);
    uint64_t* C = (uint64_t*)malloc(8 * sizeof(uint64_t));
  
    C[7] = (X[32][0] + WK[4]) % 256;
    C[6] = X[32][1];
    C[5] = X[32][2] ^ WK[5];
    C[4] = X[32][3];
    C[3] = (X[32][4] + WK[6]) % 256;
    C[2] = X[32][5];
    C[1] = X[32][6] ^ WK[7];
    C[0] = X[32][7];

    return C;
}


