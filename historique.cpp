#include "historique.h"
#include<QMessageBox>
#include <QDateTime>

historique::historique()
{
tmp="";
}
void historique::save(QString nom,QString prenom)
{    QFile file ("historique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
     out << "\n"+nom << "\n" +prenom<< "\n un nouveau employe a etat ajouter le " +sDate << "\n";


}
QString historique::load()
{   tmp="";
    QFile file("historique.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {


         QString myString = in.readLine();
         tmp+=myString+"\n";


   }
   return tmp;
}
void historique::save1(QString nom,QString prenom)
{    QFile file ("historique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
     out << "\n"+nom << "\n" +prenom<< "\n cet employe a etait modifier le " +sDate << "\n";


}
void historique::save2(QString id)
{
    QFile file ("historique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
     out << id  << "\n cet employe a etait supprimer le " +sDate << "\n";


}
