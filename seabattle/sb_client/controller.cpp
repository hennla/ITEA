#include "controller.h"
#include <QDebug>

const quint16 DEFAULT_SERVER_PORT = 1234;
const quint16 DEFAULT_SERVER_TIMEOUT = 5000;

Controller::Controller(Model *model) : model_(model),
    serverAddress(QHostAddress::LocalHost),
    serverPort(DEFAULT_SERVER_PORT)
{
    client = new QTcpSocket(this);

    connect(
                client, SIGNAL(readyRead()),
                this, SLOT(onReceived())
                );

    connect(
                client, SIGNAL(connected()),
                this, SLOT(onConnected())
                );

    connect(
                client, SIGNAL(errorOccurred(QAbstractSocket::SocketError)),
                this, SLOT(onError(QAbstractSocket::SocketError))
                );

}

Controller::~Controller() = default;

void Controller::parseData( const QString& data ){
    parseUserId(data);
    parseEnemyUserId(data);
    parseEnemyStep(data);
    parseMyStepResult(data);
    parseDisconnect(data);
}

bool Controller::parseUserId(const QString& data) {
    QStringList dataList = data.split("::");
    if (dataList[0] != "USERID") {
        return false;
    }
    qDebug() << "Setting user id :" << dataList[3];
    model_->setUserId(dataList[3].toUInt());
    model_->setState(WAITING_ENEMY);
    QString cmd = QString("GET_ENEMY::0::%1::END")
            .arg(model_->getUserId());
    client->write(cmd.toLocal8Bit());
    emit stateChanged();
    return true;
}

bool Controller::parseEnemyUserId(const QString& data) {
    QStringList dataList = data.split("::");
    if (dataList[0] != "ENEMY_USERID") {
        return false;
    }
    model_->setEnemyUserId(dataList[3].toUInt());
    model_->setEnemyLogin(dataList[4]);
    qDebug() << "Setting enmy user id :" << dataList[3];
    if (dataList[5] == "GO") {
        model_->setState(MAKING_STEP);
    }
    else {
        model_->setState(WAITING_STEP);
    }

    emit stateChanged();
    return true;
}

bool Controller::parseEnemyStep(const QString& data) {
    QStringList dataList = data.split("::");
    if (dataList[0] != "SHOT") {
        return false;
    }
    int x = dataList[3].toInt();
    int y = dataList[4].toInt();

    QString cmd;
    GameResult currGameResult = GAME_NONE;
    Cell cell = model_->getMyCell(x, y);

    if (cell == CL_CLEAR) {
        cmd = QString("SHOT_RESULT::%1::%2::PAST::END")
                .arg(model_->getEnemyUserId())
                .arg(model_->getUserId());
        model_->setMyCell(x, y, CL_DOT);
        model_->setState(MAKING_STEP);
    } else if (cell == CL_SHIP) {
        model_->setMyCell(x, y, CL_DAMAGE);
        if (model_->isShipKilled(x, y)) {
            model_->markKilledShip(x, y, false);
            if (!model_->isAlive()) {
                cmd = QString("SHOT_RESULT::%1::%2::WIN::%3::%4::END")
                        .arg(model_->getEnemyUserId())
                        .arg(model_->getUserId())
                        .arg(x)
                        .arg(y);
                model_->setState(PLACING_SHIPS);
                currGameResult = GAME_LOST;
            } else {
                cmd = QString("SHOT_RESULT::%1::%2::KILL::%3::%4::END")
                        .arg(model_->getEnemyUserId())
                        .arg(model_->getUserId())
                        .arg(x)
                        .arg(y);
                model_->setState(WAITING_STEP);
            }
        } else {
            cmd = QString("SHOT_RESULT::%1::%2::DAMAGE::%3::%4::END")
                    .arg(model_->getEnemyUserId())
                    .arg(model_->getUserId())
                    .arg(x)
                    .arg(y);
            model_->setState(WAITING_STEP);
        }

    }

    client->write(cmd.toLocal8Bit());
    qDebug() << "Send to server: " <<cmd.toLocal8Bit();
    if (currGameResult != GAME_NONE) {
        emit gameResult(currGameResult);
    } else {
        emit stateChanged();
    }
    return true;
}

