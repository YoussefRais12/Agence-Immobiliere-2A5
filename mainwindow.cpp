#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "employes.h"
int test=0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow ::rech(QString nomuitlisateur,QString mdp )
{


    QSqlQuery query;
    query.prepare("select * from AUTHENTIFICATION where NOM_UTILISATEUR=:NOM_UTILISATEUR");
    query.bindValue(":NOM_UTILISATEUR",nomuitlisateur);
    if(query.exec()){
        query.next();
        if(query.value(2)== mdp){
             test = 1;
        }else {
             test = 0;
        }
    }else {
        test = 0;
    }

    return test;
}
bool MainWindow::supprimerA(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("delete from AUTHENTIFICATION where ID=:id");
    query.bindValue(":id",res);
    return query.exec();
}



void MainWindow::on_pushButton_clicked()
{
    employes *myLog = new employes();

    //Close the welcome class
    this->close();

    //open the Login class
    myLog->show();
}

void MainWindow::on_pushButton_2_clicked()
{

    QString n = ui->lineEdit_ut->text();
    QString mdp = ui->lineEdit_mdp->text();
    if(MainWindow::rech(n,mdp)==1) {
        QMessageBox::information(this, "Login", "Username and password is correct");
        employes *myLog = new employes();
        //Close the welcome class
        this->close();
        //open the Login class
        myLog->show();

    }
    else {
        QMessageBox::warning(this,"Login", "username and password is not correct");
    }
}


/*

void login::on_ajouter_clicked()
{
    QString mdp=ui->ajoutmdp->text();
    QString nom=ui->ajoutnom->text();



     employe P(nom,mdp,1);

    bool test=P.ajouter2();

   if(test)
    {
       QMessageBox::information(nullptr,QObject::tr("ok"),
                              QObject::tr(" effectue\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
   }
   else  QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                  QObject::tr("non effectue\n"
                                            "click cancel to exit."),QMessageBox::Cancel);

}
*/

void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit_ut->clear();
    ui->lineEdit_mdp->clear();

}
