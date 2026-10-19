#ifndef BUDGET_H
#define BUDGET_H

void budgetMenu(void);
void addBudget(void);
void addExpenditure(void);
void displayBudgets(void);
void showOverBudget(void);
int findDepartment(const char *name);
double calculateRemaining(int i);
const char *budgetStatus(int i);

#endif
