#pragma once

#include <QtWidgets>
#include <QtNetwork>

class Room : public QTextEdit
{
    Q_OBJECT
public:
    int id;
    QString name;
    QStringList userList;

    Room(QWidget *parent, int _id, const QString &_name = "Tab");
    ~Room();

    void addUser(const QString &name);
    void delUser(const QString &name);
    void send(const QString &text);
};
