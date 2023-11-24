#include "header.h"
#include <stdio.h>
#include <string.h>

/* function: getAccountFromFile
 * ------------------------
const char *RECORDS = "./data/records.txt";
const char *USERS = "./data/users.txt";
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

bool passCorrect(FILE *file, char *pass) {
  char localPass[50];

  while (fscanf(file, "%*d %*s %49s", localPass) != EOF) {
    if (strcmp(localPass, pass) == 0) {
      return true;
    }
  }

  return false;
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
 *  Save the given user to file.
 */
void saveUserToFile(FILE *file, struct User u) {
  fprintf(file, "%d %s %s\n", u.id, u.name, u.password);
}
