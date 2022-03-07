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
    int ID,DEBIT_CREDIT;
    QString DESCRIPTION;
    float MONTANT;
    QString DATE;
public:
    transactions();
    transactions(int ID_TRANSACTION,QString DATE,float MONTANT,QString DESCRIPTION,int DEBIT_CREDIT );
    QSqlQueryModel *afficher();
    bool supprimer(int id);
    bool Ajouter();
    bool modifier();

};

#endif // TRANSACTIONS_H
