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
        printf("0. Back to main menu\n");
        choice = getInt("Enter your choice: ", 0, 2);

        switch (choice)
        {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
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
