#ifndef TEE_H
#define TEE_H

#include <QObject>
#include <QList>

#include "hole.h"
#include "domainbase.h"

class Tee : public QObject, public DomainBase
{
    Q_OBJECT

public:

    ~Tee();

    Q_INVOKABLE QString name();
    Q_INVOKABLE void setName(QString name);

    Q_INVOKABLE float slope();
    Q_INVOKABLE void setSlope(float slope);

    Q_INVOKABLE Hole* addHole();

    Q_INVOKABLE QList<Hole*> holes();

private:
    explicit Tee(int courseId, QObject *parent = 0);

private:
    QString mName;
    float mSlope;
    QList<Hole*> mHoles;
    int mCourseId;
    friend class Course;
    
};

#endif // TEE_H
