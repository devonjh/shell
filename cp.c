#include "ucode.c"

int main (int argc, char *argv[]) {
    int fd1, fd2, i, debug;
    struct stat s;
    char buf[1024];

    prints("\n********** DEVON'S COPY **********\n\n");

    if (argc != 3) {
        prints("Input Error.\n");
        exit(1);
    }

    if ((fd1 = open(argv[1], 0)) < 0) {
        prints("Error opening file for cp.\n");
        exit(1);
    }

    //determine if file 1 exists.
    if((debug = stat(argv[2], &s)) == -1) {
        printf("%s does not exist. creating now.", argv[2]);
        creat(argv[2]);
    }

    prints("outside debug.\n");

    if ((fd2 = open(argv[2], 1)) < 0) {
        prints("Error opening second file.\n");
        exit(1);
    }

    prints("file 2 opened correctly.\n");

    while ((i = read(fd1, buf, 1024)) != 0) {
        write(fd2, buf, i);
    }

    prints("Copy complete. Closing files.\n");

    close(fd1);
    close(fd2);
    
}