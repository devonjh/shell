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
    char tty[128];

    if (argc == 2) {                    //filename specified.

        if ((fd = open(argv[1], 0)) < 0) {
            prints("Error opening file.\n");
            exit(1);
        }
    }

    if(argc == 1) {                      //no filename given.        
        fd = dup(0);
        close(0);
        gettty(tty);
        open(tty, O_RDONLY);
    }

    debug = startPage(fd);

    if (debug == -1) {
        close(fd);
        exit(1);
    }
    
    while(1) {

        userInput = getc();

        switch(userInput) {
            case '\r':
                debug = printNewLine(fd);
                break;
            case ' ':
                debug = startPage(fd);
                break;
            case 'q':
                mputc('\n');
                close(fd);
                return 0;
                break;
        }

        if (debug == -1) {
            close(fd);
            exit(1);
        }
    }
}