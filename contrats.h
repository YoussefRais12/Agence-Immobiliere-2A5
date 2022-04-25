#ifndef CONTRATS_H
#define CONTRATS_H
#include <QString>
#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QSortFilterProxyModel>

class contrat {
private:
    QString Nom_client, Prenom_client, contenu, telephone,date_s,prixfinal;
    int Numero_contrat, Cin_client, signe,type;

public:
    //constructors
    contrat(){};
    contrat(int, int, QString, QString, QString, int, int, QString,QString,QString);

    //getters
    int getNumero(){return Numero_contrat;}
    int getCin(){return Cin_client;}
    QString getNom(){return Nom_client;}
    QString getPrenom(){return Prenom_client;}
    QString getTel(){return telephone;}
    int getsigne(){return signe;}
    int getType(){return type;}
    QString getContenu(){return contenu;}
    QString getDate(){return date_s;}

    //setters
    void setNumero(int n){Numero_contrat=n;}
    void setCin(int carte){Cin_client=carte;}
    void setNom(QString nom){Nom_client=nom;}
    void setPrenom(QString prenom){Prenom_client=prenom;}
    void setTel(QString tel){telephone=tel;}
    void setsigne(int s){signe=s;}
    void setType(int t){type=t;}
    void setContenu(QString cont){contenu=cont;}
    void setdate(QString d){date_s=d;}

    bool ajouter();
    QSortFilterProxyModel * afficher();
    bool supprimer(int);
    bool modifier(int);

    bool rech(int);
    QSqlQueryModel* rechercher(QString);
    bool rechnom(QString);
    QSqlQueryModel* recherchernom(QString);
    bool rechcin(int);
    QSqlQueryModel* recherchercin(QString);
};




#endif // CONTRATS_H
