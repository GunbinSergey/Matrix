#ifndef MYMATRIX_H
#define MYMATRIX_H

#include <QStandardItemModel>
#include <QDebug>

class MyMatrix
{

private:
    double** mtr;
    int mtr_r;
    void write_arr(double** arr, int r);
    double** mini_matrix(double** mtrx, int rang, int ban_col);

public:
    MyMatrix();
    MyMatrix(int n,QAbstractItemModel* data);
    double Opred(double** mr, int n);
    double Opred();
};

#endif // MYMATRIX_H
