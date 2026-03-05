//
// Created by ritokk on 18.02.26.
//

#include "product.h"

#include <iostream>


void round(cina &c_1) {
    if (c_1.cop % 10 <= 3) {
        c_1.cop = c_1.cop - (c_1.cop % 10);
    }else {
        c_1.cop = c_1.cop - c_1.cop % 10 + 10 ;
    }
}
void add(cina &c_1, cina &c_2, cina &c_3) {
    c_3.grn = c_1.grn + c_2.grn;
    c_3.cop = c_1.cop + c_2.cop;

    if (c_3.cop >= 100) {
        c_3.grn = c_3.grn + (c_3.cop / 100);
        c_3.cop = c_3.cop % 100;
    }
}

void multiply(cina &c_1, int n) {
    c_1.grn = c_1.grn * n;
    c_1.cop = c_1.cop * n;

    if (c_1.cop >= 100) {
        c_1.grn = c_1.grn + c_1.cop / 100;
        c_1.cop = c_1.cop % 100;
    }
}

void showCina(cina c) {
    std::cout << c.grn << " грн " << c.cop << " коп."<< std::endl;
}

void showSum(cina &sum_c) {
    std::cout << "Загальна сума: ";
    showCina(sum_c);
    std::cout << std::endl;
}

void readSum(cina &sum_c) {
    FILE *file;

    file = fopen("./cina.txt", "r");

    if (file == nullptr) {
        std::cout << "Помилка відкриття файлу" << std::endl;
        return;
    }

    int rows_read = 0;

    for (int i = 0; i < 90; i++) {
        bool row_complete = true;

        for (int j = 0; j < 3; j++) {
            int temp_grn, temp_cop, temp_qty;
            int result = fscanf(file, "%*s %d %d %d", &temp_grn, &temp_cop, &temp_qty);

            if (result != 3) {
                row_complete = false;
                break;
            }
            if (temp_grn < 0 || temp_cop < 0 || temp_qty < 0) {
                std::cout << "виявлено від'ємні значення у файлі." << std::endl;
                continue;
            }
            cina c = {0, 0};
            c.grn = temp_grn;
            c.cop = temp_cop;

            multiply(c, temp_qty);

            add(c, sum_c, sum_c);
        }
        if (!row_complete) {
            break;
        }
        rows_read++;
    }

    fclose(file);
}

void showRoundedSum() {
    cina sum_c = {0, 0};
    readSum(sum_c);

    showSum(sum_c);

    cina r_sum = sum_c;
    round(r_sum);

    std::cout << "Сума до оплати: ";
    showCina(r_sum);
    std::cout << std::endl;
}