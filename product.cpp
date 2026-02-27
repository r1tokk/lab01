//
// Created by ritokk on 18.02.26.
//

#include "product.h"

#include <iostream>


short int round(short int cop) {
    if (cop % 10 <= 3) {
        return cop - (cop % 10);
    }
    return (cop / 10) * 10 + 10 ;
}
cina add(cina c_1, cina c_2) {
    cina c_3;

    c_3.grn = c_1.grn + c_2.grn;
    c_3.cop = c_1.cop + c_2.cop;

    if (c_3.cop >= 100) {
        c_3.grn = c_3.grn + (c_3.cop / 100);
        c_3.cop = c_3.cop % 100;
    }

    return c_3;
}

cina multiply(cina c_1, short int n) {
    cina c_2;
    c_2.grn = c_1.grn * n;
    c_2.cop = c_1.cop * n;

    if (c_2.cop >= 100) {
        c_2.grn = c_2.grn + c_2.cop / 100;
        c_2.cop = c_2.cop % 100;
    }

    return c_2;
}

void showCina(cina c) {
    std::cout << c.grn << " грн " << c.cop << " коп."<< std::endl;
}

void showSum(cina sum_c) {
    std::cout << "Загальна сума: ";
    showCina(sum_c);
    std::cout << std::endl;
}

cina readSum() {
    int data[90][3];
    FILE *file;

    file = fopen("../cina.txt", "r");

    if (file == NULL) {
        std::cout << "Помилка відкриття файлу" << std::endl;
        return {0,0};
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
            data[j][0] = temp_grn;
            data[j][1] = temp_cop;
            data[j][2] = temp_qty;
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
    return sum_c;
}

void showRoundedSum() {
    cina sum_c = readSum();
    cina r_sum = {0,0};
    r_sum = add({sum_c.grn, 0}, {0, round(sum_c.cop)});
    showSum(sum_c);

    std::cout << "Сума до оплати: ";
    showCina(r_sum);
    std::cout << std::endl;
    std::cout << std::endl;
}