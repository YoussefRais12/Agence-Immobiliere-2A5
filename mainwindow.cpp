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

using namespace std;
int status, v;

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


void MainWindow::on_Ajouter_clicked()
{
    int matricule=ui->Matricule->text().toInt();
    QString nom=ui->Nomprop->text();
    QString prenom=ui->prenomprop->text();
    int cin=ui->cin->text().toInt();
    QString adresse=ui->adresse->text();
    QString description=ui->description->text();
    float prix=ui->price->text().toFloat();
    if (ui->checkBox->isChecked())
        status=1;
                else status=0;

    if (ui->radioButton->isChecked()){
        v=1;
    } else if(ui->radioButton_2->isChecked()){
        v=0;
    } else QMessageBox::information(this,"Type","select type please");

    propriete p(matricule,nom,prenom,cin,v,adresse,description,prix,status);

    bool test=p.ajouter();

    if (test){
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("ajout effectue\n"),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("ajout non effectue\n"),QMessageBox::Cancel);

}






