#ifndef STORABLE_H
#define STORABLE_H

#include <QSqlQuery>
#include <QTextStream>

#include <QVariant>

class DomainBase
{   
public:    
    virtual ~DomainBase(){}

    void setId(int id) { mId = id;}
    int id() {return mId;}

protected:
    int mId;

};

#endif
