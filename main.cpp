#include "mainwindow.h"
#include "tableview.h"
#include "datastorage.h"
#include <QApplication>
#include <QVector>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QVector<DataStorage> h;
    MainWindow w;
    TableModel t(nullptr,&h);
    w.setModelToTable(&t);
    w.show();
    return a.exec();
}
