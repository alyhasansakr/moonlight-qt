#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "streaming/session.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&computerManager, SIGNAL(computerAddCompleted(QVariant)), this, SLOT(computerConnected(QVariant)));
    connect(&computerManager, SIGNAL(pairingCompleted(NvComputer*, QString)), this, SLOT(computerPaired(NvComputer*, QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete session;
}

void MainWindow::on_connect_pushButton_clicked()
{
    ui->status_label->setText("connecting... (127.0.0.1)");
    computerManager.addNewHost("127.0.0.1", false);
}

void MainWindow::on_pair_pushButton_clicked()
{
    ui->status_label->setText("pairing... (1111)");
    QVector<NvComputer*> computers = computerManager.getComputers();
    if(computers.isEmpty() == true || computers[0]->state != NvComputer::CS_ONLINE)
    {
        ui->status_label->setText("please connect first!");
    }
    else
    {
        ui->status_label->setText("pairing... (1111)");
        computerManager.pairHost(computers[0], "1111");
    }
}

void MainWindow::on_launch_pushButton_clicked()
{
    QVector<NvComputer*> computers = computerManager.getComputers();
    if(computers.isEmpty() == true || computers[0]->state != NvComputer::CS_ONLINE || computers[0]->pairState != NvComputer::PS_PAIRED)
    {
        ui->status_label->setText("please connect and pair first!");
    }
    else
    {
        ui->status_label->setText("launching...");

        session = new Session(computers[0], computers[0]->appList[0]);
        session->exec(0,0);
    }
}

void MainWindow::computerConnected(QVariant success)
{
    if (success.toBool() == true)
    {
        computerManager.getComputers()[0]->pairState = NvComputer::PS_NOT_PAIRED;

        ui->status_label->setText("computer successfully connected");
    }
    else
    {
        ui->status_label->setText("computer falied to connect");
    }
}

void MainWindow::computerPaired(NvComputer* computer, QString error)
{
    if (error.isEmpty())
    {
        computer->pairState = NvComputer::PS_PAIRED;

        ui->status_label->setText("computer successfully paired");

        qInfo() << computer->appList.size() << " apps found\n";

        for (int i = 0; i < computer->appList.size(); i++)
        {
            qInfo() << "ID: " << computer->appList[i].id << ", Name: " << computer->appList[i].name << "\n";
        }
    }
    else
    {
        computer->pairState = NvComputer::PS_NOT_PAIRED;

        ui->status_label->setText("computer paired failed");
    }
}
