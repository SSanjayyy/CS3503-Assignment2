#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

// A1 prot 
void div_convert(uint32_t n, int base, char *out);
void sub_convert(uint32_t n, int base, char *out);
void print_tables(uint32_t n);

// A2 prot 
void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int32_t n, char *out);
void to_ones_complement(int32_t n, char *out);
void to_twos_complement(int32_t n, char *out);

static void trim(char *s){
    size_t n = strlen(s);
    while (n && (s[n-1]=='\n' || s[n-1]=='\r' ||
                 isspace((unsigned char)s[n-1]))) s[--n]=0;
}

int main(int argc, char **argv){
    // default to A2_tests.txt
    const char *fname = (argc >= 2) ? argv[1] : "A2_tests.txt";
    FILE *f = fopen(fname, "r");
    if(!f){
        fprintf(stderr,"Could not open %s\n", fname);
        return 1;
    }

    char line[512];
    int total=0, passed=0;

    while (fgets(line, sizeof line, f)) {
        trim(line);
        if (line[0]=='#' || line[0]==0) continue;

        char fn[64];
       

        // mapping funcs
        {
            char in_str[256], expected[256];
            if (sscanf(line, "%63s %255s %255s", fn, in_str, expected) == 3) {
                char got[512];

                if (strcmp(fn,"oct_to_bin")==0) {
                    oct_to_bin(in_str, got);
                } else if (strcmp(fn,"oct_to_hex")==0) {
                    oct_to_hex(in_str, got);
                } else if (strcmp(fn,"hex_to_bin")==0) {
                    hex_to_bin(in_str, got);
                } else {
                    goto not_mapping;
                }

                int ok = (strcmp(got, expected)==0);
                printf("Test %d: %s(\"%s\") -> Expected: \"%s\", Got: \"%s\" [%s]\n",
                       ++total, fn, in_str, expected, got, ok?"PASS":"FAIL");
                if (ok) passed++;
                continue;
            }
        }
not_mapping: ;

        // signed funcs
        {
            int n;
            char expected[256];
            if (sscanf(line, "%63s %d %255s", fn, &n, expected) == 3) {
                char got[256];

                if      (strcmp(fn,"to_sign_magnitude")==0)    to_sign_magnitude(n, got);
                else if (strcmp(fn,"to_ones_complement")==0)   to_ones_complement(n, got);
                else if (strcmp(fn,"to_twos_complement")==0)   to_twos_complement(n, got);
                else goto unknown;

                int ok = (strcmp(got, expected)==0);
                printf("Test %d: %s(%d) -> Expected: \"%s\", Got: \"%s\" [%s]\n",
                       ++total, fn, n, expected, got, ok?"PASS":"FAIL");
                if (ok) passed++;
                continue;
            }
        }

unknown:
        fprintf(stderr, "Unrecognized test line: %s\n", line);
    }

    fclose(f);
    printf("Summary: %d/%d tests passed\n", passed, total);
    return 0;
}