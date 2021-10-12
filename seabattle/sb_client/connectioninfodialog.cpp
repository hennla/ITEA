#include "connectioninfodialog.h"
#include "ui_connectioninfodialog.h"

ConnectionInfoDialog::ConnectionInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionInfoDialog)
{
    ui->setupUi(this);
    ui->serverIpEdit->setInputMask("000.000.000.000");
    ui->portEdit->setValue(1234);
    connect(ui->applyButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

ConnectionInfoDialog::~ConnectionInfoDialog()
{
    delete ui;
}

void ConnectionInfoDialog::setAddressString(const QString& address_, quint16 port_) {
    ui->serverIpEdit->setText(address_);
    ui->portEdit->setValue(port_);
}

void ConnectionInfoDialog::setLogin(const QString& login_) {
    ui->loginEdit->setText(login_);
}

QString ConnectionInfoDialog::getAddress() const {
    return address;
}

quint16 ConnectionInfoDialog::getServerPort() const {
    return port;
}

QString ConnectionInfoDialog::getLogin() const {
    return login;
}

void ConnectionInfoDialog::accept() {
    QHostAddress serverIp;
    if(serverIp.setAddress(ui->serverIpEdit->text())) {
        address = serverIp.toString();
        port    = ui->portEdit->value();
        login   = ui->loginEdit->text();
        if (!login.isEmpty()) {
            done(QDialog::Accepted);
        } else {
            QMessageBox::warning(
                        this,
                        "Warning",
                        "Specify the valid login"
                        );
            ui->loginEdit->setFocus();
        }

    } else {
        QMessageBox::warning(
                    this,
                    "Warning",
                    "Specify the valid IPv4 address"
                    );
        ui->serverIpEdit->setFocus();
    }
}
