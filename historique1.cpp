#include "historique.h"
#include<QMessageBox>
#include <QDateTime>

Historique::Historique()
{
tmp="";
}
void Historique::save(QString nom,QString prenom)
{    QFile file ("historique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
         return;
     QTextStream out(&file);
      out.setCodec("UTF-8");
     QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
     out << "\n"+nom << "\n" +prenom<< "\n un nouveau employe a etat ajouter le " +sDate << "\n";

}
QString Historique::load()
{   tmp="";
    QFile file("historique.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {


         QString myString = in.readLine();
         tmp+=myString;


   }
   return tmp;
}
void Historique::save1(QString nom,QString prenom)
{    QFile file ("historique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
     out << "\n"+nom << "\n" +prenom<< "\n cet employe a etait modifier le " +sDate << "\n";


}
void Historique::save2(QString id)
{
    QFile file ("C:/Users/kchaa/Desktop/qt real estate/khadija/his.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
     out << id  << "\n cet employe a etait supprimer le " +sDate << "\n";


}
