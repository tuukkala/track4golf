#ifndef TEE_H
#define TEE_H

#include <QObject>

#include "hole.h"
#include "storable.h"

class Tee : public QObject, public Storable
{
    Q_OBJECT
    Q_INTERFACES(Storable)

public:
    ~Tee();

    Q_INVOKABLE QString name();
    Q_INVOKABLE void setName(QString name);

    Q_INVOKABLE float slope();
    Q_INVOKABLE void setSlope(float slope);

    int teeId() {return mRowId;}

    void serializeToSql();
    QString serializeToJson();

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
