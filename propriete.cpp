#include "propriete.h"
#include "ui_propriete.h"
#include <QString>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlResult>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QApplication>

propriete::propriete(int Matricule, QString Nom_prop, QString Prenom_prop, int Cin_prop, QString Adresse, QString Description, float prix, int status, int type){

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
    QString res_price = QString::number(prix);

    query.prepare("insert into Propriete (MATRICULE, NOM_PROP, PRENOM_PROP, CIN_PROP, ADRESSE, DESCRIPTION, STATUS, TYPE)" "values (:MATRICULE, :NOM_PROP, :PRENOM_PROP, :CIN_PROP, :ADRESSE, :DESCRIPTION,:STATUS, :TYPE)");

    query.bindValue(":MATRICULE", res);
    query.bindValue(":NOM_PROP", Nom_prop );
    query.bindValue(":PRENOM_PROP",Prenom_prop);
    query.bindValue(":CIN_PROP",res_cin);
    query.bindValue(":ADRESSE", Adresse);
    query.bindValue(":DESCRIPTION", Description);
    //query.bindValue(":PRIX", res_price);
    query.bindValue(":STATUS", res_status);
    query.bindValue(":TYPE",res_type);
    return query.exec();
}


QSqlQueryModel * propriete::afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from Propriete");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Matricule"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Description"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Prix"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Status"));

    return model;
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
    QString res_cin = QString::number(Cin_prop);
    QString res_status = QString::number(status);
    QString res_type = QString::number(type);
    QString res_price = QString::number(prix);
    query.prepare("UPDATE Propriete SET NOM_PROP='pppp' WHERE MATRICULE=32");
    //query.bindValue(":NOM_PROP", Nom_prop);
    /*query.bindValue(":PRENOM_PROP",Prenom_prop);
    query.bindValue(":CIN_PROP",res_cin);
    query.bindValue(":ADRESSE", Adresse);
    query.bindValue(":DESCRIPTION", Description);
    //query.bindValue(":PRIX", res_price);
    query.bindValue(":STATUS", res_status);
    */ //query.bindValue(":TYPE",res_type);
    return    query.exec();

}

