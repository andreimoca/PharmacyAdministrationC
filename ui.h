#ifndef UI_H
#define UI_H

#include "controller.h"

typedef struct {
    PharmacyController* controller;
} PharmacyUI;

PharmacyUI* createUI(PharmacyController* controller);

void freeUI(PharmacyUI* ui);
void startUI(PharmacyUI* ui);


#endif // UI_H
