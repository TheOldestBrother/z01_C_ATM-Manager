#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

const char *USERS = "./data/users.txt";

/* function: promptPassword
 * ------------------------
 *  Used to prompt password to user, with a specific message.
 * */
void promptPassword(char pass[50], char *text) {
  struct termios oflags, nflags;

  // disabling echo
  tcgetattr(fileno(stdin), &oflags);
  nflags = oflags;
  nflags.c_lflag &= ~ECHO;
  nflags.c_lflag |= ECHONL;

  if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
    perror("tcsetattr");
    return exit(1);
  }
  printf("\n\n\n\n\n\t\t  %s: \n\t\t\t", text);
  scanf("%50s", pass);

  // restore terminal
  if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
    perror("tcsetattr");
    return exit(1);
  }
}

/* function: registerMenu
 * ------------------------
 *  Prompts the user with all the questions to create a new User,
 *  if everything is okay, it saves it to a specific file.
 * */
bool registerMenu(void) {
  struct User u = {0};

  char username[50];
  char password[50];
  char checkPassword[50];
  char input;
  FILE *file = fopen(USERS, "r+");

  system("clear");
usernamePrompt:
  printf("\n\n\t\t======== ATM ========\n\n");
  printf("\n\t\t\tRegister\n\n");
  printf("\t\tPlease provide a Username: \n\t\t\t");
  scanf("%50s", u.name);

  if (strcmp(u.name, "") == 0) {
    system("clear");
    printf("\n\n The size of the username is incorrect, it must be greater "
           "than 0 and smaller than 50 characters");
    sleep(2);
    goto usernamePrompt;
  } else if ((userExist(file, u.name))) {
    system("clear");
    printf("\nThe user already exists, please provide another Username.\n\n");
    goto usernamePrompt;
  }

passwordPrompt:
  printf("%s\n", u.name);
  promptPassword(u.password, "Choose a new password");
  promptPassword(checkPassword, "Verifie your password");
  printf("--");

  if (strcmp(u.password, checkPassword) != 0 || strcmp(u.password, "") == 0) {
    printf("\nThe password check mismatched, press 1 to try again, 2 to "
           "restart Registering, 3 to go back to main menu or "
           "any other key to exit\n");
    scanf(" %s", &input);

    switch (input) {
    case '1':
      goto passwordPrompt;
    case '2':
      goto usernamePrompt;
    case '3':
      return false;
    default:
      exit(1);
    }
  } else {
    u.id = getNewID(file);
    saveUserToFile(file, u);
  }

  fclose(file);
  return true;
}

/* function: loginMenu
 * ------------------------
 *  A menu that offers all sorts of options to create/modify accounts from
 * users.
 * */
bool loginMenu(struct User *u) {
  struct termios oflags, nflags;
  FILE *file = fopen(USERS, "r+");
  bool res = false;

  system("clear");
  printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
  scanf("%s", u->name);

  promptPassword(u->password, "Enter the password to login");
  // printf("userExist= %s\n", userExist(file, u->name) ? "true" : "false");
  // printf("passCorrect= %s\n",
  // passCorrect(file, u->password) ? "true" : "false");
  if (userExist(file, u->name) && passCorrect(file, u->password)) {
    res = true;
  }

  fclose(file);
  return res;
};
