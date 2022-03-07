#ifndef EMPLOYEEE_H
#define EMPLOYEEE_H

#include <QDeclarativeItem>
#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>

class employeeeData;

class employeee
{
    Q_OBJECT
public:
    employeee();
    employeee(const employeee &);
    employeee &operator=(const employeee &);
    ~employeee();

private:
    QSharedDataPointer<employeeeData> data;
};

#endif // EMPLOYEEE_H
