#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "contrats.h"
#include <QMainWindow>

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

    void on_supp_clicked();

    void on_generer_clicked();

    void on_load_clicked();

    void on_Modif_clicked();

    void on_pushButton_4_clicked();

    void on_genpdf_clicked();

    void on_pede_clicked();

    void on_mail_2_clicked();

    void on_pushButton_2_clicked();

    void on_Ajouter_2_clicked();

private:
    Ui::MainWindow *ui;
    contrat pimp;
};
#endif // MAINWINDOW_H
