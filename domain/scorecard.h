#ifndef SCORECARD_H
#define SCORECARD_H

#include <QObject>
#include <QDateTime>
#include <QList>

#include "holescore.h"
#include "course.h"
#include "domainbase.h"

class ScoreCard : public QObject, public DomainBase
{
    Q_OBJECT    

public:    
    ~ScoreCard();

    Q_INVOKABLE void start();
    Q_INVOKABLE void end();

    Q_INVOKABLE QDateTime startDate();
    Q_INVOKABLE QDateTime endDate();

    Q_INVOKABLE void setStartDate(QDateTime date);
    Q_INVOKABLE void setEndDate(QDateTime date);

    Q_INVOKABLE void setCourse(Course* course);
    Q_INVOKABLE Course* course();

    Q_INVOKABLE Tee* tee();
    Q_INVOKABLE void setTee(Tee* tee);

    Q_INVOKABLE HoleScore* nextHole();
    Q_INVOKABLE HoleScore* previouseHole();
    Q_INVOKABLE HoleScore* holeAt(int index);
    QList<HoleScore*> holeScores();

    Q_INVOKABLE void finish();
    Q_INVOKABLE bool isFinished();

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

