#include "Structs.h"

int main()
{
    FILE *file = fopen("Accounts.txt", "r");
    char buffer[256];
    unsigned char line_counter = 0;

    while (fgets(buffer, sizeof(buffer), file))
    {
        line_counter += 1;
    }

    unsigned char bankAccount_array_size = line_counter / 4; //! 4 is the number of fields in the struct BankAccount

    BankAccount *bankAccount_array = (BankAccount *)malloc(bankAccount_array_size * sizeof(BankAccount));

    fseek(file, 0, SEEK_SET);

    unsigned char item_offset = 0;

    while (fgets(buffer, sizeof(buffer), file)) //* buffer must contain IBAN
    {
        strncpy(bankAccount_array[item_offset].iban, buffer, strlen(buffer) - 1);
        bankAccount_array[item_offset].iban[strlen(buffer) - 1] = 0;

        fgets(buffer, sizeof(buffer), file); //* buffer must contain the name
        bankAccount_array[item_offset].owner_name = (char *)malloc(strlen(buffer));
        strncpy(bankAccount_array[item_offset].owner_name, buffer, strlen(buffer) - 1);
        bankAccount_array[item_offset].owner_name[strlen(buffer) - 1] = 0;

        fgets(buffer, sizeof(buffer), file); //* buffer must contain balance data (as a string)
        bankAccount_array[item_offset].balance = atof(buffer);

        fgets(buffer, sizeof(buffer), file); //* buffer must contain the currency
        bankAccount_array[item_offset].currency = (char *)malloc(strlen(buffer));
        strncpy(bankAccount_array[item_offset].currency, buffer, strlen(buffer) - 1);
        bankAccount_array[item_offset].currency[strlen(buffer) - 1] = 0;

        item_offset += 1;
    }

    printf("List of Bank Accounts:\n");
    for (unsigned char i = 0; i < bankAccount_array_size; i++)
    {
        printf("%s %s\n", bankAccount_array[i].iban, bankAccount_array[i].owner_name);
    }

    //! deallocate the bank account array
    for (unsigned char i = 0; i < bankAccount_array_size; i++)
    {
        free(bankAccount_array[i].owner_name);
        free(bankAccount_array[i].currency);
    }
    free(bankAccount_array);
    bankAccount_array = NULL;

    printf("\nList of bank accounts after deallocation:\n");
    for (unsigned char i = 0; i < bankAccount_array_size; i++)
    {
        if (bankAccount_array != NULL)
        {
            printf("%s %s\n", bankAccount_array[i].iban, bankAccount_array[i].owner_name);
        }
    }

    fclose(file);
    return 0;
}
