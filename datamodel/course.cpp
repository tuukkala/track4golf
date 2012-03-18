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
    return new Tee(mRowId, this);
}

void Course::serializeToSql()
{
    QSqlQuery query;
    query.prepare("INSERT INTO course (name, country, address) "
                  "VALUES (:name, :country, :address)");
    query.bindValue(":name", name());
    query.bindValue(":country", country());
    query.bindValue(":address", address());
    query.exec();
    foreach(Tee* tee, mTees){
        tee->serializeToSql();
    }
}

QString Course::serializeToJson()
{
    return "";
}
