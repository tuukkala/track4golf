    #include "course.h"

Course::Course(QObject *parent) :
    QObject(parent)
{
}

Course::~Course()
{
    qDeleteAll(mTees);
}

QString Course::name()
{
    return mName;
}

void Course::setName(QString name)
{
    mName = name;
}

QString Course::country()
{
    return mCountry;
}

void Course::setCountry(QString country)
{
    mCountry = country;
}

QString Course::address()
{
    return mAddress;
}

void Course::setAddress(QString address)
{
    mAddress = address;
}

Tee* Course::addTee()
{
    Tee* tee = new Tee(this->id(), this);
    mTees.append(tee);
    return tee;
}

Tee* Course::tee(int id)
{
    Tee* tee = 0;
    foreach(Tee* aTee, mTees){
        if(aTee->id() == id){
            tee = aTee;
            break;
        }
    }
    return tee;
}

QList<Tee*> Course::tees()
{
    return mTees;
}
