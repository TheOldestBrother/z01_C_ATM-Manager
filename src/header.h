#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct User {
  int id;
  char name[50];
  char password[50];
};

struct Date {
  int month, day, year;
};

// all fields for each record of an account
struct Record {
  int id;
  int userId;
  char name[100];
  char country[100];
  int phone;
  char accountType[10];
  int accountNbr;
  double amount;
  struct Date deposit;
  struct Date withdraw;
};

// #define RECORDS char "./data/records.txt";
// #define USERS char "./data/users.txt";

// File access Functions
// int getUserFromFile(struct User *u, char *name);
bool userExist(FILE *file, char *name);
bool passCorrect(FILE *file, char *pass);
void getUserFromFile(FILE *file, struct User *u, char *name);
void saveUserToFile(FILE *file, struct User u);
void createNewAcc(struct User u);
void checkAllAccounts(struct User u);
int getNewID(FILE *file);

// Authentication Funcctions
// bool loginMenu(char a[50], char pass[50]);
bool loginMenu(struct User *u);
bool registerMenu(void);

// Account Functions
void mainMenu(struct User u);
