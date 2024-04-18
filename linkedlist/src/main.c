#include "Structs.h"

Node *insert_node_beggining(Node *list, BankAccount bankAccount)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = bankAccount;
    newNode->next = list;

    return newNode;
}

Node *insert_node_end(Node *list, BankAccount bankAccount)
{
    Node *tempList = list;
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = bankAccount;
    newNode->next = NULL;

    if (list == NULL)
    {
        list = newNode;
    }
    else
    {
        while (tempList->next)
        {
            tempList = tempList->next;
        }

        tempList->next = newNode;
    }
    return list;
}

DoubleList simple_to_double(Node *list)
{
    DoubleList doubleList;
    doubleList.head = NULL;
    doubleList.tail = NULL;

    Node *tempList = list;

    while (tempList)
    {
        NodeD *newNode = (NodeD *)malloc(sizeof(NodeD));
        newNode->pData = &tempList->data;
        newNode->next = NULL;

        if (doubleList.head == NULL)
        {
            doubleList.head = newNode;
            doubleList.tail = newNode;
            newNode->prev = NULL;
        }
        else
        {
            doubleList.tail->next = newNode;
            newNode->prev = doubleList.tail;
            doubleList.tail = newNode;
        }

        tempList = tempList->next;
    }

    return doubleList;
}

void print_list(Node *list)
{
    printf("The list after creation:\n");

    Node *tempList = list;

    while (tempList)
    {
        printf("%s %s\n", tempList->data.owner_name, tempList->data.iban);

        tempList = tempList->next;
    }
}

int main()
{
    FILE *file = fopen("Accounts.txt", "r");
    char buffer[256];

    Node *head = NULL;

    while (fgets(buffer, sizeof(buffer), file))
    {
        BankAccount tBankAccount;
        strncpy(tBankAccount.iban, buffer, strlen(buffer) - 1);
        tBankAccount.iban[strlen(buffer) - 1] = 0;

        fgets(buffer, sizeof(buffer), file);
        tBankAccount.owner_name = (char *)malloc(strlen(buffer));
        strncpy(tBankAccount.owner_name, buffer, strlen(buffer) - 1);
        tBankAccount.owner_name[strlen(buffer) - 1] = 0;

        fgets(buffer, sizeof(buffer), file);
        tBankAccount.balance = atof(buffer);

        fgets(buffer, sizeof(buffer), file);
        tBankAccount.currency = (char *)malloc(strlen(buffer));
        strncpy(tBankAccount.currency, buffer, strlen(buffer) - 1);
        tBankAccount.currency[strlen(buffer) - 1] = 0;

        head = insert_node_end(head, tBankAccount);
    }

    print_list(head);

    DoubleList doubleList = simple_to_double(head);

    NodeD *tempList = doubleList.head;

    printf("\nThe double list after creation (start - to - end):\n");

    while (tempList)
    {
        printf("%s %s\n", tempList->pData->owner_name, tempList->pData->iban);

        tempList = tempList->next;
    }

    // print the double list from end to start
    tempList = doubleList.tail;

    printf("\nThe double list after creation (end - to - start):\n");

    while (tempList)
    {
        printf("%s %s\n", tempList->pData->owner_name, tempList->pData->iban);

        tempList = tempList->prev;
    }
}