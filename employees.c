#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "utils.h"

#define MAX 100
#define SIZE 30

/* one employee = the same position in every array */
int empId[MAX];
char empName[MAX][SIZE];
char empDept[MAX][SIZE];
char empPosition[MAX][SIZE];
double basicSalary[MAX];
double housing[MAX];
double transport[MAX];
int count = 0;

void employeeMenu(void)
{
    int choice = -1;

    while (choice != 0)
    {
        printf("\n---- EMPLOYEE MANAGEMENT ----\n");
        printf("1. Add employee\n");
        printf("2. Display employees\n");
        printf("3. Search employee\n");
        printf("0. Back to main menu\n");
        choice = getInt("Enter your choice: ", 0, 3);

        switch (choice)
        {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                searchEmployee();
                break;
        }
    }
}

/* returns the position of the employee, or -1 if the ID is not found */
int findEmployeeById(int id)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (empId[i] == id)
        {
            return i;
        }
    }
    return -1;
}

void addEmployee(void)
{
    int id;

    if (count >= MAX)
    {
        printf("Employee list is full.\n");
        return;
    }

    id = getInt("Employee ID (1 to 99999): ", 1, 99999);

    if (findEmployeeById(id) != -1)
    {
        printf("ID %d is already used.\n", id);
        return;
    }

    empId[count] = id;
    getString("Name: ", empName[count], SIZE);
    getString("Department: ", empDept[count], SIZE);
    getString("Position: ", empPosition[count], SIZE);
    basicSalary[count] = getDouble("Basic salary (N$): ", 0);
    housing[count] = getDouble("Housing allowance (N$): ", 0);
    transport[count] = getDouble("Transport allowance (N$): ", 0);

    count++;
    printf("Employee added.\n");
}

void displayEmployees(void)
{
    int i;

    if (count == 0)
    {
        printf("\nNo employees yet.\n");
        return;
    }

    printf("\n%-6s %-20s %-15s %-15s %10s\n", "ID", "Name", "Department", "Position", "Basic");
    printf("--------------------------------------------------------------------\n");

    for (i = 0; i < count; i++)
    {
        printf("%-6d %-20s %-15s %-15s %10.2f\n",
               empId[i], empName[i], empDept[i], empPosition[i], basicSalary[i]);
    }

    printf("\nTotal employees: %d\n", count);
}

/* prints all the details of one employee */
void printEmployee(int i)
{
    printf("\nID:                  %d\n", empId[i]);
    printf("Name:                %s\n", empName[i]);
    printf("Department:          %s\n", empDept[i]);
    printf("Position:            %s\n", empPosition[i]);
    printf("Basic salary:        N$%.2f\n", basicSalary[i]);
    printf("Housing allowance:   N$%.2f\n", housing[i]);
    printf("Transport allowance: N$%.2f\n", transport[i]);
}

void searchEmployee(void)
{
    int choice;
    int id;
    int i;
    int found;
    char name[SIZE];

    if (count == 0)
    {
        printf("\nNo employees yet.\n");
        return;
    }

    printf("\n1. Search by ID\n");
    printf("2. Search by name\n");
    choice = getInt("Enter your choice: ", 1, 2);

    if (choice == 1)
    {
        id = getInt("Enter employee ID: ", 1, 99999);
        i = findEmployeeById(id);

        if (i == -1)
        {
            printf("No employee with ID %d.\n", id);
        }
        else
        {
            printEmployee(i);
        }
    }
    else
    {
        getString("Enter full name: ", name, SIZE);
        found = 0;

        for (i = 0; i < count; i++)
        {
            if (strcmp(empName[i], name) == 0)
            {
                printEmployee(i);
                found++;
            }
        }

        if (found == 0)
        {
            printf("No employee named %s.\n", name);
        }
    }
}
