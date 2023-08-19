#include "mymatrix.h"

void MyMatrix::write_arr(double **arr, int r)
{
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < r; ++j)
        {
            qDebug() << arr[i][j];
        }
    }
}

double **MyMatrix::mini_matrix(double **mtrx, int rang, int ban_col)
{
    //Матрица с пониженным рангом для расчёта опредилителя старшей
    int new_r = rang - 1;
    double** new_m = new double* [new_r];

    for(int i =0; i < new_r; ++i)
    {
        *new_m = new double[new_r];
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

MyMatrix::MyMatrix()
{

}

MyMatrix::MyMatrix(int n, QAbstractItemModel *data)
{
   //Создание двойного динамического массива
   mtr_r = n;
   mtr = new double*[n];
   for(int i = 0; i < mtr_r; ++i)
   {
       *mtr = new double[mtr_r] {1, 2};
       mtr++;
   }
   mtr -= mtr_r;
   //write_arr(mtr, mtr_r);

   //Заполнение массива
   for (int i = 0; i < mtr_r; ++i)
   {
       for (int j = 0; j < mtr_r; ++j)
       {
           double d = 0;
           bool isOk;
           d = data->data(data->index(i, j)).toDouble(&isOk);;
           if (isOk)
           {
                mtr[i][j] = d;
           }
           else
           {
               //Значение не double
               //Тут может быть вызов предупреждения
               mtr[i][j] = 0;
           }
       }
   }


}

double MyMatrix::Opred(double** mr, int n)
{
    //Расчёт определителя
    if (n == 2)
    {
        return mr[0][0] * mr[1][1] - mr[1][0] * mr[0][1];
    }

    int n2 = n -1;
    double** frs = mini_matrix(mr, n, 0);
    double** sec = mini_matrix(mr, n, 1);
    double** thr = mini_matrix(mr, n, 2);
    if (n == 3)
    {

        return mr[0][0] * Opred(frs, n2) - mr[0][1] * Opred(sec, n2) + mr[0][2] * Opred(thr,n2);
    }
    else if (n == 4)
    {
         double** frt = mini_matrix(mr, n, 2);
         return mr[0][0] * Opred(frs, n2) - mr[0][1] * Opred(sec, n2) + mr[0][2] * Opred(thr,n2) * mr[0][3] * Opred(frt, n2);
    }
    return 0;
}

double MyMatrix::Opred()
{
   return Opred(mtr, mtr_r);
}
