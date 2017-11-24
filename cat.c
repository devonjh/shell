#include "ucode.c"

int main(int argc, char *argv[ ]) {
  int i, fd;
  char c;
  char buf[1024];

  int pid = getpid();

  printf("cat.c file started.\n");

  printf("proc %d running cat program\n", pid);

  printf("argc = %d\n",argc);

  if (argc == 2) {                  //a filename is present.

    prints("filename entered.\n");
    
    if ((fd = open(argv[1], O_RDONLY) < 0)) {           //Error opening file.
        prints("Error opening file.\n");
        exit(1);
    }

    prints("File opened correctly.\n");

    while (i = read(fd, buf, 1024)) {
        printf("%s", buf);
    }

    prints("after while loop.\n");

  }

  else {
      prints("We gotta do some weird shit.\n");
  }

}