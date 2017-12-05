#include "ucode.c"

int main(int argc, char *argv[]) {
    int i = 0, j = 0;

    for (i = 0; i < 21; i++) {
        for (j = 0; j < 80; j++) {
            mputc(' ');
        }
    }

    return 0;
}