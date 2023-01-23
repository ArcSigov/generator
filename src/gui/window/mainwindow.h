#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractTableModel>
#include <QMessageBox>
#include "optionwindow.h"
#include "messages.h"

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void filePathSetted(const QString& path);
    void saveFilePath(const QString& path);
    void generateActive();
    void rawRemoved();
private slots:
    void on_rem_triggered();
    void on_dob_triggered();
    void on_Open_triggered();
    void on_Save_triggered();
    void on_generate_triggered();
    void clearRowData(bool flag);
    void defaultRowData(bool flag);
    void menuRequested(QPoint pos);
public slots:
    void message(const MessageCategory& category = MessageCategory::notify, const QString& text = " ");
private:
    Ui::MainWindow *ui;
    OptionWindow *optionWindow;
    QMessageBox* box;
    QLabel*      status;
};

#endif
