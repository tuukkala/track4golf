#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "storable.h"
#include "scorecard.h"

class Player : public QObject, public Storable
{
    Q_OBJECT
    Q_INTERFACES(Storable)

public:
    explicit Player(QString userName, QString password, QObject *parent = 0);

    ~Player();

    Q_INVOKABLE QString name();
    void setName(const QString& name);

    Q_INVOKABLE QString email();
    void setEmail(const QString& email);

    Q_INVOKABLE float hcp();
    void setHcp(float hcp);

    ScoreCard* newRound();

    void serializeToSql();
    QString serializeToJson();

private:
    QString mName;
    QString mEmail;
    float mHcp;
    QString mUserName;
    QString mPassWord;
    ScoreCard* mCurrentRound;
};

#endif // PLAYER_H
