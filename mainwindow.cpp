#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    hLayoutMain = new QHBoxLayout();

    vLayoutLeft = new QVBoxLayout();
    vLayoutRight = new QVBoxLayout();
    hLayoutMain->addLayout(vLayoutLeft, 5);
    hLayoutMain->addLayout(vLayoutRight, 2);

    // Left layout (chatWindow, textEdit, buttonSend)
    chatWindow = new QTextEdit();
    chatWindow->setReadOnly(true);
    vLayoutLeft->addWidget(chatWindow, 5);
    // Bottom layout (textEdit, buttonSend)
    hLayoutBottom = new QHBoxLayout();
    textEdit = new QPlainTextEdit();
    buttonSend = new QPushButton("Send");
    hLayoutBottom->addWidget(textEdit, 5);
    hLayoutBottom->addWidget(buttonSend, 1);
    vLayoutLeft->addLayout(hLayoutBottom, 1);

    // Right layout (list, buttons)
    listUsers = new QListWidget();
    buttonAdd = new QPushButton("Add...");
    buttonRemove = new QPushButton("Remove...");
    buttonLeave = new QPushButton("Leave");
    buttonNew = new QPushButton("+New");
    vLayoutRight->addWidget(listUsers, 5);
    vLayoutRight->addStretch(1);
    vLayoutRight->addWidget(buttonAdd, 1);
    vLayoutRight->addWidget(buttonRemove, 1);
    vLayoutRight->addWidget(buttonLeave, 1);
    vLayoutRight->addWidget(buttonNew, 1);

    this->setLayout(hLayoutMain);
}

MainWindow::~MainWindow()
{

}
