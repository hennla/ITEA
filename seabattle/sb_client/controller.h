#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QPoint>
#include <QTcpSocket>
#include <QHostAddress>
#include "model.h"
#include "def_con.h"


enum GameResult
{
    GAME_NONE = 0,
    GAME_WON = 1,
    GAME_LOST = -1
};

enum GameErrorMessage
{
    GAME_ERROR_UNKNOWN = -1,
    GAME_ERROR_NONE = 0,
    GAME_ERROR_WRONG_FIELD,
    GAME_ERROR_ALREADY_CONNECTED,
    GAME_ERROR_USER_DISCONNECTED,
    GAME_ERROR_SERVER_ERROR,
    GAME_ERROR_SERVER_CONNECTION_REFUSED,
    GAME_ERROR_SERVER_CONNECTION_TIMEOUT,
    GAME_ERROR_SERVER_UNAVAILABLE
};


class Controller : public QWidget
{
    Q_OBJECT
public:
    Controller(Model *model);
    ~Controller();
    void onMousePressed(const QPoint& position, bool set_ship = true);
    void onGameStart();
    void onGameQuit();
    State getState() const;
    QString getLogin() const;
    void setLogin(QString & login);
    void setConnectionInfo(QString & adress, quint16 port);
    QString getServerAddress() const;
    quint16 getServerPort() const;
private slots:
    void onReceived();
    void onConnected();
    void onError(QAbstractSocket::SocketError socketError);
signals:
    void stateChanged();
    void gameError(GameErrorMessage message);
    void gameResult(GameResult result);

private:
    QPoint getMyFieldCoord( const QPoint& pos );
    QPoint getEnemyFieldCoord( const QPoint& pos );
    void parseData(const QString& data);
    bool parseUserId(const QString& data);
    bool parseEnemyUserId(const QString& data);
    bool parseEnemyStep(const QString& data);
    bool parseMyStepResult(const QString& data);
    bool parseDisconnect(const QString& data);
    bool parseErrorMessage(const QString& data);
private:
    Model *model_;
    QTcpSocket* client;
    QHostAddress serverAddress;
    quint16 serverPort;
    bool connectionError;
};

#endif // CONTROLLER_H
