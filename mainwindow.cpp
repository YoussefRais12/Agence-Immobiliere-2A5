#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"contrats.h"
#include <QString>
#include<QDateEdit>
#include<QMessageBox>
#include <iostream>
#include <QTabWidget>
#include <QMessageBox>
#include <QDebug>
#include <QDate>
#include <QPdfWriter>
#include <QPainter>
#include <QUrl>
#include <QDesktopServices>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintEngine>
#include <QPlainTextEdit>
#include <smtp.h>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setSortingEnabled(true); // enable sortingEnabled
    ui->tableView->setModel(pimp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_Ajouter_clicked()
{
    int numero_contrat=ui->numero->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    int cin=ui->cin->text().toInt();
    QString telephone=ui->telephone->text();
    int type=ui->type->text().toInt();
    QString contenu=ui->contenu->text();
    int signe=ui->signe->text().toInt();
    QString date=ui->date->text();
    QString numerotest=ui->numero->text();
    QString cintest=ui->cin->text();
    QString signetest=ui->signe->text();
    QString testtype=ui->type->text();
    QString prixfinal=ui->prixfinal->text();
    if (prixfinal==""){
        prixfinal="0";
    }
    contrat p(numero_contrat,cin,nom,prenom,telephone,signe, type,contenu,date,prixfinal);

    /*if (numerotest.isEmpty() || nom.isEmpty() || prenom.isEmpty() || cintest.isEmpty() || telephone.isEmpty() ||
            contenu.isEmpty() || signetest.isEmpty() || testtype.isEmpty() || prixfinal.isEmpty()) {

        QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("Il y a un champ vide"),QMessageBox::Cancel);

    }
    else {
        if (numerotest.length()!=8){
                    QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("Length != 8 ."),QMessageBox::Cancel);
                }
    else if((signe!=0) && (signe!=1)) {
            QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr(" signe doit etre 0 ou 1. 1 si signé sinon 0"),QMessageBox::Cancel);
        }
        else if(cintest.length()!=8) {
                QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr(" CIN must have 8 digits"),QMessageBox::Cancel);
            }*/
        //else {



    bool test=p.ajouter();

    if (test){
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("ajout effectue\n"),QMessageBox::Cancel);
        ui->tableView->setModel(pimp.afficher());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("ajout non effectue\n"),QMessageBox::Cancel);
}
/*}
}*/

void MainWindow::on_supp_clicked()
{
    int Num=ui->combo->currentText().toInt();
    QString Numtest=ui->combo->currentText();
    bool test=pimp.supprimer(Num);

    if(Numtest.isEmpty()){
        QMessageBox::critical(0,qApp->tr("Erreur"),qApp->tr("Veuillez choisir le numero du contrat à supprimer."),QMessageBox::Cancel);
    }
    else {

    if(test) {
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr(" DELETED\n"),QMessageBox::Cancel);
        ui->tableView->setModel(pimp.afficher());

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("Couldn't delete\n"),QMessageBox::Cancel);

    }
}
}
void MainWindow::on_generer_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString sql;
    sql = "select NUMERO_CONTRAT From Contrat";
    QSqlDatabase db = QSqlDatabase::database("QODBC");
    QSqlQuery* query=new QSqlQuery(db);
    query->exec(sql);
    model->setQuery(*query);
    ui->combo->setModel(model);
}

void MainWindow::on_load_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString sql;
    sql = "select NUMERO_CONTRAT From Contrat";
    QSqlDatabase db = QSqlDatabase::database("QODBC");
    QSqlQuery* query=new QSqlQuery(db);
    query->exec(sql);
    model->setQuery(*query);
    ui->comboBox->setModel(model);
}

void MainWindow::on_Modif_clicked()
{
    //int Num=ui->comboBox->currentText().toInt();
    /*int Cin=ui->cin->text().toInt();
    QString Nom=ui->nom->text();
    QString Prenom=ui->prenom->text();
    QString Email=ui->mail->text();
    QString Telephone=ui->telephone->text();
    int signe=ui->signe->text().toInt();
    int type=ui->type->text().toInt();
    QString Contenu=ui->contenu->text();
    QString Date=ui->date->text();*/
    int numero_contrat=ui->numero->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    int cin=ui->cin->text().toInt();
    QString telephone=ui->telephone->text();
    int type=ui->type->text().toInt();
    QString contenu=ui->contenu->text();
    int signe=ui->signe->text().toInt();
    QString date=ui->date->text();
    QString numerotest=ui->numero->text();
    QString cintest=ui->cin->text();
    QString signetest=ui->signe->text();
    QString testtype=ui->type->text();
    QString prixfinal=ui->prixfinalmodif->text();
    contrat p(numero_contrat,cin,nom,prenom,telephone,signe, type,contenu,date,prixfinal);


    bool test=p.modifier(numero_contrat);
    if(test) {
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr(" MODIFIED\n"),QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not Okay"), QObject::tr("Couldn't MODIFY\n"),QMessageBox::Cancel);

    }
}

void MainWindow::on_pushButton_4_clicked()
{
    contrat c;
    QString choix=ui->comboo->currentText();

    if (choix=="Numero"){
       QString numero=ui->chercher->text();
       ui->tableView->setModel(c.rechercher(numero));
    }

    if (choix=="Nom"){
        QString nom=ui->chercher->text();
        ui->tableView->setModel(c.recherchernom(nom));
    }

    if (choix=="Cin") {
        QString cin=ui->chercher->text();
        ui->tableView->setModel(c.recherchercin(cin));
    }
}

