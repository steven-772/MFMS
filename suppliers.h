#ifndef SUPPLIERS_H
#define SUPPLIERS_H

void supplierMenu(void);
void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);
void printSupplier(int i);
int findSupplierById(int id);
int isValidEmail(const char *email);
int isValidPhone(const char *phone);

#endif
