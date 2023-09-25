#ifndef MYMATRIX_H
#define MYMATRIX_H

#include <QStandardItemModel>
#include <QDebug>

class MyMatrix
{

private:
    double** mtr;
    int mtr_r;
    double opred;

    void write_arr(double** arr, int r);
    double** mini_matrix(double** mtrx, int rang, int ban_col, int ban_row = 0);
    double** minor_matrix();
    double** alg_dop_mtr(double** minor, int n);
    double** trans_matrix(double** mtr, int n);
    double** empty_arr(int r);
    double** fill_arr(double **);
    void clr_mem(double** mtr, int n);

public:
    MyMatrix();
    MyMatrix(int n,QAbstractItemModel* data);
    double Opred(double** mr, int n);
    double Opred();
    QStandardItemModel* Obrat();
};

#endif // MYMATRIX_H
