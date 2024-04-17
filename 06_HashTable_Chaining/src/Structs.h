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

struct NodeDP
{
    struct BankAccount *pData;
    struct NodeD *next, *prev;
};

typedef struct NodeD NodeD;

struct DoubleList
{
    NodeD *head, *tail;
};

typedef struct DoubleList DoubleList;