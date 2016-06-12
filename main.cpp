#include "mainwindow.h"
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    if(!w.connectToHost("127.0.0.1", 2424))
    {
        cerr << "Error: server is not avaliable" << endl;
    }

    return a.exec();
}
