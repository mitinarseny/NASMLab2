#include <stdio.h>
#include <stdint.h>

int32_t c(int16_t x, int8_t y, int8_t z) {
    return (4 * z + y * (x - 3)) / (2 * y + 5) + 2;
}

int32_t a(int16_t x, int8_t y, int8_t z) {
    int32_t v;
    
    __asm__(
    ".intel_syntax noprefix\n\t" // ensure intel syntax syntax
    "sub eax, 3\n\t"             // EAX       <- (x - 3)
    "imul eax, edx\n\t"          // (EDX:EAX) <- (y * (x - 3))
    "lea eax, [eax+ecx*4]\n\t"   // EAX       <- (4 * z + y * (x - 3))
    "lea ecx, 5[edx+edx]\n\t"    // ECX       <- (2 * y + 5)
    "cdq\n\t"                    // (EDX:EAX) <- EAX 
    "idiv ecx\n\t"               // EAX       <- (4 * z + y * (x - 3)) / (2 * y + 5)
    "add eax, 2\n\t"             // EAX       <- (4 * z + y * (x - 3)) / (2 * y + 5) + 2
    : [v] "=a"(v) // EAX -> v
    : [x] "a"((signed)x), // x -> AX
    [y] "d"((signed)y),   // y -> DL
    [z] "c"((signed)z)    // z -> CL
    );
    return v;
}

void v(int16_t x, int8_t y, int8_t z, int32_t expect) {
    printf("v(0x%X, 0x%X, 0x%X) = 0x%X:\n\tC:   0x%X\n\tASM: 0x%X\n", x, y, z, expect, c(x, y, z), a(x, y, z));
}

int main() {
    v(0x7, -0x2, -0x1, -0xA);
    v(0x3AF, -0x71, 0x5E, 0x1E0);
    return 0;
}
