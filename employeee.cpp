#include "employeee.h"

class employeeeData : public QSharedData
{
public:

};

employeee::employeee() : data(new employeeeData)
{

}

employeee::employeee(const employeee &rhs) : data(rhs.data)
{

}

employeee &employeee::operator=(const employeee &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

employeee::~employeee()
{

}
