#ifndef PROPRIETE_H
#define PROPRIETE_H
#include <QString>
#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>

class propriete {
    int Matricule, Cin_prop, status, type;
    float prix;
    QString Nom_prop, Prenom_prop, Adresse, Description;

public:
    //constructors
    propriete(){}
    propriete(int, QString, QString, int, QString, QString, float, int, int);

    //getters
    int getMatricule(){return Matricule;}
    QString getNom(){return Nom_prop;}
    QString getPrenom(){return Prenom_prop;}
    int getCin(){return Cin_prop;}
    QString getAdresse(){return Adresse;}
    QString getDescription(){return Description;}
    float getPrix(){return prix;}
    int getstatus(){return status;}
    int getType(){return type;}

    //setters
    void setMatricule(int m){Matricule=m;}
    void setNom(QString n){Nom_prop=n;}
    void setPrenom(QString p){Prenom_prop=p;}
    void setCin(int cin){Cin_prop=cin;}
    void setAdresse(QString adr){Adresse=adr;}
    void setDescription(QString desc){Description=desc;}
    void setPrix(float price){prix=price;}
    void setstatus(int stat){status=stat;}
    void setType(int tp){type=tp;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);

};

#endif // PROPRIETE_H
