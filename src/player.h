#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QString name, QObject *parent = 0);
    ~Player();

    Q_INVOKABLE QString name();
    void setName(const QString& name);

    Q_INVOKABLE QString email();
    void setEmail(const QString& email);

    Q_INVOKABLE float hcp();
    void setHcp(float hcp);

private:
    QString mName;
    QString mEmail;
    float mHcp;


};

#endif // PLAYER_H