bool Controller::parseMyStepResult(const QString& data) {
    QStringList dataList = data.split("::");
    if (dataList[0] != "SHOT_RESULT") {
        return false;
    }

    if(dataList[3] == "PAST") {
        model_->setState(WAITING_STEP);
    } else {
        int x = dataList[4].toInt();
        int y = dataList[5].toInt();
        if (dataList[3] == "WIN") {
            model_->markKilledShip(x, y, true);
            model_->setState(PLACING_SHIPS);
            emit gameResult(GAME_WON);
        } else if (dataList[3] == "DAMAGE" || dataList[3] == "KILL") {
            model_->setEnemyCell(x, y, CL_DAMAGE);
            if (dataList[3] == "KILL") {
                model_->markKilledShip(x, y, true);
            }
            model_->setState(MAKING_STEP);
        }
    }
    emit stateChanged();
    return true;
}

bool Controller::parseDisconnect(const QString& data) {
    QStringList dataList = data.split("::");
    if (dataList[0] != "DISCONNECT") {
        return false;
    }
    qDebug() << "Enemy disconnecting from host";
    client->disconnectFromHost();
    model_->clearEnemyField();
    model_->clearMyField();

    if (model_->getState() != PLACING_SHIPS) {
        model_->setState(PLACING_SHIPS);
        model_->disconnect();
    }
    emit gameError(GAME_ERROR_USER_DISCONNECTED);
    return true;
}

bool Controller::parseErrorMessage(const QString& data) {
    QStringList dataList = data.split("::");
    if (dataList[0] != "ERROR_MESSAGE") {
        return false;
    }
    qDebug() << "Error from server:" << dataList[3] <<"! Message: "<<dataList[4];
    emit gameError(GAME_ERROR_SERVER_ERROR);
    return true;
}

State Controller::getState() const {
    return model_->getState();
}

QPoint Controller::getMyFieldCoord(const QPoint& pos) {
    QPoint res;
    res.setX( -1 );
    res.setY( -1 );

    if(pos.x() < MY_FIELD_X || pos.x() > (MY_FIELD_X + FIELD_WIDTH) ||
            pos.y() < MY_FIELD_Y || pos.y() > (MY_FIELD_Y + FIELD_HEIGHT)) {
        return res;
    }

    res.setX( 1.0 * (pos.x() - MY_FIELD_X) / (0.1 * FIELD_WIDTH) );
    res.setY( 1.0 * (pos.y() - MY_FIELD_Y) / (0.1 * FIELD_HEIGHT) );
    return res;
}

QPoint Controller::getEnemyFieldCoord(const QPoint& pos) {
    QPoint res;
    res.setX( -1 );
    res.setY( -1 );

    if(pos.x() < ENEMY_FIELD_X || pos.x() > (ENEMY_FIELD_X + FIELD_WIDTH) ||
            pos.y() < ENEMY_FIELD_Y || pos.y() > (ENEMY_FIELD_Y + FIELD_HEIGHT)) {
        return res;
    }

    res.setX( 1.0 * (pos.x() - ENEMY_FIELD_X) / (0.1 * FIELD_WIDTH) );
    res.setY( 1.0 * (pos.y() - ENEMY_FIELD_Y) / (0.1 * FIELD_HEIGHT) );
    return res;
}

