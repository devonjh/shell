#include "ucode.c"

int console;

int parent() {      //Code for P1.
    int pid, status;

    prints("\ninit.c -> parent.\n");

    while (1) {                             
        prints("INIT File.\n");
        pid = wait(&status);                //wait for exit status from child process.
        if (pid == console) {
            prints("INIT: forks a new console for login.c\n");
            console = fork();
            if (console) {
                continue;
            }

            else {                              //execute login.c from within parent
                exec("login /dev/tty0");
            }
        }

        printf("INIT: I just buried an orphan child prc %d\n", pid);
    }
}

int main(int argc, char *argv[]) {
    int in,out;

    in = open("/dev/tty0", O_RDONLY);
    out = open("/dev/tty0", O_WRONLY);

    prints("\ninit.c -> main.\n");

    prints("INIT: fork a login proc on console.\n");

    console = fork();

    if(console) {
        parent();
    }

    else {
        prints("Executing login from within INIT.\n");
        exec("login /dev/tty0");
    }
}