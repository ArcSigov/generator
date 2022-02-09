#include <QApplication>
#include "generator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Generator g;
    return a.exec();
}
