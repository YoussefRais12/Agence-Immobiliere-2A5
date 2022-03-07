#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class employe
{
protected:
    QString nom, prenom, adresse ,telephone, agence, role;
    int id;

public:
    //constructeur
    employe(){}
    employe(int,QString,QString,QString,QString,QString,QString);

    //Getters
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    QString getAdresse(){return adresse;}
    QString getTelephone(){return telephone;}
    QString getAgence(){return agence;}
    QString getRole(){return role;}
    int getId(){return id;}

    //setters
    void setNom(QString n){nom=n;}
    void setPrenom(QString p){prenom=p;}
    void setAdresse(QString a){adresse=a;}
    void setTelephone(QString t){telephone=t;}
    void setAgence(QString ag){agence=ag;}
    void setRole(QString r){role=r;}
    void setId(int id){this->id=id;}

    //fonctionnalites de base relatives a l'entite employe
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
     bool modifier(int,QString,QString,QString,QString,QString,QString);
};

#endif // EMPLOYE_H
