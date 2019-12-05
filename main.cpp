#include "mainwindow.h"
#include <QApplication>
#include "answindow.h"
#include "legend.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.resize(800,800);

    legend win2;
    win2.show();

    AnsWindow win;
    win.show();



    return a.exec();
}
