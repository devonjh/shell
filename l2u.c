#include "ucode.c"

int main(int argc, char *argv[]) {
    int fd1, fd2, i, toScreen;
    char c;

    prints("\n********** DEVON'S L2U IN ACTION **********\n");

    if (argc < 2) {
        prints("Incorrect input given.\n");
        exit(1);
    }

    if (argc == 3) {

        fd1 = open(argv[1], O_RDONLY);
        fd2 = open(argv[2], O_WRONLY | O_CREAT);

        if (!fd1) {
            printf("Error opening %s\n", argv[1]);
            exit(1);
        }

        if (!fd2) {
            printf("Error opening %s\n", argv[2]);
            exit(1);
        }
    }

    i = read(fd1, &c, 1);               //Read char from first file into char c.

    while (i) {
        if (c >= 97 && c <= 122) {      //c is a lowercase letter.
            c -= 32;                    //convert c to uppercase equivalent.
        }

        i = write(fd2, &c, 1);

        if (!i) {
            prints("Error writing to file.\n");
        }

        i = read(fd1, &c, 1);
    }

    prints("Lowercase to Uppercase conversion complete.\n\n");

    return 1;
}