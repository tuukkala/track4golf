#include "player.h"

Player::Player(QString name, QObject *parent) :
    QObject(parent)
{
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
