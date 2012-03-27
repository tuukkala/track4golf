#include "holescore.h"

HoleScore::HoleScore(int number, QObject *parent) :
    QObject(parent)
{
    mNumber = number;
    mSkipped = false;
    mPlayed = false;
    mFairway = false;
    mSandTrap = false;
}

bool HoleScore::skipped()
{
    return mSkipped;
}

void HoleScore::skip(bool skip)
{
    mSkipped = skip;
}

bool HoleScore::played()
{
    return mPlayed;
}

void HoleScore::setPlayed(bool played)
{
    mPlayed = played;
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



