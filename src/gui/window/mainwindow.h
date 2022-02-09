#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    explicit MainWindow(QVector<DataStorage> *_s = nullptr, QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void filePathSetted(const QString& path);
    void saveFilePath(const QString& path);
    void generateActive(bool);
    void settingsUpdated(const Settings&);
private slots:
    void on_rem_triggered();
    void on_dob_triggered();
    void on_Open_triggered();
    void on_Save_triggered();
    void on_generate_triggered();
    void readSettings(const Settings&);
public slots:
    void updateTable();
    void notify(const QString& quittance);
private:
    Ui::MainWindow *ui;
    QVector<DataStorage> *s;
    QMessageBox* box;
    OptionWindow* options;
};

#endif // MAINWINDOW_H
