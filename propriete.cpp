#include "propriete.h"
#include "ui_propriete.h"
#include <QString>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlResult>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QApplication>

propriete::propriete(int Matricule, QString Nom_prop, QString Prenom_prop, int Cin_prop, QString Adresse, QString Description, float prix, int status){

    this->Matricule=Matricule;
    this->Nom_prop=Nom_prop;
    this->Prenom_prop=Prenom_prop;
    this->Cin_prop=Cin_prop;
    this->Adresse=Adresse;
    this->Description=Description;
    this->prix=prix;
    this->status=status;
}


bool propriete::ajouter(){
    QSqlQuery query;
    query.prepare("insert into Propriete (MATRICULE, NOM_PROP, PRENOM_PROP, CIN_PROP, ADRESSE, PRIX, STATUS) values (:Matricule, :Nom_prop, :Prenom_prop, :Cin_prop, :Adresse, :Description, :prix, :status)");
    query.bindValue(":MATRICULE", Matricule);
    query.bindValue(":NOM_PROP", Nom_prop );
    query.bindValue(":PRENOM_PROP",Prenom_prop);
    query.bindValue(":CIN_PROP",Cin_prop);
    query.bindValue(":ADRESSE", Adresse);
    query.bindValue(":PRIX", prix);
    query.bindValue(":STATUS", status);

    return query.exec();
}

QSqlQueryModel * propriete::afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from propriete");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Matricule"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Description"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Prix"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Status"));

    return model;
}

bool propriete::supprimer(int Mat) {
    QSqlQuery query;
    QString res= QString::number(Mat);
    query.prepare("Delete from client where MATRICULE=:Mat ");
    query.bindValue(":Mat", res);
    return query.exec();
}





