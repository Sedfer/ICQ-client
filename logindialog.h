#pragma once

#include <QtNetwork>
#include <QtWidgets>

class LoginDialog : public QDialog
{
    Q_OBJECT
private:
    QLineEdit *name;
    QLineEdit *password;

signals:
    void buttonClickedLogin(const QString &name, const QString &password);
    void buttonClickedRegister(const QString &name, const QString &password);
    void buttonClickedCancel();

private slots:
    void slotLogin();
    void slotRegister();

public:
    LoginDialog(QWidget *parent);
    ~LoginDialog();
};
