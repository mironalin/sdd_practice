#include "Structs.h"

Node *insertAtBeggining(Node *list, BankAccount bankAccount)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = bankAccount;
    newNode->next = list;
    list = newNode;

    return list;
}

Node *insertAtEnd(Node *list, BankAccount bankAccount)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    Node *current = list;

    newNode->data = bankAccount;
    newNode->next = NULL;

    if (list == NULL)
    {
        list = newNode;
    }
    else
    {
        while (current->next)
        {
            current = current->next;
        }
        current->next = newNode;
    }

    return list;
}

// swap nodes without swapping data
void swap_general(Node *list, char *iban1, char *iban2)
{
    Node *current = list;
    Node *prev1 = NULL, *prev2 = NULL;
    Node *node1 = NULL, *node2 = NULL;

    while (current)
    {
        if (strcmp(current->data.iban, iban1) == 0)
        {
            node1 = current;
            break;
        }
        prev1 = current;
        current = current->next;
    }

    current = list;
    while (current)
    {
        if (strcmp(current->data.iban, iban2) == 0)
        {
            node2 = current;
            break;
        }
        prev2 = current;
        current = current->next;
    }

    if (node1 == NULL || node2 == NULL)
    {
        printf("One or both of the IBANs are not found in the list\n");
        return;
    }

    if (prev1 != NULL)
    {
        prev1->next = node2;
    }
    else
    {
        list = node2;
    }

    if (prev2 != NULL)
    {
        prev2->next = node1;
    }
    else
    {
        list = node1;
    }

    Node *temp = node1->next;
    node1->next = node2->next;
    node2->next = temp;
}

// Function to print the list
void printList(Node *list)
{
    Node *current = list;

    printf("The elements of the list:\n");
    while (current)
    {
        printf("%s %s\n", current->data.iban, current->data.owner_name);
        current = current->next;
    }
}

int main()
{
    FILE *file = fopen("Accounts.txt", "r");
    char buffer[256];

    Node *head = NULL;

    while (fgets(buffer, sizeof(buffer), file)) // buffer must contain iban
    {
        BankAccount tBankAccount;
        strncpy(tBankAccount.iban, buffer, strlen(buffer) - 1);
        tBankAccount.iban[strlen(buffer) - 1] = 0;

        fgets(buffer, sizeof(buffer), file); // buffer must contain owner's name
        tBankAccount.owner_name = (char *)malloc(strlen(buffer));
        strncpy(tBankAccount.owner_name, buffer, strlen(buffer) - 1);
        tBankAccount.owner_name[strlen(buffer) - 1] = 0;

        fgets(buffer, sizeof(buffer), file); // buffer must contain balance data (as string)
        tBankAccount.balance = atof(buffer);

        fgets(buffer, sizeof(buffer), file); // buffer must contain currency
        tBankAccount.currency = (char *)malloc(strlen(buffer));
        strncpy(tBankAccount.currency, buffer, strlen(buffer) - 1);
        tBankAccount.currency[strlen(buffer) - 1] = 0;

        // insert tBankAccount data into the simple list handled by head
        // new node addded to the begining of the simple list
        head = insertAtEnd(head, tBankAccount);
    }

    printList(head);
    // swap_general(head, "RO04RNCB1234567890999000", "RO04BRDE1234000000999000");
    printf("\n");
    printList(head);
}