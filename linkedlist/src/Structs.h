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

struct Node
{
    struct BankAccount data;
    struct Node *next;
};

typedef struct Node Node;

struct NodeD
{
    struct BankAccount *pData;
    struct NodeD *prev, *next;
};

typedef struct NodeD NodeD;

struct DoubleList
{
    struct NodeD *head, *tail;
};

typedef struct DoubleList DoubleList;
