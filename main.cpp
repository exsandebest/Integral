#include "mainwindow.h"
#include <QApplication>
#include "answindow.h"
#include "legend.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow windowMain;
    windowMain.show();

    legend windowLegend;
    windowLegend.show();

    AnsWindow windowAns;
    windowAns.show();

    return a.exec();
}
