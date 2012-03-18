#include "holescore.h"

HoleScore::HoleScore(int number, QObject *parent) :
    QObject(parent)
{
    mNumber = number;
}

int HoleScore::number()
{
    return mNumber;
}

HoleScore::~HoleScore()
{}

void HoleScore::setStrokes(int strokes)
{
    mStrokes = strokes;
}
int HoleScore::strokes()
{
    return mStrokes;
}

void HoleScore::setPuts(int puts)
{
    mPuts = puts;
}

int HoleScore::puts()
{
    return mPuts;
}

void HoleScore::setFairway(bool hit)
{
    mFairway = hit;
}

bool HoleScore::fairway()
{
    return mFairway;
}

void HoleScore::setSandtrap(bool hit)
{
    mSandTrap = hit;
}

bool HoleScore::sandtrap()
{
    return mSandTrap;
}

void HoleScore::setNote(QString note)
{
    mNotes = note;
}

QString HoleScore::note()
{
    return mNotes;
}

void HoleScore::serializeToSql()
{
    QSqlQuery query;
    query.prepare("INSERT INTO holescore (number, strokes, puts, fairway, sandtrap, notes) "
                  "VALUES (:number, :strokes, :puts, :fairway, :sandtrap, :notes)");
    query.bindValue(":number", number());
    query.bindValue(":strokes", strokes());
    query.bindValue(":puts", puts());
    query.bindValue(":fairway", fairway());
    query.bindValue(":sandtrap", sandtrap());
    query.bindValue(":notes", note());
    query.exec();
}

QString HoleScore::serializeToJson()
{
    return "";
}

