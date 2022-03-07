#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "propriete.h"
#include "connection.h"
#include <QString>
#include<QDateEdit>
#include<QMessageBox>
#include <iostream>
#include <QTabWidget>
#include <QMessageBox>
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(pimp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Ajouter_clicked()
{
    int matricule=ui->Matricule->text().toInt();
    QString nom=ui->Nomprop->text();
    QString prenom=ui->prenomprop->text();
    int cin=ui->cin->text().toInt();
    QString adresse=ui->adresse->text();
    QString description=ui->description->text();
    float prix=ui->price->text().toFloat();
    int status=ui->status->text().toInt();
    int type=ui->type->text().toInt();


    propriete p(matricule,nom,prenom,cin,adresse,description,prix,status,type);

    bool test=p.ajouter();

    if (test){
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("ajout effectue\n"),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("ajout non effectue\n"),QMessageBox::Cancel);

}




void MainWindow::on_confirmer_clicked()
{
    int Mat=ui->combo->currentText().toInt();
    bool test=pimp.supprimer(Mat);

    if(test) {
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr(" DELETED\n"),QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("Couldn't delete\n"),QMessageBox::Cancel);

    }
}


void MainWindow::on_pushButton_4_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString sql;
    sql = "select Matricule From Propriete";
    QSqlDatabase db = QSqlDatabase::database("QODBC");
    QSqlQuery* query=new QSqlQuery(db);
    query->exec(sql);
    model->setQuery(*query);
    ui->combo->setModel(model);
}




void MainWindow::on_pushButton_clicked()
{
    int Mat=ui->comboo->currentText().toInt();
    QString Nom=ui->nomprop->text();
    QString Prenom=ui->prenompropr->text();
    int Cin=ui->Cin_prop->text().toInt();
    QString Adresse=ui->adre->text();
    QString Description=ui->decri->text();
    int type=ui->typeprop->text().toInt();
    int status=ui->status_2->text().toInt();
    float price=ui->pri->text().toFloat();
    propriete p(Mat,Nom,Prenom,Cin,Adresse,Description,price,status,type);


    bool test=pimp.modifier(Mat);
    if(test) {
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr(" MODIFIED\n"),QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("Couldn't MODIFY\n"),QMessageBox::Cancel);

    }
}

void MainWindow::on_generer_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString sql;
    sql = "select Matricule From Propriete";
    QSqlDatabase db = QSqlDatabase::database("QODBC");
    QSqlQuery* query=new QSqlQuery(db);
    query->exec(sql);
    model->setQuery(*query);
    ui->comboo->setModel(model);
}
