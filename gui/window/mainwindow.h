#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractTableModel>
#include "datastorage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QVector<DataStorage> *_s = nullptr, QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void filePathSetted(const QString& path);
    void saveFilePath(const QString& path);
private slots:
    void on_rem_triggered();
    void on_dob_triggered();
    void on_Open_triggered();
    void on_Save_triggered();
public slots:
    void updateTable(bool);
    void showSaveFileResult(bool);
private:
    Ui::MainWindow *ui;
    QVector<DataStorage> *s;
};

#endif // MAINWINDOW_H
