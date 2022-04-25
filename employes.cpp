#include "employes.h"
#include "ui_employes.h"
#include "employe.h"
#include "connection.h"
#include<QIntValidator>
#include<QDesktopServices>
#include<QFileDialog>
#include <QPushButton>
#include "mainwindow.h"
#include "historique.h"
#include <QDebug>
#include <QApplication>
#include"historique.h"
#include <QListWidget>
#include "QString"
#include "QDate"
#include "transaction.h"
#include<QMessageBox>
#include <iostream>
#include <QTabWidget>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QFile>
#include <QTextStream>
#include <QObject>
#include <QTableView>
#include <QStringList>
#include <QFileDialog>
#include <QTextEdit>
#include "exportexcelobject.h"

employes::employes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::employes)
{
    ui->setupUi(this);

      /* QListWidgetItem *item3 =new QListWidgetItem(QIcon(""),"gestion des Agences");
       ui->listWidget->addItem(item3);
       QListWidgetItem *item4 =new QListWidgetItem(QIcon(""),"gestion des Produits");
       ui->listWidget->addItem(item4);
*/
   ui->tableView->setModel(Etmp.afficher());
    popUp = new PopUp();
    ui->comboBox->setModel(Etmp.comboBoxemployes());
    ui->comboboxmodif->setModel(Etmp.comboBoxemployes());

    ui->tableView_2->setModel(t.afficher());

}

employes::~employes()
{
    delete ui;
}

void employes::on_pushButton_ajouter_clicked()
{
    int id=ui->lineEdit->text().toInt();
    QString telephones=ui->lineEdit_Telephone->text();
    QString idd=ui->lineEdit->text();
    QString prenom=ui->lineEdit_Prenom->text();
    QString nom=ui->lineEdit_Nom->text();
    QString adresse=ui->lineEdit_Agence->text();
    QString telephone=ui->lineEdit_Telephone->text();
    QString agence=ui->lineEdit_Agence->text();
    QString role=ui->lineEdit_Role->text();
    QString user=ui->ajoutnom->text();
    employe E(id,prenom,nom,adresse,telephone,agence,role);



    QString mdp=ui->ajoutmdp->text();
    QString nomm=ui->ajoutnom->text();



     employe P(nomm,mdp,id);
     int idverif=0,i;
     if (telephone.length()==8){
                 for (i=0;i<=telephone.length();i++){
                     if (telephone[i]>='0' && telephone[i]<="9"){
                         idverif+=1;
                     }
                 }
              }
     if(idd.isEmpty() || prenom.isEmpty() || nom.isEmpty() || adresse.isEmpty() || telephones.isEmpty() || agence.isEmpty() || role.isEmpty() || user.isEmpty() || mdp.isEmpty()   )
                      {
                          QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("Saisir les champs ."),QMessageBox::Cancel);
                      }
     else {


      if (idd.length()!=5){
         QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("ID doit etre 5 chiffres ."),QMessageBox::Cancel);

     }

         else if (telephone.length()!=8){
             QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("La longuere de num ne depasse pas 8 chiffres ."),QMessageBox::Cancel);
         }
         else if (idverif!=telephone.length()){
             QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("Num doit contient seulement des chiffres ."),QMessageBox::Cancel);

         }

     else
     {
    bool test1=P.ajouter2();
    bool test=E.ajouter(user);


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



    popUp->setPopupText(" un employe a ete ajouté !!");

    popUp->show();
}
}
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
    popUp->setPopupText(" un employe a ete supprimé !!");

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
    popUp->setPopupText(" un employe a ete modifié !!");

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
        ui->tableView->setModel(Etmp.tri_ide());
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



void employes::on_tri_prenom_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
         QObject::tr("tri effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(Etmp.tri_prenom());
}



void employes::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString s = ui->listWidget->currentItem()->text();
    if (s=="Employes"){
        ui->page->show();
        ui->page_2->hide();
    }
    else if(s=="Transactions")
    {
            ui->page->hide();
            ui->page_2->show();

        }

}

