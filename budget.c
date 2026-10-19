#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "utils.h"

#define MAX_DEPT 20
#define SIZE 30

/* one department = the same position in every array */
char deptName[MAX_DEPT][SIZE];
double allocated[MAX_DEPT];
double spent[MAX_DEPT];
int deptCount = 0;

void budgetMenu(void)
{
    int choice = -1;

    while (choice != 0)
    {
        printf("\n---- BUDGET MANAGEMENT ----\n");
        printf("1. Add department budget\n");
        printf("2. Enter expenditure\n");
        printf("3. Display budgets\n");
        printf("4. Show departments over budget\n");
        printf("0. Back to main menu\n");
        choice = getInt("Enter your choice: ", 0, 4);

        switch (choice)
        {
            case 1:
                addBudget();
                break;
            case 2:
                addExpenditure();
                break;
            case 3:
                displayBudgets();
                break;
            case 4:
                showOverBudget();
                break;
        }
    }
}

/* returns the position of the department, or -1 if it is not found */
int findDepartment(const char *name)
{
    int i;

    for (i = 0; i < deptCount; i++)
    {
        if (strcmp(deptName[i], name) == 0)
        {
            return i;
        }
    }
    return -1;
}

double calculateRemaining(int i)
{
    return allocated[i] - spent[i];
}

const char *budgetStatus(int i)
{
    if (spent[i] > allocated[i])
    {
        return "OVER BUDGET";
    }
    return "WITHIN BUDGET";
}

void addBudget(void)
{
    char name[SIZE];

    if (deptCount >= MAX_DEPT)
    {
        printf("The department list is full.\n");
        return;
    }

    getString("Department name: ", name, SIZE);

    if (findDepartment(name) != -1)
    {
        printf("%s already has a budget.\n", name);
        return;
    }

    strcpy(deptName[deptCount], name);
    allocated[deptCount] = getDouble("Allocated budget (N$): ", 0);
    spent[deptCount] = 0;

    deptCount++;
    printf("Budget added.\n");
}

void addExpenditure(void)
{
    char name[SIZE];
    int i;
    double amount;

    if (deptCount == 0)
    {
        printf("\nNo department budgets yet.\n");
        return;
    }

    getString("Department name: ", name, SIZE);
    i = findDepartment(name);

    if (i == -1)
    {
        printf("There is no department called %s.\n", name);
        return;
    }

    amount = getDouble("Expenditure to add (N$): ", 0);
    spent[i] = spent[i] + amount;

    printf("Total spent by %s is now N$%.2f.\n", deptName[i], spent[i]);
    if (spent[i] > allocated[i])
    {
        printf("Warning: %s is over its budget.\n", deptName[i]);
    }
}

void displayBudgets(void)
{
    int i;

    if (deptCount == 0)
    {
        printf("\nNo department budgets yet.\n");
        return;
    }

    for (i = 0; i < deptCount; i++)
    {
        printf("\nDepartment:       %s\n", deptName[i]);
        printf("Allocated Budget: N$%.2f\n", allocated[i]);
        printf("Expenditure:      N$%.2f\n", spent[i]);
        printf("Remaining Budget: N$%.2f\n", calculateRemaining(i));
        printf("Status:           %s\n", budgetStatus(i));
    }
}

void showOverBudget(void)
{
    int i;
    int found = 0;

    printf("\nDepartments over budget:\n");
    for (i = 0; i < deptCount; i++)
    {
        if (spent[i] > allocated[i])
        {
            printf("- %s (over by N$%.2f)\n", deptName[i], spent[i] - allocated[i]);
            found++;
        }
    }

    if (found == 0)
    {
        printf("None. All departments are within budget.\n");
    }
}
