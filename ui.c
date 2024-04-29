#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

static void addMedicineUI(PharmacyUI* ui);
static void deleteMedicineUI(PharmacyUI* ui);
static void displayAllMedicinesUI(PharmacyUI* ui);
static void displayMenu();
static void listMedicinesContainingStringUI(PharmacyUI* ui);
static void listMedicinesInShortSupplyUI(PharmacyUI* ui);

PharmacyUI* createUI(PharmacyController* controller) {
    PharmacyUI* ui = (PharmacyUI*)malloc(sizeof(PharmacyUI));
    ui->controller = controller;
    return ui;
}

void freeUI(PharmacyUI* ui) {
    free(ui);
}

void startUI(PharmacyUI* ui) {

    int option;
    do {
        displayMenu();
        printf("Enter option: ");
        scanf("%d", &option);
        switch (option) {
            case 1:
                addMedicineUI(ui);
                break;
            case 2:
                deleteMedicineUI(ui);
                break;
            case 3:
                displayAllMedicinesUI(ui);
                break;
            case 4:
                listMedicinesInShortSupplyUI(ui);
                break;
            case 5:
                listMedicinesContainingStringUI(ui);
                break;
            case 6:
                undoAction(ui->controller);
                break;
            case 7:
                redoAction(ui->controller);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 0);
}

static void displayMenu() {
    printf("\nTypes of operations\n");
    printf("1. Add or Update a Medicine\n");
    printf("2. Delete a Medicine\n");
    printf("3. List All Medicines\n");
    printf("4. List Medicines in Short Supply\n");
    printf("5. List Medicines Containing String\n");
    printf("6. Undo\n");
    printf("7. Redo\n");
    printf("0. Exit\n");
}


static void addMedicineUI(PharmacyUI* ui) {
    char name[256];
    float concentration;
    int quantity;
    float price;

    printf("Medicine name: ");
    scanf("%255s", name);
    printf("Concentration: ");
    scanf("%f", &concentration);
    printf("Quantity: ");
    scanf("%d", &quantity);
    printf("Price: ");
    scanf("%f", &price);

    if (addMedicineController(ui->controller, name, concentration, quantity, price) == 1) {
        printf("Medicine added successfully.\n");
    } else {
        printf("Failed to add medicine.\n");
    }
}

static void deleteMedicineUI(PharmacyUI* ui) {
    char name[256];
    float concentration;

    printf("Medicine name to delete: ");
    scanf("%255s", name);
    printf("Concentration: ");
    scanf("%f", &concentration);

    if (deleteMedicineController(ui->controller, name, concentration) == 0) {
        printf("Medicine deleted successfully.\n");
    } else {
        printf("Medicine not found.\n");
    }
}

static void displayAllMedicinesUI(PharmacyUI* ui) {
    int count = 0;
    Medicine** allMedicines = getAllMedicines(ui->controller->repo, &count);
    sortMedicinesByName(ui->controller);
    printf("\nList of All Medicines:\n");
    for (int i = 0; i < count; i++) {
        Medicine* m = allMedicines[i];
        printf("%d: %s, Concentration: %.2f, Quantity: %d, Price: $%.2f\n",
               i + 1, m->name, m->concentration, m->quantity, m->price);
    }
    if (count == 0) {
        printf("No medicines in the system.\n");
    }
}
static void listMedicinesInShortSupplyUI(PharmacyUI* ui) {
    int threshold, count;
    printf("Enter the quantity threshold for medicines in short supply: ");
    scanf("%d", &threshold);

    Medicine** medicines = listMedicinesInShortSupply(ui->controller->repo, threshold, &count);
    printf("Medicines in short supply (less than %d):\n", threshold);
    for (int i = 0; i < count; i++) {
        printf("%d. %s - Concentration: %.2f, Quantity: %d, Price: $%.2f\n",
               i + 1, medicines[i]->name, medicines[i]->concentration, medicines[i]->quantity, medicines[i]->price);
    }
    if (count == 0) {
        printf("No medicines are in short supply.\n");
    }
    free(medicines);
}
static void listMedicinesContainingStringUI(PharmacyUI* ui) {
    char name[256];
    printf("String to be searched: ");
    scanf("%s", name);
    listMedicinesContainingString(ui->controller, name);
}
