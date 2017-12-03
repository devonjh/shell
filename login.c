#include "ucode.c"

int in, out, err;
char userName[128];
char password[128];

int main(int argc, char *argv[]) {
    int fd, n, i = 1, userFound = 0;
    char *lastToken;
    char *tempString;
    char *testString = "This is a test";
    char *readName;
    char *readPass;
    int gid;
    int uid;
    char *fullName;
    char *homedir;
    char *program;
    char buf[1024];
    char *readLines[6];
    int test;
    char dummy;
    char *readLine;

    //close file descriptors inehrited from INIT.
    prints("\n**********DEVON'S LOGIN**********\n\n");

    close (0);
    close (1);
    close (2);

    in = open(argv[1], O_RDONLY);             //open argv[1] 3 times as in(0), out(1), err(2).);
    out = open(argv[1], O_WRONLY);
    err = open(argv[1], 2);

    fixtty(argv[1]);                             //set tty name string in proc.

    fd = open("/etc/passwd", 0);             //open passwords file for reading.

    if (fd < 0) {
        printf("Error opening file.\n");
        return 0;
    }

    //get username from the user.
    printf("username: ");
    gets(userName);                                            //gets() to show username while its typed.
    userName[strlen(userName)] = 0;

    //get password from the user.
    printf("password: ");
    gets(password);                                        //getline() to hide password while its typed.
    password[strlen(password)] = 0;

    /*printf("\nThe entered username is: %s\n", userName);
    printf("the entered password is: %s\n", password);*/

    n = read(fd, buf, 1024);

    readLines[0] = strtok(buf, "\n");

    while (readLines[i] = strtok(0, "\n")) {
        //printf("readLines[i] = %s\n", readLines[i]);
        i++;
    }

    i = 0;

    /*while (readLines[i] != '\0') {
        printf("readLines[i] = %s\n", readLines[i]);
        i++;
    }*/

    i = 0;

    while (readLines[i] != '\0') {
        readName = strtok(readLines[i], ":");

        //printf("readName = %s\n", readName);
        
        if (!strcmp(readName, userName)) {              //usernames matchup. see if passwords match.
            readPass = strtok(0, ":");
            //printf("readPass = %s\n", readPass);
    
            if (!strcmp(readPass, password)) {          //username and password matchup. load in all needed stuff.
                prints("\nSUCCESS: User logged in successfully.\n\n");
                userFound = 1;
                gid = atoi(strtok(0, ":"));
                uid = atoi(strtok(0, ":"));
                fullName = strtok(0, ":");
                homedir = strtok(0, ":");
                program = strtok(0, ":");
    
                /*printf("gid = %d\n", gid);
                printf("uid = %d\n", uid);
                printf("fullname = %s\n", fullName);
                printf("homedir = %s\n", homedir);
                printf("program = %s\n", program);*/

                //change to home directory read from the passwords file.
                printf("changing home directory to '%s'\n", homedir);
                chdir(homedir);

                close (fd);
                break;
            }
        }

        i++;
    }

    if (!userFound) {
        close(fd);             //Close the password file before exec the user program.
        prints("\nERROR: Specified user not found.\n\n");
        return;
    }

    //Execute program specified in passwords file.
    printf("Executing '%s' program.\n\n", program);
    exec(program);
}