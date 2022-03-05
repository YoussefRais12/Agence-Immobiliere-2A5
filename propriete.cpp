#include "propriete.h"
#include "ui_propriete.h"

propriete::propriete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::propriete)
{
    ui->setupUi(this);
}

propriete::~propriete()
{
    delete ui;
}
