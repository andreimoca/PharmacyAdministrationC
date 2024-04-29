#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "repository.h"

typedef struct {
    MedicineRepository* repo;
} PharmacyController;

PharmacyController* createController(MedicineRepository* repo);
void freeController(PharmacyController* controller);
void sortMedicinesByName(PharmacyController* controller);
void listMedicinesContainingString(PharmacyController* controller, const char* search);
int addMedicineController(PharmacyController* controller, const char* name, float concentration, int quantity, float price);
int deleteMedicineController(PharmacyController* controller, const char* name, float concentration);
void undoAction(PharmacyController* controller);
void redoAction(PharmacyController* controller);
#endif // CONTROLLER_H
