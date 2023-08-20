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

double **MyMatrix::mini_matrix(double **mtrx, int rang, int ban_col, int ban_row)
{
    //Матрица с пониженным рангом для расчёта опредилителя старшей
    //ВОзможно row и coll перепутаны названиями (главное, что робит)
    int new_r = rang - 1;
    double ** new_m = empty_arr(new_r);

    //Проход по строкам
    int coll = 0;
    for (int i = 0; i < rang; ++i)
    {
        if(i == ban_row)
            continue;

        int row = 0;
        //Проход по столбцам
        for (int j = 0; j < rang; ++j)
        {
            if (j == ban_col)
                continue;
            new_m[coll][row] = mtrx[i][j];
            //qDebug() << new_m[i-1][row] << " " << mtrx[i][j];
            row++;
        }
        coll++;
    }

    return new_m;
}

double **MyMatrix::minor_matrix()
{
    //Составление минорной матриксы
    int n = mtr_r;
    double** min_mtr = empty_arr(n);

    if (n == 2)
    {
        //Протиаоположные элементы
        min_mtr[0][0] = mtr[1][1];
        min_mtr[0][1] = mtr[1][0];
        min_mtr[1][0] = mtr[0][1];
        min_mtr[1][1] = mtr[0][0];

        write_arr(mtr, n);

        return min_mtr;
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
           double** sub_mtr = mini_matrix(mtr, n-1, i, j);
           min_mtr[i][j] = Opred(sub_mtr, n-1);
        }
    }
    return  min_mtr;
}

double **MyMatrix::alg_dop_mtr(double **minor, int n)
{
    //Растанавливаем минусы, если элемент нечётный
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if((i+j)%2 == 1)
            {
                minor[i][j] *= -1;
            }
        }
    }
    return minor;
}

double **MyMatrix::trans_matrix(double **mtr, int n)
{
    double** trans = empty_arr(n);

    for (int i =0; i < n; ++i)
    {
        for(int j = 0; j< n; ++j)
        {
            trans[i][j] = mtr[j][i];
        }
    }
    return trans;
}

double **MyMatrix::empty_arr(int n)
{
    //Создание пустого массива
    mtr = new double*[n];
    for(int i = 0; i < mtr_r; ++i)
    {
        *mtr = new double[mtr_r];
        mtr++;
    }
    mtr -= mtr_r;
    return  mtr;
}


MyMatrix::MyMatrix()
{

}

MyMatrix::MyMatrix(int n, QAbstractItemModel *data)
{
   //Создание двойного динамического массива
   mtr_r = n;
   mtr = empty_arr(mtr_r);

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
                mtr[i][j] *= d;
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
         return mr[0][0] * Opred(frs, n2) - mr[0][1] * Opred(sec, n2) + mr[0][2] * Opred(thr,n2) - mr[0][3] * Opred(frt, n2);
    }
    return 0;
}

double MyMatrix::Opred()
{
    return Opred(mtr, mtr_r);
}

QStandardItemModel *MyMatrix::Obrat()
{
    int n= mtr_r;
    QStandardItemModel* data = new QStandardItemModel(n, n);
    //Создание обратной матрицы как транспортированной алгоритмоической матрицы на основе обратной
    //double** omtr = trans_matrix(alg_dop_mtr(minor_matrix(),  n),  n);
    double** omtr = minor_matrix();

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            data->setData(data->index(i,j), omtr[i][j]);
        }
    }

    return data;
}
