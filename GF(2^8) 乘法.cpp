#include <stdio.h>
#include <stdint.h>

uint8_t GMul2(uint8_t v) {
    return (v << 1) ^ ((v & 0x80) ? 0x1B : 0x00); // 0x1B 是模多項式
}

uint8_t GMul(uint8_t u, uint8_t v) {
    uint8_t p = 0;

    for (int i = 0; i < 8; ++i) {
        if (u & 0x01) {
            p ^= v;
        }

        v = GMul2(v); // 乘以 2，防止遞歸的問題所以沒使用GMul2 
        u >>= 1;
    }

    return p;
}

int main() {
    uint8_t a = 0x57; // 87 in decimal
    uint8_t b = 0x83; // 131 in decimal
    uint8_t result = GMul(a, b);
    
    printf("Result of GMul(0x%X, 0x%X) = 0x%X\n", a, b, result);
    return 0;
}

