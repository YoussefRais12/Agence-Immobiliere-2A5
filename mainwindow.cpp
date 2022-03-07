#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QDate"
#include "transactions.h"
#include<QMessageBox>
#include <iostream>
#include <QTabWidget>
#include <QMessageBox>
#include <QSqlQueryModel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   /* QStringList list=(QStringList()<<"red"<<"yellow"<<"blue");
    ui->combobox2->addItems(list);*/
   ui->tableView->setModel(t.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int ID_TRANSACTION=ui->id_transaction->text().toInt();
    QString DATE = ui->date_transaction->date().toString();
    float MONTANT=ui->montant_transaction->text().toFloat();
    int DEBIT_CREDIT=ui->debit_transaction->text().toInt();
    QString DESCRIPTION=ui->description_transaction->text();
    transactions t(ID_TRANSACTION,DATE,MONTANT,DESCRIPTION,DEBIT_CREDIT);

    bool test=t.Ajouter();

        if (test){
            QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("ajout effectue\n"),QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("ajout non effectue\n"),QMessageBox::Cancel);
}






void MainWindow::on_pushButton_8_clicked()
{
    int ID=ui->comboboxsup->currentText().toInt();
   bool test=t.supprimer(ID);

       if (test){
           QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectue\n"),QMessageBox::Cancel);
       }
       else
           QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("Suppression non effectue\n"),QMessageBox::Cancel);
}



void MainWindow::on_pushButton_4_clicked()
{
    int ID=ui->comboboxmodif->currentText().toInt();
    QString DATE = ui->date_transaction_2->date().toString();
    float MONTANT=ui->montant_transaction_2->text().toFloat();
    int DEBIT_CREDIT=ui->debit_transaction_2->text().toInt();
    QString DESCRIPTION=ui->description_transaction_2->text();
    transactions t(ID,DATE,MONTANT,DESCRIPTION,DEBIT_CREDIT);

    bool test=t.modifier();

        if (test){
            QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Mis à jour effectue\n"),QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("Mis à jour ne pas effectue\n"),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_11_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
      QString sql;
      sql = "select ID_T From TRANSACTION";
      QSqlDatabase db = QSqlDatabase::database("QODBC");
      QSqlQuery* query=new QSqlQuery(db);
      query->exec(sql);
      model->setQuery(*query);
      ui->comboboxsup->setModel(model);
}

void MainWindow::on_pushButton_12_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
      QString sql;
      sql = "select ID_T From TRANSACTION";
      QSqlDatabase db = QSqlDatabase::database("QODBC");
      QSqlQuery* query=new QSqlQuery(db);
      query->exec(sql);
      model->setQuery(*query);
      ui->comboboxmodif->setModel(model);
}
