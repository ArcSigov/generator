#include "optionwindow.h"
#include "ui_optionwindow.h"
#include <QFileDialog>

OptionWindow::OptionWindow(Settings* _s,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionWindow),
    s(_s)
{
    ui->setupUi(this);
    connect(ui->ok,       &QPushButton::clicked,       this, &OptionWindow::editSettings);
    connect(ui->ok,       &QPushButton::clicked,       this, &OptionWindow::close);

    if (s)
    {
        ui->loadPath->setText(s->loadpath);
        ui->kernelPath->setText(s->kernelpath);
    }
}

OptionWindow::~OptionWindow()
{
    delete ui;
}

void OptionWindow::editSettings()
{
    if (s)
    {
        s->loadpath = ui->loadPath->text();
        s->kernelpath = ui->kernelPath->text();
        if (ui->bgs->isChecked())
            s->type = BlockType::bgs;
        else if (ui->bis->isChecked())
            s->type = BlockType::bis;
        else if (ui->bcvm->isChecked())
            s->type = BlockType::bcvm;
        else
            s->type = BlockType::undef;
        emit settingsUpdated();
    }
}

void OptionWindow::updateSettings()
{
    if (s)
    {
        ui->loadPath->setText(s->loadpath);
        ui->kernelPath->setText(s->kernelpath);
        switch(s->type)
        {
        case BlockType::bis:        ui->bis->setChecked(true); break;
        case BlockType::bgs:        ui->bgs->setChecked(true); break;
        case BlockType::bcvm:       ui->bcvm->setChecked(true); break;
        case BlockType::undef:
            default: break;
        }
        emit settingsUpdated();
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

