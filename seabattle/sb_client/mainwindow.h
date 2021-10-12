#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QMessageBox>
#include "model.h"
#include "controller.h"
#include "images.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void redraw();
    void on_actionStart_triggered();
    void showGameResult(GameResult result);
    void showGameError( GameErrorMessage message );
    void on_actionClear_triggered();
    void on_actionLeave_triggered();
    void on_actionExit_triggered();
protected:
    void paintEvent( QPaintEvent* event );
    void mousePressEvent( QMouseEvent* event );
    void closeEvent (QCloseEvent *event);
private:
    void setStatus(QString status);
    void setEnemyName();
    QImage myFieldImage();
    QImage enemyFieldImage();
    QImage getFieldImage( char );
private:
    Ui::MainWindow *ui;
    Model *model_;
    Controller *controller_;
};
#endif // MAINWINDOW_H
