#ifndef OPTIONWINDOW_H
#define OPTIONWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include "storage.h"

namespace Ui {
class OptionWindow;
}

class OptionWindow : public QWidget
{
    Q_OBJECT
public:
    explicit OptionWindow(QWidget *parent = nullptr);
    ~OptionWindow();
    void initializeSettings();
public slots:

private slots:
    void editSettings();
    void editStorage(int value);
    void on_kernelbtn_clicked();
    void on_loadbtn_clicked();
private:
    Ui::OptionWindow *ui;
};

#endif // OPTIONWINDOW_H
