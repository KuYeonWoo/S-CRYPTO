#pragma once

uint64_t LCS(uint64_t value, int shift) {
    return (value << shift) | (value >> (8 - shift));
}

uint64_t F0(uint64_t x) {
	return LCS(x, 1) ^ LCS(x, 2) ^ LCS(x, 7);
}

uint64_t F1(uint64_t x) {
	return LCS(x, 3) ^ LCS(x, 4) ^ LCS(x, 6);
}