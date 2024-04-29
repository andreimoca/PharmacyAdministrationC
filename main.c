#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include "tests.h"


int main() {
    runAllTests();

    MedicineRepository* repo = createRepository();
    PharmacyController* controller = createController(repo);
    PharmacyUI* ui = createUI(controller);

    addMedicineController(ui->controller, "Paracetamol", 500.0, 100, 3.99);
    addMedicineController(ui->controller, "Ibuprofen", 200.0, 50, 5.49);
    addMedicineController(ui->controller, "Aspirin", 100.0, 50, 9.99);
    addMedicineController(ui->controller, "Amoxicillin", 250.0, 20, 15.99);
    addMedicineController(ui->controller, "Ciprofloxacin", 200.0, 15, 12.49);
    addMedicineController(ui->controller, "Loratadine", 10.0, 30, 7.99);
    addMedicineController(ui->controller, "Omeprazole", 40.0, 25, 6.49);
    addMedicineController(ui->controller, "Diazepam", 5.0, 10, 8.99);
    addMedicineController(ui->controller, "Naproxen", 250.0, 40, 4.99);
    addMedicineController(ui->controller, "Ranitidine", 150.0, 60, 3.49);

    startUI(ui);


    freeUI(ui);
    freeController(controller);
    freeRepository(repo);

    return EXIT_SUCCESS;
}
