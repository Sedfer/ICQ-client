#include "logindialog.h"


LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *layout1 = new QHBoxLayout();
    QHBoxLayout *layout2 = new QHBoxLayout();
    QHBoxLayout *layout3 = new QHBoxLayout();

    QLabel *loginLabel = new QLabel("Login:");
    name = new QLineEdit();
    layout1->addWidget(loginLabel, 1);
    layout1->addWidget(name, 3);

    QLabel *passwordLabel = new QLabel("Password:");
    password = new QLineEdit();
    password->setEchoMode(QLineEdit::Password);
    layout2->addWidget(passwordLabel, 1);
    layout2->addWidget(password, 3);

    QPushButton *buttonLogin = new QPushButton("Login");
    QPushButton *buttonRegister = new QPushButton("Register");
    QPushButton *buttonCancel = new QPushButton("Cancel");
    layout3->addWidget(buttonLogin, 1);
    layout3->addWidget(buttonRegister, 1);
    layout3->addWidget(buttonCancel, 1);

    mainLayout->addLayout(layout1, 1);
    mainLayout->addLayout(layout2, 1);
    mainLayout->addLayout(layout3, 1);
    this->setLayout(mainLayout);

    connect(buttonLogin, SIGNAL(clicked(bool)), SLOT(slotLogin()));
    connect(buttonRegister, SIGNAL(clicked(bool)), SLOT(slotRegister()));
    connect(buttonCancel, SIGNAL(clicked(bool)), SIGNAL(buttonClickedCancel()));

}

LoginDialog::~LoginDialog()
{

}

void LoginDialog::slotLogin()
{
    emit buttonClickedLogin(name->text(), password->text());
}

void LoginDialog::slotRegister()
{
    emit buttonClickedRegister(name->text(), password->text());
}
