#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "transactions.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::MainWindow *ui;
    transactions t;
};

#endif // MAINWINDOW_H
