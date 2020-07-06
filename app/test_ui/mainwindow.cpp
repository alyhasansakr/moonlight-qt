#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QPointer>
#include <iostream>
#include "dialog.h"

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
    QPointer<QMessageBox> messagebox = new QMessageBox;
    messagebox->setWindowTitle("Hello World");
    messagebox->setText("Hello World");
    messagebox->show();


    QPointer<Dialog> dialog = new Dialog;
    dialog->show();
    dialog->raise();


    qDebug() << "Hello World\n";
}