void employes::on_pushButton_4_clicked()
{
    QString montanttest=ui->montant_transaction->text();
    QString debittest=ui->debit_transaction->text();

    QString ID_TRANSACTION=ui->id_transaction->text();
    QString DATE = ui->date_transaction->date().toString();
    QString MONTANT=ui->montant_transaction->text();
    int DEBIT_CREDIT=ui->debit_transaction->text().toInt();
    QString DESCRIPTION=ui->description_transaction->text();



    transactions t(ID_TRANSACTION,DATE,MONTANT,DESCRIPTION,DEBIT_CREDIT);

    if(ID_TRANSACTION.isEmpty() || montanttest.isEmpty() || debittest.isEmpty() || DESCRIPTION.isEmpty())
                     {
                         QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("Saisir les champs ."),QMessageBox::Cancel);
                     }
    else{
        int idverif=0,i;

        if (ID_TRANSACTION.length()<=8){
           for (i=0;i<=ID_TRANSACTION.length();i++){
               if (ID_TRANSACTION[i]>='0' && ID_TRANSACTION[i]<="9"){
                   idverif+=1;
               }
           }
        }
        if (ID_TRANSACTION.length()>8){
            QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("La longuere de ID transaction ne depasse pas 8 chiffres ."),QMessageBox::Cancel);
        }
        else if (idverif!=ID_TRANSACTION.length()){
            QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("ID transaction doit contient seulement des chiffres ."),QMessageBox::Cancel);

        }



        else if (debittest.length()!=1){
            QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("Debit credit doit 0 ou 1  ."),QMessageBox::Cancel);
        }
        else {

    bool test=t.Ajouter();
        if (test){
            QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("ajout effectue\n"),QMessageBox::Cancel);
            ui->tableView_2->setModel(t.afficher());


        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("ajout non effectue\n"),QMessageBox::Cancel);
}

}
}

void employes::on_pushButton_12_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
      QString sql;
      sql = "select ID_T From TRANSACTION";
      QSqlDatabase db = QSqlDatabase::database("QODBC");
      QSqlQuery* query=new QSqlQuery(db);
      query->exec(sql);
      model->setQuery(*query);
      qDebug() <<model ;
      ui->comboboxmodif_2->setModel(model);
}


void employes::on_pushButton_15_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
      QString sql;
      sql = "select ID_T From TRANSACTION";
      QSqlDatabase db = QSqlDatabase::database("QODBC");
      QSqlQuery* query=new QSqlQuery(db);
      query->exec(sql);
      model->setQuery(*query);
      ui->comboboxsup->setModel(model);
}


void employes::on_pushButton_14_clicked()
{
    QString idtest=ui->comboboxsup->currentText();

    int ID=ui->comboboxsup->currentText().toInt();
    if (idtest.isEmpty()){
        QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("Saisir le champ ID ."),QMessageBox::Cancel);
    }
    else {
   bool test=t.supprimer(ID);

       if (test){
           QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectue\n"),QMessageBox::Cancel);
           ui->tableView_2->setModel(t.afficher());

       }
       else
           QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("Suppression non effectue\n"),QMessageBox::Cancel);
}
}

void employes::on_pushButton_8_clicked()
{
    QString debittest=ui->debit_transaction_2->text();
    QString idtest=ui->comboboxmodif_2->currentText();

    QString ID=ui->comboboxmodif_2->currentText();
    QString DATE = ui->date_transaction_2->date().toString();
    QString MONTANT=ui->montant_transaction_2->text();
    int DEBIT_CREDIT=ui->debit_transaction_2->text().toInt();
    QString DESCRIPTION=ui->description_transaction_2->text();

    transactions t(ID,DATE,MONTANT,DESCRIPTION,DEBIT_CREDIT);
    if(MONTANT.isEmpty() || debittest.isEmpty() || DESCRIPTION.isEmpty() || idtest.isEmpty())
                     {
        qDebug()<<"ID : "<<ID ;
        qDebug()<<"DATE : "<<DATE ;
        qDebug()<<"Debit  : "<<DEBIT_CREDIT ;
        qDebug()<<"montant : "<<MONTANT ;
                         QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("Saisir les champs ."),QMessageBox::Cancel);
                     }
    else {
         if ((DEBIT_CREDIT!=0) && (DEBIT_CREDIT!=1)){
            QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("Debit credit doit 0 ou 1  ."),QMessageBox::Cancel);
        }
         else {
    bool test=t.modifier();

        if (test){
            QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Mis à jour effectue\n"),QMessageBox::Cancel);
            ui->tableView_2->setModel(t.afficher());

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("Mis à jour ne pas effectue\n"),QMessageBox::Cancel);
}
}
}

void employes::on_pushButton_6_clicked()
{
    ui->montant_transaction_2->clear();
    ui->description_transaction_2->clear();
    ui->debit_transaction_2->clear();
}


void employes::on_pushButton_5_clicked()
{
    ui->id_transaction->clear();
    ui->montant_transaction->clear();
    ui->description_transaction->clear();
    ui->debit_transaction->clear();
}


