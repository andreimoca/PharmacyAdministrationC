#include "tests.h"
#include "medicine.h"
#include "repository.h"
#include "controller.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void testMedicineFunctions();
static void testRepositoryFunctions();
static void testControllerFunctions();
static MedicineRepository* setupTestRepository();

void runAllTests() {
    testMedicineFunctions();
    testRepositoryFunctions();
    testControllerFunctions();
    printf("All tests passed successfully.\n");
}

static void testMedicineFunctions() {
    Medicine* m = createMedicine("Aspirin", 100.0, 50, 9.99);
    assert(m != NULL && "createMedicine() failed to create a medicine.");
    assert(strcmp(m->name, "Aspirin") == 0 && "Medicine name is incorrect.");
    assert(m->concentration == 100.0 && "Medicine concentration is incorrect.");
    assert(m->quantity == 50 && "Medicine quantity is incorrect.");
    freeMedicine(m);
    printf("Medicine module tests passed.\n");
}

static void testRepositoryFunctions() {
    MedicineRepository* repo = setupTestRepository();
    assert(repo->size == 2 && "setupTestRepository() did not set up initial medicines correctly.");
    addOrUpdateMedicine(repo, "Ibuprofen", 200.0, 30, 5.49);
    Medicine* ibuprofen = repo->medicines[1];
    assert(ibuprofen->quantity == 80 && "Quantity update failed.");
    deleteMedicine(repo, "Paracetamol", 500.0);
    assert(repo->size == 1 && "deleteMedicine() failed to delete.");
    int result = deleteMedicine(repo, "NonExist", 100.0);
    assert(result == -1 && "Deleting non-existing medicine should return error.");
    freeRepository(repo);
    printf("Repository module tests passed.\n");
}

static void testControllerFunctions() {
    MedicineRepository* repo = createRepository();
    PharmacyController* controller = createController(repo);
    addMedicineController(controller, "Amoxicillin", 250.0, 20, 15.99);
    assert(repo->size == 1 && "addMedicineController() failed to add new medicine.");
    deleteMedicineController(controller, "Amoxicillin", 250.0);
    assert(repo->size == 0 && "deleteMedicineController() failed to delete medicine.");
    freeController(controller);
    freeRepository(repo);
    printf("Controller module tests passed.\n");
}

static MedicineRepository* setupTestRepository() {
    MedicineRepository* repo = createRepository();
    addOrUpdateMedicine(repo, "Paracetamol", 500.0, 100, 3.99);
    addOrUpdateMedicine(repo, "Ibuprofen", 200.0, 50, 5.49);
    return repo;
}
