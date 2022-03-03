#ifndef OPTIONWINDOW_H
#define OPTIONWINDOW_H

#include <QWidget>
#include "datastorage.h"

namespace Ui {
class OptionWindow;
}

class OptionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OptionWindow(QWidget *parent = nullptr);
    ~OptionWindow();
public:
    void updateSettings();
private slots:
    void editSettings();
    void on_kernelbtn_clicked();
    void on_loadbtn_clicked();

private:
    Ui::OptionWindow *ui;
    Settings& settings{Storage::load()->settings()};
};

#endif // OPTIONWINDOW_H
