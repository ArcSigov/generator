#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogitemdelegate.h"
#include "calendaritemdelegate.h"
#include "checkdelegate.h"
#include "tableview.h"

#include <QDebug>
#include <QLabel>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    box(new QMessageBox(this)),
    status(new QLabel(this))
{

    optionWindow = new OptionWindow();

    ui->setupUi(this);
    ui->progressBar->setVisible(false);
    ui->dob->setIcon(style()->standardIcon(QStyle::SP_FileDialogStart));
    ui->rem->setIcon(style()->standardIcon(QStyle::SP_TrashIcon));
    ui->generate->setIcon(style()->standardIcon(QStyle::SP_DialogYesButton));
    ui->tableView->setItemDelegateForColumn(IS_CHECKED,new CheckDelegate(this));
    ui->tableView->setItemDelegateForColumn(FILE_PATH,new DialogDelegate(this));
    ui->tableView->setItemDelegateForColumn(ID_DATE,new CalendarDelegate(this));
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(new TableModel(this));

    ui->statusBar->addWidget(status);
    ui->statusBar->setVisible(true);


    connect(ui->options,    &QAction::triggered,             optionWindow,&OptionWindow::show);
    connect(this,           &MainWindow::rawRemoved,         optionWindow,&OptionWindow::updateSettings);
    connect(static_cast<TableModel*>(ui->tableView->model()),&TableModel::tableUpdated,      Storage::load(),&Storage::sort);
    connect(Storage::load(),&Storage::sectionError,          this,&MainWindow::buttonsMode);                       ///< Соединенение главного окна с генератором с уведомлением о выборе файла для записи
}

MainWindow::~MainWindow()
{
    delete ui;
    delete optionWindow;
}

void MainWindow::on_rem_triggered()
{
    auto list = ui->tableView->selectionModel()->selection().indexes();
    for (auto it = list.begin(); it != list.end() ; it++)
    {
        if (it->column() == 0)
        {
            ui->tableView->model()->removeRows(it->row(),1,*it);
            emit rawRemoved();
        }
    }
}

void MainWindow::on_dob_triggered()
{
    ui->tableView->model()->insertRows(ui->tableView->model()->rowCount(),1);
}

void MainWindow::on_Open_triggered()
{
    emit filePathSetted(QFileDialog::getOpenFileName(this, tr("Открыть файл"), " ", "table(*.tbl)"));
}

void MainWindow::on_Save_triggered()
{
    emit saveFilePath(QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "", tr("table(*.tbl)")));
}

void MainWindow::buttonsMode(const QString& checkList)
{
    if (!checkList.isEmpty())
    {
        ui->generate->setEnabled(false);
        status->setText(checkList + tr(", перейдите в настройки и задайте корректный размер сектора ПЗУ"));
        ui->statusBar->setStyleSheet("color : red");
    }
    else
    {
        ui->generate->setEnabled(true);
        status->setText("Готов");
        ui->statusBar->setStyleSheet("color : green");
    }
}

void MainWindow::message(const MessageCategory& category,const QString& text)
{
    status->setText(text);

    switch (category)
    {
        case MessageCategory::error:
        break;
        case MessageCategory::info:
            ui->statusBar->setStyleSheet("color : green");
            ui->textBrowser->setTextColor(Qt::green);
        break;
        case MessageCategory::notify:
        {
            box->setText(text);
            box->exec();
        }
        break;
        case MessageCategory::warning:
        {
            ui->textBrowser->setTextColor(Qt::red);
            break;
        }
        case MessageCategory::update:
        {
            optionWindow->updateSettings();
            static_cast<TableModel*>(ui->tableView->model())->resetModel();
        }
        break;
        default: break;
    }

    if (!text.isEmpty()) ui->textBrowser->insertPlainText(text+"\r\n");
}


void MainWindow::on_generate_triggered()
{
    emit generateActive();
}

