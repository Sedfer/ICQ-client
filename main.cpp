#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    QTextEdit *tab1 = new QTextEdit();
    QTextEdit *tab2 = new QTextEdit();
    w.addTab(tab1, "Tab 1");
    w.addTab(tab2, "Tab 2");

    return a.exec();
}
