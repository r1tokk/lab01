//
// Created by ritokk on 18.02.26.
//

#ifndef LAB1_PRODUCT_H
#define LAB1_PRODUCT_H

struct cina {
    int grn;
    short int cop;
};
short int round(short int cop);
cina add(cina c_1, cina c_2);
cina multiply(cina c_1, short int n);
void showCina(cina c);

#endif //LAB1_PRODUCT_H