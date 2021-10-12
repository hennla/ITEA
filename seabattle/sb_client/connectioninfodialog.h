#ifndef CONNECTIONINFODIALOG_H
#define CONNECTIONINFODIALOG_H

#include <QDialog>
#include <QHostAddress>
#include <QMessageBox>

namespace Ui {
class ConnectionInfoDialog;
}

class ConnectionInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionInfoDialog(QWidget *parent = nullptr);
    ~ConnectionInfoDialog();

    void setAddressString(const QString& address_, quint16 port_);
    void setLogin(const QString& login_);
    QString getAddress() const;
    quint16 getServerPort() const;
    QString getLogin() const;

public slots:
    void accept();

private:
    Ui::ConnectionInfoDialog *ui;
    QString address;
    QString login;
    quint16 port;
};

#endif // CONNECTIONINFODIALOG_H
