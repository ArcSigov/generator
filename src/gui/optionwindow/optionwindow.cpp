#include "optionwindow.h"
#include "ui_optionwindow.h"
#include <QFileDialog>

OptionWindow::OptionWindow(Settings* _s,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionWindow),
    s(_s)
{
    ui->setupUi(this);
    connect(ui->ok,       &QPushButton::clicked,       this, &OptionWindow::updateSettings);
    connect(ui->ok,       &QPushButton::clicked,       this, &OptionWindow::close);
    if (s) ui->lineEdit->setText(s->abspath);
}

OptionWindow::~OptionWindow()
{
    delete ui;
}

void OptionWindow::updateSettings()
{
    if (s)
    {
        s->abspath = ui->lineEdit->text();

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

void OptionWindow::setSettings()
{
    if (s)
    {
        ui->lineEdit->setText(s->abspath);
        switch(s->type)
        {
        case BlockType::bis:        ui->bis->setChecked(true); break;
        case BlockType::bgs:        ui->bgs->setChecked(true); break;
        case BlockType::bcvm:       ui->bcvm->setChecked(true); break;
        case BlockType::undef:
            default: break;
        }
    }
}

void OptionWindow::on_pushButton_clicked()
{
    ui->lineEdit->setText(QFileDialog::getExistingDirectory(this,"Путь для сохранения"));
}

