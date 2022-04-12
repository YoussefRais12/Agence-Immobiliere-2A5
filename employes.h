#ifndef EMPLOYES_H
#define EMPLOYES_H

#include <QDialog>
#include "employe.h"
#include"popup.h"
namespace Ui {
class employes;
}

class employes : public QDialog
{
    Q_OBJECT

public:
    explicit employes(QWidget *parent = nullptr);
    ~employes();

private slots :
    void on_pushButton_ajouter_clicked();
     void on_pushButton_supprimer_clicked();
     void on_pushButton_modifier_clicked();

     void on_tri_nom_clicked();

     void on_tri_id_clicked();

     void on_lineEdit_rech_textEdited(const QString &arg1);

     void on_pushButton_clicked();

     void on_pushButton_2_clicked();

     void on_buttonafficher_clicked();

     void on_pushButton_3_clicked();

     void on_tri_pre_clicked();

private:
    Ui::employes *ui;
    employe Etmp;
    PopUp *popUp;

};

#endif // EMPLOYES_H