void employes::on_pushButton_32_clicked()
{
    int who;
    QString a=ui->combo_rech->currentText();
    if (a=="ID"){
      who=1;
    }
    else if (a=="Montant"){
        who=2;
    }
    else if (a=="Description"){
        who=3;
    }
    QString b=ui->who_rech->text();
    ui->tableView2->setModel(t.recherche(b,who));
}


void employes::on_pushButton_34_clicked()
{
    int w,m ;
    QString a=ui->combo_tri->currentText();
    QString b=ui->combo_tri_mode->currentText();
    if (a=="ID"){
      w=1;
    }
    else if (a=="Description"){
        w=2;
    }
    else if (a=="Debit_Credit"){
        w=3;
    }
    if (b=="Croissant"){
        m=1;
    }
    else {
        m=0;
    }

    ui->tableView3->setModel(t.tri(w,m));
}


void employes::on_pushButton_16_clicked()
{
    QFile file("historique2.txt");
    if(!file.open(QIODevice::ReadOnly)){
        qCritical() << "file not found ";
        qCritical() << file.errorString();

    }
    QTextStream in(&file);
    ui->textBrowser->setText(in.readAll());
}

void employes::on_pushButton_38_clicked()
{
    float a =0,b=0,max_t0=0,max_t1=0,min_t0=0,min_t1=0,c=0,s0=0,s1=0;int nb_t,debit0,debit1;
    QSqlQuery query,query2;
    query.prepare("SELECT MONTANT_T FROM TRANSACTION WHERE DEBIT_CREDIT = 1");
    query.exec();
    while(query.next()) {
        QString stock = query.value(0).toString();
        a =a+stock.toFloat();

    }
    query.prepare("SELECT MONTANT_T FROM TRANSACTION WHERE DEBIT_CREDIT = 0");
    query.exec();
    while(query.next()) {
        QString stock = query.value(0).toString();
        b =b+stock.toFloat();

    }


    query.prepare("SELECT count(*) FROM TRANSACTION ");
    query.exec();
    if(query.next()){
        nb_t= query.value(0).toInt();
    }
    query.prepare("SELECT count (MONTANT_T) FROM TRANSACTION where DEBIT_CREDIT= 0 ");
    query.exec();
    if(query.next()){
        debit0= query.value(0).toInt();
    }
    query.prepare("SELECT count (MONTANT_T) FROM TRANSACTION where DEBIT_CREDIT= 1 ");
    query.exec();
    if(query.next()){
        debit1= query.value(0).toInt();
    }

    query.prepare("SELECT MONTANT_T FROM TRANSACTION where DEBIT_CREDIT= 0 ");
    query.exec();
    while(query.next()){
        c= query.value(0).toFloat();
        if (max_t0<c){
            max_t0=c;
            min_t0=c;
        }
    }
    query2.prepare("SELECT MONTANT_T FROM TRANSACTION where DEBIT_CREDIT= 0 ");
    query2.exec();

    while(query2.next()){
        c= query2.value(0).toFloat();
        if (min_t0>c){
            min_t0=c;
        }
    }




    query.prepare("SELECT MONTANT_T FROM TRANSACTION where DEBIT_CREDIT= 1 ");
    query.exec();
    while(query.next()){
        c= query.value(0).toFloat();
        if (max_t1<c){
            max_t1=c;
            min_t1=c;
        }
    }
    query2.prepare("SELECT MONTANT_T FROM TRANSACTION where DEBIT_CREDIT= 1 ");
    query2.exec();
    while(query2.next()){
        c= query2.value(0).toFloat();
        if (min_t1>c){
            min_t1=c;
        }
    }
    query.prepare("SELECT MONTANT_T FROM TRANSACTION where DEBIT_CREDIT= 0 ");
    query.exec();
    while(query.next()){
        s0+= query.value(0).toFloat();

    }
    query.prepare("SELECT MONTANT_T FROM TRANSACTION where DEBIT_CREDIT= 1 ");
    query.exec();
    while(query.next()){
        s1+= query.value(0).toFloat();

    }




    /*qDebug() << a ;
    qDebug() << b ;
    qDebug() << "le nombre des transactions : "<<nb_t;
    qDebug() <<debit1<< "Transactions de debit credit 1 ( somme ="<<s1<< ")";
    qDebug() <<debit0<< "Transaction de debit credit 0 ( somme ="<<s0<< ")";
    qDebug() <<"la transaction maximale de debit '0' " <<max_t0<<"DT";
    qDebug() <<"la transaction minimale de debit '0' " <<min_t0<<"DT";
    qDebug() <<"la transaction maximale de debit '1' " <<max_t1<<"DT";
    qDebug() <<"la transaction minimale de debit '1' " <<min_t1<<"DT";*/
    float r=a-b;
    QString snb_t = QString::number(nb_t);
    QString smax_t0 = QString::number(max_t0);
    QString smax_t1 = QString::number(max_t1);
    QString smin_t0 = QString::number(min_t0);
    QString smin_t1 = QString::number(min_t1);
    QString ss1 = QString::number(s1);
    QString sdebit0 = QString::number(debit0);
    QString sdebit1 = QString::number(debit1);
    QString ss0 = QString::number(s0);
    QString sr = QString::number(r);
    ui->textEdit->setReadOnly(true);
    ui->textEdit->append("[ * ] Le nombre des transactions : "+snb_t+"\n" );
    ui->textEdit->append("[ * ] "+sdebit1+" Transaction de debit credit ' 1 ' ( somme = "+ss1+ " DT)\n");
    ui->textEdit->append("[ * ] "+sdebit0+" Transaction de debit credit ' 0 ' ( somme = "+ss0+ " DT)\n");
    ui->textEdit->append("[ * ] La transaction maximale de debit credit ' 0 ' : " +smax_t0+" DT\n");
    ui->textEdit->append("[ * ] La transaction minimale de debit credit ' 0 ' : " +smin_t0+" DT\n");
    ui->textEdit->append("[ * ] La transaction maximale de debit credit ' 1 ' : " +smax_t1+" DT\n");
    ui->textEdit->append("[ * ] La transaction minimale de debit credit ' 1 ' : " +smin_t1+" DT\n");

    //QString astring=QString::number(a);
    if (a<b){
        ui->textEdit->append("[ - ] Aucun gain dans les transactions\n ");
    }
    else if (a>b){
        ui->textEdit->append("[ + ] Votre gain est :  "+sr+" DT\n ");
    }

ui->textEdit->append("[ ------------------------------------------------------------- ]");

}


