#include "hole.h"

Hole::Hole(int teeId, QObject *parent) :
    QObject(parent)
{
    mTeeId = teeId;
}

int Hole::number()
{
    return mNumber;
}

void Hole::setNumber(int number)
{
    mNumber = number;
}

int Hole::par()
{
    return mPar;
}

void Hole::setPar(int par)
{
    mPar = par;
}

int Hole::hcp()
{
    return mHcp;
}

void Hole::setHcp(int hcp)
{
    mHcp = hcp;
}

int Hole::length()
{
    return mLength;
}

void Hole::setLength(int length)
{
    mLength = length;
}

//TODO tee id needed!
void Hole::serializeToSql()
{
    QSqlQuery query;
    query.prepare("INSERT INTO hole (number, par, hcp, lenght, teeid) "
                  "VALUES (:hole, :number, :par, :hcp, :length, :teeid)");
    query.bindValue(":number", number());
    query.bindValue(":par", par());
    query.bindValue(":hcp", hcp());
    query.bindValue(":length", length());
    query.bindValue(":teeid", mTeeId);
    query.exec();
}

QString Hole::serializeToJson()
{
    return "";
}


