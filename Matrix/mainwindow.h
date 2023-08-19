#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QMap>

#include "mymatrix.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget* contrl_panel();
    QWidget* matrix_widget();
    QTableView* mtr_view;

    QMap<QString, QLineEdit*>* widg;
    int mtr_r;

    QLineEdit* r_le;
    QLineEdit* det_le;

private slots:
    void imput_rang(const QString);
    void create_matr();
    void calc_opred();
};
#endif // MAINWINDOW_H
