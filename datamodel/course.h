#ifndef COURSE_H
#define COURSE_H

#include <QObject>

#include "tee.h"
#include "storable.h"

class Course : public QObject, public Storable
{
    Q_OBJECT
    Q_INTERFACES(Storable)

public:
    explicit Course(QObject *parent = 0);
    ~Course();

    Tee* addTee();

    QString name();
    void setName(QString name);

    QString country();
    void setCountry(QString country);

    QString address();
    void setAddress(QString address);

    void serializeToSql();
    QString serializeToJson();

    int courseId() {return mRowId;}

private:
    QString mName;
    QString mCountry;
    QString mAddress;
    QList<Tee*> mTees;
};

#endif // COURSE_H
