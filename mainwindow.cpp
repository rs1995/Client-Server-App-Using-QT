#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    pclient= new QTcpSocket(this);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonConnect_clicked()
{
    pclient->connectToHost(ui->textEditIP->toPlainText(),quint16(ui->textEditPort->toPlainText().toInt()));
    connect(pclient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
}

void MainWindow::on_pushButtonSend_clicked()
{
    QString message=ui->textEditMessage->toPlainText().trimmed();
    if(!message.isEmpty()){
        pclient->write(QString(message + "\n").toUtf8());
    }
    ui->textEditMessage->clear();
    ui->textEditMessage->setFocus();
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {

    case QAbstractSocket::RemoteHostClosedError:
        break;

    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Client"),
                                 tr("The host was not found. "));
        break;

    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Client"),
                                 tr("The connection was refused by the peer. "
                                   ));
        break;

    default:
        QMessageBox::information(this, tr("Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(pclient->errorString()));
        break;
    }
}
