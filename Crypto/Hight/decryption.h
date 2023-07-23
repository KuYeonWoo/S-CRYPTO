#pragma once

#include "function.h"
#include "keySchedule.h"

uint64_t** decSetX(uint64_t* C, uint64_t* K) {
	    uint64_t** X = (uint64_t**)malloc(33 * sizeof(uint64_t));
	    for (int i = 0; i <= 32; i++) {
	        X[i] = (uint64_t*)malloc(8 * sizeof(uint64_t));
	    }
	
	    uint64_t* WK = encSetWK(K);
	    uint64_t* SK = decSetSK(K);
	
	    X[0][0] = (C[0] - WK[4]) % 256;
	    X[0][1] = C[1];
	    X[0][2] = C[2] ^ WK[5];
	    X[0][3] = C[3];
	    X[0][4] = (C[4] - WK[6]) % 256;
	    X[0][5] = C[5];
	    X[0][6] = C[6] ^ WK[7];
	    X[0][7] = C[7];
	
	
	    for (int i = 1; i <= 31; i++) {
			X[i][0] = (X[i - 1][1] - (F1(X[i - 1][0]) ^ SK[4 * i - 1])) % 256;
	        X[i][1] = X[i - 1][2];
	        X[i][2] = X[i - 1][3] ^ ((F0(X[i - 1][2]) + SK[4 * i - 2]) % 256);
	        X[i][3] = X[i - 1][4];
	        X[i][4] = (X[i - 1][5] - (F1(X[i - 1][4]) ^ SK[4 * i - 3])) % 256;
	        X[i][5] = X[i - 1][6];
	        X[i][6] = X[i - 1][7] ^ ((F0(X[i - 1][6]) + SK[4 * i - 4]) % 256);
	        X[i][7] = X[i - 1][0];
	    }
	
	    X[32][0] = X[31][0];
	    X[32][1] = (X[31][1] - (F1(X[31][0]) ^ SK[127])) % 256;
	    X[32][2] = X[31][2];
	    X[32][3] = X[31][3] ^ ((F0(X[31][2]) + SK[126]) % 256);
	    X[32][4] = X[31][4];
	    X[32][5] = (X[31][5] - (F1(X[31][4]) ^ SK[125])) % 256;
	    X[32][6] = X[31][6];
	    X[32][7] = X[31][7] ^ ((F0(X[31][6]) + SK[124]) % 256);



	////round
	//for (int i = 0; i <= 32; i++) {
	//	printf("[round %d]: ", i);
	//	for (int j = 0; j <= 7; j++) {
	//		printf("%llx ", X[i][j]);
	//	}
	//	printf("\n");
	//}
	//printf("\n");

	////SK
	//for (int i = 0; i <= 127; i++) {
	//	printf("SK%d: %llx, ", i, SK[i]);
	//	if ((i-3) % 4 == 0)
	//		printf("\n");
	//}
	//printf("\n\n");
	
	    return X;
	}

uint64_t* decryption(uint64_t* C, uint64_t* K) {
	uint64_t Ct[8];
	uint64_t key[16];
	uint64_t* Pt = (uint64_t*)malloc(8 * sizeof(uint64_t));

	for (int i = 0; i <= 7; i++) {
		Ct[i] = C[7 - i];
	}
	for (int i = 0; i <= 15; i++) {
		key[i] = K[15 - i];
	}

	uint64_t** X = decSetX(Ct, key);
	uint64_t* WK = encSetWK(key);
	uint64_t* P = (uint64_t*)malloc(8 * sizeof(uint64_t));

	P[0] = (X[32][0] - WK[0]) % 256;
	P[1] = X[32][1];
	P[2] = X[32][2] ^ WK[1];
	P[3] = X[32][3];
	P[4] = (X[32][4] - WK[2]) % 256;
	P[5] = X[32][5];
	P[6] = X[32][6] ^ WK[3];
	P[7] = X[32][7];

	for (int i = 0; i <= 7; i++) {
		Pt[i] = P[7 - i];
	}

	return Pt;
}