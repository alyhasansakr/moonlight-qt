#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QPointer>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QPointer<QMessageBox> dialog = new QMessageBox;
    dialog->setWindowTitle("Hello World");
    dialog->setText("Hello World");
    dialog->show();
    qDebug() << "Hello World\n";
}
