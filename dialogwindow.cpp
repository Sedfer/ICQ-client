#include "dialogwindow.h"

DialogWindow::DialogWindow(QWidget *parent, const QString &text)
    : QWidget(parent)
{
    mainLayout = new QVBoxLayout();
    label = new QLabel(text);
    lineEdit = new QLineEdit();
    buttonsLayout = new QHBoxLayout();
    buttonOK = new QPushButton("OK");
    buttonCancel = new QPushButton("Cancel");

    buttonsLayout->addWidget(buttonOK, 1);
    buttonsLayout->addWidget(buttonCancel, 1);

    mainLayout->addWidget(label, 1);
    mainLayout->addWidget(lineEdit, 1);
    mainLayout->addLayout(buttonsLayout, 1);

    this->setLayout(mainLayout);
    this->setGeometry(600, 800, 200, 50);

    connect(buttonOK, SIGNAL(clicked(bool)), SLOT(slotOK()));
    connect(buttonCancel, SIGNAL(clicked(bool)), SLOT(slotCancel()));
}

DialogWindow::~DialogWindow()
{

}

void DialogWindow::slotOK()
{
    emit buttonClickedOK(lineEdit->text());
}

void DialogWindow::slotCancel()
{
    emit buttonClickedCancel();
}
