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
    QListWidget *listUsers;
    QPushButton *buttonAdd;
    QPushButton *buttonJoin;
    QPushButton *buttonLeave;
    QPushButton *buttonCreate;

private slots:
    void readyRead();
    void disconnected();

    void dialogSendMessage();
    void dialogAddUser();
    void dialogJoinRoom();
    void dialogLeaveRoom();
    void dialogCreateRoom();

    void sendMessage();
    void addUser();
    void joinRoom();
    void leaveRoom();
    void createRoom(const QString &name);

private:
    void errorNoActiveTab();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //void addTab(QTextEdit *chatWindow, const QString &name = "Tab");
    bool connectToHost(const QString &hostName, int port);

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

    // Signals from server


    void updateButtons(); // make them inactive
};

