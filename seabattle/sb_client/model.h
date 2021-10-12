#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QObject>
#include "field.h"

enum State {
    PLACING_SHIPS,
    WAITING_ENEMY,
    WAITING_STEP,
    MAKING_STEP
};


class Model: public QObject
{
    Q_OBJECT
public:
    Model();
    ~Model();
    State getState() const;
    void setState( State );
    Cell getMyCell( int x, int y ) const;
    void setMyCell( int x, int y, Cell cell );
    Cell getEnemyCell( int x, int y ) const;
    void setEnemyCell( int x, int y, Cell cell );
    void clearEnemyField();
    void clearMyField();
    bool validatePoint(int x, int y) const;
    bool validateMyField() const;
    void setLogin(const QString& login_);
    void setUserId(const quint16 userId_);
    QString getLogin() const;
    quint16 getUserId() const;
    void setEnemyUserId(const quint16 enemyUserId_);
    quint16 getEnemyUserId() const;
    void setEnemyLogin(const QString enemyLogin_);
    QString getEnemyLogin() const;
    void disconnect();
    bool isAlive();
    bool isShipKilled(int x, int y);
    void markKilledShip(int x, int y, bool isEnemy);
private:
    Field *my_field_, *enemy_field_;
    State state_;
    QString login;
    quint16 userId;
    quint16 enemyUserId;
    QString enemyLogin;
private:
    void initNears(nears& nears_, int x, int y) const;
    bool isShip(int decks, int x, int y) const;
    int calcDecks(nears& nears_, int x, int y, bool offset) const;
    int shipCount(int decks) const;
};

#endif // MODEL_H
