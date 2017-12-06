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

int pipeHead(char *cmd, char *headHolder) {
    int i = 0, length = strlen(cmd);
    int j = 0;
    char *tempHead;

    while( i < length) {
        if (cmd[i] == '|') {            //we have found the first pipe symbol.
            break;
        }

        i++;
    }

    for(j = 0; j < i; j++) {
        headHolder[j] = cmd[j];
    }

    headHolder[i] = 0;
}

int pipeTail(char *cmd, char *tailHolder) {
    int i = 0, length = strlen(cmd);

    for (i = 0; i < length; i++) {
        if (cmd[i] == '|') {
            strcpy(tailHolder, cmd + i + 2);
            return 1;
        }
    }

    return -1;
}


int doPipe(char *cmd) {
    int pid, pd[2];
    char head[128], tail[128];

    pipe(pd);           //create pipe.
    
    pipeHead(cmd, head);
    pipeTail(cmd, tail);

    printf("head = %s\n", head);
    printf("tail = %s\n", tail);

    pid = fork();

    if (pid) {              //parent.
        close(pd[1]);
        dup2(pd[0], 0);

        if (containsPipe(tail)) {
            prints("Another pipe found.\n");
            doPipe(tail);
        }

        else {
            exec(tail);
        }
    }

    else {                  //child
        close(pd[0]);
        dup2(pd[1], 1);
        exec(head);
    }

    return 1;

}

int main(int argc, char *argv[]) {
    int i, fd, hasPipe, debug, pid;
    char tempString[128];

    prints("\n********** DEVON'S SHELL **********\n\n");

    while(1) {

        resetStrings();                     //Clear global command char arry.

        debug = getCommand();           //Get the user command.
        hasPipe = containsPipe(cmd);

        pipeHead(cmd, tempString);

        if (hasPipe) {                  //at least one pip within command.
            doPipe(cmd);
        }

        else {
            pid = fork();
            
            if (pid) {          //parent
                pid = wait(&debug);
            }

            else {
                tokenizeCommand();
                
                if (!strcmp(simpleCommand, "logout")) {               //handle logout seperately
                    prints("Logging out . . .\n");
                    exit(1);
                }
        
                if (!strcmp(simpleCommand, "cd")) {
                    prints("Change dir.\n");
                }
        
                else {
                    printf("simpleCommand within main: %s\n", simpleCommand);
                    exec(cmd);
                }

            }
            
        }

        prints("\n");
    }

    return 0;
}