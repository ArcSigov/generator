#ifndef TABLE_H
#define TABLE_H

#include <QWidget>
#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QTableWidgetItem>
#include <QDebug>
#include <QThread>
#include <QMessageBox>
#include <memory>
#include "cfggenerator/cfggenerator.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <mutex>
#include <thread>
#include <atomic>


namespace Ui {
class Table;
}





class Table : public QMainWindow
{
    Q_OBJECT
    Ui::Table *ui;
    QThread*        thread;
    std::unique_ptr<QFileDialog>    Dialog;
public:
    explicit Table(QMainWindow *parent = nullptr);
    ~Table();
private slots:
    void on_Generate_clicked();
};



#endif // TABLE_H
