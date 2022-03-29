#include "transactions.h"
#include "ui_transactions.h"

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
transactions::transactions(int ID_TRANSACTION,QString DATE,QString MONTANT, QString DESCRIPTION,int DEBIT_CREDIT)
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
   // QString m=QString(MONTANT);
    QString resid= QString::number(ID);
    QString resdebit= QString::number(DEBIT_CREDIT);

    query.prepare("insert into TRANSACTION (ID_T,DATE_T,MONTANT_T,DESCRIPTION_T,DEBIT_CREDIT)" "values (:ID,:DATE,:MONTANT,:DESCRIPTION,:DEBIT_CREDIT)");
    query.bindValue(":ID", resid);
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
        stream << QString() << "ID : " << resid << "\n";
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
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from TRANSACTION");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_T"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_T"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("MONTANT_T"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESCRIPTION_T"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DEBIT_CREDIT"));
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
    QString resid= QString::number(ID);
    QString resdebit= QString::number(DEBIT_CREDIT);
       query.prepare("update  TRANSACTION    set  DATE_T=:DATE,MONTANT_T=:MONTANT,DESCRIPTION_T=:DESCRIPTION,DEBIT_CREDIT=:DEBIT_CREDIT where(ID_T=:ID)");
       query.bindValue(":ID", resid);
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
QSqlQueryModel * transactions::recherche(QString id)
{

    QSqlQueryModel *a=new::QSqlQueryModel;

        a->setQuery("select * from  TRANSACTION where ID_T like '%"+id+"%'");

               return a;


}
QSqlQueryModel * transactions::triasc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM TRANSACTION ORDER BY ID_T ASC");
        return model;
}
QSqlQueryModel * transactions::tridesc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM TRANSACTION ORDER BY ID_T DESC");
        return model;
}
/*float transactions::calculgain(){

    float a,b=0;
    QString c;
QString resdebit= QString::number(DEBIT_CREDIT);

QSqlQuery query1,query2;
query1.prepare("SELECT MONTANT_T FROM TRANSACTION WHERE DEBIT_CREDIT=:DEBIT_CREDIT");
query1.bindValue(":DEBIT_CREDIT",resdebit);


if(query1.exec())
{
QString c =query1.value(0).toString;

qDebug()<<" Mis a jour effectuer!!\n"<<c;
}

else{ qDebug()<<" Echec de la mis a jour!!\n";
}
query2.exec("SELECT MONTANT_T FROM TRANSACTION WHERE DEBIT_CREDIT=1");
while (query1.next()) {
      float a= query1.value(0).toFloat();
      //qDebug() << a ;
  }
while (query2.next()) {

      int b= b+ query2.value(0).toFloat();
      //qDebug() << a ;
  }
return a ;

}*/
