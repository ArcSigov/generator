#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogitemdelegate.h"
#include "calendaritemdelegate.h"
#include "checkdelegate.h"
#include "tableview.h"

#include <QDebug>
#include <QLabel>
#include <QStyle>
#include <QPalette>

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
    message(MessageCategory::def);

    connect(ui->options,    &QAction::triggered,             optionWindow,&OptionWindow::show);
    connect(Storage::load(),&Storage::sendMessage,           this,&MainWindow::message);                       ///< Соединенение главного окна с генератором с уведомлением о выборе файла для записи
    connect(ui->tableView->horizontalHeader(),  &QHeaderView::sectionDoubleClicked, this, &MainWindow::removeRowData);
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
            ui->tableView->model()->removeRows(it->row(),1,*it);
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


void MainWindow::message(const MessageCategory& category,const QString& text)
{
    static QPalette p;
    ui->progressBar->setPalette(p);
    status->clear();
    switch (category)
    {
    //!< первоначальная настройка
    case MessageCategory::def:
    {
        ui->rem->setEnabled(false);
        ui->generate->setEnabled(false);
        ui->textBrowser->setVisible(false);
        ui->Save->setEnabled(false);
        ui->Save_as->setEnabled(false);
        ui->progressBar->setVisible(false);
        ui->tableView->setVisible(false);
        ui->textBrowser->setTextColor(Qt::black);
        break;
    }
    //!< при запуске генерации
    case MessageCategory::run:
    {
        ui->rem->setEnabled(false);
        ui->generate->setEnabled(false);
        ui->textBrowser->setVisible(true);
        ui->Save->setEnabled(false);
        ui->Save_as->setEnabled(false);
        ui->progressBar->setVisible(true);
        ui->progressBar->setMinimum(0);
        ui->progressBar->setMaximum(Storage::load()->data().size());
        ui->progressBar->setValue(0);
        p.setColor(QPalette::Highlight,Qt::green);
        break;
    }
    //!< при завершении генерации
    case MessageCategory::stop:
    {
        ui->generate->setEnabled(true);
        ui->Save->setEnabled(true);
        ui->Save_as->setEnabled(true);
        ui->textBrowser->setVisible(false);
        ui->textBrowser->clear();
        ui->progressBar->setVisible(false);
        break;
    }
    //!< при готовности данных
    case MessageCategory::dataReady:
    {
        ui->rem->setEnabled(true);
        ui->generate->setEnabled(true);
        ui->Save->setEnabled(true);
        ui->Save_as->setEnabled(true);
        ui->tableView->setVisible(true);
        ui->textBrowser->setVisible(false);
        ui->textBrowser->clear();
        optionWindow->initializeSettings();
        static_cast<TableModel*>(ui->tableView->model())->resetModel();
        break;
    }
    //!< обновление табличного состояния и строки прогресса
    case MessageCategory::update:
    {
        ui->progressBar->setValue(ui->progressBar->value()+1);
        static_cast<TableModel*>(ui->tableView->model())->resetModel();
        break;
    }
    //!< при генерации ошибок
    case MessageCategory::error:
    {
        ui->generate->setEnabled(false);
        status->setStyleSheet("color:red");
        status->setText(text);
        return;
    }
    //!< предупреждения
    case MessageCategory::warning:
    {
        ui->textBrowser->setTextColor(Qt::yellow);
        break;
    }
    default : break;
    }
    if (!text.isEmpty()) ui->textBrowser->insertPlainText(text+"\r\n");
}

void MainWindow::on_generate_triggered()
{
    emit generateActive();
}

void MainWindow::removeRowData(int v)
{
    auto list = ui->tableView->selectionModel()->selection().indexes();
    for (const auto& index:list)
        ui->tableView->model()->setData(index,{});
}

