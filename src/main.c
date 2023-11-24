#include "header.h"

void mainMenu(struct User u) {
  int option;
  system("clear");
  printf("\n\n\t\t======= ATM =======\n\n");
  printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
  printf("\n\t\t[1]- Create a new account\n");
  printf("\n\t\t[2]- Update account information\n");
  printf("\n\t\t[3]- Check accounts\n");
  printf("\n\t\t[4]- Check list of owned account\n");
  printf("\n\t\t[5]- Make Transaction\n");
  printf("\n\t\t[6]- Remove existing account\n");
  printf("\n\t\t[7]- Transfer ownership\n");
  printf("\n\t\t[8]- Exit\n");
  scanf("%d", &option);

  switch (option) {
  case 1:
    // createNewAcc(u);
    break;
  case 2:
    // student TODO : add your **Update account information** function
    // here
    break;
  case 3:
    // student TODO : add your **Check the details of existing accounts**
    // function here
    break;
  case 4:
    // checkAllAccounts(u);
    break;
  case 5:
    // student TODO : add your **Make transaction** function
    // here
    break;
  case 6:
    // student TODO : add your **Remove existing account** function
    // here
    break;
  case 7:
    // student TODO : add your **Transfer owner** function
    // here
    break;
  case 8:
    exit(1);
    break;
  default:
    printf("Invalid operation!\n");
  }
};

void initMenu(struct User *u) {
  char option;

initMenu:
  system("clear");
  printf("\n\n\t\t======= ATM =======\n\n");
  printf("\n\t\t[1] - Login\n");
  printf("\n\t\t[2] - Register\n");
  printf("\n\t\t[3] - Exit\n");

  scanf(" %s", &option);
  switch (option) {
  case '1':
    printf("You're being redirected to the login menu\n");
    if (loginMenu(u)) {
      mainMenu(*u);
    } else {
      printf("Error while trying to login\n");
      goto initMenu;
    }
    break;
  case '2':
    registerMenu();
    break;
    // goto initMenu;
  default:
    printf("Not a valid operation, please try again\n");
    goto initMenu;
  }
}

int main() {
  struct User u;

  initMenu(&u);
  return 0;
}
