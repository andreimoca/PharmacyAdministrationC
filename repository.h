#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "medicine.h"

typedef struct {
    Medicine** state;
    int size;
} HistoryState;

typedef struct {
    Medicine** medicines;
    int size;
    int capacity;
    HistoryState* history;
    int historySize;
    int historyCapacity;
    int currentIndex;
} MedicineRepository;

MedicineRepository* createRepository();

void snapshotHistory(MedicineRepository* repo);
void undo(MedicineRepository* repo);
void redo(MedicineRepository* repo);

void freeRepository(MedicineRepository* repo);
int addOrUpdateMedicine(MedicineRepository* repo, const char* name, float concentration, int quantity, float price);
int deleteMedicine(MedicineRepository* repo, const char* name, float concentration);
Medicine** getAllMedicines(MedicineRepository* repo, int* count);
Medicine** listMedicinesInShortSupply(MedicineRepository* repo, int threshold, int* count);

#endif // REPOSITORY_H
