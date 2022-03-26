#include "propriete.h"
#include "ui_propriete.h"
#include <QString>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlResult>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QApplication>
#include <QSortFilterProxyModel>
#include <QAbstractTableModel>
#include "mainwindow.h"
#include <QVector>
#include "ui_mainwindow.h"

propriete::propriete(int Matricule, QString Nom_prop, QString Prenom_prop, int Cin_prop, QString Adresse, QString Description, QString prix, int status, int type){

    this->Matricule=Matricule;
    this->Nom_prop=Nom_prop;
    this->Prenom_prop=Prenom_prop;
    this->Cin_prop=Cin_prop;
    this->Adresse=Adresse;
    this->Description=Description;
    this->prix=prix;
    this->status=status;
    this->type=type;
}


bool propriete::ajouter(){
    QSqlQuery query;
    QString res = QString::number(Matricule);
    QString res_cin = QString::number(Cin_prop);
    QString res_status = QString::number(status);
    QString res_type = QString::number(type);

    query.prepare("insert into Propriete (MATRICULE, NOM_PROP, PRENOM_PROP, CIN_PROP, ADRESSE, DESCRIPTION,PRIX, STATUS, TYPE)" "values (:MATRICULE, :NOM_PROP, :PRENOM_PROP, :CIN_PROP, :ADRESSE, :DESCRIPTION,:PRIX, :STATUS, :TYPE)");

    query.bindValue(":MATRICULE", res);
    query.bindValue(":NOM_PROP", Nom_prop );
    query.bindValue(":PRENOM_PROP",Prenom_prop);
    query.bindValue(":CIN_PROP",res_cin);
    query.bindValue(":ADRESSE", Adresse);
    query.bindValue(":DESCRIPTION", Description);
    query.bindValue(":PRIX", prix);
    query.bindValue(":STATUS", res_status);
    query.bindValue(":TYPE",res_type);
    return query.exec();
}


QSortFilterProxyModel * propriete::afficher(){
    QSqlQueryModel * model=new QSqlQueryModel;
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(model);
    model->setQuery("select MATRICULE, NOM_PROP, PRENOM_PROP, CIN_PROP, ADRESSE, DESCRIPTION, PRIX, STATUS, TYPE from Propriete");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Matricule"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Description"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Prix"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("status"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Type"));
    proxyModel->setSourceModel(model);

    return proxyModel;
}

bool propriete::supprimer(int Mat) {
    QSqlQuery query;
    QString res= QString::number(Mat);
    query.prepare("Delete from Propriete where MATRICULE=:Mat ");
    query.bindValue(":Mat", res);
    return query.exec();
}

bool propriete::modifier(int Mat)
{
    QSqlQuery query;
    QString res= QString::number(Mat);
    //QString res_cin = QString::number(Cin_prop);
    QString res_status = QString::number(status);
    QString res_type = QString::number(type);
    query.prepare("update Propriete set NOM_PROP=:NOM_PROP WHERE (MATRICULE=:Mat)");
    query.bindValue(":Mat", res);
    //query.bindValue(":CIN_PROP",Cin_prop);
    query.bindValue(":NOM_PROP", Nom_prop);
    //query.bindValue(":PRENOM_PROP",Prenom_prop);
    //query.bindValue(":ADRESSE", Adresse);
    //query.bindValue(":DESCRIPTION", Description);
    //query.bindValue(":PRIX", res_price);
    //query.bindValue(":TYPE",res_type);
    //query.bindValue(":STATUS", res_status);
    return  query.exec();

}


bool propriete::rech(int x){
    QSqlQuery query;
    query.prepare("select MATRICULE, NOM_PROP, PRENOM_PROP, CIN_PROP, ADRESSE, DESCRIPTION, PRIX, STATUS, TYPE from PROPRIETE where CIN_PROP = :cin;");
    query.bindValue(":cin", x);
    return query.exec();
}


QSqlQueryModel* propriete::rechercher(QString a) {

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select MATRICULE, NOM_PROP, PRENOM_PROP, CIN_PROP, ADRESSE, DESCRIPTION, PRIX, STATUS, TYPE from Propriete where CIN_PROP='"+a+"'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Matricule"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Description"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Prix"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("status"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Type"));
    return model;
}

bool propriete::rechnom(QString x){
    QSqlQuery query;
    query.prepare("select MATRICULE, NOM_PROP, PRENOM_PROP, CIN_PROP, ADRESSE, DESCRIPTION, PRIX, STATUS, TYPE from PROPRIETE where NOM_PROP = :nom;");
    query.bindValue(":nom", x);
    return query.exec();
}


QSqlQueryModel * propriete::recherchernom(QString a){

    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select MATRICULE, NOM_PROP, PRENOM_PROP, CIN_PROP, ADRESSE, DESCRIPTION, PRIX, STATUS, TYPE from PROPRIETE where NOM_PROP ='"+a+"' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Matricule"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Description"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Prix"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("status"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Type"));
    return model;
}

bool propriete::rechmat(QString x){
    QSqlQuery query;
    query.prepare("select MATRICULE, NOM_PROP, PRENOM_PROP, CIN_PROP, ADRESSE, DESCRIPTION, PRIX, STATUS, TYPE from PROPRIETE where MATRICULE = :matricule;");
    query.bindValue(":matricule", x);
    return query.exec();
}

QSqlQueryModel * propriete::recherchermat(QString a){

    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select MATRICULE, NOM_PROP, PRENOM_PROP, CIN_PROP, ADRESSE, DESCRIPTION, PRIX, STATUS, TYPE from PROPRIETE where MATRICULE ='"+a+"' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Matricule"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Description"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Prix"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("status"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Type"));
    return model;
}

/*
void propriete::statistique(QVector<double>* PlaceData)
{
    QSqlQuery q;
    int i=0;
    q.exec("select PRIX from PROPRIETE");
    while (q.next())
    {
        if(q.value(0).toInt()>15)
            i++;
    }
    *PlaceData<< i;
}
void propriete::statistique_1(QVector<double>* PlaceData)
{
    QSqlQuery q;
    int i=0;
    q.exec("select PRIX from PROPRIETE");
    while (q.next())
    {
        if((q.value(0).toInt())>15&&(q.value(0).toInt()<25))
            i++;
    }
    *PlaceData<< i;
}
void propriete::statistique_2(QVector<double>* PlaceData)
{
    QSqlQuery q;
    int i=0;
    q.exec("select PRIX from PROPRIETE");
    while (q.next())
    {
        if((q.value(0).toInt())>25&&(q.value(0).toInt()<35))
            i++;
    }
    *PlaceData<< i;
}
void propriete::statistique_3(QVector<double>* PlaceData)
{
    QSqlQuery q;
    int i=0;
    q.exec("select PRIX from PROPRIETE");
    while (q.next())
    {
        if((q.value(0).toInt())>35&&(q.value(0).toInt()<45))
            i++;
    }
    *PlaceData<< i;
}
void propriete::statistique_4(QVector<double>* PlaceData)
{
    QSqlQuery q;
    int i=0;
    q.exec("select PRIX from PROPRIETE");
    while (q.next())
    {
        if(q.value(0).toInt()>45)
            i++;
    }
    *PlaceData<< i;
}
*/
