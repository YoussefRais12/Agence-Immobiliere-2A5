#include "mainwindow.h"
#include <QtSql>
#include <QApplication>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug()<<"start";

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet");
    db.setUserName("MARWEN");
    db.setPassword("marwen1005");

    MainWindow w;
    w.show();

    qDebug()<<"end";
    return a.exec();
}
