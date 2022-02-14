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
    explicit OptionWindow(QWidget *parent = nullptr);
    ~OptionWindow();

signals :
    void settingsUpdated(const Settings&);
private slots:
    void on_pushButton_clicked();

private:
    void updateSettings();
    Ui::OptionWindow *ui;
    Settings s;
};

#endif // OPTIONWINDOW_H
