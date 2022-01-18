#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractTableModel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
        public:
                 explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setModelToTable(QAbstractTableModel*);
public slots:
private slots:
    void on_rem_triggered();
    void on_dob_triggered();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
