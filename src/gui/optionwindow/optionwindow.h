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
    void on_pushButton_clicked();
    void editSettings();
private:
    Ui::OptionWindow *ui;
    Settings* s;
};

#endif // OPTIONWINDOW_H