void employes::on_pushButton_29_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->tableView);

    obj.addField(0, "ID_T", "char(20)");
    obj.addField(1, "DATE_T", "char(20)");
    obj.addField(2, "MONTANT_T", "char(20)");
    obj.addField(3, "DESCRIPTION_T", "char(20)");
    obj.addField(4, "DEBIT_CREDIT", "char(20)");




    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 Transactions a été enregistrée !")).arg(retVal)
                                 );
    }
}

void employes::on_pushButton_31_clicked()
{
     ui->who_rech->clear();
}

void employes::on_pushButton_7_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
      QString sql;
      sql = "select NUMERO_CONTRAT From CONTRAT";
      QSqlDatabase db = QSqlDatabase::database("QODBC");
      QSqlQuery* query=new QSqlQuery(db);
      query->exec(sql);
      model->setQuery(*query);
      qDebug() << model ;
      ui->comboboxajout->setModel(model);
}

void employes::on_pushButton_9_clicked()
{
    QSqlQuery query;QString a,b ;
    a=ui->comboboxajout->currentText();
   //qDebug()<<"a= "<<a;
    query.prepare("SELECT CONTENU,PRIXFINAL FROM CONTRAT where NUMERO_CONTRAT=? ");
     query.addBindValue(a);
    query.exec();
    while(query.next()){
    a=query.value(0).toString();
     b=query.value(1).toString();
   /* qDebug()<<"a= "<<a;
    qDebug()<<"b= "<<b;*/
    }
    ui->description_transaction->setText(a);
    ui->montant_transaction->setText(b);
    ui->debit_transaction->setText("1");
}


void employes::on_pushButton_10_clicked()
{
    QSqlQuery query;QString a,b,c ;
    a=ui->comboboxmodif_2->currentText();
   //qDebug()<<"a= "<<a;
    query.prepare("SELECT MONTANT_T,DESCRIPTION_T,DEBIT_CREDIT from transaction WHERE ID_T=? ");
     query.addBindValue(a);
    query.exec();
    while(query.next()){
    a=query.value(0).toString();
     b=query.value(1).toString();
     c=query.value(2).toString();
    //qDebug()<<"a= "<<a;
    //qDebug()<<"b= "<<b;
    }
    ui->montant_transaction_2->setText(a);
    ui->description_transaction_2->setText(b);
    ui->debit_transaction_2->setText(c);

}

