#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include <QDialog>
#include <QString>
#include <QtMath>
#include <QDate>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <iostream>
using namespace std;
class transactions
{
    int DEBIT_CREDIT;
    QString DATE,MONTANT,DESCRIPTION,ID;
public:
    transactions();
    transactions(QString ID_TRANSACTION,QString DATE,QString MONTANT,QString DESCRIPTION,int DEBIT_CREDIT );
    QSqlQueryModel *afficher();
    bool supprimer(int id);
    bool Ajouter();
    bool modifier();
    QSqlQueryModel *recherche(QString,int);
    QSqlQueryModel *tri(int,int);

};

#endif // TRANSACTIONS_H
