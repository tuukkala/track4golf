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
void ScoreCard::serializeToSql()
{
    QSqlQuery query;
    query.prepare("INSERT INTO scorecard (startdate, enddate, finished, courseid, teeid, playerid) "
                  "VALUES (startdate, enddate, finished, courseid, teeid, playerid)");
    query.bindValue("startdate:", startDate());
    query.bindValue("enddate:", endDate());
    query.bindValue(":finished", mFinished);
    query.bindValue(":courseId", mCourse->courseId());
    query.bindValue(":teeid", mTee->teeId());
    query.bindValue(":playerid", mPlayerId);

    query.exec();
}

QString ScoreCard::serializeToJson()
{
    return "";
}
