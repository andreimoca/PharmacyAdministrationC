#include "medicine.h"
#include <stdlib.h>
#include <string.h>

Medicine* createMedicine(const char* name, float concentration, int quantity, float price) {
    Medicine* newMedicine = (Medicine*)malloc(sizeof(Medicine));
    if (newMedicine == NULL) {
        return NULL;
    }
    newMedicine->name = strdup(name);
    if (newMedicine->name == NULL) {
        free(newMedicine);
        return NULL;
    }
    newMedicine->concentration = concentration;
    newMedicine->quantity = quantity;
    newMedicine->price = price;

    return newMedicine;
}

void freeMedicine(Medicine* m) {
    if (m != NULL) {
        free(m->name);
        free(m);
    }
}
