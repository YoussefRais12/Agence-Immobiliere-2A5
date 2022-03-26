#ifndef PROPRIETE_H
#define PROPRIETE_H
#include <QString>
#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>

class propriete {
    int Matricule, Cin_prop, status, type;
    QString prix;
    QString Nom_prop, Prenom_prop, Adresse, Description;

public:
    //constructors
    propriete(){}
    propriete(int, QString, QString, int, QString, QString, QString, int, int);

    //getters
    int getMatricule(){return Matricule;}
    QString getNom(){return Nom_prop;}
    QString getPrenom(){return Prenom_prop;}
    int getCin(){return Cin_prop;}
    QString getAdresse(){return Adresse;}
    QString getDescription(){return Description;}
    QString getPrix(){return prix;}
    int getstatus(){return status;}
    int getType(){return type;}

    //setters
    void setMatricule(int m){Matricule=m;}
    void setNom(QString n){Nom_prop=n;}
    void setPrenom(QString p){Prenom_prop=p;}
    void setCin(int cin){Cin_prop=cin;}
    void setAdresse(QString adr){Adresse=adr;}
    void setDescription(QString desc){Description=desc;}
    void setPrix(QString price){prix=price;}
    void setstatus(int stat){status=stat;}
    void setType(int tp){type=tp;}

    bool ajouter();
    QSortFilterProxyModel * afficher();
    bool supprimer(int);
    bool modifier(int);

    bool rech(int);
    QSqlQueryModel* rechercher(QString);
    bool rechnom(QString);
    QSqlQueryModel* recherchernom(QString);
    bool rechmat(QString);
    QSqlQueryModel* recherchermat(QString);
    void statistique(QVector<double>* ticks);
    void statistique_1(QVector<double>* PlaceData);
    void statistique_2(QVector<double>* PlaceData);
    void statistique_3(QVector<double>* PlaceData);
    void statistique_4(QVector<double>* PlaceData);
};

#endif // PROPRIETE_H
