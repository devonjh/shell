#include "ucode.c"

int clearBuf(char *line) {
    int i;

    for(i = 0; i < 1024; i++) {
        line[i] = 0;
    }

    return 1;
}

int getNewLine(int fd, char *line, int *eof) {
    int i = 0, n;

    while (i < 1024) {
        n  = read(fd, &line[i], 1);

        if (!n) {
            //prints("Reached End of File.\n");
            *eof = 1;
            //printf("eof = %d\n", *eof);
            return 1;
        }

        if (line[i] == '\n' || line[i] == '\r') {
            return 1;
        }

        i++;
    }
}

int checkPattern(char *line, char *pattern) {
    return searchString(line, pattern);
}

int main(int argc, char *argv[ ]) {
    int i, j, fd, eof = 0;
    char *pattern = argv[1];
    char *buf;
    char line[1024];

    prints("\n********** DEVON'S GREP **********\n\n");

    if (argc == 2) {
        fd = 0;
    }

    else {
        if ((fd = open(argv[2], 0)) < 0) {
            prints("ERROR opening file.\n");
            exit(1);
        }
    }

    while (!eof) {
        clearBuf(line);
        getNewLine(fd, line, &eof);

        if ((checkPattern(line, pattern)) == 1) {              //if the line contains the pattern, print it to the screen.
            prints(line);
        }
    }

    prints("\n**********************************\n");
    close (fd);
}