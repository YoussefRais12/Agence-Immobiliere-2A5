#include "dialog.h"
#include "ui_dialog.h"
#include "employe.h"
#include<QIntValidator>
#include<QMessageBox>
#include<QDesktopServices>
#include<QFileDialog>
#include <QPushButton>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->tableView->setModel(etmp.afficher());
    //ui->tableWidget->setModel(etmp.afficher());
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    int id=ui->lineEdit->text().toInt();
    QString nom=ui->lineEdit_2->text();
    QString prenom=ui->lineEdit_3->text();
    QString adresse=ui->lineEdit_4->text();
    QString telephone=ui->lineEdit_5->text();
    QString agence=ui->lineEdit_6->text();
    QString role=ui->lineEdit_7->text();
    employe E(id,nom,prenom,adresse,telephone,agence,role);

    bool test=E.ajouter();
ui->tableView->setModel(etmp.afficher());
    if(test){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("ajout effectuer.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("ajout non effectuer.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
ui->lineEdit->clear();
ui->lineEdit_2->clear();
ui->lineEdit_3->clear();
ui->lineEdit_4->clear();
ui->lineEdit_5->clear();
ui->lineEdit_6->clear();
ui->lineEdit_7->clear();

}

void Dialog::on_pushButton_2_clicked()
{
    int id=ui->lineEdit_4->text().toInt();
    bool test=etmp.supprimer(id);
    ui->tableView->setModel(etmp.afficher());
    if(test){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("suppression effectuer.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("suppression non effectuer.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    ui->lineEdit_4->clear();

}
