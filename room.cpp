#include "room.h"

Room::Room(QWidget *parent, int _id, const QString &_name)
    : QTextEdit(parent), id(_id), name(_name), userList()
{
    this->setReadOnly(true);
}

Room::~Room()
{

}

void Room::addUser(const QString &name)
{
    userList.append(name);
}

void Room::delUser(const QString &name)
{
    userList.removeOne(name);
}

void Room::send(const QString &text)
{
    this->append(text);
}
