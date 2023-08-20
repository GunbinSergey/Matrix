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

    widg = new QMap<QString, QLineEdit*>;
    widg->insert("rang", r_le);

    p_vl->addWidget(r_lab);
    p_vl->addWidget(r_le);
    connect(r_le, SIGNAL(textChanged(const QString)), this, SLOT(imput_rang(const QString)));

    QPushButton* b_crt = new QPushButton("Cоздать матрицу");
    p_vl->addWidget(b_crt);
    connect(b_crt, &QPushButton::clicked, this, &MainWindow::create_matr);

    QPushButton* b_calc = new QPushButton("Рассчитать определитель");
    p_vl->addWidget(b_calc);
    connect(b_calc, &QPushButton::clicked, this, &MainWindow::calc_opred);

    QPushButton* b_obr = new QPushButton("Рассчитать обратную матрицу");


    QLabel* det_lab = new QLabel("Определитель матрицы");
    QLineEdit* det_le = new QLineEdit;
    det_le->setReadOnly(true);
    widg->insert("det", det_le);

    p_vl->addWidget(det_lab);
    p_vl->addWidget(det_le);


    return wid;
}

QWidget *MainWindow::matrix_widget()
{
    //Создание поля под вывод матрицы
    QWidget* wid = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(wid);
    mtr_view = new QTableView();
    lay->addWidget(mtr_view);
    return(wid);

}


void MainWindow::imput_rang(const QString text)
{
    bool isOk = true;
    int mat_size = text.toInt(&isOk);
    if (isOk)
    {
        mtr_r = mat_size;
    }
}

void MainWindow::create_matr()
{
    QStandardItemModel* mtr_data = new QStandardItemModel(mtr_r, mtr_r);
    mtr_view->setModel(mtr_data);
}

void MainWindow::calc_opred()
{
    //Запрос на расчёт определителя
    //Получения размерности матрицы
    int mtr_r = 0;
    bool isOk = true;
    QLineEdit* ed = widg->find("rang").value();
    QString str = ed->text();
    int mat_size = str.toInt(&isOk);
    if (isOk)
    {
        mtr_r = mat_size;
    }
    else {
        return;
    }

    //Рассчёт определителя
    MyMatrix matr(mtr_r, mtr_view->model());
    double res = matr.Opred();
    ed = widg->find("det").value();
    ed->setText(QString::number(res));

}

void MainWindow::make_obr()
{

}


