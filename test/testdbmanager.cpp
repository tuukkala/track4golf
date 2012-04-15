#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QFile>

#include "../domain/dbmanager.h"
#include "../domain/player.h"

const char* const TESTDBS = "track4GolfTestDbs";
const char* const CREDENTIALS = "test";
const char* const NAME = "John Doe";
const char* const EMAIL = "john@doe.com";
const float HCP = 10;


class TestDbManager : public QObject
{
    Q_OBJECT
    
public:
    TestDbManager();
    ~TestDbManager();
    
private Q_SLOTS:
    void testCreateDb();
    void testCreatePlayer();

private:
    QString dbPath;
};

TestDbManager::TestDbManager()
{
    if(!QDir::home().exists(TESTDBS)){
        QDir::home().mkdir(TESTDBS);
    }

    dbPath = QDir::home().path();
    dbPath.append(QDir::separator());
    dbPath.append(TESTDBS);

    QDir dir(dbPath);
    foreach(QFileInfo entry, dir.entryInfoList()){
        if(entry.absoluteFilePath().endsWith("sqlite")){
            qDebug() << "Remove db: " << entry.absoluteFilePath();
            QFile::remove(entry.absoluteFilePath());
        }
    }
}

TestDbManager::~TestDbManager()
{

}

void TestDbManager::testCreateDb()
{
    QString db = "testCreateDb.db.sqlite";
    DbManager manager;
    QVERIFY(manager.openDataBase(dbPath, db));
}

void TestDbManager::testCreatePlayer()
{
    QString db = "testCreatePlayer.db.sqlite";

    DbManager manager;
    QVERIFY(manager.openDataBase(dbPath, db));
    Player* player = new Player(CREDENTIALS, CREDENTIALS);
    player->setName(NAME);
    player->setHcp(HCP);
    player->setEmail(EMAIL);
    QVERIFY(player->name() == NAME);
    QVERIFY(player->hcp() == HCP);
    QVERIFY(player->email() == EMAIL);
    QVERIFY(manager.savePlayer(player));
    delete player;
    player = manager.loadPlayer(CREDENTIALS, CREDENTIALS);
    QVERIFY(player != 0);
    QVERIFY(player->name() == NAME);
    QVERIFY(player->hcp() == HCP);
    QVERIFY(player->email() == EMAIL);
}

QTEST_APPLESS_MAIN(TestDbManager)

#include "testdbmanager.moc"
