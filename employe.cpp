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

bool employe::ajouter(QString user)
{
    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("insert into employe (id,NOM_UTILISATEUR,prenom,nom,adresse,telephone,agence,role)" " values (?,?,?,?,?,?,?,?)");

    query.addBindValue(res);
    query.addBindValue(user);
    query.addBindValue(prenom);
    query.addBindValue(nom);
    query.addBindValue(adresse);
    query.addBindValue(telephone);
    query.addBindValue(agence);
    query.addBindValue(role);

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
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Agence"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Telephone"));
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
employe::employe(QString nomuitlisateur,QString mdp,int id)
{

    this->nomuitlisateur=nomuitlisateur;
    this->mdp=mdp;
    this->id=id;

}
bool employe::ajouter2(){
    QSqlQuery query;


        query.prepare("insert into AUTHENTIFICATION (NOM_UTILISATEUR,ID,MDP)" "values(?,?,?)");

        query.addBindValue(nomuitlisateur);
        query.addBindValue(id);
        query.addBindValue(mdp);



          query.exec();
}
QSqlQueryModel * employe::tri_nom()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from employe order by nom");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Prenom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Telephone"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Agence"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("Role"));
    return model;
}

QSqlQueryModel * employe::tri_ide()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from employe order by ID");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Prenom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Telephone"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Agence"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("Role"));
    return model;
}
QSqlQueryModel * employe::tri_prenom()
{
    {QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from employe order by prenom");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_UTILISATEUR"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Telephone"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Agence"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Role"));
        return model;
        }

}
QSqlQueryModel * employe::recherche(QString  ch)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QSqlQuery query;
    model->setQuery("select * from employe where lower(cast(ID as varchar(20))) like lower(('"+ch+"%')) or lower(Nom) like lower(('"+ch+"%')) or lower(Prenom) like lower(('"+ch+"%')) ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Telephone"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Agence"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Role"));
    return model;
}
QSqlQueryModel * employe::comboBoxemployes()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select id  from employe");
        /*
         *
         *

*/
    return model;
}



