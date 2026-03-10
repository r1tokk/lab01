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
    if (c_1.cop >= 100) {
        c_1.grn = c_1.grn + (c_1.cop / 100);
        c_1.cop = c_1.cop % 100;
    }
}
void add(cina &c_1, cina &c_2, cina &result) {
    result.grn = c_1.grn + c_2.grn;
    result.cop = c_1.cop + c_2.cop;

    if (result.cop >= 100) {
        result.grn = result.grn + (result.cop / 100);
        result.cop = result.cop % 100;
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

void readSum(cina &sum_c) {
    FILE *file;

    file = fopen("./cina.txt", "r");

    if (file == nullptr) {
        std::cout << "Помилка відкриття файлу" << std::endl;
        return;
    }
    int temp_grn, temp_cop, temp_qty;
    while (fscanf(file, "%*s %d %hd %d", &temp_grn, &temp_cop, &temp_qty) == 3){
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
    fclose(file);
}

void showRoundedSum() {
    cina sum_c = {0, 0};
    readSum(sum_c);
    std::cout << "Загальна сума: ";
    showCina(sum_c);
    std::cout << std::endl;

    cina r_sum = sum_c;
    round(r_sum);
    std::cout << "Сума до оплати: ";
    showCina(r_sum);
    std::cout << std::endl;
}