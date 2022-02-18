#ifndef OPTIONWINDOW_H
#define OPTIONWINDOW_H

#include <QWidget>
#include "options.h"

namespace Ui {
class OptionWindow;
}

class OptionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OptionWindow(Settings*,QWidget *parent = nullptr);
    ~OptionWindow();
public:

    void updateSettings();
signals:
    void settingsUpdated();
private slots:
    void editSettings();
    void on_kernelbtn_clicked();
    void on_loadbtn_clicked();

private:
    Ui::OptionWindow *ui;
    Settings* s;
};

#endif // OPTIONWINDOW_H
