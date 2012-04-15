#include <QDir>
#include <QFile>
#include <QDebug>
#include <QSqlError>

#include "dbmanager.h"

DbManager::DbManager(QObject *parent) :
    QObject(parent)
{        
}

DbManager::~DbManager()
{
    mDataBase.close();
}

bool DbManager::deleteDataBase()
{
    if(mDataBase.isOpen()){
        mDataBase.close();
    }
    if(QFile::exists(mDbPath)){
        QFile::remove(mDbPath);
    }
}

void DbManager::printError(QSqlQuery query)
{
    qDebug() << query.lastError().text();
}
void DbManager::printError()
{
    qDebug() << mDataBase.lastError().text();
}

bool DbManager::openDataBase(QString dbPath, QString name)
{
    mDataBase = QSqlDatabase::addDatabase("QSQLITE");
    mDbPath = dbPath;
    mDbPath.append(QDir::separator()).append(name);
    mDbPath = QDir::toNativeSeparators(mDbPath);
    mDataBase.setDatabaseName(mDbPath);
    // Open databasee
    qDebug() << "Open database";
    bool ret = mDataBase.open();
    if(ret && mDataBase.tables().count() != 6){
        qDebug() << "Database open, initialize.";
        ret = initializeDataBase();
    }
    if(!ret){
        printError();
    }
    return ret;
}

bool DbManager::initializeDataBase()
{
    qDebug() << "create player";
    bool ret = createTablePlayer();
    if(ret){
        qDebug() << "create player ok, make course";
        ret = createTableCourse();
        qDebug() << "course of make scorecard.";
        ret = createTableScoreCard();
    }
    return ret;
}
bool DbManager::createTablePlayer()
{
    QSqlQuery query;
    bool ret = query.exec("create table player("
                     "id integer primary key, "
                     "username varchar(100), "
                     "password varchar(50), "
                     "name varchar(100), "
                     "email varchar(100), "
                     "hcp real)");    
    if(!ret){
        printError(query);
    }
    return ret;
}


bool DbManager::createTableCourse()
{
    QSqlQuery query;
    bool ret = query.exec("create table course ("
                     "id integer primary key, "
                     "name varchar(100), "
                     "country varchar(100), "
                     "address varchar(100))");    
    if(ret){
        ret = query.exec("create table tee ("
                         "id integer primary key, "
                         "name varchar(100), "
                         "slope real, "
                         "courseid integer, "
                         "FOREIGN KEY(courseid) REFERENCES course(id) )");
        if(ret){
            ret = query.exec("create table hole ("
                             "id integer primary key, "
                             "number integer, "
                             "par integer, "
                             "hcp integer, "
                             "length integer, "
                             "teeid integer, "
                             "FOREIGN KEY(teeid) REFERENCES tee(id) )");

        }
    }
    if(!ret){
        printError(query);
    }
    return ret;
}

bool DbManager::createTableScoreCard()
{
    QSqlQuery query;
    bool ret = query.exec("create table scorecard ("
                          "id integer primary key, "
                          "startdate integer, "
                          "enddate integer, "
                          "courseid integer, "
                          "teeid integer, "
                          "FOREIGN KEY(courseid) REFERENCES course(id) "
                          "FOREIGN KEY(teeid) REFERENCES tee(id) )");

    if(ret){
        ret = query.exec("create table holescore ("
                         "id integer primary key, "
                         "number integer, "
                         "strokes integer, "
                         "puts integer, "
                         "fairway integer, "
                         "sandtrap integer, "
                         "skipped integer, "
                         "played integer, "
                         "note varchar(256), "
                         "scorecardid integer, "
                         "FOREIGN KEY(scorecardid) REFERENCES scorecard(id) )");
    }

    if(!ret){
        printError(query);
    }
    return ret;
}


Player* DbManager::loadPlayer(const QString& username, const QString& password)
{
    QSqlQuery query;
    query.prepare("SELECT id, username, password, name, email, hcp from player where username= :username");
    query.bindValue(":username", username);
    Player* player = 0;
    if(query.exec()){        
        if (query.next()){
            if(query.value(2).toString() == password){
                player = new Player(query.value(1).toString(), query.value(2).toString());
                player->setName(query.value(3).toString());
                player->setEmail(query.value(4).toString());
                player->setHcp(query.value(5).toFloat());
            }
       }
    }
    else{
        printError(query);
    }
    return player;
}

