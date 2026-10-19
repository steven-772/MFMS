#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employees.h"

void displayMenu(void);
int getMenuChoice(void);

void budgetMenu(void);
void supplierMenu(void);
void assetMenu(void);
void reportsMenu(void);

int main(void)
{
    int choice = 0;

    while (choice != 6)
    {
        displayMenu();
        choice = getMenuChoice();

        switch (choice)
        {
            case 1:
                employeeMenu();
                break;
            case 2:
                budgetMenu();
                break;
            case 3:
                supplierMenu();
                break;
            case 4:
                assetMenu();
                break;
            case 5:
                reportsMenu();
                break;
            case 6:
                printf("Goodbye.\n");
                break;
            default:
                printf("Invalid choice, please pick 1 to 6.\n");
        }
    }

    return 0;
}

void displayMenu(void)
{
    printf("\n========================================\n");
    printf("MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
}

/* reads a line and turns it into a number, returns 0 if it isn't a number */
int getMenuChoice(void)
{
    char line[50];
    int num;
    char leftover;

    printf("Enter your choice: ");
    if (fgets(line, sizeof(line), stdin) == NULL)
    {
        return 6;   /* input ended, just exit */
    }

    if (sscanf(line, "%d %c", &num, &leftover) != 1)
    {
        return 0;   /* not a clean number */
    }

    return num;
}

/* placeholders for now */
void budgetMenu(void)   { printf("\nBudget Management - not done yet\n"); }
void supplierMenu(void) { printf("\nSupplier Management - not done yet\n"); }
void assetMenu(void)    { printf("\nAsset Management - not done yet\n"); }
void reportsMenu(void)  { printf("\nReports - not done yet\n"); }
