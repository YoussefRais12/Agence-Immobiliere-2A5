#include "employes.h"
#include "ui_employes.h"
#include "employe.h"
#include "connection.h"
#include<QIntValidator>
#include<QMessageBox>
#include<QDesktopServices>
#include<QFileDialog>
#include <QPushButton>
#include "mainwindow.h"
#include "historique.h"
#include <QDebug>
#include <QApplication>
#include"historique.h"
#include "arduino.h"



employes::employes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::employes)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher());
    popUp = new PopUp();
    ui->comboBox->setModel(Etmp.comboBoxemployes());
    ui->comboboxmodif->setModel(Etmp.comboBoxemployes());
    ui->lineEdit->setMaxLength(5);
    ui->lineEdit_Telephone->setMaxLength(8);
}


employes::~employes()
{
    delete ui;
}



void employes::on_pushButton_ajouter_clicked()
{
    int id=ui->lineEdit->text().toInt();
    QString prenom=ui->lineEdit_Prenom->text();
    QString nom=ui->lineEdit_Nom->text();
    QString adresse=ui->lineEdit_Agence->text();
    QString telephone=ui->lineEdit_Telephone->text();
    QString agence=ui->lineEdit_Agence->text();
    QString role=ui->lineEdit_Role->text();
    QString user=ui->ajoutnom->text();
    employe E(id,prenom,nom,adresse,telephone,agence,role);

    bool test=E.ajouter(user);

    QString mdp=ui->ajoutmdp->text();
    QString nomm=ui->ajoutnom->text();



     employe P(nomm,mdp,id);

    bool test1=P.ajouter2();

    if(test && test1)
    {
         ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("ajout effectuer.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
historique h;
h.save(prenom,nom);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("ajout non effectuer.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    popUp->setPopupText(" ajout effectué !!");

    popUp->show();

}
void employes::on_pushButton_supprimer_clicked()
{
    int id=ui->comboBox->currentText().toInt();
    QString idtest=ui->comboBox->currentText();

    if(idtest.isEmpty()){
        QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("Veuillez choisir un id  d'un employe à supprimer."),QMessageBox::Cancel);
    }
    else {
        MainWindow e;
bool test1=e.supprimerA(id);
    bool test=Etmp.supprimer(id);

    if(test && test1) {
        //refresh
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr(" suppression effectuer\n"),QMessageBox::Cancel);
        historique h;
        h.save2(idtest);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("suppression non effectuer\n"),QMessageBox::Cancel);

    }
}
    popUp->setPopupText(" suppression effectué !!");

    popUp->show();
}
void employes::on_pushButton_modifier_clicked()
{
    //récupération des informations saisies
   QString id=ui->comboboxmodif->currentText();
//    e.setId(ui->update_id->text().toInt())
       QString prenom=ui->lineEdit_4->text();
       QString nom=ui->lineEdit_5->text();
       QString adresse=ui->lineEdit_6->text();
       QString telephone=ui->lineEdit_7->text();
        QString agence=ui->lineEdit_8->text();
         QString role=ui->lineEdit_9->text();
//    e.setNom(ui->new_nom->text());
//    e.setPrenom(ui->new_prenom->text());
//    etudiant e(id,nom,prenom);
         int idint=id.toInt();
    bool test=Etmp.modifier(idint,prenom,nom,adresse,telephone,agence,role);
    if(test)
    {
        //REFRESH
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Modification effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        historique h;
        h.save1(prenom,nom);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Failed"),
                    QObject::tr("Modification non effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    popUp->setPopupText(" modification effectué !!");

    popUp->show();
}

void employes::on_tri_nom_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
         QObject::tr("tri effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(Etmp.tri_nom());

}

void employes::on_tri_id_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
         QObject::tr("tri effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(Etmp.tri_id());
}

void employes::on_lineEdit_rech_textEdited(const QString &arg1)
{
      ui->tableView->setModel(Etmp.recherche(ui->lineEdit_rech->text()));
}

void employes::on_pushButton_clicked()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QString sql;
    sql="select ID from EMPLOYE ";
QSqlDatabase db=QSqlDatabase::database("QODBC");
QSqlQuery *query=new QSqlQuery(db);
query->exec(sql);
model->setQuery(*query);
ui->comboboxmodif->setModel(model);

}

void employes::on_pushButton_2_clicked()
{
    QSqlQuery query;QString a,b,c,d,e,k ;
        a=ui->comboboxmodif->currentText();
       //qDebug()<<"a= "<<a;
        query.prepare("SELECT PRENOM,NOM,ADRESSE,TELEPHONE,AGENCE,ROLE from employe where ID=?  ");
         query.addBindValue(a);
        query.exec();
        while(query.next()){
         a=query.value(0).toString();
         b=query.value(1).toString();
         c=query.value(2).toString();
         d=query.value(3).toString();
         e=query.value(4).toString();
         k=query.value(5).toString();


       /* qDebug()<<"a= "<<a;
        qDebug()<<"b= "<<b;*/
        }
        ui->lineEdit_4->setText(a);
        ui->lineEdit_5->setText(b);
        ui->lineEdit_6->setText(c);
        ui->lineEdit_7->setText(d);
        ui->lineEdit_8->setText(e);
        ui->lineEdit_9->setText(k);
}

void employes::on_buttonafficher_clicked()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QString sql;
    sql="select ID from EMPLOYE ";
QSqlDatabase db=QSqlDatabase::database("QODBC");
QSqlQuery *query=new QSqlQuery(db);
query->exec(sql);
model->setQuery(*query);
ui->comboBox->setModel(model);
}

void employes::on_pushButton_3_clicked()
{
historique h;
QString his;
his=h.load();
qDebug()<<his;
ui->lineEdit_2->setText(his);
}

void employes::on_tri_pre_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
         QObject::tr("tri effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(Etmp.tri_prenom());
}
