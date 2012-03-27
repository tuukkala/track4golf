#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include "course.h"
#include "scorecard.h"
#include "player.h"

class DbManager : public QObject
{
    Q_OBJECT
public:
    explicit DbManager(QObject *parent = 0);
    ~DbManager();

    Q_INVOKABLE Player* loadPlayer(const QString& username, const QString& password);
    Q_INVOKABLE bool createPlayer(Player* player);
    Q_INVOKABLE bool savePlayer(Player* player);
    Q_INVOKABLE bool deletePlayer(Player* player);

    Q_INVOKABLE Course* loadCourse(int id);
    Q_INVOKABLE bool createCourse(Course* course);
    Q_INVOKABLE bool saveCourse(Course* course);
    Q_INVOKABLE bool deleteCourse(Course* course);

    Q_INVOKABLE ScoreCard* loadScoreCard(Player* player, int id);
    Q_INVOKABLE ScoreCard* createScoreCard(Player* player, Course* course, Tee* tee);
    Q_INVOKABLE bool saveScoreCard(ScoreCard* scoreCard);
    Q_INVOKABLE bool deleteScoreCard(ScoreCard* scoreCard);

private:
    bool openDataBase();
    bool initializeDataBase();

private:

    QSqlDatabase mDataBase;

};

#endif // DBMANAGER_H
