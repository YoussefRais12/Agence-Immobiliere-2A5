#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include "connection.h"
#include<QIntValidator>
#include<QMessageBox>
#include<QDesktopServices>
#include<QFileDialog>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_ajouter_clicked()
{
    int id=ui->lineEdit->text().toInt();
    QString prenom=ui->lineEdit_Prenom->text();
    QString nom=ui->lineEdit_Nom->text();
    QString adresse=ui->lineEdit_Agence->text();
    QString telephone=ui->lineEdit_Telephone->text();
    QString agence=ui->lineEdit_Agence->text();
    QString role=ui->lineEdit_Role->text();
    employe E(id,prenom,nom,adresse,telephone,agence,role);

    bool test=E.ajouter();
    if(test)
    {
         ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("ajout effectuer.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("ajout non effectuer.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);





}
void MainWindow::on_pushButton_supprimer_clicked()
{
    int id=ui->lineEdit_2->text().toInt();
    bool test=Etmp.supprimer(id);

    if(test)
    {
         ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("suppression effectuer.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("suppression non effectuer.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
void MainWindow::on_pushButton_modifier_clicked()
{
    //récupération des informations saisies
    int id=ui->lineEdit_3->text().toInt();
//    int id=ui->update_id->text().toInt();
//    e.setId(ui->update_id->text().toInt())
       QString prenom=ui->lineEdit_4->text();
       QString nom=ui->lineEdit_5->text();
       QString adresse=ui->lineEdit_6->text();
       QString telephone=ui->lineEdit_7->text();
        QString agence=ui->lineEdit_8->text();
         QString role=ui->lineEdit_9->text();
//    e.setNom(ui->new_nom->text());
//    e.setPrenom(ui->new_prenom->text());
//    etudiant e(id,nom,prenom);
    bool test=Etmp.modifier(id,prenom,nom,adresse,telephone,agence,role);
    if(test)
    {
        //REFRESH
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Modification effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Failed"),
                    QObject::tr("Modification non effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

