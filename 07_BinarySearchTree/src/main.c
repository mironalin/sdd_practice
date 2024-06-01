#include "Structs.h"

NodeBST *insert_ba_binary_search_tree(NodeBST *tree, BankAccount ba, char *insert_flag)
{
    if (tree != NULL)
    {
        if (strcmp(tree->data.iban, ba.iban) == 0)
        {
            *insert_flag = 0;
        }
        else
        {
            if (strcmp(tree->data.iban, ba.iban) > 0)
            {
                tree->left = insert_ba_binary_search_tree(tree->left, ba, insert_flag);
            }
            else
            {
                tree->right = insert_ba_binary_search_tree(tree->right, ba, insert_flag);
            }
        }
    }
    else
    {
        NodeBST *new_node = (NodeBST *)malloc(sizeof(NodeBST));
        new_node->data = ba;
        new_node->left = new_node->right = NULL;

        *insert_flag = 1;
        tree = new_node;
    }

    return tree;
}

int main()
{
    FILE *f = fopen("Accounts.txt", "r");
    char buffer[256];

    NodeBST *root = NULL;

    while (fgets(buffer, sizeof(buffer), f))
    {
        BankAccount tBankAccount;
        strncpy(tBankAccount.iban, buffer, strlen(buffer) - 1);
        tBankAccount.iban[strlen(buffer) - 1] = 0;

        fgets(buffer, sizeof(buffer), f);
        tBankAccount.owner_name = (char *)malloc(strlen(buffer));
        strncpy(tBankAccount.owner_name, buffer, strlen(buffer) - 1);
        tBankAccount.owner_name[strlen(buffer) - 1] = 0;

        fgets(buffer, sizeof(buffer), f);
        tBankAccount.balance = atof(buffer);

        fgets(buffer, sizeof(buffer), f);
        tBankAccount.currency = (char *)malloc(strlen(buffer));
        strncpy(tBankAccount.currency, buffer, strlen(buffer) - 1);
        tBankAccount.currency[strlen(buffer) - 1] = 0;

        char flag;
        root = insert_ba_binary_search_tree(root, tBankAccount, &flag);
        if (flag == 1)
        {
            printf("Succesful insertion: %s %s \n", tBankAccount.iban, tBankAccount.owner_name);
        }
        else
        {
            printf("Insertion has failed!\n");
            free(tBankAccount.currency);
            free(tBankAccount.owner_name);
        }
    }
}
