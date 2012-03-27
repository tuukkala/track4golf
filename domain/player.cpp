#include "player.h"

Player::Player(QString userName, QString password, QObject *parent) :
    QObject(parent)
{
    mUserName = userName;
    mPassWord = password;
    mCurrentRound = 0;
}


Player::~Player()
{}


void Player::setName(const QString& name)
{
    mName = name;
}

QString Player::name()
{
    return mName;
}

void Player::setEmail(const QString& email)
{
    mEmail = email;
}

QString Player::email()
{
    return mEmail;
}

void Player::setHcp(float hcp)
{
    mHcp = hcp;
}

float Player::hcp()
{
    return mHcp;
}

ScoreCard* Player::newRound()
{
    //TODO: maybe not delete brutally
    if(mCurrentRound){ delete mCurrentRound;}
    mCurrentRound = new ScoreCard(this->id(), this);
    return mCurrentRound;
}