void Controller::onMousePressed( const QPoint& position, bool set_ship ) {

    if( model_->getState() == PLACING_SHIPS )
    {
        QPoint point = getMyFieldCoord( position );
        qDebug() << point.x()<< " : " << point.y();
        if( point.x() == -1 || point.y() == -1 )
            return;
        if (set_ship && !model_->validatePoint(point.x(),point.y())) {
            return;
        }
        model_->setMyCell( point.x(), point.y(), set_ship ? CL_SHIP : CL_CLEAR );
        emit stateChanged();
        return;
    }
    if( model_->getState() == MAKING_STEP )
    {
        QPoint point = getEnemyFieldCoord(position);
        if( point.x() == -1 || point.y() == -1 )
            return;
        Cell cell = model_->getEnemyCell(point.x(), point.y());

        if( cell != CL_CLEAR )
            return;
        model_->setEnemyCell(point.x(), point.y(), CL_DOT);
        QString cmd = QString("SHOT::%1::%2::%3::%4::END")
                        .arg(model_->getEnemyUserId())
                        .arg(model_->getUserId())
                        .arg(point.x())
                        .arg(point.y());

        client->write(cmd.toLocal8Bit()); //cmd.toLocal8Bit()
        qDebug() << "Send to server: " <<cmd;
        model_->setState(WAITING_STEP);
        emit stateChanged();
    }
}

void Controller::setConnectionInfo(QString & adress, quint16 port) {
    serverAddress = QHostAddress(adress);
    serverPort = port;
}

void Controller::onReceived()
{
    QString data;
    data = client->readAll();
    qDebug() << "Recieve from server:" << data;
    parseData(data);
    emit stateChanged();
}

void Controller::onError( QAbstractSocket::SocketError socketError )
{
    qDebug() << client->errorString();

    if(
        model_->getState() == WAITING_STEP ||
        model_->getState() == MAKING_STEP
    )
        model_->setState( PLACING_SHIPS );

    if( socketError == QAbstractSocket::ConnectionRefusedError )
        emit gameError( GAME_ERROR_SERVER_CONNECTION_REFUSED );

    if(
        socketError == QAbstractSocket::HostNotFoundError ||
        socketError == QAbstractSocket::SocketTimeoutError
    )
        emit gameError( GAME_ERROR_SERVER_UNAVAILABLE );
}

void Controller::onConnected()
{
    QString response;
    QString request;
    connectionError = false;

    request = QString( "LOGIN::0::0::%1::END" )
        .arg(model_->getLogin());

    client->write( request.toLocal8Bit() );

    if( !client->waitForReadyRead(DEFAULT_SERVER_TIMEOUT) )
        return;

    if( connectionError )
        return;

    response = client->readAll();

    qDebug() << response;

    model_->setState(WAITING_ENEMY);

    emit stateChanged();
}

void Controller::onGameStart() {
    if (!model_->validateMyField()) {
        emit gameError(GAME_ERROR_WRONG_FIELD);
        return;
    }

    if(client->state() == QAbstractSocket::ConnectedState)
    {
        emit gameError(GAME_ERROR_ALREADY_CONNECTED);
        return;
    }

    client->connectToHost( serverAddress, serverPort );

    if(!client->waitForConnected(DEFAULT_SERVER_TIMEOUT))
    {
        if(client->error() == QAbstractSocket::SocketTimeoutError)
            emit gameError(GAME_ERROR_SERVER_CONNECTION_TIMEOUT);

        return;
    }
}

void Controller::onGameQuit()
{
    if( client->state() == QAbstractSocket::ConnectedState )
    {
        qDebug() << "Disconnecting from host";
        QString cmd = QString("DISCONNECT::%1::%2::END")
                .arg(model_->getEnemyUserId())
                .arg(model_->getUserId());
        client->write(cmd.toLocal8Bit());
        client->flush();
        client->disconnectFromHost();
        model_->clearEnemyField();
        model_->clearMyField();
        model_->setState( PLACING_SHIPS );
        model_->disconnect();
    }
}

QString Controller::getServerAddress() const
{
    return serverAddress.toString();
}

quint16 Controller::getServerPort() const
{
    return serverPort;
}

QString Controller::getLogin() const
{
    return model_->getLogin();
}

void Controller::setLogin(QString & login) {
    model_->setLogin(login);
}
