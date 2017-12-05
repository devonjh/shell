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

    while (i = read(fd, &c, 1)) {
        //catBuf[i] = '\0';
        if (c == '\n') {
          i = write(1, &c, 1);
          c = '\r';
          i = write(1, &c, 1);
        } else {
          i = write(1, &c, 1);
        }
    }

    prints("\n****************************************\n\n");
    close(fd);

  }

  else {
      prints("No file specified. Use stdin and stdout.\n");

      fd = 0;

      prints("\n**********DEVON'S CAT... MEOW?**********\n\n");

      while (1) {
          i = read(fd, &c, 1);

          if (c == 13) {
            c = '\n';
          }

          if (c == 4 || !i) {
            prints("\n****************************************\n\n");
            return;
          }

          mputc(c);
      }
  }
}