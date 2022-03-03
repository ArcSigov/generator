#include "optionwindow.h"
#include "ui_optionwindow.h"
#include <QFileDialog>

OptionWindow::OptionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionWindow)
{
    ui->setupUi(this);
    connect(ui->ok,       &QPushButton::clicked,       this, &OptionWindow::editSettings);
    connect(ui->ok,       &QPushButton::clicked,       this, &OptionWindow::close);

    ui->loadPath->setText(settings.loadpath);
    ui->kernelPath->setText(settings.kernelpath);
}

OptionWindow::~OptionWindow()
{
    delete ui;
}

void OptionWindow::editSettings()
{
    settings.loadpath               = ui->loadPath->text();
    settings.kernelpath             = ui->kernelPath->text();
    if (ui->bgs->isChecked())       settings.init(BlockType::bgs);
    else if (ui->bis->isChecked())  settings.init(BlockType::bis);
    else if (ui->bcvm->isChecked()) settings.init(BlockType::bcvm);
    else                            settings.init(BlockType::undef);

}

void OptionWindow::updateSettings()
{
    ui->loadPath->setText(settings.loadpath);
    ui->kernelPath->setText(settings.kernelpath);
    settings.init(settings.type);
    switch(settings.type)
    {
        case BlockType::bis:    ui->bis->setChecked(true);  break;
        case BlockType::bgs:    ui->bgs->setChecked(true);  break;
        case BlockType::bcvm:   ui->bcvm->setChecked(true); break;
        case BlockType::undef:  default:                    break;
    }

}

void OptionWindow::on_kernelbtn_clicked()
{
    ui->kernelPath->setText(QFileDialog::getExistingDirectory(this,"Путь к ядрам"));
}

void OptionWindow::on_loadbtn_clicked()
{
    ui->loadPath->setText(QFileDialog::getExistingDirectory(this,"Путь для сохранения"));
}

