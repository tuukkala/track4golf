#include "scorecard.h"

ScoreCard::ScoreCard(int playerId, QObject *parent) :
    QObject(parent)
{    
    mPlayerId = playerId;
    mCurrentHole = 0;
    mFinished = false;
}

ScoreCard::~ScoreCard()
{
    qDeleteAll(mHoles);
    delete mTee;
    delete mCourse;
}

void ScoreCard::start()
{
    mStartDate = QDateTime::currentDateTime();
}
void ScoreCard::end()
{
    mEndDate = QDateTime::currentDateTime();
    mFinished = true;
}

void ScoreCard::setStartDate(QDateTime date)
{
    mStartDate = date;
}

void ScoreCard::setEndDate(QDateTime date)
{
    mEndDate = date;
    mFinished = true;
}

QDateTime ScoreCard::startDate()
{
    return mStartDate;
}
QDateTime ScoreCard::endDate()
{
    return mEndDate;
}

void ScoreCard::setCourse(Course* course)
{
    mCourse = course;
}

Course* ScoreCard::course()
{
    return mCourse;
}

Tee* ScoreCard::tee()
{
    return mTee;
}

void ScoreCard::setTee(Tee* tee)
{
    mTee = tee;
    foreach(HoleScore* hole, mHoles){
        mHoles.append(new HoleScore(hole->number(), this));
    }
}

QList<HoleScore*> ScoreCard::holeScores()
{
    return mHoles;
}


HoleScore* ScoreCard::nextHole()
{
    HoleScore* current = 0;
    if(!mHoles.isEmpty()){
        if(mHoles.size() < (mCurrentHole - 1)){
            mCurrentHole--;
        }
        current = mHoles.at(mCurrentHole);
    }
    return current;
}

HoleScore* ScoreCard::previouseHole()
{
    HoleScore* current = 0;
    if(!mHoles.isEmpty()){
        if(mCurrentHole > 0){
            mCurrentHole--;
        }
        current = mHoles.at(mCurrentHole);
    }
    return current;
}

HoleScore* ScoreCard::holeAt(int index)
{
    if(index < mHoles.size()){
        return mHoles.at(index);
    }
    return 0;
}

void ScoreCard::finish()
{
    mFinished = true;
    endDate() = QDateTime::currentDateTime();
}
bool ScoreCard::isFinished()
{
    return mFinished;
}


