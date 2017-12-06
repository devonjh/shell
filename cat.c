#include "ucode.c"

int main(int argc, char *argv[ ]) {
  int i, fd, procNum;
  char c;
  char catBuf[1024];

  procNum = getpid();

  if (argc == 2) {                  //a filename is present.
    
    if ((fd = open(argv[1], 0)) < 0) {           //Error opening file.
        prints("Error opening file.\n");
        exit(1);
    }

    printf("Proc %d running cat.\n", procNum);

    prints("\n**********DEVON'S CAT... MEOW?**********\n\n");

    //i = read(fd, &c, 1);

    /*while (i) {
      mputc(c);
      i = read(fd, &c, 1);
    }*/

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

      prints("\n**********DEVON'S CAT... MEOW?**********\n\n");

      i = read(fd, &c, 1);
      
      while (i) {
        if (c == '\r') {
          mputc('\n');
          mputc('\r');
        }
        else {
          mputc(c);
        }
        
        i = read(fd, &c, 1);
      }

      /*while (i = read(fd, catBuf, 1024)) {
        catBuf[i] = '\0';
        printf("%s", catBuf);
        print("\n");
      }*/

      exit(1);
  }
}