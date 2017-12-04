#include "ucode.c"

int printNewLine(int fd) {
    int i, j;
    char c;

    for (i = 0; i < 80; i++) {
        j = read(fd, &c, 1);

        if (!j) {
            return -1;
        }

        mputc(c);

        if (c == '\n') {
            break;
        }
    }
}

int startPage (int fd) {
    int i, j, k;
    char c;


    for (i = 0; i < 20; i++) {
        for (j = 0; j < 80; j++) {
            k = read(fd, &c, 1);

            if (!k) {
                return -1;
            }

            mputc(c);

            if (c == '\n') {
                break;
            }
        }
    }
}

int main(int argc, char *argv[ ]) {
    int fd, i;
    char firstPage[800];
    char *newLine;
    char userInput;
    int debug;
    char c;


    prints("\n********** DEVON'S MORE **********\n\n");

    if (argc == 2) {                    //filename specified.

        if ((fd = open(argv[1], 0)) < 0) {
            prints("Error opening file.\n");
            exit(1);
        }

        debug = startPage(fd);

        while(1) {

            userInput = getc();

            switch(userInput) {
                case '\r':
                    debug = printNewLine(fd);
                    break;
                case 'q':
                    mputc('\n');
                    close(fd);
                    return 0;
                    break;
            }

            if (debug == -1) {
                close(fd);
                return 0;
            }
        }

        return 0;
    }

    else {                      //no filename given.        
        fd = 0;

        while (1) {
            i = read(fd, &c, 1);

            if (c == 13) {
            c = '\n';
            }

            if (c == 4 || !i) {
            return;
            }

            mputc(c);
        }
    }
}