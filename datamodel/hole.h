#ifndef HOLE_H
#define HOLE_H

#include <QObject>

#include "storable.h"

class Hole : public QObject, public Storable
{
    Q_OBJECT
    Q_INTERFACES(Storable)

public:    
    
    int number();
    void setNumber(int number);

    int par();
    void setPar(int par);

    int hcp();
    void setHcp(int hcp);

    int length();
    void setLength(int length);

    void serializeToSql();
    QString serializeToJson();

private:
    explicit Hole(int teeId, QObject *parent = 0);


private:
    int mNumber;
    int mPar;
    int mHcp;
    int mLength;
    int mTeeId;
};

#endif // HOLE_H
