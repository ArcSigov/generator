#include "itempathwidget.h"
#include "ui_itempathwidget.h"

ItemPathWidget::ItemPathWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemPathWidget)
{
    ui->setupUi(this);
}

ItemPathWidget::~ItemPathWidget()
{
    delete ui;
}

QString ItemPathWidget::text()
{
    return ui->lineEdit->text();
}

void ItemPathWidget::setText(const QString& other)
{
    ui->lineEdit->setText(other);
}

void ItemPathWidget::on_pushButton_clicked()
{
    auto str = QFileDialog::getOpenFileName(this, tr("Добавление файла"), " ", tr("ius_types (*.mot *.elf)"));
    if (!str.isEmpty())
        ui->lineEdit->setText(str);
}

