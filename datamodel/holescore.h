#ifndef HOLESCORE_H
#define HOLESCORE_H

#include <QObject>
#include "storable.h"

class HoleScore : public QObject, public Storable
{
    Q_OBJECT
    Q_INTERFACES(Storable)

public:
    explicit HoleScore(int number, QObject *parent = 0);
    ~HoleScore();

    Q_INVOKABLE int number();

    Q_INVOKABLE void setStrokes(int strokes);
    Q_INVOKABLE int strokes();

    Q_INVOKABLE void setPuts(int puts);
    Q_INVOKABLE int puts();

    Q_INVOKABLE void setFairway(bool hit);
    Q_INVOKABLE bool fairway();

    Q_INVOKABLE void setSandtrap(bool hit);
    Q_INVOKABLE bool sandtrap();

    Q_INVOKABLE void setNote(QString note);
    Q_INVOKABLE QString note();

    void serializeToSql();
    QString serializeToJson();


private:
    int mNumber;
    int mStrokes;
    int mPuts;
    bool mFairway;
    bool mSandTrap;
    QString mNotes;
    
};

#endif // HOLESCORE_H
