#include <stdio.h>
#include <stdint.h>

int32_t c(signed short int x, char y, char z) {
    return 4 * z + y * (x - 3);
//    return (4 * z + y * (x - 3)) / (2 * y + 5) + 2;
}

int32_t a(signed short x, char y, char z) {
    int32_t v;
//    __asm__("lea eax, 0[0+cl*4]");
    __asm__(
    ".intel_syntax noprefix\n\t" // ensure intel syntax syntax
    "sub %[x], 3\n\t"            // x = (x - 3)
    "cbw\n\t"                    // AX <- AL
    "imul bx\n\t"                // (DX:AX) <- y * (x - 3)
    "mov bx, ax\n\t"             // (DX:BX) <- y * (x - 3)
    "mov cx, dx\n\t"             // (CX:BX) <- y * (x - 3)
    "mov al, %[z]\n\t"           // AL <- z
    "cbw\n\t"                    // AX <- AL
    "mov bx, 4\n\t"              // BX <- 4
    "imul bx\n\t"                // (DX:AX) <- 4 * z
    "add bx, ax\n\t"
    "adc cx, dx\n\t"             // (CX:BX) <- 4 * z + y * (x - 3)
//    "mov %[v], bx\n\t"
    : [v] "=r" (v)
    : [x] "b"(x), // BX <- x
    [y] "a"(y),   // AL <- y
    [z] "c"(z)    // CL <- z
    );
    return v;
}

void v(short x, char y, char z) {
    printf("v(0x%X, 0x%X, 0x%X):\n\tC:   0x%X\n\tASM: 0x%X\n", x, y, z, c(x, y, z), a(x, y, z));
}

int main() {
    v(0x7, -0x2, -0x1);
    v(0x3af, -0x71, 0x5e);
    return 0;
}
