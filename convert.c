#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h> 
#include <stdlib.h>
#include <ctype.h>

static void write_bin32(uint32_t x, char *out) {
    for (int i = 31; i >= 0; --i) {
        *out++ = ((x >> i) & 1u) ? '1' : '0';
    }
    *out = '\0';
}
static int hex_val(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
    if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
    return -1;
}

// oct_to_bin: map each oct digit
void oct_to_bin(const char *oct, char *out) {
    int pos = 0;
    for (const char *p = oct; *p; ++p) {
        if (*p < '0' || *p > '7') { out[0] = '\0'; return; } /* simple guard */
        int v = *p - '0';
        out[pos++] = (v & 0b100) ? '1' : '0';
        out[pos++] = (v & 0b010) ? '1' : '0';
        out[pos++] = (v & 0b001) ? '1' : '0';
    }
    out[pos] = '\0';
}

static char d2c16(int d) { return d < 10 ? ('0' + d) : ('A' + (d - 10)); }

// oct_to_hex: oct to bin (3 bits/digit) to group by 4 yo hex (uppercase)
void oct_to_hex(const char *oct, char *out) {
    // 1) binary string
    char bin[512];
    oct_to_bin(oct, bin);
    size_t n = strlen(bin);
    if (n == 0) { strcpy(out, ""); return; }

    // 2) left pad with zeros to multiple of 4
    int pad = (4 - (int)(n % 4)) % 4;
    char padded[520];
    int k = 0;
    for (int i = 0; i < pad; ++i) padded[k++] = '0';
    for (size_t i = 0; i < n; ++i) padded[k++] = bin[i];
    padded[k] = '\0';

    // 3) convert each nibble to hex
    char hex[520];
    int hpos = 0;
    for (int i = 0; padded[i]; i += 4) {
        int v = (padded[i]   - '0') * 8 +
                (padded[i+1] - '0') * 4 +
                (padded[i+2] - '0') * 2 +
                (padded[i+3] - '0');
        hex[hpos++] = d2c16(v);  
    }
    hex[hpos] = '\0';

    // 4) strip leading zeros
    int start = 0;
    while (hex[start] == '0' && hex[start+1] != '\0') start++;
    strcpy(out, hex + start);
}

// hex_to_bin: each hex char to 4-bit nibble
void hex_to_bin(const char *hex, char *out) {
    int pos = 0;
    for (const char *p = hex; *p; ++p) {
        int v = hex_val(*p);
        if (v < 0) { out[0] = '\0'; return; } // empty 
        out[pos++] = (v & 0b1000) ? '1' : '0';
        out[pos++] = (v & 0b0100) ? '1' : '0';
        out[pos++] = (v & 0b0010) ? '1' : '0';
        out[pos++] = (v & 0b0001) ? '1' : '0';
    }
    out[pos] = '\0';
}

// to_sign_magnitude: MSB = sign; lower 31 bits = magnitude
void to_sign_magnitude(int32_t n, char *out) {
    if (n >= 0) {
        write_bin32((uint32_t)n, out);
        return;
    }
    // magnitude = |n| in lower 31 bits
    uint32_t mag = (uint32_t)(- (int64_t)n);   
    mag &= 0x7FFFFFFFu;                        // keep 31-bit magnitude 
    uint32_t rep = 0x80000000u | mag;
    write_bin32(rep, out);
}

// to_ones_complement: nonnegative unchanged
void to_ones_complement(int32_t n, char *out) {
    if (n >= 0) {
        write_bin32((uint32_t)n, out);
    } else {
        uint32_t pos = (uint32_t)(- (int64_t)n);
        uint32_t rep = ~pos;
        write_bin32(rep, out);
    }
}

// to_twos_complement: the native 32-bit two's-complement bit pattern
void to_twos_complement(int32_t n, char *out) {
    write_bin32((uint32_t)n, out);
}