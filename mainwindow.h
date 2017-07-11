#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTcpSocket *pclient;

private slots:
    void displayError(QAbstractSocket::SocketError socketError);
private slots:

    void on_pushButtonConnect_clicked();

    void on_pushButtonSend_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
