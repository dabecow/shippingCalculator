#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExpValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Thomann calculator");
    this->setWindowIcon(QIcon(":/new/icons/to4ka.icns"));
    QRegExp rx("[+]?[0-9]*\\.?[0-9]?[0-9]");
    ui->priceEdit->setValidator(new QRegExpValidator(rx));
    ui->euroValueEdit->setValidator(new QRegExpValidator(rx));
    ui->questionMark->setToolTip("Курс евро вашего банка, а не ЦБ. \nПолная цена с доставкой, как \nуказано в конце корзины в €.");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_clicked()
{
    float price, tax = 0, euroToRubValue;
    price = ui->priceEdit->text().toFloat();
    QString tmp = ui->euroValueEdit->text();
    euroToRubValue = tmp.toFloat();
    price -= 40;
    if (price > 200){
        tax = price - 200;
        tax*=0.15;
        tax*=euroToRubValue;
        tax+=500;
    }

    price+=40.0;
    price*=euroToRubValue;
    price+=tax;


//    ui->priceValueLabel->repaint();
    if (price <= 0) ui->priceValueLabel->setText("Error");
    else ui->priceValueLabel->setText(QString::number(price));
    ui->priceValueLabel->repaint();
}
