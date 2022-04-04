#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QDate"
#include "transactions.h"
#include<QMessageBox>
#include <iostream>
#include <QTabWidget>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QObject>
#include <QTableView>
#include <QStringList>
#include <QFileDialog>
#include <QTextEdit>
#include "exportexcelobject.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   ui->tableView->setModel(t.afficher());
   ui->id_transaction->setValidator( new QIntValidator(11111111, 99999999, this) );
   ui->debit_transaction->setValidator( new QIntValidator(0, 1, this) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{


    QString idtest=ui->id_transaction->text();
    QString montanttest=ui->montant_transaction->text();
    QString debittest=ui->debit_transaction->text();

    int ID_TRANSACTION=ui->id_transaction->text().toInt();
    QString DATE = ui->date_transaction->date().toString();
    QString MONTANT=ui->montant_transaction->text();
    int DEBIT_CREDIT=ui->debit_transaction->text().toInt();
    QString DESCRIPTION=ui->description_transaction->text();



    transactions t(ID_TRANSACTION,DATE,MONTANT,DESCRIPTION,DEBIT_CREDIT);

    if(idtest.isEmpty() || montanttest.isEmpty() || debittest.isEmpty() || DESCRIPTION.isEmpty())
                     {
                         QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("Saisir les champs ."),QMessageBox::Cancel);
                     }
    else{
        if (idtest.length()!=8){
            QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("La longuere de ID transaction doit étre de 8 chiffres ."),QMessageBox::Cancel);
        }
        else if (debittest.length()!=1){
            QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("Debit credit doit 0 ou 1  ."),QMessageBox::Cancel);
        }
        else {

    bool test=t.Ajouter();
        if (test){
            QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("ajout effectue\n"),QMessageBox::Cancel);
            ui->tableView->setModel(t.afficher());


        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("ajout non effectue\n"),QMessageBox::Cancel);
}

}

}


void MainWindow::on_pushButton_11_clicked()
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

void MainWindow::on_pushButton_12_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
      QString sql;
      sql = "select ID_T From TRANSACTION";
      QSqlDatabase db = QSqlDatabase::database("QODBC");
      QSqlQuery* query=new QSqlQuery(db);
      query->exec(sql);
      model->setQuery(*query);
      ui->comboboxmodif->setModel(model);
}


void MainWindow::on_pushButton_8_clicked()
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
           ui->tableView->setModel(t.afficher());

       }
       else
           QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("Suppression non effectue\n"),QMessageBox::Cancel);
}
}

void MainWindow::on_pushButton_4_clicked()
{
    QString montanttest=ui->montant_transaction_2->text();
    QString debittest=ui->debit_transaction_2->text();
    QString idtest=ui->comboboxmodif->currentText();

    int ID=ui->comboboxmodif->currentText().toInt();
    QString DATE = ui->date_transaction_2->date().toString();
    QString MONTANT=ui->montant_transaction_2->text();
    int DEBIT_CREDIT=ui->debit_transaction_2->text().toInt();
    QString DESCRIPTION=ui->description_transaction_2->text();

    transactions t(ID,DATE,MONTANT,DESCRIPTION,DEBIT_CREDIT);
    if(montanttest.isEmpty() || debittest.isEmpty() || DESCRIPTION.isEmpty() || idtest.isEmpty())
                     {
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
            ui->tableView->setModel(t.afficher());

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("Mis à jour ne pas effectue\n"),QMessageBox::Cancel);
}
}
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->montant_transaction_2->clear();
    ui->description_transaction_2->clear();
    ui->debit_transaction_2->clear();
}

void MainWindow::on_pushButton_2_clicked()
{
  ui->id_transaction->clear();
  ui->montant_transaction->clear();
  ui->description_transaction->clear();
  ui->debit_transaction->clear();
}

void MainWindow::on_pushButton_32_clicked()
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

void MainWindow::on_pushButton_34_clicked()
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

void MainWindow::on_pushButton_15_clicked()
{
    QFile file("historique.txt");
    if(!file.open(QIODevice::ReadOnly)){
        qCritical() << "file not found ";
        qCritical() << file.errorString();

    }
    QTextStream in(&file);
    ui->textBrowser->setText(in.readAll());
}


void MainWindow::on_pushButton_38_clicked()
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



}

void MainWindow::on_pushButton_29_clicked()
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

void MainWindow::on_pushButton_31_clicked()
{

    ui->who_rech->clear();
}

void MainWindow::on_pushButton_7_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
      QString sql;
      sql = "select NUMERO_CONTRAT From CONTRAT";
      QSqlDatabase db = QSqlDatabase::database("QODBC");
      QSqlQuery* query=new QSqlQuery(db);
      query->exec(sql);
      model->setQuery(*query);
      ui->comboboxajout->setModel(model);

}

void MainWindow::on_pushButton_9_clicked()
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
