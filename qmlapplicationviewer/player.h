#ifndef PLAYER_H
#define PLAYER_H

class Player : public QObject
{
    Q_OBJECT

public:
    Player(QString name);
    ~Player();

    QString name();
    void setName(QString name);

    QString email();
    void setEmail(QString email);

    float hcp();
    void setHcp(float hcp);

private:
    QString mName;
    QString mEmail;
    float mHcp;

}


#endif // PLAYER_H
