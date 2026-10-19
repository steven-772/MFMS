#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "suppliers.h"
#include "utils.h"

#define MAX_SUP 50
#define SIZE 40

/* one supplier = the same position in every array */
int supId[MAX_SUP];
char supName[MAX_SUP][SIZE];
char supEmail[MAX_SUP][SIZE];
char supPhone[MAX_SUP][SIZE];
char supTown[MAX_SUP][SIZE];
int supCount = 0;

void supplierMenu(void)
{
    int choice = -1;

    while (choice != 0)
    {
        printf("\n---- SUPPLIER MANAGEMENT ----\n");
        printf("1. Add supplier\n");
        printf("2. Display suppliers\n");
        printf("3. Search supplier\n");
        printf("0. Back to main menu\n");
        choice = getInt("Enter your choice: ", 0, 3);

        switch (choice)
        {
            case 1:
                addSupplier();
                break;
            case 2:
                displaySuppliers();
                break;
            case 3:
                searchSupplier();
                break;
        }
    }
}

/* returns the position of the supplier, or -1 if the ID is not found */
int findSupplierById(int id)
{
    int i;

    for (i = 0; i < supCount; i++)
    {
        if (supId[i] == id)
        {
            return i;
        }
    }
    return -1;
}

/* an email needs an @ and a dot somewhere after the @ */
int isValidEmail(const char *email)
{
    const char *at = strchr(email, '@');

    if (at == NULL)
    {
        return 0;
    }
    if (at == email)
    {
        return 0;   /* nothing before the @ */
    }
    if (strchr(at, '.') == NULL)
    {
        return 0;
    }
    return 1;
}

/* a phone number must be 7 to 15 digits and nothing else */
int isValidPhone(const char *phone)
{
    int i;
    int len = strlen(phone);

    if (len < 7 || len > 15)
    {
        return 0;
    }

    for (i = 0; i < len; i++)
    {
        if (!isdigit((unsigned char)phone[i]))
        {
            return 0;
        }
    }
    return 1;
}

void addSupplier(void)
{
    int id;
    int n;

    if (supCount >= MAX_SUP)
    {
        printf("Supplier list is full.\n");
        return;
    }

    id = getInt("Supplier ID (1 to 99999): ", 1, 99999);

    if (findSupplierById(id) != -1)
    {
        printf("ID %d is already used.\n", id);
        return;
    }

    n = supCount;
    supId[n] = id;
    getString("Supplier name: ", supName[n], SIZE);

    /* keep asking until the email looks right */
    getString("Email: ", supEmail[n], SIZE);
    while (!isValidEmail(supEmail[n]))
    {
        printf("That is not a valid email (example: name@company.com).\n");
        getString("Email: ", supEmail[n], SIZE);
    }

    /* same for the phone number */
    getString("Telephone (digits only): ", supPhone[n], SIZE);
    while (!isValidPhone(supPhone[n]))
    {
        printf("Phone must be 7 to 15 digits, no spaces or symbols.\n");
        getString("Telephone (digits only): ", supPhone[n], SIZE);
    }

    getString("Town/Location: ", supTown[n], SIZE);

    supCount++;
    printf("Supplier added.\n");
}

void displaySuppliers(void)
{
    int i;

    if (supCount == 0)
    {
        printf("\nNo suppliers yet.\n");
        return;
    }

    printf("\n%-6s %-20s %-28s %-12s %-12s\n", "ID", "Name", "Email", "Phone", "Town");
    printf("-------------------------------------------------------------------------------------\n");

    for (i = 0; i < supCount; i++)
    {
        printf("%-6d %-20s %-28s %-12s %-12s\n",
               supId[i], supName[i], supEmail[i], supPhone[i], supTown[i]);
    }

    printf("\nTotal suppliers: %d\n", supCount);
}

/* prints all the details of one supplier */
void printSupplier(int i)
{
    printf("\nID:        %d\n", supId[i]);
    printf("Name:      %s\n", supName[i]);
    printf("Email:     %s\n", supEmail[i]);
    printf("Telephone: %s\n", supPhone[i]);
    printf("Town:      %s\n", supTown[i]);
}

void searchSupplier(void)
{
    int choice;
    int id;
    int i;
    int found;
    char text[SIZE];

    if (supCount == 0)
    {
        printf("\nNo suppliers yet.\n");
        return;
    }

    printf("\n1. Search by ID\n");
    printf("2. Search by name\n");
    printf("3. Search by town\n");
    choice = getInt("Enter your choice: ", 1, 3);

    if (choice == 1)
    {
        id = getInt("Enter supplier ID: ", 1, 99999);
        i = findSupplierById(id);

        if (i == -1)
        {
            printf("No supplier with ID %d.\n", id);
        }
        else
        {
            printSupplier(i);
        }
    }
    else if (choice == 2)
    {
        getString("Enter supplier name: ", text, SIZE);
        found = 0;

        for (i = 0; i < supCount; i++)
        {
            if (strcmp(supName[i], text) == 0)
            {
                printSupplier(i);
                found++;
            }
        }
        if (found == 0)
        {
            printf("No supplier named %s.\n", text);
        }
    }
    else
    {
        getString("Enter town: ", text, SIZE);
        found = 0;

        for (i = 0; i < supCount; i++)
        {
            if (strcmp(supTown[i], text) == 0)
            {
                printSupplier(i);
                found++;
            }
        }
        if (found == 0)
        {
            printf("No suppliers in %s.\n", text);
        }
    }
}
