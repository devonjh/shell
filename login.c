#include "ucode.c"

char *passwordsFile[8];

int main(int argc, char *argv[]) {
    char userName[64] = "";
    char password[64] = "";
    //char *userName = "";
    //char *password = "";

    char dummy;

    printf("login.c file\n");

    //get username from the user.
    printf("username: ");
    getline(userName);                                             //gets() to show username while its typed.
    userName[strlen(userName)] = 0;

    //get password from the user.
    printf("\npassword: ");
    getline(password);                                          //getline() to hide password while its typed.
    password[strlen(password)] = 0;

    printf("\nThe entered username is: %s\n", userName);
    printf("the entered password is: %s\n", password);

    getc(dummy);

}