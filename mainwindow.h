#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "propriete.h"
#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Ajouter_clicked();

    void on_confirmer_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_generer_clicked();

    void on_pushButton_2_clicked();

    void on_qrpushbutton_clicked();

private:
    Ui::MainWindow *ui;
    propriete pimp;
};
#endif // MAINWINDOW_H
