#include "ucode.c"

char cmd[128], *simpleCommand;

int tokenizeCommand() {
    char tempCMD[128];

    strcpy(tempCMD, cmd);

    simpleCommand = strtok(tempCMD, " ");

    printf("simpleCommand = %s\n",  simpleCommand);
}

int containsRedirection(char *cmd) {
    char *tempCMD;
    int i = 0, len;

    strcpy(tempCMD, cmd);
    len = strlen(tempCMD);

    for (i = 0; i < len; i++) {
        if (tempCMD[i] == '>' || tempCMD[i] == '<') {
            //prints("redirection found.\n");
            return 1;
        }
    }
    return 0;
}

int doRedirect(char *cmd) {
    int i = 0, j = 0, rdIndex = 0, len = strlen(cmd), rdType = 0, fd;
    char headCMD[128], fileCMD[128];

    //get the headCMD from the original command.
    for (i = 0; i < len; i++) {
        if (cmd[i] == '>') {
            if (cmd[i + 1] == '>') {
                rdType = 3;
                rdIndex = i + 1;
                break;
            }

            rdType = 2;
            rdIndex = i;
            break;
        }

        if (cmd[i] == '<') {
            rdType = 1;
            rdIndex = i;
        }
    }

    //printf("rdType = %d\n", rdType);
    //printf("rdIndex = %d\n", rdIndex);

    //find 'head' command.
    for (i = 0; i < rdIndex-1; i++) {
        headCMD[i] = cmd[i];
    }

    headCMD[i] = '\0';

    //printf("headCMD = %s\n", headCMD);

    for (i = rdIndex + 2; i < len; i++) {
        fileCMD[j] = cmd[i];
        j++;
    }

    fileCMD[j] = '\0';

    //printf("fileCMD = %s\n", fileCMD);

    //now handle the redirection.
    if (rdType == 1) {                          //input redirection.

        if ((fd = (open(fileCMD, O_RDONLY))) < 0) {
            prints("Error opening file within redirection.\n");
            exit(1);
        }

        dup2(fd, 0);

    }

    if (rdType == 2) {                          //output redirection.

        if ((fd = (open(fileCMD, 1 | 0100))) < 0) {
            prints("Erroer opening file within redirection.\n");
            exit(1);
        }

        dup2(fd, 1);
    }

    if (rdType == 3) {                          //Appending output redirection.

    }

    exec(headCMD);
}

int runCommand(char *cmd) {
    int i = 0, hasPipe, debug = 0, pid, redirect;

    if ((strcmp(cmd, "\0")) == 0) {
        //prints("Invalid command.\n");
        return -1;
    }

    pid = fork();

    if (pid < 0) {
        prints("Error forking child.\n");
        exit(1);
    }
    
    if (pid) {          //parent
        pid = wait(&debug);
    }

    else {

        hasPipe = containsPipe(cmd);

        printf("Pipe Status: %d\n", hasPipe);

        if (hasPipe) {                  //at least one pip within command.
            doPipe(cmd);
        }

        else {
            //prints("in else.\n");

            //tokenizeCommand();
            
            /*if (!strcmp(simpleCommand, "logout")) {               //handle logout seperately
                prints("Logging out . . .\n");
                exit(1);
            }
    
            if (!strcmp(simpleCommand, "cd")) {
                prints("Change dir.\n");
            }
    
            else {
                printf("simpleCommand within main: %s\n", simpleCommand);
                exec(cmd);
            }*/

            redirect = containsRedirection(cmd);

            printf("redirect = %d\n", redirect);

            if (redirect) {
                doRedirect(cmd);
            }

            else {
                exec(cmd);
            } 
        }
    }
    
    return 1;
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

    pid = fork();

    if (pid < 0) {
        prints("Error forking within pipe.\n");
        exit(1);
    }

    if (pid) {              //parent.
        close(pd[1]);
        dup2(pd[0], 0);

        if (containsPipe(tail)) {
            doPipe(tail);
        }

        else {
            exec(tail);
        }
    }

    else {                  //child
        close(pd[0]);
        dup2(pd[1], 1);

        //Have to check for file redirection.

        //if no redirection.
        exec(head);
    }

}

int main(int argc, char *argv[]) {
    int i, fd, hasPipe, debug, pid;
    char tempString[128];

    prints("\n********** DEVON'S SHELL **********\n\n");

    while(1) {

        resetStrings();                     //Clear global command char arry.

        debug = getCommand();           //Get the user command.

        printf("cmd = %s\n", cmd);

        /*if (containsRedirection(cmd)) {
            doRedirect(cmd);
        }

        else {
            prints("No redirect.\n");
        }*/
        

        if (!runCommand(cmd)) {
            prints("Error running command.\n");
            return -1;
        }

        prints("\n");
    }

    return 0;
}