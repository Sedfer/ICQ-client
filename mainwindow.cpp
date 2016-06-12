#include "mainwindow.h"
#include "dialogwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    socket = new QTcpSocket();

    connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));

    hLayoutMain = new QHBoxLayout();

    vLayoutLeft = new QVBoxLayout();
    vLayoutRight = new QVBoxLayout();
    hLayoutMain->addLayout(vLayoutLeft, 5);
    hLayoutMain->addLayout(vLayoutRight, 2);

    // Left layout (tabWindow, textEdit, buttonSend)
    roomList = new QList<Room*>();
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
    buttonAdd = new QPushButton("Add user...");
    buttonLeave = new QPushButton("Leave room");
    buttonJoin = new QPushButton("Join room...");
    buttonCreate = new QPushButton("Create room...");
    vLayoutRight->addWidget(listUsers, 5);
    vLayoutRight->addWidget(buttonAdd, 1);
    vLayoutRight->addWidget(buttonLeave, 1);
    vLayoutRight->addStretch(1);
    vLayoutRight->addWidget(buttonJoin, 1);
    vLayoutRight->addWidget(buttonCreate, 1);

    this->setLayout(hLayoutMain);

    buttonSend->setDefault(true);

    // Connections
    connect(buttonSend, SIGNAL(clicked()), SLOT(dialogSendMessage()));
    connect(buttonAdd, SIGNAL(clicked()), SLOT(dialogAddUser()));
    connect(buttonJoin, SIGNAL(clicked()), SLOT(dialogJoinRoom()));
    connect(buttonLeave, SIGNAL(clicked()), SLOT(dialogLeaveRoom()));
    connect(buttonCreate, SIGNAL(clicked()), SLOT(dialogCreateRoom()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::readyRead()
{
    cerr << "Ready to read" << endl;
}

void MainWindow::disconnected()
{

}

void MainWindow::dialogSendMessage()
{
//    QString text = textEdit->toPlainText();
//    if(!text.compare("")) // Empty message
//        return;

//    int index = tabWidget->currentIndex();
//    if(index == -1){
//        errorNoActiveTab();
//        return;
//    }

//    QTime time = QTime::currentTime();
//    QString color = "\"brown\"";
//    QString name = "Someone";
//    QString nameAndTime = "<font color=" + color + ">" + name +
//            " [" + time.toString() + "] " + "</font>";

//    listTabs->at(index)->append(nameAndTime);
//    listTabs->at(index)->append(text + "\n");
//    textEdit->clear();
}

void MainWindow::dialogAddUser()
{
    cout << "Add user" << endl;
}

void MainWindow::dialogJoinRoom()
{
    cout << "Remove user" << endl;
}

void MainWindow::dialogLeaveRoom()
{
//    int index = tabWidget->currentIndex();
//    if(index == -1){
//        errorNoActiveTab();
//        return;
//    }

//    tabWidget->removeTab(index);
//    delete listTabs->at(index);
//    listTabs->removeAt(index);
}

void MainWindow::dialogCreateRoom()
{
    DialogWindow *dialog = new DialogWindow(nullptr, "Enter name of the room:");

    connect(dialog, SIGNAL(buttonClickedOK(QString)), SLOT(createRoom(QString)));

    dialog->show();
}

void MainWindow::sendMessage()
{

}

void MainWindow::addUser()
{

}

void MainWindow::joinRoom()
{

}

void MainWindow::leaveRoom()
{

}

void MainWindow::createRoom(const QString &name)
{
    cerr << "Create room " << name.toStdString() << endl;
}

void MainWindow::errorNoActiveTab()
{
    cerr << "Error: no active tab" << endl;
}

//void MainWindow::addTab(QTextEdit *chatWindow, const QString &name)
//{
//    chatWindow->setReadOnly(true);
//    listTabs->append(chatWindow);
//    tabWidget->addTab(chatWindow, name);
//}

bool MainWindow::connectToHost(const QString &hostName, int port)
{
    socket->connectToHost(hostName, port);
    return socket->isOpen();
}

void MainWindow::sendData(const QByteArray &data)
{
    if(socket != nullptr && socket->isWritable())
    {
        socket->write(data);
    }
    else
    {
        cerr << "Error: can not write data: " << data.toStdString() << endl;
    }
}

void MainWindow::sendRegisterUser(const QString &name,
                                  const QString &password)
{
    string str = "reg " + name.toStdString() + " " +
            password.toStdString() + "\n";
    sendData(QByteArray(str.c_str()));
}

void MainWindow::sendLogin(const QString &name, const QString &password)
{
    string str = "login " + name.toStdString() + " " +
            password.toStdString() + "\n";
    sendData(QByteArray(str.c_str()));
}

void MainWindow::sendLogoff()
{
    string str = "logoff\n";
    sendData(QByteArray(str.c_str()));
}

void MainWindow::sendAddRoom()
{
    string str = "addroom\n";
    sendData(QByteArray(str.c_str()));
}

void MainWindow::sendLeaveRoom(int id)
{
    string str = "leave " + to_string(id) + "\n";
    sendData(QByteArray(str.c_str()));
}

void MainWindow::sendJoinRoom(int id)
{
    string str = "join " + to_string(id) + "\n";
    sendData(QByteArray(str.c_str()));
}

void MainWindow::sendAddUser(int id, const QString &name)
{
    string str = "invite " + to_string(id) + " " + name.toStdString() + "\n";
    sendData(QByteArray(str.c_str()));
}

void MainWindow::sendText(int id, const QString &text)
{
    string str = "send " + to_string(id) + "\n" +
            text.toStdString() + "\n\xFF\n";
    sendData(QByteArray(str.c_str()));
}