void MainWindow::on_genpdf_clicked()
{
        QSqlDatabase db;
                        QTableView table_client;
                        QSqlQueryModel * Modal=new  QSqlQueryModel();

                        QSqlQuery qry;
                         qry.prepare("SELECT * FROM CONTRAT ");
                         qry.exec();
                         Modal->setQuery(qry);
                         table_client.setModel(Modal);



                         db.close();


                         QString strStream;
                         QTextStream out(&strStream);


                         const int rowCount = table_client.model()->rowCount();
                         const int columnCount =  table_client.model()->columnCount();


                         const QString strTitle ="Document";


                         out <<  "<html>\n"
                                 "<img src='C:/Users/marwe/Documents/logocin.png' height='120' width='120'/>"
                             "<head>\n"
                                 "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                 "<img src='e-care.png'>"
                             <<  QString("<title>%1</title>\n").arg(strTitle)
                             <<  "</head>\n"
                             "<body bgcolor=#ffffff link=#5000A0>\n"
                            << QString("<h3 style=\" font-size: 50px; font-family: Arial, Helvetica, sans-serif; color: #e80e32; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("Liste des contrats")
                            <<"<br>"

                            <<"<table border=1 cellspacing=0 cellpadding=2 width=\"100%\">\n";
                         out << "<thead><tr bgcolor=#f0f0f0>";
                         for (int column = 0; column < columnCount; column++)
                             if (!table_client.isColumnHidden(column))
                                 out << QString("<th>%1</th>").arg(table_client.model()->headerData(column, Qt::Horizontal).toString());
                         out << "</tr></thead>\n";

                         for (int row = 0; row < rowCount; row++) {
                             out << "<tr>";
                             for (int column = 0; column < columnCount; column++) {
                                 if (!table_client.isColumnHidden(column)) {
                                     QString data = table_client.model()->data(table_client.model()->index(row, column)).toString().simplified();
                                     out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                 }
                             }
                             out << "</tr>\n";
                         }
                         out <<  "</table>\n"
                                 "<br><br>"
                                 <<"<br>"
                                 <<"<table border=1 cellspacing=0 cellpadding=2>\n";


                             out << "<thead><tr bgcolor=#f0f0f0>";

                                 out <<  "</table>\n"

                             "</body>\n"
                             "</html>\n";

                         QTextDocument *document = new QTextDocument();
                         document->setHtml(strStream);

                         QPrinter printer;
                         QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                         if (dialog->exec() == QDialog::Accepted) {

                             QLabel lab;
                              QPixmap pixmap("C:/aze.png");
                             lab.setPixmap(pixmap);
                             QPainter painter(&lab);
                             QPrinter printer(QPrinter::PrinterResolution);

                             pixmap.load("aze.png");
                             painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
                             painter.drawPixmap(10,10,50,50, pixmap);

                             document->print(&printer);
                         }

                         printer.setOutputFormat(QPrinter::PdfFormat);
                         printer.setPaperSize(QPrinter::A4);
                         printer.setOutputFileName("C:/kekwlmao.pdf");
                         printer.setPageMargins(QMarginsF(15, 15, 15, 15));



                         delete document;

}

void MainWindow::on_pede_clicked()
{

}

void MainWindow::on_mail_2_clicked()
{
    Smtp* smtp = new Smtp("rais.youssef@esprit.tn", "201JMT1744", "smtp.gmail.com", 465);
         connect(smtp, SIGNAL(status(QString)), this, SLOT(mailsent(QString)));
         QString a=ui->Linemail->text();
         QString b=ui->Lineobjet->text();
         QString c=ui->plaincontenu->toPlainText();

         smtp->sendMail("rais.youssef@esprit.tn", a , b,c);

}

void MainWindow::on_pushButton_2_clicked()
{
    QSqlQuery query;
    float tax=0.7,commission0=0.1,commission1=0.2,prixfinal,prix;
    int mat=ui->comboboxmatricule->currentText().toInt();
    int type=ui->type->text().toInt();
    query.prepare("select PRIX from PROPRIETE where MATRICULE=:mat");
    query.bindValue(":mat",mat);
    query.exec();
    if (query.next()){
         prix=query.value(0).toFloat();
    }
    qDebug()<<"prix"<<prix;

    if (type==0){
        prixfinal=prix+(prix*tax)+(commission0*prix);
    }
    else if (type==1){
        prixfinal=prix+(prix*tax)+(commission1*prix);

    }
    qDebug()<<prixfinal;
    ui->textEdit->setReadOnly(true);
    QString prixfinals=QString::number(prixfinal);
    QString prixs=QString::number(prix);
    ui->textEdit->append("Tax = 7%\n" );

     if(type==0){
         ui->textEdit->append("Type de contrat : 0 \n" );
         ui->textEdit->append("Commission = 10%\n" );

     }
     else if (type==1){
         ui->textEdit->append("Type de contrat : 1 \n" );
         ui->textEdit->append("Commission = 20%\n" );

     }
     ui->textEdit->append("Le prix initiale =  "+prixs+" DT\n" );
    ui->textEdit->append("Le prix final =  "+prixfinals+" DT\n" );
    ui->textEdit->append("________\n" );
    ui->prixfinal->setText(prixfinals);

}

void MainWindow::on_Ajouter_2_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
      QString sql;
      sql = "select MATRICULE From PROPRIETE";
      QSqlDatabase db = QSqlDatabase::database("QODBC");
      QSqlQuery* query=new QSqlQuery(db);
      query->exec(sql);
      model->setQuery(*query);
      qDebug() <<model ;
      ui->comboboxmatricule->setModel(model);
}