bool DbManager::savePlayer(Player* player)
{
    QSqlQuery query(mDataBase);
    query.prepare("INSERT INTO player (username, password, name, email, hcp) "
                  "VALUES (:username, :password, :name, :email, :hcp)");
    query.bindValue(":username", player->username());
    query.bindValue(":password", player->password());
    query.bindValue(":name", player->name());
    query.bindValue(":email", player->email());
    query.bindValue(":hcp", player->hcp());

    bool ret = query.exec();
    if(ret){
        player->setId(query.lastInsertId().toInt());
    }
    else{
        printError(query);
    }
    return ret;
}

bool DbManager::updatePlayer(Player* player)
{
    QSqlQuery query;
    query.prepare("UPDATE player set username = :username, password = :password, name = :name, email = :email, hcp = :hcp"
                  "WHERE id=:id");

    query.bindValue("id:", player->id());
    query.bindValue(":username", player->username());
    query.bindValue(":password", player->password());
    query.bindValue(":name", player->name());
    query.bindValue(":email", player->email());
    query.bindValue(":hcp", player->hcp());

    bool ret = query.exec();
    if(!ret){
        printError(query);
    }
    return ret;
}

bool DbManager::deletePlayer(Player* player)
{
    QSqlQuery query;
    query.prepare("DELETE from player WHERE id=:id");
    query.bindValue(":id", player->id());
    bool ret = query.exec();
    if(!ret){
        printError(query);
    }
    return ret;
}

Course* DbManager::loadCourse(int id)
{
    QSqlQuery query;
    query.prepare("SELECT id, name, country, address from course where id= :id");
    query.bindValue(":id", id);
    Course* course = 0;
    if(query.exec() && query.next()){
        course = new Course();
        course->setId(query.value(0).toInt());
        course->setName(query.value(1).toString());
        course->setCountry(query.value(2).toString());
        course->setAddress(query.value(3).toString());
        //load tees
        QSqlQuery teeQuery;
        teeQuery.prepare("SELECT id, name, slope from tee where courseid = :courseId");
        teeQuery.bindValue(":courseId", course->id());
        if(teeQuery.exec()){
            while(teeQuery.next()){
                Tee* tee = course->addTee();
                tee->setId(teeQuery.value(0).toInt());
                tee->setName(teeQuery.value(1).toString());
                tee->setSlope(teeQuery.value(2).toFloat());
                //load holes
                QSqlQuery holeQuery;
                holeQuery.prepare("SELECT id, number, par, hcp, length from hole where teeid = :teeId");
                holeQuery.bindValue(":teeId", tee->id());
                if(holeQuery.exec()){
                    while(holeQuery.next()){
                        Hole* hole = tee->addHole();
                        hole->setId(holeQuery.value(0).toInt());
                        hole->setNumber(holeQuery.value(1).toInt());
                        hole->setPar(holeQuery.value(2).toInt());
                        hole->setHcp(holeQuery.value(3).toInt());
                        hole->setLength(holeQuery.value(4).toInt());
                    }
                }
                else{
                    printError(holeQuery);
                }
            }            
        }
        else{
            printError(teeQuery);
        }
    }
    else{
        printError();
    }
    return course;
}


bool DbManager::saveCourse(Course* course)
{
    mDataBase.transaction();
    bool needRollBack = false;
    QSqlQuery query;
    query.prepare("INSERT into course (name, country, address) values (:name, :country, :address)");
    query.bindValue(":name", course->name());
    query.bindValue(":address", course->address());
    query.bindValue(":country", course->country());
    if(query.exec()){
        course->setId(query.lastInsertId().toInt());
        //insert tees
        foreach(Tee* tee, course->tees()){
            QSqlQuery teeQuery;
            teeQuery.prepare("INSERT into tee (name, slope, courseid) values (:name, :slope, :courseid)");
            teeQuery.bindValue(":name", tee->name());
            teeQuery.bindValue(":slope", tee->slope());
            teeQuery.bindValue(":courseid", course->id());
            if(!teeQuery.exec()){
                teeQuery.finish();
                needRollBack = true;
                printError(teeQuery);
                break;
            }
            tee->setId(teeQuery.lastInsertId().toInt());
            teeQuery.finish();
            foreach(Hole* hole, tee->holes()){
                QSqlQuery holeQuery;
                holeQuery.prepare("INSERT into hole (number, par, hcp, lenght, teeid) values (:number, :par, :hcp, :lenght, :teeid)");
                holeQuery.bindValue(":number", hole->number());
                holeQuery.bindValue(":par", hole->par());
                holeQuery.bindValue(":hcp", hole->hcp());
                holeQuery.bindValue(":lenght", hole->length());
                holeQuery.bindValue(":teeid", tee->id());
                if(!holeQuery.exec()){
                    holeQuery.finish();
                    needRollBack = true;
                    printError(holeQuery);
                    break;
                }
                hole->setId(holeQuery.lastInsertId().toInt());
                holeQuery.finish();
            }
            if(needRollBack) {break;}
        }
    }
    if(needRollBack){
        printError(query);
        mDataBase.rollback();
        return false;
    }
    return true;
}

