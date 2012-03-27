#include "tee.h"

Tee::Tee(int courseId, QObject *parent):
    QObject(parent)
{
    mCourseId = courseId;
}

Tee::~Tee()
{
    qDeleteAll(mHoles);
}

QString Tee::name()
{
    return mName;
}

void Tee::setName(QString name)
{
    mName = name;
}

float Tee::slope()
{
    return mSlope;
}

void Tee::setSlope(float slope)
{
    mSlope = slope;
}

Hole* Tee::addHole()
{
    Hole* hole = new Hole(this->id());
    mHoles.append(hole);
    return hole;
}

QList<Hole*> Tee::holes()
{
    return mHoles;
}
