#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct BankAccount
{
    char iban[25];
    char *owner_name;
    double balance;
    char *currency;
};

typedef struct BankAccount BankAccount;
