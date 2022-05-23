#include <QApplication>
#include <QObject>
#include "generator.h"
#include "mainwindow.h"
#include <QThread>
#include <QTextCodec>
#include "messages.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "filemanager.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Generator g;
    MainWindow w;
    QThread*    t = new QThread();
    g.moveToThread(t);

    qRegisterMetaType<MessageCategory>("MessageCategory");
    QObject::connect(&g, &Generator::sendMessage,      &w,  &MainWindow::message);
    QObject::connect(&w, &MainWindow::generateActive,  &g,  &Generator::run);
    QObject::connect(&w, &MainWindow::filePathSetted,  &g,  &Generator::readTblFile);
    QObject::connect(&w, &MainWindow::saveFilePath,    &g,  &Generator::saveTblFile);

    if (argc < 2)
    {
        w.show();
        t->start();
    }
    else
    {

    }
    return a.exec();
}
