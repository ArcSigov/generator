#include "mainwindow.h"
#include "tableview.h"
#include "datastorage.h"
#include <QApplication>
#include <QVector>
#include "generator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Generator g;
    g.run();
    return a.exec();
}
