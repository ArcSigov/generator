#ifndef ITEMPATHWIDGET_H
#define ITEMPATHWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QDir>

namespace Ui {
class ItemPathWidget;
}

class ItemPathWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ItemPathWidget(QWidget *parent = nullptr);
    ~ItemPathWidget();
    QString text();
    void setText(const QString& text);
    void openDialog(const QString& path);
private slots:
    void on_pushButton_clicked();
private:
    Ui::ItemPathWidget *ui;
};

#endif // ITEMPATHWIDGET_H
