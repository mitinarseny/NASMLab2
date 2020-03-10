#include <stdio.h>
#include <stdint.h>

//__int16_t a(int16_t x, int8_t y, int8_t z) {
//    int16_t v;
//    __asm__(".intel_syntax noprefix\n\t"
//            "mov al, %[z]\n\t"
//            "cbw\n\t"
//            "mov bx, 4\n\t"
//            "imul bx\n\t"
//            "mov bx, ax\n\t" //4z in bx
//            "mov al, %[y]\n\t"
//            "cbw\n\t"
//            "mov cx, ax\n\t"
//            "mov ax, %[x]\n\t"
//            "sub ax, 3\n\t"
//            "imul cx\n\t"
//            "add ax, bx\n\t"
//            "mov bx, ax\n\t"
//            "mov al, %[y]\n\t"
//            "cbw\n\t"
//            "mov cx, 2\n\t"
//            "imul cx\n\t"
//            "add ax, 5\n\t"
//            "xchg ax, bx\n\t"
//            "idiv bx\n\t"
//            "add ax, 2\n\t"
//            "mov %[vas], ax\n\t"
//    : [vas] "=r" (v)
//    : [x] "r" (x), [y] "r" (y), [z] "r" (z)
//    );
//    return v;
//}

int32_t c(int16_t x, int8_t y, int8_t z) {
//    return 4 * z + y * (x - 3);
//    return y * (x - 3);
//    return (4 * z + y * (x - 3)) / (2 * y + 5) + 2;
    return (4 * z + y * (x - 3)) / (2 * y + 5);
}

//int16_t mul2(int8_t x) {
//    int16_t v;
//    __asm__(
//    ".intel_syntax noprefix\n\t" // ensure intel syntax syntax
//    "cbw\n\t"
//    "mov bx, 2\n\t"
//    "imul bx\n\t"
////    "mov cx, dx\n\t"
////    "shl cx, 16\n\t"
////    "mov cx, ax\n\t"
////    "mov eax, ecx\n\t"
//    : [v] "=a"(v)
//    : [x] "a"(x)
//    );
//    return v;
//}

int32_t a(int16_t x, int8_t y, int8_t z) {
    int32_t v;
//    __asm__("lea eax, 0[0+cl*4]");
    __asm__(
    ".intel_syntax noprefix\n\t" // ensure intel syntax syntax
    "sub eax, 3\n\t"
    "imul eax, edx\n\t"
    "lea eax, [eax+ecx*4]\n\t"
    "lea ecx, 5[edx+edx]\n\t"
    "cdq\n\t"
    "idiv ecx\n\t"
//    "add eax, 2\n\t"
//    "imul eax, edx\n\t"
//    "add eax, ecx\n\t"
//    "cwde\n\t"
//    "sub %[x], 3\n\t"            // x = (x - 3)
//    "cbw\n\t"                    // AX <- AL
//    "imul bx\n\t"                // (DX:AX) <- y * (x - 3)
//    // WE WILL USE AX ONLY
//    "lea cx, 0[0+cx*4]\n\t"
//    "add ax, cx"
//    "mov bx, ax\n\t"             // BX <- y * (x - 3)
//    "mov ax, 4\n\t"              // AX <- 4
//    "imul cl\n\t"                // (DX:AX) <- 4 * z
//    "add ax, bx\n\t"             // AX <- 4 * z + y * (x - 3)
//    "mov bx, ax\n\t"             // BX <- 4 * z + y * (x - 3)
//    "mov al, %[y]\n\t"           // AL <- y
//    "cbw\n\t"                    // AX <- y
//    "mov cx, 2\n\t"              // CX <- 2
//    "imul cx\n\t"                // AX <- 2 * y
//    "add ax, 5\n\t"              // AX <- 2 * y + 5
//    "xchg ax, bx\n\t"            // AX <-> BX
//    "idiv bx\n\t"                // AX <- (4 * z + y * (x - 3))/(2 * y + 5)
//    "add ax, 2\n\t"
    /* "mov bx, ax\n\t"             // (DX:BX) <- y * (x - 3) */
    /* "mov cx, dx\n\t"             // (CX:BX) <- y * (x - 3) */
    /* "mov al, %[z]\n\t"           // AL <- z */
    /* "cbw\n\t"                    // AX <- AL */
    /* "mov bx, 4\n\t"              // BX <- 4 */
    /* "imul bx\n\t"                // (DX:AX) <- (4 * z + y * (x - 3))/() */
    /* "add bx, ax\n\t" */
    /* "adc cx, dx\n\t"             // (CX:BX) <- 4 * z + y * (x - 3) */

//    "push cx\n\t"
//    "push bx\n\t"
//    "pop %[v]\n\t"
//    "mov %[v], bx\n\t"
    : [v] "=a"(v) // EAX -> v
    : [x] "a"(x),  // x -> AX
    [y] "d"(y),    // y -> DL
    [z] "c"(z)     // z -> CL
    : "ebx"
    );
    return v;
}

void v(int16_t x, int8_t y, int8_t z, int32_t expect) {
    printf("v(0x%X, 0x%X, 0x%X) = 0x%X:\n\tC:   0x%X\n\tASM: 0x%X\n", x, y, z, expect, c(x, y, z), a(x, y, z));
}

int main() {
//    printf("0x%X", mul2(8));
    v(0x7, -0x2, -0x1, -0xA);
    v(0x3AF, -0x71, 0x5E, 0x1E0);
    return 0;
}
