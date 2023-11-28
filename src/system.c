#include "header.h"
#include <stdio.h>
#include <string.h>

const char *RECORDS = "./data/records.txt";

/* function: getAccountFromFile
 * ------------------------
 *  Retrieves a scan from a file containing all the users.
 * */
int getAccountFromFile(FILE *ptr, char name[50], struct Record *r) {
  return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s", &r->id, &r->userId,
                name, &r->accountNbr, &r->deposit.month, &r->deposit.day,
                &r->deposit.year, r->country, &r->phone, &r->amount,
                r->accountType) != EOF;
}

/* function: saveAccountFromFile
 * ------------------------
 * Saves new created account to specified file.
 * */
void saveAccountToFile(FILE *ptr, struct User u, struct Record r) {
  fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n", r.id, u.id, u.name,
          r.accountNbr, r.deposit.month, r.deposit.day, r.deposit.year,
          r.country, r.phone, r.amount, r.accountType);
}

/* function: success
 * ------------------------
 * function for success to prompt the user for what to do next.
 * */
void success(struct User u) {
  int option;
  printf("\n✔ Success!\n\n");
invalid:
  printf("Enter 1 to go to the main menu and 0 to exit!\n");
  scanf("%d", &option);
  system("clear");
  if (option == 1) {
    mainMenu(u);
  } else if (option == 0) {
    exit(1);
  } else {
    printf("Insert a valid operation!\n");
    goto invalid;
  }
}

/* function: userExist
 * ------------------------
 *  If the given user exists in the file return true, else,
 *  return false.
 * */
bool userExist(FILE *file, char *name) {
  char localName[50];

  while (fscanf(file, "%*d %49s %*s", localName) != EOF) {
    if (strcmp(localName, name) == 0) {
      return true;
    }
  }
  return false;
}

/* function: passCorrect
 * ------------------------
 *  Verifies the password to see if it matches the password
 *  registered in the file.
 * */
bool passCorrect(FILE *file, char *pass) {
  char localPass[50];
  rewind(file);

  while (fscanf(file, "%*d %*s %49s\n", localPass) != EOF) {
    if (strcmp(localPass, pass) == 0) {
      return true;
    }
  }

  return false;
}

/* function: createNewAcc
 * ------------------------
 * Creates a new account for the loggedin user and adds then calls
 * the function to write it to the file.
 * */
void createNewAcc(struct User u) {
  struct Record r;
  struct Record cr;
  char userName[50];
  FILE *pf = fopen(RECORDS, "a+");

noAccount:
  system("clear");
  printf("\t\t\t===== New record =====\n");

  printf("\nEnter today's date(mm/dd/yyyy):");
  scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
  printf("\nEnter the account number:");
  scanf("%d", &r.accountNbr);

  while (getAccountFromFile(pf, userName, &cr)) {
    if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr) {
      printf("✖ This Account already exists for this user\n\n");
      goto noAccount;
    }
  }

  printf("\nEnter the country:");
  scanf("%s", r.country);
  printf("\nEnter the phone number:");
  scanf("%d", &r.phone);
  printf("\nEnter amount to deposit: $");
  scanf("%lf", &r.amount);
  printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> "
         "fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 "
         "years)\n\n\tEnter your choice:");
  scanf("%s", r.accountType);

  saveAccountToFile(pf, u, r);

  fclose(pf);
  success(u);
}

/* function: getNewID
 * ------------------------
 *  Finds last ID in the file and returns it +1;
 */
int getNewID(FILE *file) {
  rewind(file);
  int id = 0;

  while (fscanf(file, "%d %*s %*s", &id) != EOF) {
  }

  return id + 1;
}

/* function: saveUserToFile
 * ------------------------
 *  Save the given user to given file.
 */
void saveUserToFile(FILE *file, struct User u) {
  fprintf(file, "%d %s %s\n", u.id, u.name, u.password);
}

/* function: saveUserToFile
 * ------------------------
 *
 */
void checkAllAccounts(struct User u) {
  char userName[100];
  struct Record r;

  FILE *pf = fopen(RECORDS, "r");

  system("clear");
  printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
  while (getAccountFromFile(pf, userName, &r)) {
    if (strcmp(userName, u.name) == 0) {
      printf("_____________________\n");
      printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone "
             "number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
             r.accountNbr, r.deposit.day, r.deposit.month, r.deposit.year,
             r.country, r.phone, r.amount, r.accountType);
    }
  }
  fclose(pf);
  success(u);
}
