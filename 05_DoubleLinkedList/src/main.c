#include "Structs.h"

DoubleList insert_node_beggining(DoubleList list, BankAccount *bankAccountData)
{
    NodeD *newNode = (NodeD *)malloc(sizeof(NodeD));

    newNode->pdata = bankAccountData;
    newNode->next = list.head;
    newNode->prev = NULL;

    if (list.head != NULL)
    {
        //* There is at least one node in the list
        list.head->prev = newNode;
        list.head = newNode;
    }
    else
    {
        //* The list is empty
        list.head = list.tail = newNode;
    }

    return list;
}

DoubleList insert_node_end(DoubleList list, BankAccount *bankAccountData)
{
    NodeD *newNode = (NodeD *)malloc(sizeof(NodeD));

    newNode->pdata = bankAccountData;
    newNode->prev = list.tail;
    newNode->next = NULL;

    if (list.tail != NULL)
    {
        //* There is at least one node in the list
        list.tail->next = newNode;
        list.tail = newNode;
    }
    else
    {
        list.head = list.tail = newNode;
    }

    return list;
}

void print_double_linked_list(DoubleList list)
{
    printf("The double list after creation:\n");
    NodeD *temp = list.head;
    while (temp)
    {
        printf("%s %s\n", temp->pdata->iban, temp->pdata->owner_name);
        temp = temp->next;
    }
}

void double_linked_list_to_circular_list(DoubleList list)
{
    list.head->prev = list.tail;
    list.tail->next = list.head;
}

void deallocate_double_linked_list(NodeD **head, NodeD **tail)
{
    if (*tail == NULL)
    {
        return;
    }

    NodeD *temp = *tail;
    while (temp->next)
    {
        temp = temp->next;
        free(temp->prev->pdata->owner_name);
        free(temp->prev->pdata->currency);
        free(temp->prev->pdata);
        free(temp->prev);
    }

    free(temp);
    *head = *tail = NULL;
}

int main()
{
    FILE *file = fopen("Accounts.txt", "r");
    char buffer[256];

    DoubleList dList;
    dList.head = dList.tail = NULL;

    while (fgets(buffer, sizeof(buffer), file)) //! buffer must contain IBAN
    {
        BankAccount tempBankAccount, *permanentBankAccount;
        strncpy(tempBankAccount.iban, buffer, strlen(buffer) - 1);
        tempBankAccount.iban[strlen(buffer) - 1] = 0;

        fgets(buffer, sizeof(buffer), file); //! buffer must contain owner's name
        tempBankAccount.owner_name = (char *)malloc(strlen(buffer));
        strncpy(tempBankAccount.owner_name, buffer, strlen(buffer) - 1);
        tempBankAccount.owner_name[strlen(buffer) - 1] = 0;

        fgets(buffer, sizeof(buffer), file); //! buffer must contain balance data as a string
        tempBankAccount.balance = atof(buffer);

        fgets(buffer, sizeof(buffer), file); //! buffer must contain the currency
        tempBankAccount.currency = (char *)malloc(strlen(buffer));
        strncpy(tempBankAccount.currency, buffer, strlen(buffer) - 1);
        tempBankAccount.currency[strlen(buffer) - 1] = 0;

        //* Allocate heap memory for BankAccount data
        permanentBankAccount = (BankAccount *)malloc(sizeof(BankAccount));
        *permanentBankAccount = tempBankAccount;

        //* Pass pointer to Bank Account to add a new node in the double list
        dList = insert_node_end(dList, permanentBankAccount);
    }
    print_double_linked_list(dList);
    deallocate_double_linked_list(&dList.head, &dList.tail);
    print_double_linked_list(dList);
    fclose(file);
    return 0;
}