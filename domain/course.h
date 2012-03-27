#ifndef COURSE_H
#define COURSE_H

#include <QObject>

#include "tee.h"
#include "domainbase.h"

class Course : public QObject, public DomainBase
{
    Q_OBJECT    

public:
    explicit Course(QObject *parent = 0);
    ~Course();

    Tee* addTee();

    Q_INVOKABLE QString name();
    Q_INVOKABLE void setName(QString name);

    Q_INVOKABLE QString country();
    Q_INVOKABLE void setCountry(QString country);

    Q_INVOKABLE QString address();
    Q_INVOKABLE void setAddress(QString address);

    Q_INVOKABLE QList<Tee*> tees();
    Q_INVOKABLE Tee* tee(int id);

private:
    QString mName;
    QString mCountry;
    QString mAddress;
    QList<Tee*> mTees;    
};

#endif // COURSE_H
