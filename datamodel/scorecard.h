#ifndef SCORECARD_H
#define SCORECARD_H

#include <QObject>
#include <QDateTime>
#include <QList>

#include "holescore.h"
#include "course.h"
#include "storable.h"

class ScoreCard : public QObject, public Storable
{
    Q_OBJECT
    Q_INTERFACES(Storable)

public:    
    ~ScoreCard();

    Q_INVOKABLE void start();
    Q_INVOKABLE void end();

    Q_INVOKABLE QDateTime startDate();
    Q_INVOKABLE QDateTime endDate();

    Q_INVOKABLE void setCourse(Course* course);
    Q_INVOKABLE Course* course();

    Q_INVOKABLE Tee* tee();
    Q_INVOKABLE void setTee(Tee* tee);

    Q_INVOKABLE HoleScore* nextHole();
    Q_INVOKABLE HoleScore* previouseHole();

    void serializeToSql();
    QString serializeToJson();

private:
    explicit ScoreCard(int playerId, QObject *parent = 0);

private:
    QDateTime mStartDate;
    QDateTime mEndDate;
    Course* mCourse;
    Tee* mTee;
    QList<HoleScore*> mHoles;
    int mCurrentHole;
    friend class Player;
    bool mFinished;
    int mPlayerId;
};

#endif // SCORECARD_H

