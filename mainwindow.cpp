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

    updateButtons();

    // Connections
    connect(buttonSend, SIGNAL(clicked()), SLOT(sendMessage()));
    connect(buttonAdd, SIGNAL(clicked()), SLOT(dialogAddUser()));
    connect(buttonJoin, SIGNAL(clicked()), SLOT(dialogJoinRoom()));
    connect(buttonLeave, SIGNAL(clicked()), SLOT(leaveRoom()));
    connect(buttonCreate, SIGNAL(clicked()), SLOT(dialogCreateRoom()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::readyRead()
{
    while(socket && socket->bytesAvailable() > 0)
    {
        QByteArray data = socket->readLine(1024);
        respond(QString(data));
    }
}

void MainWindow::disconnected()
{
    cerr << "Error: connection lost" << endl;
}

void MainWindow::dialogRegisterUser()
{

}

void MainWindow::dialogLogin()
{

}

void MainWindow::dialogAddUser()
{
    DialogWindow *dialog = new DialogWindow(nullptr, "Enter name:");

    connect(dialog, SIGNAL(buttonClickedOK(QString)), SLOT(addUser(QString)));
    connect(dialog, SIGNAL(buttonClickedCancel()), SLOT(dialogCanceled()));

    dialog->show();
}

void MainWindow::dialogJoinRoom()
{
    DialogWindow *dialog = new DialogWindow(nullptr, "Enter room number:");

    connect(dialog, SIGNAL(buttonClickedOK(QString)), SLOT(joinRoom(QString)));
    connect(dialog, SIGNAL(buttonClickedCancel()), SLOT(dialogCanceled()));

    dialog->show();
}

void MainWindow::dialogCreateRoom()
{
    DialogWindow *dialog = new DialogWindow(nullptr, "Enter name of the room:");

    connect(dialog, SIGNAL(buttonClickedOK(QString)), SLOT(createRoom(QString)));
    connect(dialog, SIGNAL(buttonClickedCancel()), SLOT(dialogCanceled()));

    dialog->show();
}

void MainWindow::registerUser()
{

}

void MainWindow::login()
{

}

void MainWindow::logoff()
{

}

void MainWindow::createRoom(const QString &name)
{
    DialogWindow *dialog = static_cast<DialogWindow*>(sender());
    dialog->hide();
    dialog->deleteLater();

    sendAddRoom();
    cout << "-> addroom (" << name.toStdString() << ")" << endl;
}

void MainWindow::leaveRoom()
{
    int id = getCurrentRoomID();

    sendLeaveRoom(id);
    cout << "-> leave " << id << endl;
}

void MainWindow::joinRoom(const QString &id)
{
    DialogWindow *dialog = static_cast<DialogWindow*>(sender());
    dialog->hide();
    dialog->deleteLater();

    sendJoinRoom(id.toInt());
    cout << "-> join " << id.toInt() << endl;
}

void MainWindow::addUser(const QString &name)
{
    DialogWindow *dialog = static_cast<DialogWindow*>(sender());
    dialog->hide();
    dialog->deleteLater();

    int id = getCurrentRoomID();

    sendAddUser(id, name);
    cout << "-> invite " << id << " " << name.toStdString() << endl;
}

void MainWindow::sendMessage()
{
    int id = getCurrentRoomID();
    const QString &text = textEdit->toPlainText();

    sendText(id, text);
    cout << "-> send " << id << endl << text.toStdString() << endl;

    textEdit->clear();
}

void MainWindow::dialogCanceled()
{
    DialogWindow *dialog = static_cast<DialogWindow*>(sender());
    dialog->hide();
    dialog->deleteLater();
}

bool MainWindow::connectToHost(const QString &hostName, int port)
{
    socket->connectToHost(hostName, port);
    return socket->isOpen();
}

void MainWindow::respond(const QString &request)
{
    cout << "<- " << request.toStdString() << endl;
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

void MainWindow::updateButtons()
{
//    buttonAdd->setDisabled(true);
    //    buttonLeave->setEnabled(false);
}

// TODO: complete
int MainWindow::getCurrentRoomID()
{
    return 0;
}
