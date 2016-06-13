#pragma once

#include <QtWidgets>
#include <QtNetwork>
#include "room.h"

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    // Server
    QTcpSocket *socket;

    // Main layout
    QHBoxLayout *hLayoutMain;

    // Left layout (tabWindows, bottom layout)
    QVBoxLayout *vLayoutLeft;
    QTabWidget *tabWidget;
    QList<Room*> *roomList;
    // Bottom layout (textEdit, buttonSend)
    QHBoxLayout *hLayoutBottom;
    QPlainTextEdit *textEdit;
    QPushButton *buttonSend;

    // Right layout (list, buttons)
    QVBoxLayout *vLayoutRight;
    QListWidget *userList;
    QPushButton *buttonAdd;
    QPushButton *buttonJoin;
    QPushButton *buttonLeave;
    QPushButton *buttonCreate;

public slots:
    void readyRead();
    void disconnected();

    void dialogRegisterUser();
    void dialogLogin();
    void dialogAddUser();
    void dialogJoinRoom();
    void dialogCreateRoom();

    void registerUser(const QString &name, const QString &password);
    void login(const QString &name, const QString &password);
    void logoff();
    void createRoom(const QString &name);
    void leaveRoom();
    void joinRoom(const QString &id);
    void addUser(const QString &name);
    void sendMessage();

    void dialogCanceled();

    void updateUserList();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void sendData(const QByteArray &data);
    // Signals to server
    void sendRegisterUser(const QString &name, const QString &password);
    void sendLogin(const QString &name, const QString &password);
    void sendLogoff();
    void sendAddRoom();
    void sendLeaveRoom(int id);
    void sendJoinRoom(int id);
    void sendAddUser(int id, const QString &name);
    void sendText(int id, const QString &text);

    void respond(const QString &request);
    // Signals from server
    void doError(int code);
    void doOK();
    void doAddRoom(int id);
    void doAddUser(int id, const QString &name);
    void doDelUser(int id, const QString &name);
    void doDelRoom(int id);
    void doSend(int id);

    void updateButtons(); // make them inactive
    bool connectToHost(const QString &hostName, int port);
    int getCurrentRoomID();
    Room* findRoom(int id);
};

