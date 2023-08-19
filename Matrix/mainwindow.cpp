#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget* wid = new QWidget();
    this->setCentralWidget(wid);

    QHBoxLayout* m_lay = new QHBoxLayout(wid);

    //Панель управление
     m_lay->addWidget(contrl_panel());

    //Пространства для ввода матрицы
    m_lay->addWidget(matrix_widget());

    //Настройка layout
    m_lay->setStretch(0, 20);
    m_lay->setStretch(1, 80);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QWidget *MainWindow::contrl_panel()
{
    QWidget* wid = new QWidget();
    QVBoxLayout* p_vl = new QVBoxLayout(wid);

    QLabel* r_lab = new QLabel("Ранг матрицы");
    QLineEdit* r_le = new QLineEdit;

    p_vl->addWidget(r_lab);
    p_vl->addWidget(r_le);

    QPushButton* b_calc = new QPushButton("Рассчитать определитель");

    p_vl->addWidget(b_calc);

    QLabel* det_lab = new QLabel("Определитель матрицы");
    QLineEdit* det_le = new QLineEdit;
    det_le->setReadOnly(true);

    p_vl->addWidget(det_lab);
    p_vl->addWidget(det_le);


    return wid;
}

QWidget *MainWindow::matrix_widget()
{
    //Создание поля под вывод матрицы
    QWidget* wid = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(wid);
    mtr_view = new QTabWidget();
    //QLabel* l = new QLabel("test");
    lay->addWidget(mtr_view);
    //lay->addWidget(l);

    return(wid);

}

