#include "controller.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

PharmacyController* createController(MedicineRepository* repo) {
    PharmacyController* controller = (PharmacyController*)malloc(sizeof(PharmacyController));
    if (!controller) {
        return NULL;
    }
    controller->repo = repo;
    return controller;
}
int compareMedicineByName(const void* a, const void* b) {
    Medicine* medicineA = *(Medicine**)a;
    Medicine* medicineB = *(Medicine**)b;
    return strcmp(medicineA->name, medicineB->name);
}

void sortMedicinesByName(PharmacyController* controller) {
    qsort(controller->repo->medicines, controller->repo->size, sizeof(Medicine*), compareMedicineByName);
}
void undoAction(PharmacyController* controller) {
    undo(controller->repo);
}

void redoAction(PharmacyController* controller) {
    redo(controller->repo);
}
void freeController(PharmacyController* controller) {
    free(controller);
}

int addMedicineController(PharmacyController* controller, const char* name, float concentration, int quantity, float price) {
    if (!controller) return -1;
    return addOrUpdateMedicine(controller->repo, name, concentration, quantity, price);
}

int deleteMedicineController(PharmacyController* controller, const char* name, float concentration) {
    if (!controller) return -1;
    return deleteMedicine(controller->repo, name, concentration);
}
void listMedicinesContainingString(PharmacyController* controller, const char* search) {
    MedicineRepository* repo = controller->repo;
    sortMedicinesByName(controller);

    printf("Medicines Containing \"%s\"\n", search);
    for (int i = 0; i < repo->size; ++i) {
        if (search[0] == '\0' || strstr(repo->medicines[i]->name, search)) {
            printf("Name: %s, Concentration: %.2f, Quantity: %d, Price: $%.2f\n",
                   repo->medicines[i]->name, repo->medicines[i]->concentration,
                   repo->medicines[i]->quantity, repo->medicines[i]->price);
        }
    }
}