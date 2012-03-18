#ifndef STORABLE_H
#define STORABLE_H

#include <QSqlQuery>
#include <QTextStream>

#include <QVariant>

class Storable
{
public:
    virtual ~Storable(){}

    virtual void serializeToSql() = 0;
    virtual QString serializeToJson() = 0;

protected:
    int mRowId;

};

Q_DECLARE_INTERFACE(Storable,
                    "com.track4.Storable/1.0")

#endif
