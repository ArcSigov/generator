#include "optionwindow.h"
#include "ui_optionwindow.h"
#include <QFileDialog>
#include <QDebug>

OptionWindow::OptionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionWindow)
{
    ui->setupUi(this);
    connect(ui->ok,          &QPushButton::clicked,       this, &OptionWindow::editSettings);
    connect(ui->sectorSize,  &QSpinBox::textChanged,     this, &OptionWindow::editStorage);
    connect(ui->ok,          &QPushButton::clicked,       this, &OptionWindow::close);
    connect(Storage::load(), &Storage::sectionError,      this, &OptionWindow::editSpinBox);

    ui->loadPath->setText(settings.loadpath);
    ui->kernelPath->setText(settings.kernelpath);

    ui->ramSWScript->setChecked(true);
    ui->romSWScript->setChecked(true);
    ui->romRS232Script->setChecked(true);
    ui->romKernelsFpoScript->setChecked(true);
    ui->kernelScript->setChecked(true);
    ui->what->setVisible(false);
    ui->what->setStyleSheet("color: red");
}

OptionWindow::~OptionWindow()
{
    delete ui;
}

void OptionWindow::editSettings()
{
    settings.loadpath               = ui->loadPath->text();
    settings.kernelpath             = ui->kernelPath->text();

    settings.ramSW_enabled          = ui->ramSWScript->isChecked();
    settings.romSW_enabled          = ui->romSWScript->isChecked();
    settings.romRS232_enabled       = ui->romRS232Script->isChecked();
    settings.romKernelsFpo_enabled  = ui->romKernelsFpoScript->isChecked();

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
    ui->sectorSize->setValue(settings.max_rom_section_size);
    editStorage(QString::number(settings.max_rom_section_size,16));

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
    ui->kernelPath->setText(QFileDialog::getExistingDirectory(this,ui->kernelbtn->text()));
}

void OptionWindow::on_loadbtn_clicked()
{
    ui->loadPath->setText(QFileDialog::getExistingDirectory(this,ui->loadbtn->text()));
}

void OptionWindow::editStorage(QString value)
{
    settings.max_rom_section_size = value.toUInt(nullptr,16);
    Storage::load()->calcRom();
}

void OptionWindow::editSpinBox(const QString& what)
{
    if (!what.isEmpty())
    {
        ui->what->setVisible(true);
        ui->what->setText(what);
        ui->sectorSize->setStyleSheet("color: red");
    }
    else
    {
        ui->what->setVisible(false);
        ui->sectorSize->setStyleSheet("color: black");
    }
}
