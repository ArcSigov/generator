#include "optionwindow.h"
#include "ui_optionwindow.h"
#include <QFileDialog>
#include <QDebug>

OptionWindow::OptionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionWindow)
{
    ui->setupUi(this);
    connect(ui->ok,       &QPushButton::clicked,       this, &OptionWindow::updateSettings);
    connect(ui->ok,       &QPushButton::clicked,       this, &OptionWindow::close);

    ui->lineEdit->setText(s.abspath);
}

OptionWindow::~OptionWindow()
{
    delete ui;
}

void OptionWindow::updateSettings()
{
    s.type = BlockType::undef;
    s.abspath = ui->lineEdit->text();

    if (ui->bgs->isChecked())
        s.type = BlockType::bgs;
    else if (ui->bis->isChecked())
        s.type = BlockType::bis;
    else if (ui->bcvm->isChecked())
        s.type = BlockType::bcvm;


    emit settingsUpdated(s);
}

void OptionWindow::on_pushButton_clicked()
{
    ui->lineEdit->setText(QFileDialog::getExistingDirectory(this,"Путь для сохранения"));
}

