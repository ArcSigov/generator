#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "generator.h"
#include <QMainWindow>
#include <QAbstractTableModel>
#include <QMessageBox>
#include "datastorage.h"
#include "optionwindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(Generator *_gen, QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void filePathSetted(const QString& path);
    void saveFilePath(const QString& path);
    void generateActive();
private slots:
    void on_rem_triggered();
    void on_dob_triggered();
    void on_Open_triggered();
    void on_Save_triggered();
public slots:
    void update();
    void notify(const QString& quittance);
private:
    Ui::MainWindow *ui;
    OptionWindow *optionWindow;
    QVector<DataStorage> *storage;
    Settings* settings;
    QMessageBox* box;
};

#endif // MAINWINDOW_H
