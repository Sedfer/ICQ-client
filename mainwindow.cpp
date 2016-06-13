#include "mainwindow.h"
#include "dialogwindow.h"
#include <iostream>
#include <sstream>

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
    userList = new QListWidget();
    buttonAdd = new QPushButton("Add user...");
    buttonLeave = new QPushButton("Leave room");
    buttonJoin = new QPushButton("Join room...");
    buttonCreate = new QPushButton("Create room");
    vLayoutRight->addWidget(userList, 5);
    vLayoutRight->addWidget(buttonAdd, 1);
    vLayoutRight->addWidget(buttonLeave, 1);
    vLayoutRight->addStretch(1);
    vLayoutRight->addWidget(buttonJoin, 1);
    vLayoutRight->addWidget(buttonCreate, 1);

    this->setLayout(hLayoutMain);
    this->setGeometry(350, 150, 600, 400);

    updateButtons();

    // Connections
    connect(buttonSend, SIGNAL(clicked()), SLOT(sendMessage()));
    connect(buttonAdd, SIGNAL(clicked()), SLOT(dialogAddUser()));
    connect(buttonJoin, SIGNAL(clicked()), SLOT(dialogJoinRoom()));
    connect(buttonLeave, SIGNAL(clicked()), SLOT(leaveRoom()));
    connect(buttonCreate, SIGNAL(clicked()), SLOT(createRoom()));

    connect(tabWidget, SIGNAL(currentChanged(int)), SLOT(updateUserList()));
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
    doError(100);
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

void MainWindow::registerUser(const QString &name, const QString &password)
{
    sendRegisterUser(name, password);
    cout << "-> reg " << name.toStdString() << " "
         << password.toStdString() << endl;
}

void MainWindow::login(const QString &name, const QString &password)
{
    sendLogin(name, password);
    cout << "-> login " << name.toStdString() << " "
         << password.toStdString() << endl;
}

void MainWindow::logoff()
{
    sendLogoff();
    cout << "-> logoff" << endl;
}

void MainWindow::createRoom()
{
    sendAddRoom();
    cout << "-> addroom" << endl;
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

void MainWindow::respond(const QString &request)
{
    cout << "<- " << request.toStdString() << endl;

    stringstream in(request.toStdString());
    string action;
    in >> action;

    if(!action.compare("ok"))
    {
        doOK();
        return;
    }

    if(!action.compare("error"))
    {
        int id = -1;
        in >> id;
        doError(id);
        return;
    }

    if(!action.compare("addroom"))
    {
        int id = -1;
        in >> id;
        doAddRoom(id);
        return;
    }

    if(!action.compare("delroom"))
    {
        int id = -1;
        in >> id;
        doDelRoom(id);
        return;
    }

    if(!action.compare("adduser"))
    {
        int id = -1;
        string name;
        in >> id >> name;
        doAddUser(id, QString(name.c_str()));
        return;
    }

    if(!action.compare("deluser"))
    {
        int id = -1;
        string name;
        in >> id >> name;
        doDelUser(id, QString(name.c_str()));
        return;
    }

    if(!action.compare("send"))
    {
        int id = -1;
        in >> id;
        doSend(id);
        return;
    }

    cerr << "Error: action unrecognized: " << action << endl;
}

void MainWindow::doError(int code)
{
    string text = "Error (code " + to_string(code) + ")";
    QMessageBox *mbox = new QMessageBox(QMessageBox::Critical,
                                        "Error",
                                        QString(text.c_str()),
                                        QMessageBox::Ok);
    mbox->exec();
}

void MainWindow::doOK()
{
    cout << "OK" << endl;
}

void MainWindow::doAddRoom(int id)
{
    string name = "room" + to_string(id);
    Room *room = new Room(nullptr, id, QString(name.c_str()));

    roomList->append(room);
    tabWidget->addTab(room, room->name);
    updateUserList();
    updateButtons();
}

void MainWindow::doAddUser(int id, const QString &name)
{
    Room *room = findRoom(id);
    if(room == nullptr)
    {
        cerr << "Error: room not found: " << id << endl;
        return;
    }

    room->userList.append(name);
    updateUserList();
}

void MainWindow::doDelUser(int id, const QString &name)
{
    Room *room = findRoom(id);
    if(room == nullptr)
    {
        cerr << "Error: room not found: " << id << endl;
        return;
    }

    room->userList.removeOne(name);
    updateUserList();
}

void MainWindow::doDelRoom(int id)
{
    Room *room = findRoom(id);
    if(room == nullptr)
    {
        cerr << "Error: room not found: " << id << endl;
        return;
    }

    int index = roomList->indexOf(room);
    tabWidget->removeTab(index);
    roomList->removeAt(index);
    updateUserList();
    updateButtons();
}

void MainWindow::doSend(int id)
{
    QString text;
    while(socket->bytesAvailable() > 0)
    {
        QByteArray line = socket->readLine(1024);
        // '\xFF\n' means end of message
        if(line.at(0) == '\xFF')
        {
            break;
        }
        text += QString(line);
    }

    Room *room = findRoom(id);
    if(room == nullptr)
    {
        cerr << "Error: room not found: " << id << endl;
        return;
    }

    room->append(text);
}

void MainWindow::updateButtons()
{
    if(getCurrentRoomID() != -1)
    {
        buttonAdd->setEnabled(true);
        buttonLeave->setEnabled(true);
    }
    else
    {
        buttonAdd->setEnabled(false);
        buttonLeave->setEnabled(false);
    }
}

void MainWindow::updateUserList()
{
    int index = tabWidget->currentIndex();

    userList->clear();

    if(index != -1)
        userList->addItems(roomList->at(index)->userList);
}

bool MainWindow::connectToHost(const QString &hostName, int port)
{
    socket->connectToHost(hostName, port);
    return socket->isOpen();
}

int MainWindow::getCurrentRoomID()
{
    int index = tabWidget->currentIndex();
    if(index != -1)
        return roomList->at(index)->id;
    else
        return -1;
}

Room *MainWindow::findRoom(int id)
{
    auto room = find_if(roomList->begin(), roomList->end(),
                        [id](Room *room){
        return room->id == id;
    });

    if(room != roomList->end())
    {
        return *room;
    }
    else
    {
        return nullptr;
    }
}
