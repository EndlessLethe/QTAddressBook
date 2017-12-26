#include "mainwindow.h"
#include "dialog_call.h"
#include "dialog_read.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    Dialog_read r;
//    r.exec();
    return a.exec();
}
