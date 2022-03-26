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
#include <QSortFilterProxyModel>
#include "QrCode.hpp"
#include <QStandardItemModel>
#include <QLabel>
#include <QGeoAddress>
#include <QGeoCodingManager>
#include <QGeoCoordinate>
#include <QGeoLocation>
#include <QGeoServiceProvider>
#include <QApplication>

using namespace std;
using namespace qrcodegen;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/Map.qml")));
    ui->quickWidget->show();

    ui->tableView->setSortingEnabled(true); // enable sortingEnabled
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
    QString prix=ui->price->text();
    int status=ui->status->text().toInt();
    int type=ui->type->text().toInt();
    QString Matriculetest=ui->Matricule->text();
    QString cintest=ui->cin->text();
    QString pricetest=ui->price->text();
    QString statustest=ui->status->text();
    QString typetest=ui->type->text();

    propriete p(matricule,nom,prenom,cin,adresse,description,prix,status,type);

    if (Matriculetest.isEmpty() || nom.isEmpty() || prenom.isEmpty() || cintest.isEmpty() || adresse.isEmpty() ||
            description.isEmpty() || pricetest.isEmpty() || statustest.isEmpty() || typetest.isEmpty()) {

        QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("Il y a un champ vide"),QMessageBox::Cancel);

    }
    else {
        if (Matriculetest.length()!=8){
                    QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("La longueure de la matricule n'a pas 8 chiffres ."),QMessageBox::Cancel);
                }
    else if((status!=0) && (status!=1)) {
            QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr(" status doit etre 0 ou 1. 1 si logé sinon 0"),QMessageBox::Cancel);
        }
        else if(cintest.length()!=8) {
                QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr(" CIN doit avoir 8 chiffres"),QMessageBox::Cancel);
            }
        else {


    bool test=p.ajouter();

    if (test){
        //refresh
        ui->tableView->setModel(pimp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("ajout effectue\n"),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("ajout non effectue\n"),QMessageBox::Cancel);

        }
}
}

void MainWindow::on_confirmer_clicked()
{
    int Mat=ui->combo->currentText().toInt();
    QString Matriculetest=ui->combo->currentText();

    if(Matriculetest.isEmpty()){
        QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("Veuillez choisir une matricule d'une propriete à supprimer."),QMessageBox::Cancel);
    }
    else {

    bool test=pimp.supprimer(Mat);

    if(test) {
        //refresh
        ui->tableView->setModel(pimp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr(" DELETED\n"),QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("Couldn't delete\n"),QMessageBox::Cancel);

    }
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
    int Cin_prop=ui->carte->text().toInt();
    QString Adresse=ui->adre->text();
    QString Description=ui->decri->text();
    int type=ui->typeprop->text().toInt();
    int status=ui->status_2->text().toInt();
    QString price=ui->pri->text();
    propriete p(Mat,Nom,Prenom,Cin_prop,Adresse,Description,price,status,type);


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

    QSqlQueryModel *model1 = new QSqlQueryModel();
    QString sql1;
    sql1 = "select Matricule From Propriete";
    query->exec(sql1);
    model1->setQuery(*query);
    ui->combo->setModel(model1);
}



void MainWindow::on_pushButton_2_clicked()
{
    propriete p;
    QString choix=ui->comboBox->currentText();

    if (choix=="Cin"){
       QString cin=ui->chercher->text();
       ui->tableView->setModel(p.rechercher(cin));
    }

    if (choix=="Nom"){
        QString nom=ui->chercher->text();
        ui->tableView->setModel(p.recherchernom(nom));
    }

    if (choix=="Matricule") {
        QString matricule=ui->chercher->text();
        ui->tableView->setModel(p.recherchermat(matricule));
    }

}



void MainWindow::on_qrpushbutton_clicked()
{

            QVariant cinn=ui->Matricule->text().toInt();
            int matricule= cinn.toInt();

            QString cine;
            cine=int(matricule);
            cine="matricule: "+cine;
            QrCode qr = QrCode::encodeText(cine.toUtf8().constData(), QrCode::Ecc::HIGH);

            // Read the black & white pixels
            QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
            for (int y = 0; y < qr.getSize(); y++) {
                for (int x = 0; x < qr.getSize(); x++) {
                    int color = qr.getModule(x, y);  // 0 for white, 1 for black

                    // You need to modify this part
                    if(color==0)
                        im.setPixel(x, y,qRgb(254, 254, 254));
                    else
                        im.setPixel(x, y,qRgb(0, 0, 0));
                }
            }
            im=im.scaled(200,200);
            ui->qrlabel->setPixmap(QPixmap::fromImage(im));
            int i=0 ;
            for(i=0;i<100;i=i+0.1){
                i++;
                ui->progressBar->setValue(i);
            }
}

void MainWindow::on_map_clicked()
{

}
