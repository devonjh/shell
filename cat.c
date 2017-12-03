#include "ucode.c"

int main(int argc, char *argv[ ]) {
  int i, fd;
  char c;
  char catBuf[1024];

  if (argc == 2) {                  //a filename is present.
    
    if ((fd = open(argv[1], 0)) < 0) {           //Error opening file.
        prints("Error opening file.\n");
        exit(1);
    }

    prints("\n**********DEVON'S CAT... MEOW?**********\n\n");

    while (i = read(fd, catBuf, 1024)) {
        catBuf[i] = '\0';
        printf("%s", catBuf);
    }

    prints("\n****************************************\n\n");
    close(fd);

  }

  else {
      prints("No file specified. Use stdin and stdout.\n");

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