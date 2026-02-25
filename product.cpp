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
