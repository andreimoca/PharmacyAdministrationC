#ifndef MEDICINE_H
#define MEDICINE_H

typedef struct {
    char* name;
    float concentration;
    int quantity;
    float price;
} Medicine;

Medicine* createMedicine(const char* name, float concentration, int quantity, float price);
void freeMedicine(Medicine* m);

#endif // MEDICINE_H
