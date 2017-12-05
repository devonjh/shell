#include "ucode.c"

char cmd[128], *simpleCommand;

int tokenizeCommand() {
    char tempCMD[128];

    strcpy(tempCMD, cmd);

    simpleCommand = strtok(tempCMD, " ");

    printf("simpleCommand = %s\n",  simpleCommand);
}

int Execute(char *cmd) {
    int i = 0;
}

int myMemset(char *string, int length) {
    int i = 0;

    for (i = 0; i < length; i++) {
        string[i] = 0;
    }

    return 1;
}

void resetStrings() {
    myMemset(cmd, 128);
    myMemset(simpleCommand, 64);
}

int getCommand() {
    char currDirr[128];

    getcwd(currDirr);

    printf("DSH:%s $ ", currDirr);

    gets(cmd);

    if (!cmd) {
        prints("Error getting command from user.\n");
        return -1;
    }

    printf("cmd = %s\n", cmd);

    return 0;
}

int containsPipe(char *cmd) {
    int i = 0, len = strlen(cmd);

    for (i = 0; i < len; i++) {
        if (cmd[i] == '|') {
            return 1;
        }
    }

    return 0;
}

int doPipe(char *cmd) {
    int pid, int pd[2];

    pipe(pd);           //create pipe.

    pid = fork();

    if (pid) {
        close(pd[1]);
        dup2(pd[0], 0);
        exec(tail);
    }

    else {          //child
        close(pd[0]);
        dup2(pd[1], 1);
        exec(head);
    }



}

int main(int argc, char *argv[]) {
    int i, fd, hasPipe, debug;

    prints("\n********** DEVON'S SHELL **********\n\n");

    while(1) {

        resetStrings();                     //Clear global command char arry.

        debug = getCommand();           //Get the user command.

        tokenizeCommand();

        if (!strcmp(simpleCommand, "logout")) {               //handle logout seperately
            prints("Logging out . . .\n");
            exit(1);
        }

        if (!strcmp(simpleCommand, "cd")) {

        }

        else {
            printf("simpleCommand within main: %s\n", simpleCommand);
        }
    }

    return 0;
}