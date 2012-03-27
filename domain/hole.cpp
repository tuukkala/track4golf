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


