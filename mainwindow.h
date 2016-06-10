#pragma once

#include <QtWidgets>

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    // Main layout
    QHBoxLayout *hLayoutMain;

    // Left layout (tabWindows, bottom layout)
    QVBoxLayout *vLayoutLeft;
    QTabWidget *tabWidget;
    QList<QTextEdit*> *listTabs;
    // Bottom layout (textEdit, buttonSend)
    QHBoxLayout *hLayoutBottom;
    QPlainTextEdit *textEdit;
    QPushButton *buttonSend;

    // Right layout (list, buttons)
    QVBoxLayout *vLayoutRight;
    QListWidget *listUsers;
    QPushButton *buttonAdd;
    QPushButton *buttonRemove;
    QPushButton *buttonLeave;
    QPushButton *buttonNew;

private slots:
    void sendMessage();
    void addUser();
    void removeUser();
    void leaveRoom();
    void createRoom();

private:
    void errorNoActiveTab();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addTab(QTextEdit *chatWindow, const QString &name = "Tab");
};

