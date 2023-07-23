#include "encryption.h"
#include "decryption.h"
#include <stdio.h>

int main() {
	// vector 1
	//uint64_t P[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	//uint64_t K[16] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };

	// vector 2
	//uint64_t P[8] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 };
	//uint64_t K[16] = { 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00 };

	// vector 3
	//uint64_t P[8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
	//uint64_t K[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

	// vector 4
	uint64_t P[8] = { 0xb4, 0x1e, 0x6b, 0xe2, 0xeb, 0xa8, 0x4a, 0x14 };
	uint64_t K[16] = { 0x28, 0xdb, 0xc3, 0xbc, 0x49, 0xff, 0xd8, 0x7d, 0xcf, 0xa5, 0x09, 0xb1, 0x1d, 0x42, 0x2b, 0xe7 };
	
	uint64_t* Ct = encryption(P, K);
	uint64_t* Pt = decryption(Ct, K);

	printf("[Cipher text]: ");
	for (int i = 0; i <= 7; i++) {
		printf("%llx ", Ct[i]);
	}
	printf("\n");

	printf("[Plain text]: ");
	for (int i = 0; i <= 7; i++) {
		printf("%llx ", Pt[i]);
	}
	printf("\n");

	return 0;
}