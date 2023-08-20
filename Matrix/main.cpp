#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QMap>


void write_arr(int** arr, int r);
int** mini_matrix(int** mtrx, int rang, int ban_col);
int Opred(int** mtr, int n);

int Opred(int** mtr, int n)
{
    //Расчёт определителя
    if (n == 2)
    {
        return mtr[0][0] * mtr[1][1] - mtr[1][0] * mtr[0][1];
    }

    int n2 = n -1;
    int** frs = mini_matrix(mtr, n, 0);
    int** sec = mini_matrix(mtr, n, 1);
    int** thr = mini_matrix(mtr, n, 2);
    if (n == 3)
    {

        return mtr[0][0] * Opred(frs, n2) - mtr[0][1] * Opred(sec, n2) + mtr[0][2] * Opred(thr,n2);
    }
    else if (n == 4)
    {
         int** frt = mini_matrix(mtr, n, 2);
         return mtr[0][0] * Opred(frs, n2) - mtr[0][1] * Opred(sec, n2) + mtr[0][2] * Opred(thr,n2) - mtr[0][3] * Opred(frt, n2);
    }
    return 0;
}


int** mini_matrix(int** mtrx, int rang, int ban_col)
{
    //Матрица с пониженным рангом для расчёта опредилителя старшей
    int new_r = rang - 1;
    int** new_m = new int* [new_r];

    for(int i =0; i < new_r; ++i)
    {
        *new_m = new int[new_r];
        new_m++;
    }
    new_m -= (new_r);



    //Проход по строкам
    for (int i = 1; i < rang; ++i)
    {
        int row = 0;
        for (int j = 0; j < rang; ++j)
        {
            if (j == ban_col)
                continue;
            new_m[i-1][row] = mtrx[i][j];
            //qDebug() << new_m[i-1][row] << " " << mtrx[i][j];
            row++;
        }
    }

    return new_m;
}

void write_arr(int** arr, int r)
{
    //Вывести матириксу в Дебаг
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < r; ++j)
        {
            qDebug() << arr[i][j];
        }
    }
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QMap<int, int> tst;
    int t = 10;
    tst.insert(1,t);
    tst.insert(2,t);



    return a.exec();
}


