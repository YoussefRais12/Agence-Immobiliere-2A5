#include "contrats.h"
//#include "ui_contrats.h"
#include <QString>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlResult>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QApplication>
#include <QSortFilterProxyModel>
#include <QAbstractTableModel>

contrat::contrat(int Numero_contrat, int Cin_client, QString Nom_client, QString Prenom_client, QString telephone, int signe, int type, QString contenu,QString date_s,QString prixfinal) {
    this->Numero_contrat=Numero_contrat;
    this->Cin_client=Cin_client;
    this->Nom_client=Nom_client;
    this->Prenom_client=Prenom_client;
    this->telephone=telephone;
    this->signe=signe;
    this->type=type;
    this->contenu=contenu;
    this->date_s=date_s;
    this->prixfinal=prixfinal;

}

bool contrat::ajouter(){
    QSqlQuery query;
    QString res = QString::number(Numero_contrat);
    QString res_cin = QString::number(Cin_client);
    QString res_signe = QString::number(signe);
    QString res_type = QString::number(type);
    query.prepare("insert into Contrat (NUMERO_CONTRAT, CIN_CLIENT, NOM_CLIENT, PRENOM_CLIENT, EMAIL_C, TELEPHONE, SIGNE, TYPE_CONTRAT, CONTENU,DATE_SIGNATURE,PRIXFINAL)" "values (:NUMERO_CONTRAT, :CIN_CLIENT, :NOM_CLIENT, :PRENOM_CLIENT, :EMAIL_C, :TELEPHONE,:SIGNE, :TYPE_CONTRAT, :CONTENU,:DATE_SIGNATURE,:prixfinal)");

    query.bindValue(":NUMERO_CONTRAT", res);
    query.bindValue(":CIN_CLIENT",res_cin);
    query.bindValue(":NOM_CLIENT", Nom_client );
    query.bindValue(":PRENOM_CLIENT",Prenom_client);
    query.bindValue(":TELEPHONE", telephone);
    query.bindValue(":SIGNE", res_signe);
    query.bindValue(":TYPE_CONTRAT",res_type);
    query.bindValue(":CONTENU",contenu);
    query.bindValue(":DATE_SIGNATURE",date_s);
    query.bindValue(":prixfinal",prixfinal);
    return query.exec();
}

bool contrat::supprimer(int Num) {
    QSqlQuery query;
    QString res= QString::number(Num);
    query.prepare("Delete from Contrat where NUMERO_CONTRAT=:Num ");
    query.bindValue(":Num", res);
    return query.exec();
}


QSortFilterProxyModel * contrat::afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(model);
    model->setQuery("select NUMERO_CONTRAT, CIN_CLIENT, NOM_CLIENT, PRENOM_CLIENT, TELEPHONE, SIGNE, TYPE_CONTRAT, CONTENU, DATE_SIGNATURE from Contrat");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Numero de contrat"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom "));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Telephone"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Signe"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Type_contrat"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Contenu"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Date Signature"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("Prix Final"));
    proxyModel->setSourceModel(model);
    return proxyModel;
}


bool contrat::modifier(int Num)
{
    QSqlQuery query;
    QString res= QString::number(Num);
    query.prepare("update Contrat set NOM_CLIENT=:NOM_CLIENT,PRENOM_CLIENT=:PRENOM_CLIENT,TELEPHONE=:telephone,CIN_CLIENT=:CIN_CLIENT  WHERE (NUMERO_CONTRAT=:Num)");
    query.bindValue(":Num", res);

    query.bindValue(":NOM_CLIENT", Nom_client);
    query.bindValue(":PRENOM_CLIENT", Prenom_client);
    query.bindValue(":telephone", telephone);

    if (query.exec()){
        qDebug()<<"updated";
    }
    else {
        qDebug()<<"not updated";
    }

}


bool contrat::rech(int x){
    QSqlQuery query;
    query.prepare("select NUMERO_CONTRAT, CIN_CLIENT, NOM_CLIENT, PRENOM_CLIENT, EMAIL_C, TELEPHONE, SIGNE, TYPE_CONTRAT, CONTENU, DATE_SIGNATURE from Contrat where NUMERO_CONTRAT = :numero;");
    query.bindValue(":numero", x);
    return query.exec();
}


QSqlQueryModel* contrat::rechercher(QString a) {

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select NUMERO_CONTRAT, CIN_CLIENT, NOM_CLIENT, PRENOM_CLIENT, EMAIL_C, TELEPHONE, SIGNE, TYPE_CONTRAT, CONTENU, DATE_SIGNATURE from Contrat where NUMERO_CONTRAT='"+a+"'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Numero_contrat"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom_client"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom_client"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Cin_client"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Email_c"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Telephone"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Signe"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Type_contrat"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Contenu"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("Date Signature"));
    return model;
}

bool contrat::rechnom(QString x){
    QSqlQuery query;
    query.prepare("select NUMERO_CONTRAT, CIN_CLIENT, NOM_CLIENT, PRENOM_CLIENT, EMAIL_C, TELEPHONE, SIGNE, TYPE_CONTRAT, CONTENU, DATE_SIGNATURE from Contrat where NOM_CLIENT = :nom;");
    query.bindValue(":nom", x);
    return query.exec();
}

QSqlQueryModel* contrat::recherchernom(QString a) {

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select NUMERO_CONTRAT, CIN_CLIENT, NOM_CLIENT, PRENOM_CLIENT, EMAIL_C, TELEPHONE, SIGNE, TYPE_CONTRAT, CONTENU, DATE_SIGNATURE from Contrat where NOM_CLIENT='"+a+"'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Numero_contrat"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom_client"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom_client"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Cin_client"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Email_c"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Telephone"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Signe"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Type_contrat"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Contenu"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("Date Signature"));
    return model;
}

bool contrat::rechcin(int x){
    QSqlQuery query;
    query.prepare("select NUMERO_CONTRAT, CIN_CLIENT, NOM_CLIENT, PRENOM_CLIENT, EMAIL_C, TELEPHONE, SIGNE, TYPE_CONTRAT, CONTENU, DATE_SIGNATURE from Contrat where CIN_CLIENT = :cin;");
    query.bindValue(":cin", x);
    return query.exec();
}

QSqlQueryModel* contrat::recherchercin(QString a) {

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select NUMERO_CONTRAT, CIN_CLIENT, NOM_CLIENT, PRENOM_CLIENT, EMAIL_C, TELEPHONE, SIGNE, TYPE_CONTRAT, CONTENU, DATE_SIGNATURE from Contrat where CIN_CLIENT='"+a+"'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Numero_contrat"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom_client"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom_client"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Cin_client"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Email_c"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Telephone"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Signe"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Type_contrat"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Contenu"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("Date Signature"));
    return model;
}














