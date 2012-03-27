#ifndef HOLE_H
#define HOLE_H

#include <QObject>

#include "domainbase.h"

class Hole : public QObject, public DomainBase
{
    Q_OBJECT    

public:    
    
    int number();
    void setNumber(int number);

    int par();
    void setPar(int par);

    int hcp();
    void setHcp(int hcp);

    int length();
    void setLength(int length);

private:
    explicit Hole(int teeId, QObject *parent = 0);


private:
    int mNumber;
    int mPar;
    int mHcp;
    int mLength;
    int mTeeId;
    friend class Tee;
};

#endif // HOLE_H
