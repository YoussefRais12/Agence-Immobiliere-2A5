#include "transactions.h"
#include "ui_transactions.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "transactions.h"
#include <iostream>
#include <string>
#include <QFile>
#include <QTextStream>
#include <QDebug>
using namespace std;
transactions::transactions()
{

}
transactions::transactions(QString ID_TRANSACTION,QString DATE,QString MONTANT, QString DESCRIPTION,int DEBIT_CREDIT)
{
    this-> ID=ID_TRANSACTION;
    this-> DESCRIPTION=DESCRIPTION;
    this-> MONTANT=MONTANT;
    this-> DATE=DATE;
    this-> DEBIT_CREDIT=DEBIT_CREDIT;
}
bool transactions::Ajouter()
{
    QSqlQuery query;
    //QString resid= QString::number(ID);
    QString resdebit= QString::number(DEBIT_CREDIT);
    query.prepare("insert into TRANSACTION (ID_T,DATE_T,MONTANT_T,DESCRIPTION_T,DEBIT_CREDIT)" "values (:ID,:DATE,:MONTANT,:DESCRIPTION,:DEBIT_CREDIT)");
    query.bindValue(":ID", ID);
    query.bindValue(":DATE", DATE);
    query.bindValue(":MONTANT", MONTANT);
    query.bindValue(":DESCRIPTION", DESCRIPTION);
    query.bindValue(":DEBIT_CREDIT",resdebit);
    if(query.exec())
   {
        // fichier historique ajout
        QFile file("historique.txt");
        if(!file.open(QIODevice::Append)){
            qCritical() << "file not found ";
            qCritical() << file.errorString();

        }
        //qInfo() << "writing file ..";
        QTextStream stream(&file);
        stream << QString() << "ID : " << ID << "\n";
        stream << QString() << "Date : " << DATE<< "\n";
        stream << QString() << "Montant : " << MONTANT<< "\n";
        stream << QString() << "Description : " << DESCRIPTION<< "\n";
        stream << QString() << "Debit : " << resdebit<< "\n";
        stream << QString() <<"---------------------------------\n";

        file.close();
    qDebug()<<" la transaction a été ajoutée!!\n";
}
 else{ qDebug()<<" Error d'ajout !!\n";
}
}
QSqlQueryModel * transactions::afficher()
{
    QSqlQuery query;
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from TRANSACTION");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Debit credit"));
    return model;
}

bool transactions::supprimer(int ID)
{
    QSqlQuery query;
    QString resid= QString::number(ID);
    query.prepare("delete from TRANSACTION where ID_T = :id");
    query.bindValue(":id", ID);
    return query.exec();
}

bool transactions::modifier()
{
    QSqlQuery query ;
    //QString resid= QString::number(ID);
    QString resdebit= QString::number(DEBIT_CREDIT);
       query.prepare("update  TRANSACTION    set  DATE_T=:DATE,MONTANT_T=:MONTANT,DESCRIPTION_T=:DESCRIPTION,DEBIT_CREDIT=:DEBIT_CREDIT where(ID_T=:ID)");
       query.bindValue(":ID", ID);
       query.bindValue(":DATE", DATE);
       query.bindValue(":MONTANT", MONTANT);
       query.bindValue(":DESCRIPTION", DESCRIPTION);
       query.bindValue(":DEBIT_CREDIT",resdebit);

       if(query.exec())
      {


       qDebug()<<" Mis a jour effectuer!!\n";
   }

    else{ qDebug()<<" Echec de la mis a jour!!\n";
}
}
QSqlQueryModel * transactions::recherche(QString b,int who)
{

    QSqlQueryModel *a=new::QSqlQueryModel;
        if (who==1){
            a->setQuery("select * from  TRANSACTION where ID_T like '%"+b+"%'");
        }
        else if (who==2){
            a->setQuery("select * from  TRANSACTION where MONTANT_T like '%"+b+"%'");

        }
        else if (who==3){
            a->setQuery("select * from  TRANSACTION where DESCRIPTION_T like '%"+b+"%'");

        }


               return a;


}
QSqlQueryModel * transactions::tri(int a,int b)
{
    QSqlQueryModel * model= new QSqlQueryModel();
        if (a==1){
            if (b==1){
        model->setQuery("SELECT * FROM TRANSACTION ORDER BY ID_T ASC");
            }
            else {
              model->setQuery("SELECT * FROM TRANSACTION ORDER BY ID_T DESC");
            }
        }
        else if (a==2){
            if (b==1){
        model->setQuery("SELECT * FROM TRANSACTION ORDER BY DESCRIPTION_T ASC");
            }
            else {
              model->setQuery("SELECT * FROM TRANSACTION ORDER BY DESCRIPTION_T DESC");
            }
        }
        else if (a==3){
            if (b==1){
        model->setQuery("SELECT * FROM TRANSACTION ORDER BY DEBIT_CREDIT ASC");
            }
            else {
              model->setQuery("SELECT * FROM TRANSACTION ORDER BY DEBIT_CREDIT DESC");
            }
        }
        return model;
}




