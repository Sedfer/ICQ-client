#include "mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    hLayoutMain = new QHBoxLayout();

    vLayoutLeft = new QVBoxLayout();
    vLayoutRight = new QVBoxLayout();
    hLayoutMain->addLayout(vLayoutLeft, 5);
    hLayoutMain->addLayout(vLayoutRight, 2);

    // Left layout (tabWindow, textEdit, buttonSend)
    listTabs = new QList<QTextEdit*>();
    tabWidget = new QTabWidget();
    vLayoutLeft->addWidget(tabWidget, 5);
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

    buttonSend->setDefault(true);

    // Connections
    connect(buttonSend, SIGNAL(clicked()), SLOT(sendMessage()));
    connect(buttonAdd, SIGNAL(clicked()), SLOT(addUser()));
    connect(buttonRemove, SIGNAL(clicked()), SLOT(removeUser()));
    connect(buttonLeave, SIGNAL(clicked()), SLOT(leaveRoom()));
    connect(buttonNew, SIGNAL(clicked()), SLOT(createRoom()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::addTab(QTextEdit *chatWindow, const QString &name)
{
    chatWindow->setReadOnly(true);
    listTabs->append(chatWindow);
    tabWidget->addTab(chatWindow, name);
}

void MainWindow::sendMessage()
{
    QString text = textEdit->toPlainText();
    if(!text.compare("")) // Empty message
        return;

    int index = tabWidget->currentIndex();
    if(index == -1){
        errorNoActiveTab();
        return;
    }

    QTime time = QTime::currentTime();
    QString color = "\"brown\"";
    QString name = "Someone";
    QString nameAndTime = "<font color=" + color + ">" + name +
            " [" + time.toString() + "] " + "</font>";

    listTabs->at(index)->append(nameAndTime);
    listTabs->at(index)->append(text + "\n");
    textEdit->clear();
}

void MainWindow::addUser()
{
    cout << "Add user" << endl;
}

void MainWindow::removeUser()
{
    cout << "Remove user" << endl;
}

void MainWindow::leaveRoom()
{
    int index = tabWidget->currentIndex();
    if(index == -1){
        errorNoActiveTab();
        return;
    }

    tabWidget->removeTab(index);
    delete listTabs->at(index);
    listTabs->removeAt(index);
}

void MainWindow::createRoom()
{
    addTab(new QTextEdit());
}

void MainWindow::errorNoActiveTab()
{
    cerr << "Error: no active tab" << endl;
}
