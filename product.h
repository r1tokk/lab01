//
// Created by ritokk on 18.02.26.
//
#ifndef LAB1_PRODUCT_H
#define LAB1_PRODUCT_H

struct cina {
    int grn;
    short int cop;
};
void round(cina &c_1);
void add(cina &c_1, cina &c_2, cina &result);
void multiply(cina &c_1, int n);
void showCina(cina c);
void readSum(cina &sum_c);
void showRoundedSum();


#endif //LAB1_PRODUCT_H