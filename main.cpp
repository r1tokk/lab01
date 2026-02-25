#include <iostream>
#include <cstdio>
#include "product.h"
int main() {
    int data[90][3] = {0};

    FILE *file;

    file = fopen("../cina.txt", "r");

    if (file == NULL) {
        std::cout << "Помилка відкриття файлу" << std::endl;
        return 1;
    }

    int rows_read = 0;

    for (int i = 0; i < 90; i++) {
        bool row_complete = true;
        for (int j = 0; j < 3; j++) {
            int result = fscanf(file, "%d", &data[i][j]);

            if (result != 1) {
                row_complete = false;
                break;
            }
        }
        if (!row_complete) {
            break;
        }
        rows_read++;
    }

    fclose(file);

    cina sum_c = {0, 0};
    for (int i = 0; i < rows_read; i++) {
        cina c = {0, 0};

        c.grn = data[i][0];
        c.cop = data[i][1];

        c = multiply(c, data[i][2]);

        sum_c = add(c, sum_c);
    }
    cina r_sum = {0,0};
    r_sum = add({sum_c.grn, 0}, {0, round(sum_c.cop)});
    std::cout << "Загальна сума: ";
    showCina(sum_c);
    std::cout << std::endl;


    std::cout << "Сума до оплати: ";
    showCina(r_sum);
    std::cout << std::endl;
    std::cout << std::endl;
    return 0;
}