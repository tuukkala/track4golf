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

void Tee::serializeToSql()
{
    QSqlQuery query;
    query.prepare("INSERT INTO hole (name, slope, courseid) "
                  "VALUES (:name, :slope, :courseid)");
    query.bindValue(":name", name());
    query.bindValue(":slope", slope());
    query.bindValue(":courseId", mCourseId);
    query.exec();
}

QString Tee::serializeToJson()
{
    return "";
}
