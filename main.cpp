#include "mainwindow.h"
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow window;
    window.show();

    if(!window.connectToHost("127.0.0.1", 2424))
    {
        cerr << "Error: server is not avaliable" << endl;
    }

    window.dialogLogin();
//    window.logoff();

//    window.respond("error 7");
//    window.respond("error");
//    window.respond("ok");
//    window.respond("addroom 2");
//    window.respond("adduser 2 user");
//    window.respond("adduser 2 root");
//    window.respond("deluser 2 user");
//    window.respond("delroom 2");
//    window.respond("send 2\n\xFF\n");
//    window.respond("send 2\nHello\n\xFF\n");
//    window.respond("send 2\nstring1\nstring2\n\xFF\n");

    return a.exec();
}
