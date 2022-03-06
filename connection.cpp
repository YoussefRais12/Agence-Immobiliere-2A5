#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Hestia");
db.setUserName("marwen");//inserer nom de l'utilisateur
db.setPassword("marwen1005");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