bool DbManager::updateCourse(Course* course)
{
    mDataBase.transaction();
    bool needRollBack = false;
    QSqlQuery query;
    query.prepare("UPDATE course set name = :name ,country = : country, address =  :address where id = :id");
    query.bindValue(":id", course->id());
    query.bindValue(":name", course->name());
    query.bindValue(":address", course->address());
    query.bindValue(":country", course->country());
    if(query.exec()){
        foreach(Tee* tee, course->tees()){
            QSqlQuery teeQuery;
            teeQuery.prepare("UPDATE tee set name = :name, slope = :slope values where id = :id");
            teeQuery.bindValue(":name", tee->name());
            teeQuery.bindValue(":slope", tee->slope());
            teeQuery.bindValue(":id", tee->id());
            if(!teeQuery.exec()){
                teeQuery.finish();
                needRollBack = true;
                printError(teeQuery);
                break;
            }
            tee->setId(teeQuery.lastInsertId().toInt());
            teeQuery.finish();
            foreach(Hole* hole, tee->holes()){
                QSqlQuery holeQuery;
                holeQuery.prepare("UPDATE hole set number = :number, par = :par, hcp = :hcp, lenght = :length where id=:id");
                holeQuery.bindValue(":number", hole->number());
                holeQuery.bindValue(":par", hole->par());
                holeQuery.bindValue(":hcp", hole->hcp());
                holeQuery.bindValue(":lenght", hole->length());
                holeQuery.bindValue(":id", hole->id());
                if(holeQuery.exec()){
                    holeQuery.finish();
                    needRollBack = true;
                    printError(holeQuery);
                    break;
                }
                hole->setId(holeQuery.lastInsertId().toInt());
                holeQuery.finish();
            }
            if(needRollBack) {break;}
        }
    }
    if(needRollBack){
        printError(query);
        mDataBase.rollback();
        return false;
    }
    return true;


}

bool DbManager::deleteCourse(Course* course)
{
    mDataBase.transaction();
    bool needRollBack = false;
    foreach(Tee* tee, course->tees()){
        QSqlQuery holeQuery;
        holeQuery.prepare("DELETE from hole where teeid: teeid");
        holeQuery.bindValue(":teeid", tee->id());
        if(!holeQuery.exec()){
            needRollBack = true;
            printError(holeQuery);
            break;
        }
    }
    if(!needRollBack){
         QSqlQuery teeQuery;
         teeQuery.prepare("DELETE from tee where courseid = :id");
         teeQuery.bindValue(":id", course->id());
         if(!teeQuery.exec()){
            needRollBack = true;
            printError(teeQuery);
         }
         else{
             QSqlQuery query;
             query.prepare("DELETE from course WHERE id=:id");
             query.bindValue(":id", course->id());
             if(!query.exec()){
                needRollBack = true;
                printError(query);
             }
         }
    }
    if(needRollBack){
        printError();
        mDataBase.rollback();
        return false;
    }
    return true;
}

ScoreCard* DbManager::loadScoreCard(Player* player, int id)
{
    QSqlQuery query;
    query.prepare("SELECT id, startdate, enddate, courseid, teeid, finished from scorecard where id= :id");
    query.bindValue(":id", id);
    ScoreCard* scoreCard = 0;
    if(query.exec() && query.next()){
        scoreCard = player->newRound();
        scoreCard->setId(query.value(0).toInt());
        scoreCard->setStartDate(query.value(1).toDateTime());
        if(query.value(5).toBool()){
            scoreCard->setEndDate(query.value(2).toDateTime());
        }
        //load course and tee
        Course* course = loadCourse(query.value(3).toInt());
        if(course){
            scoreCard->setCourse(course);
            scoreCard->setTee(course->tee(query.value(4).toInt()));
        }
        //load scored
        QSqlQuery holeQuery;
        holeQuery.prepare("SELECT number, strokes, puts, fairway, sandtrap, note from holescore where scorecardid = :id");
        holeQuery.bindValue(":id", scoreCard->id());
        if(holeQuery.exec()){
            while(holeQuery.next()){
                HoleScore* score = scoreCard->holeAt(query.value(0).toInt());
                if(score){
                    score->setStrokes(holeQuery.value(1).toInt());
                    score->setPuts(holeQuery.value(2).toInt());
                    score->setFairway(holeQuery.value(3).toBool());
                    score->setSandtrap(holeQuery.value(4).toBool());
                    score->setNote(holeQuery.value(5).toString());
                }
            }
        }
        else{
            printError(holeQuery);
        }
    }
    else{
        printError(query);
    }
    return scoreCard;
}

