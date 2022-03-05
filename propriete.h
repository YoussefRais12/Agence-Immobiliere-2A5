#ifndef PROPRIETE_H
#define PROPRIETE_H

#include <QDialog>

namespace Ui {
class propriete;
}

class propriete : public QDialog
{
    Q_OBJECT

public:
    explicit propriete(QWidget *parent = nullptr);
    ~propriete();

private:
    Ui::propriete *ui;
};

#endif // PROPRIETE_H
