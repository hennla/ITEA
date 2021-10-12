#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "connectioninfodialog.h"
#include "./ui_connectioninfodialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pictures_.load();

    ui->gameStatusLabel->setStyleSheet( "QLabel { color : #00157f; }" );
    ui->labelEnemy->setStyleSheet( "QLabel { color : #00157f; }" );
    ui->labelEnemy->clear();

    model_ = new Model;
    controller_ = new Controller( model_ );
    connect( controller_, SIGNAL(stateChanged()), this, SLOT(redraw()));
    connect(
        controller_,
        SIGNAL(gameResult(GameResult)),
        this,
        SLOT(showGameResult(GameResult))
    );
    connect(
        controller_,
        SIGNAL(gameError(GameErrorMessage)),
        this,
        SLOT(showGameError(GameErrorMessage))
    );
    this->redraw();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setStatus(QString status) {
    ui->gameStatusLabel->setText("Status: " + status);
}

void MainWindow::setEnemyName() {
    ui->labelEnemy->setText("Enemy name: " + model_->getEnemyLogin());
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED( event );

    const int deltaY = this->centralWidget()->y();

    QPainter painter( this );
    painter.drawImage(
        0,
        deltaY,
        pictures_.get("field")
    );

    painter.drawImage( MY_FIELD_X, MY_FIELD_Y + deltaY, myFieldImage() );
    painter.drawImage( ENEMY_FIELD_X, ENEMY_FIELD_Y + deltaY, enemyFieldImage() );

    setEnemyName();

    switch( controller_->getState() )
    {
    case PLACING_SHIPS:
        setStatus( "placing ships");
        break;

    case MAKING_STEP:
        setStatus("your step");
        break;

    case WAITING_STEP:
        setStatus("wait for enemy step");
        break;
    case WAITING_ENEMY:
        setStatus("wait for enemy join");
        break;
    }
}

void MainWindow::mousePressEvent( QMouseEvent* event ) {
    QPoint pos = event->pos();
    pos.setY( pos.y() - this->centralWidget()->y() );
    controller_->onMousePressed( pos, event->button() == Qt::LeftButton );
}

void MainWindow::closeEvent (QCloseEvent *event) {
    controller_->onGameQuit();
}

QImage MainWindow::myFieldImage() {
    return getFieldImage(0);
}

QImage MainWindow::enemyFieldImage() {
    return getFieldImage(1);
}

QImage MainWindow::getFieldImage( char fld){
    QImage image( FIELD_WIDTH, FIELD_HEIGHT, QImage::Format_ARGB32 );
    Cell cell;
    image.fill( 0 );
    QPainter painter( &image );

    double cfx = 1.0 * FIELD_WIDTH / FIELD_LENGTH;
    double cfy = 1.0 * FIELD_HEIGHT / FIELD_LENGTH;

    for( int i = 0; i < FIELD_LENGTH; i++ )
        for( int j = 0; j < FIELD_LENGTH; j++ )
        {
            if( fld == 0 )
                cell = model_->getMyCell( i, j );
            else
                cell = model_->getEnemyCell( i, j );

            switch( cell )
            {
            case CL_DOT:
                painter.drawImage( i * cfx, j * cfy, pictures_.get("dot") );
                break;

            case CL_DAMAGE:
                painter.drawImage(
                    i * cfx,
                    j * cfy,
                    fld ? pictures_.get("half") : pictures_.get("redhalf")
                );
                break;
            case CL_KILL:
                painter.drawImage(
                    i * cfx,
                    j * cfy,
                    fld ? pictures_.get("full") : pictures_.get("redfull")
                );
                break;
            case CL_SHIP:
                painter.drawImage( i * cfx, j * cfy, pictures_.get("deck") );
                break;

            default:
                break;
            }
        }

    return image;
}

void MainWindow::redraw() {
    if (controller_->getState() == PLACING_SHIPS) {
        ui->actionStart->setDisabled(false);
        ui->actionLeave->setDisabled(true);
        ui->menuField->setDisabled(false);
        ui->labelEnemy->clear();
    } else {
        ui->actionStart->setDisabled(true);
        ui->actionLeave->setDisabled(false);
        ui->menuField->setDisabled(true);
    }

    this->update();
}

void MainWindow::on_actionStart_triggered()
{
    ConnectionInfoDialog* connectionDialog = new ConnectionInfoDialog(this);

    connectionDialog->setModal(true);
    connectionDialog->setAddressString(
                controller_->getServerAddress(),
                controller_->getServerPort()
                );
    connectionDialog->setLogin(controller_->getLogin());


    if( connectionDialog->exec() != QDialog::Accepted )
        return;
    QString address = connectionDialog->getAddress();
    QString login   = connectionDialog->getLogin();
    controller_->setLogin(login);
    controller_->setConnectionInfo(
                address,
                connectionDialog->getServerPort()
                );

    controller_->onGameStart();
    redraw();
}

void MainWindow::showGameResult(GameResult result)
{
    if( result == GAME_NONE )
        return;

    QString messageString = result == GAME_WON
        ? "You win!"
        : "You lose!";

    this->update();
    QMessageBox::information( this, "Game result", messageString );
    controller_->onGameQuit();
}

void MainWindow::showGameError(GameErrorMessage message)
{
    QString messageString;

    switch(message)
    {
    case GAME_ERROR_WRONG_FIELD:
        messageString = "Wrong ships placement!";
        break;

    case GAME_ERROR_USER_DISCONNECTED:
        messageString = "Enemy disconnected!";
        break;

    case GAME_ERROR_ALREADY_CONNECTED:
        messageString = "You are already connected!";
        break;

    case GAME_ERROR_SERVER_ERROR:
        messageString = "Server error!";
        break;

    case GAME_ERROR_SERVER_CONNECTION_REFUSED:
    case GAME_ERROR_SERVER_UNAVAILABLE:
        messageString = "Cannot connect to the server.";
        break;

    case GAME_ERROR_SERVER_CONNECTION_TIMEOUT:
        messageString = "Server unavailable.";
        break;

    default:
        return;
    }

    this->update();
    QMessageBox::information( this, "Game Error", messageString );
}

void MainWindow::on_actionClear_triggered()
{
    model_->clearMyField();
    model_->clearEnemyField();
    this->update();
}


void MainWindow::on_actionLeave_triggered()
{
    controller_->onGameQuit();

    QMessageBox::information(
        this,
        "Info",
        "You have disconnected!");

    redraw();
}


void MainWindow::on_actionExit_triggered()
{
    controller_->onGameQuit();
    close();
}

