#include "Structs.h"

#define HASH_TABLE_SIZE 100

Node *insert_beggining(Node *list, BankAccount ba)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = ba;
    newNode->next = list;

    return newNode;
}

unsigned char hash_function(char *key, unsigned char ht_size)
{
    unsigned int sum = 0;

    for (char i = (char)(strlen(key) - 1); i > (char)(strlen(key) - 5) && i >= 0; i--)
    {
        sum += key[i];
    }

    return (unsigned char)(sum % ht_size);
}

void insert_ba_hash_table(Node **HT, unsigned char ht_size, BankAccount ba_data)
{
    //* call function to get to the hash value
    unsigned char offset = hash_function(ba_data.owner_name, ht_size);

    printf("\nThe key %s goes into list %d.", ba_data.owner_name, (int)offset);

    //* insert into has table the ba_data on offset computed one line above
    HT[offset] = insert_beggining(HT[offset], ba_data);
}

Node *search_first_ba(Node **HT, unsigned char ht_size, char *name)
{
    //* call function to compute hash value
    unsigned char offset = hash_function(name, ht_size);

    //* once the offset is computed, the node must be searched item by item in the simple list
    Node *temp = HT[offset];

    while (temp)
    {
        if (strcmp(temp->data.owner_name, name) == 0)
        {
            return temp; //* only the first identified node is returned
        }

        temp = temp->next;
    }

    return temp; //! NULL
}

// function to search for all bank account which meets the key; the founded bank accounts will be stored
// into a separate simple list; the separate simple list does not share heap memory locations
// with the simple lists built in hash table with chaining
// the function returns the head of the separate simple list
Node *search_all_ba(Node **HT, unsigned char ht_size, char *name)
{
    Node *head = NULL;

    for (unsigned char i = 0; i < ht_size; i++)
    {
        Node *temp = HT[i];

        while (temp)
        {
            if (strcmp(temp->data.owner_name, name) == 0)
            {
                head = insert_beggining(head, temp->data);
            }

            temp = temp->next;
        }
    }

    return head;
}

// function to deallocate the memory of the hash table
void free_hash_table(Node **HT, unsigned char ht_size)
{
    for (unsigned char i = 0; i < ht_size; i++)
    {
        Node *temp = HT[i];

        while (temp)
        {
            Node *temp2 = temp;
            temp = temp->next;
            free(temp2->data.owner_name);
            free(temp2->data.currency);
            free(temp2);
        }
    }

    free(HT);
}

// function to deallocate the memory of a simple list
void free_list(Node *list)
{
    while (list)
    {
        Node *temp = list;
        list = list->next;
        free(temp->data.owner_name);
        free(temp->data.currency);
        free(temp);
    }

    free(list);
}

void print_hash_table(Node **HT, unsigned char ht_size)
{
    printf("\nHash Table:\n");
    for (unsigned char i = 0; i < ht_size; i++)
    {
        Node *temp = HT[i];

        while (temp)
        {
            printf("%s %s\n", temp->data.owner_name, temp->data.iban);
            temp = temp->next;
        }
    }
}

int main(int argc, char const *argv[])
{
    FILE *file = fopen("Accounts.txt", "r");
    char buffer[256];

    Node **HTable = (Node **)malloc(HASH_TABLE_SIZE * sizeof(Node *)); //! allocation of the support array for the hash table

    for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
    {
        HTable[i] = NULL; //* HTable[i] is the starting address of the simple linked list
    }

    while (fgets(buffer, sizeof(buffer), file)) //! buffer must contain iban
    {
        BankAccount tBankAccount;
        strncpy(tBankAccount.iban, buffer, strlen(buffer) - 1);
        tBankAccount.iban[strlen(buffer) - 1] = 0;

        fgets(buffer, sizeof(buffer), file); //! buffer must contain owner's name
        tBankAccount.owner_name = (char *)malloc(strlen(buffer));
        strncpy(tBankAccount.owner_name, buffer, strlen(buffer) - 1);
        tBankAccount.owner_name[strlen(buffer) - 1] = 0;

        fgets(buffer, sizeof(buffer), file); //! buffer must contain balance data (as string)
        tBankAccount.balance = atof(buffer);

        fgets(buffer, sizeof(buffer), file); //! buffer must contain currency
        tBankAccount.currency = (char *)malloc(strlen(buffer));
        strncpy(tBankAccount.currency, buffer, strlen(buffer) - 1);
        tBankAccount.currency[strlen(buffer) - 1] = 0;

        //! insert tBankAccount data into the hash table with chaining
        insert_ba_hash_table(HTable, HASH_TABLE_SIZE, tBankAccount);
    }

    Node *temp = search_first_ba(HTable, HASH_TABLE_SIZE, "Popescu Mircea");

    if (temp)
    {
        printf("\n\nBank Account has been found: %s %s\n", temp->data.owner_name, temp->data.iban);
    }

    Node *temp2 = search_all_ba(HTable, HASH_TABLE_SIZE, "Popescu Mircea");

    printf("\nBank Accounts with the same key:\n");
    while (temp2)
    {
        printf("%s %s\n", temp2->data.owner_name, temp2->data.iban);
        temp2 = temp2->next;
    }

    print_hash_table(HTable, HASH_TABLE_SIZE);

    free_hash_table(HTable, HASH_TABLE_SIZE);
    free_list(temp2);

    fclose(file);
    return 0;
}