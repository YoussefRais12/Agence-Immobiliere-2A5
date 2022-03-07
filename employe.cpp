#include "employe.h"
#include <QDate>
#include <QDebug>
#include<QString>

employe::employe(int id,QString prenom,QString nom,QString adresse,QString telephone,QString agence,QString role)
{
    this->id=id;
    this->prenom=prenom;
    this->nom=nom;
    this->adresse=adresse;
    this->telephone=telephone;
    this->agence=agence;
    this->role=role;

}

bool employe::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("insert into employe (id,prenom,nom,adresse,telephone,agence,role)" " values (:id,:prenom,:nom,:adresse,:telephone,:agence,:role)");

    query.bindValue(0,res);
    query.bindValue(1,prenom);
    query.bindValue(2,nom);
    query.bindValue(3,adresse);
    query.bindValue(4,telephone);
    query.bindValue(5,agence);
    query.bindValue(6,role);

    return query.exec();
}

QSqlQueryModel * employe::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from employe");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Telephone"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Agence"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Role"));

    return model;
}

bool employe::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("delete from employe where ID=:id");
    query.bindValue(":id",res);
    return query.exec();
}
bool employe::modifier(int id,QString prenom,QString nom,QString adresse,QString telephone,QString agence,QString role)
{
    QSqlQuery query;

//    nom=getNom();
//    prenom=getPrenom();
    //prend la requête en paramètre pour préparer son execution
    query.prepare("update employe set id = :id, prenom= :prenom , nom= :nom, adresse= :adresse, telephone= :telephone, agence= :agence, role= :role where ID= :id");

    //creation des variables liées
    query.bindValue(":id",id);
    query.bindValue(":prenom",prenom);
    query.bindValue(":nom",nom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone", telephone);
    query.bindValue(":agence",agence);
    query.bindValue(":role",role);
    return query.exec(); //envoie la requete pour l'executer
}
