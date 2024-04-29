#include "repository.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int findMedicineIndex(MedicineRepository* repo, const char* name, float concentration);
static void ensureCapacity(MedicineRepository* repo);
void freeMedicine(Medicine* m);
Medicine* deepCopyMedicine(const Medicine* src);

Medicine* deepCopyMedicine(const Medicine* src) {
    if (src == NULL) return NULL;

    Medicine* copy = (Medicine*)malloc(sizeof(Medicine));
    if (!copy) return NULL;
    copy->name = strdup(src->name);
    if (!copy->name) {
        free(copy);
        return NULL;
    }

    copy->concentration = src->concentration;
    copy->quantity = src->quantity;
    copy->price = src->price;

    return copy;
}

static void freeState(Medicine** state, int size) {
    for (int i = 0; i < size; ++i) {
        freeMedicine(state[i]);
    }
    free(state);
}

static Medicine** deepCopyState(Medicine** original, int size, int* newSize) {
    *newSize = size;
    Medicine** newState = malloc(sizeof(Medicine*) * size);
    for (int i = 0; i < size; ++i) {
        newState[i] = deepCopyMedicine(original[i]);
    }
    return newState;
}

void snapshotHistory(MedicineRepository* repo) {
    if (repo->currentIndex < repo->historySize - 1) {
        for (int i = repo->currentIndex + 1; i < repo->historySize; ++i) {
            freeState(repo->history[i].state, repo->history[i].size);
        }
        repo->historySize = repo->currentIndex + 1;
    }

    if (repo->historySize == repo->historyCapacity) {
        int newCapacity = repo->historyCapacity == 0 ? 1 : repo->historyCapacity * 2;
        repo->history = realloc(repo->history, sizeof(HistoryState) * newCapacity);
        repo->historyCapacity = newCapacity;
    }

    int newStateSize;
    Medicine** newState = deepCopyState(repo->medicines, repo->size, &newStateSize);
    repo->history[repo->historySize].state = newState;
    repo->history[repo->historySize].size = newStateSize;
    repo->historySize++;
    repo->currentIndex++;
}

void undo(MedicineRepository* repo) {
    if (repo->currentIndex > 0) {
        repo->currentIndex--;

        freeState(repo->medicines, repo->size);
        int newSize;
        repo->medicines = deepCopyState(repo->history[repo->currentIndex].state, repo->history[repo->currentIndex].size, &newSize);
        repo->size = newSize;
    } else {
        printf("No more actions to undo.\n");
    }
}

void redo(MedicineRepository* repo) {
    if (repo->currentIndex < repo->historySize - 1) {
        repo->currentIndex++;

        freeState(repo->medicines, repo->size);
        int newSize;
        repo->medicines = deepCopyState(repo->history[repo->currentIndex].state, repo->history[repo->currentIndex].size, &newSize);
        repo->size = newSize;
    } else {
        printf("No more actions to redo.\n");
    }
}

MedicineRepository* createRepository() {
    MedicineRepository* repo = (MedicineRepository*)malloc(sizeof(MedicineRepository));
    if (repo == NULL) {
        return NULL;
    }

    repo->medicines = (Medicine**)malloc(sizeof(Medicine*) * 10);
    repo->size = 0;
    repo->capacity = 10;

    repo->history = NULL;
    repo->historySize = 0;
    repo->historyCapacity = 0;
    repo->currentIndex = -1;
    return repo;
}

void freeRepository(MedicineRepository* repo) {
    if (repo != NULL) {
        for (int i = 0; i < repo->size; i++) {
            freeMedicine(repo->medicines[i]);
        }
        free(repo->medicines);
        free(repo);
    }
}

int addOrUpdateMedicine(MedicineRepository* repo, const char* name, float concentration, int quantity, float price) {
    int index = findMedicineIndex(repo, name, concentration);

    if (index != -1) {
        repo->medicines[index]->quantity += quantity;
        repo->medicines[index]->price = price;
        snapshotHistory(repo);
        return 0;
    } else {
        ensureCapacity(repo);

        Medicine* newMedicine = createMedicine(name, concentration, quantity, price);
        if (newMedicine == NULL) {
            return -1;
        }
        repo->medicines[repo->size++] = newMedicine;
        snapshotHistory(repo);
        return 1;
    }
}

int deleteMedicine(MedicineRepository* repo, const char* name, float concentration) {
    int index = findMedicineIndex(repo, name, concentration);
    if (index == -1) {
        return -1;
    }

    freeMedicine(repo->medicines[index]);
    for (int i = index; i < repo->size - 1; i++) {
        repo->medicines[i] = repo->medicines[i + 1];
    }
    repo->size--;
    snapshotHistory(repo);
    return 0;
}

static int findMedicineIndex(MedicineRepository* repo, const char* name, float concentration) {
    for (int i = 0; i < repo->size; i++) {
        if (strcmp(repo->medicines[i]->name, name) == 0 && repo->medicines[i]->concentration == concentration) {
            return i;
        }
    }
    return -1;
}

Medicine** listMedicinesInShortSupply(MedicineRepository* repo, int threshold, int* count) {
    int tempSize = 0;
    Medicine** tempArray = malloc(sizeof(Medicine*) * repo->size);

    for (int i = 0; i < repo->size; i++) {
        if (repo->medicines[i]->quantity < threshold) {
            tempArray[tempSize++] = repo->medicines[i];
        }
    }

    *count = tempSize;
    return tempArray;
}

static void ensureCapacity(MedicineRepository* repo) {
    if (repo->size >= repo->capacity) {
        int newCapacity = repo->capacity * 2;
        repo->medicines = (Medicine**)realloc(repo->medicines, sizeof(Medicine*) * newCapacity);
        repo->capacity = newCapacity;
    }
}
Medicine** getAllMedicines(MedicineRepository* repo, int* count) {
    *count = repo->size;
    return repo->medicines;
}
