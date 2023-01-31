#include "optionwindow.h"
#include "ui_optionwindow.h"
#include <QFileDialog>
#include <QRadioButton>
#include <QSpinBox>
#include <QLayout>

OptionWindow::OptionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionWindow)
{
    ui->setupUi(this);

    connect(ui->ok,          &QPushButton::clicked,       this, &OptionWindow::editSettings);
    connect(ui->sectorSize,  SIGNAL(valueChanged(int)),   this, SLOT(editStorage(int)));
    connect(ui->ok,          &QPushButton::clicked,       this, &OptionWindow::close);

    ui->loadPath->setText(Storage::load()->options().loadpath);
    ui->kernelPath->setText(Storage::load()->options().kernelpath);
    ui->ramSWScript->setChecked(true);
    ui->romSWScript->setChecked(true);
    ui->romRS232Script->setChecked(true);
    ui->romKernelsFpoScript->setChecked(true);
    ui->kernelScript->setChecked(true);


    QHBoxLayout *vbox = new QHBoxLayout(ui->blocksBox);
    for (const auto& it : Storage::load()->cfg().blockList())
    {
        QRadioButton* btn = new QRadioButton(it,ui->blocksBox);
        btn->setObjectName(it);
        ui->blocksBox->layout()->addWidget(btn);
    }
}

OptionWindow::~OptionWindow()
{
    delete ui;
}

void OptionWindow::editSettings()
{
    auto& options = Storage::load()->options();

    //!< Установка путей сборки и пути хранения ядер
    options.loadpath               = ui->loadPath->text();
    options.kernelpath             = ui->kernelPath->text();

    //!< Установка выбранных пользовательских настроек
    options.ramSW_enabled          = ui->ramSWScript->isChecked();
    options.romSW_enabled          = ui->romSWScript->isChecked();
    options.romRS232_enabled       = ui->romRS232Script->isChecked();
    options.romKernelsFpo_enabled  = ui->romKernelsFpoScript->isChecked();

    //!< Конфигурирование хранилища под выбранный блок
    for (const auto& it : ui->blocksBox->children())
    {
        auto t = dynamic_cast<QRadioButton*>(it);
        if (t && t->isChecked())
        {
            Storage::load()->cfg().setCurrentBlock(it->objectName());
            break;
        }
    }
}



void OptionWindow::initializeSettings()
{
    ui->loadPath->setText(Storage::load()->options().loadpath);
    ui->kernelPath->setText(Storage::load()->options().kernelpath);
    ui->sectorSize->setValue(Storage::load()->options().max_rom_section_size);

    for (const auto& it : ui->blocksBox->children())
    {
        auto t = dynamic_cast<QRadioButton*>(it);
        if (t && t->objectName() == Storage::load()->cfg().BlockName())
        {
            t->setChecked(true);
            break;
        }
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

void OptionWindow::editStorage(int value)
{
    Storage::load()->options().max_rom_section_size = value;
    Storage::load()->calcRom();
}
