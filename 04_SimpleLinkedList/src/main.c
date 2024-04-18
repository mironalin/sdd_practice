#include "Structs.h"

void deallocate_list(Node *list)
{
    Node *temp = list;
    while (list)
    {
        temp = list;
        list = list->next;
        free(temp->data.owner_name);
        free(temp->data.currency);
        free(temp);
    }

    list = NULL;

    printf("\nThe list after deallocation:\n");

    while (list)
    {
        printf("%s %s\n", list->data.owner_name, list->data.iban);

        list = list->next;
    }
}

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
    printf("\nThe list after creation:\n");

    Node *tempList = list;

    while (tempList)
    {
        printf("%s %s\n", tempList->data.owner_name, tempList->data.iban);

        tempList = tempList->next;
    }
}

// function to swap a node which contains a given IBAN with the first node in a simple linked list
Node *swap_first_node(Node *list, char *iban)
{
    Node *tempList = list;

    while (tempList)
    {
        if (strcmp(tempList->data.iban, iban) == 0)
        {
            BankAccount tempBankAccount = tempList->data;
            tempList->data = list->data;
            list->data = tempBankAccount;

            return list;
        }

        tempList = tempList->next;
    }

    return list;
}

// function to swap 2 nodes with given ibans in a simple linked list
Node *swap_nodes(Node *list, char *iban1, char *iban2)
{
    Node *tempList = list;
    Node *node1 = NULL;
    Node *node2 = NULL;

    while (tempList)
    {
        if (strcmp(tempList->data.iban, iban1) == 0)
        {
            node1 = tempList;
        }

        if (strcmp(tempList->data.iban, iban2) == 0)
        {
            node2 = tempList;
        }

        tempList = tempList->next;
    }

    if (node1 && node2)
    {
        BankAccount tempBankAccount = node1->data;
        node1->data = node2->data;
        node2->data = tempBankAccount;
    }

    return list;
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

    head = swap_first_node(head, "RO98BTRL1234567899900321");
    print_list(head);

    head = swap_nodes(head, "RO04BRDE0000000000999000", "RO04BRDE1234000000999000");
    print_list(head);

    deallocate_list(head);

    fclose(file);
    return 0;
}