ScoreCard* DbManager::createScoreCard(Player* player, Course* course, Tee* tee)
{ 
    QSqlQuery query;
    query.prepare("INSERT into scorecard (finished, courseid, teeid) values ( :finished, :courseId, :teeId)");
    query.bindValue(":finished", false);
    query.bindValue(":courseid", course->id());
    query.bindValue(":teeid", tee->id());
    ScoreCard* scoreCard = 0;
    if(query.exec()){
        scoreCard = player->newRound();
        scoreCard->setId(query.lastInsertId().toInt());
        scoreCard->setCourse(course);
        scoreCard->setTee(tee);
        foreach(HoleScore* score, scoreCard->holeScores()){
            QSqlQuery holeQuery;
            holeQuery.prepare("INSERT into holescore (scorecardid, number, skipped, played, fairway, sandtrap) "
                              "values (:id, :number, :skipped, :played, :fairway, :sandtrap)");
            holeQuery.bindValue(":id", scoreCard->id());
            holeQuery.bindValue(":skipped", score->skipped());
            holeQuery.bindValue(":spalyed", score->played());
            holeQuery.bindValue(":fairway", score->fairway());
            holeQuery.bindValue(":sandtrap", score->sandtrap());
            if(holeQuery.exec()){
                score->setId(holeQuery.lastInsertId().toInt());
            }
            else{
                printError(holeQuery);
            }
        }
    }
    else{
        printError(query);
    }
    return scoreCard;
}

bool DbManager::saveScoreCard(ScoreCard* scoreCard)
{
    mDataBase.transaction();
    bool needRollBack = false;
    QSqlQuery query;
    query.prepare("Update scorecard set finished = :finished, courseid= :courseid, teeid = :teeId where id = :id");
    query.bindValue(":id", scoreCard->id());
    query.bindValue(":finished", scoreCard->isFinished());
    query.bindValue(":courseid", scoreCard->course()->id());
    query.bindValue(":teeid", scoreCard->tee()->id());
    if(query.exec()){
        foreach(HoleScore* score, scoreCard->holeScores()){
            QSqlQuery holeQuery;
            holeQuery.prepare("UPDATE holescore set number = :number, strokes = :strokes, puts = :puts,"
                              "fairway = :fairway, sandtrap = :sandtrap, note = :note where id = :id");
            holeQuery.bindValue(":id", score->id());
            holeQuery.bindValue(":number", score->number());
            holeQuery.bindValue(":strokes", score->strokes());
            holeQuery.bindValue(":puts", score->puts());
            holeQuery.bindValue(":fairway", score->fairway());
            holeQuery.bindValue(":sandtrap", score->sandtrap());
            holeQuery.bindValue(":note", score->note());
            if(!holeQuery.exec()){
                needRollBack = true;
                printError(holeQuery);
                break;
            }
        }
    }
    if(needRollBack){        
        printError(query);
        mDataBase.rollback();
        return false;
    }
    return true;
}

bool DbManager::deleteScoreCard(ScoreCard* scoreCard)
{
    mDataBase.transaction();
    bool needRollBack = false;

    QSqlQuery holeQuery;
    holeQuery.prepare("DELETE from holescore where scorecardid = :id");
    holeQuery.bindValue(":id", scoreCard->id());
    if(holeQuery.exec()){
         QSqlQuery query;
         query.prepare("DELETE from scorecard where id= :id");
         query.bindValue(":id", scoreCard->id());
         if(!query.exec()){
            needRollBack = true;
            printError(query);
         }
    }

    if(needRollBack){        
        printError(holeQuery);
        mDataBase.rollback();
        return false;
    }
    return true;
}




