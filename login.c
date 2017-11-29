#include "ucode.c"

int in, out, err;
char userName[128];
char password[128];

int main(int argc, char *argv[]) {
    char *lastToken;
    char *tempString;
    int fd;
    char *testString = "This is a test";
    int test;
    char dummy;

    //close file descriptors inehrited from INIT.


    
    in = open(argv[1], O_RDONLY);             //open argv[1] 3 times as in(0), out(1), err(2).);
    out = open(argv[1], O_WRONLY);
    err = open(argv[1], 2);

    fixtty(argv[1]);                             //set tty name string in proc.

    fd = open("/etc/passwd", O_RDONLY);             //open passwords file for reading.

    if (fd < 0) {
        printf("Error opening file.\n");
        return 0;
    }

    printf("login.c file\n");

    //get username from the user.
    printf("username: ");
    gets(userName);                                            //gets() to show username while its typed.
    userName[strlen(userName)] = 0;

    //get password from the user.
    printf("\npassword: ");
    gets(password);                                        //getline() to hide password while its typed.
    password[strlen(password)] = 0;

    printf("\nThe entered username is: %s\n", userName);
    printf("the entered password is: %s\n", password);

    test = strcmp(userName, "devonjh");

    printf("test = %d\n", test);
}