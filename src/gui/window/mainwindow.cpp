#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogitemdelegate.h"
#include "calendaritemdelegate.h"
#include "checkdelegate.h"
#include "tableview.h"


#include <QLabel>
#include <QStyle>
#include <QPalette>
#include <QMenu>

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
    ui->verify->setIcon(style()->standardIcon(QStyle::SP_FileDialogInfoView));
    ui->generate->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->tableView->setItemDelegateForColumn(IS_CHECKED,new CheckDelegate(this));
    ui->tableView->setItemDelegateForColumn(FILE_PATH,new DialogDelegate(this));
    ui->tableView->setItemDelegateForColumn(ID_DATE,new CalendarDelegate(this));
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(new TableModel(this));
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->statusBar->addWidget(status);
    ui->statusBar->setVisible(true);
    message(MessageCategory::def);

    connect(ui->options,    &QAction::triggered,             optionWindow,&OptionWindow::show);
    connect(Storage::load(),&Storage::sendMessage,           this,&MainWindow::message);                       ///< Соединенение главного окна с генератором с уведомлением о выборе файла для записи

    QMenu* menu = new QMenu(this);
    QAction* remove = new QAction("Очистить выделенное",this);
    QAction* defval = new QAction("Установить по умолчанию",this);
    QAction* setval = new QAction("Установить выделенное для всех ячеек в столбце",this);
    menu->addAction(remove);
    menu->addAction(defval);
    menu->addAction(setval);
    connect(remove, &QAction::triggered,this,&MainWindow::clearRowData);
    connect(defval, &QAction::triggered,this,&MainWindow::defaultRowData);
    connect(setval, &QAction::triggered,this,&MainWindow::setRowData);
    connect(ui->tableView,&QTableView::customContextMenuRequested,this,&MainWindow::menuRequested);

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
        ui->verify->setEnabled(false);
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
        ui->textBrowser->clear();
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
        ui->rem->setEnabled(true);
        ui->Save->setEnabled(true);
        ui->Save_as->setEnabled(true);
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
        ui->verify->setEnabled(true);
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
        ui->textBrowser->setTextColor(Qt::black);
        ui->progressBar->setValue(ui->progressBar->value()+1);
        static_cast<TableModel*>(ui->tableView->model())->resetModel();
        break;
    }
    //!< при генерации ошибок
    case MessageCategory::error:
    {
        ui->textBrowser->setTextColor(Qt::red);
        ui->progressBar->setStyleSheet("color:red");
        break;
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

void MainWindow::clearRowData(bool flag)
{
    if (!flag)
    {
        auto list = ui->tableView->selectionModel()->selection().indexes();
        for (const auto& index:list)
            ui->tableView->model()->setData(index,{});
    }
}

void MainWindow::defaultRowData(bool flag)
{
    if (!flag)
    {
        auto list = ui->tableView->selectionModel()->selection().indexes();
        for (const auto& index:list)
        {
            switch (index.column())
            {
                case  IS_CHECKED:
                    ui->tableView->model()->setData(index,true);
                    break;
                case  MODULE_NUM:
                    ui->tableView->model()->setData(index,"25");
                    break;
                case  ID_DATE:
                    ui->tableView->model()->setData(index,QDate::currentDate());
                    break;
                case  VERSION:
                    ui->tableView->model()->setData(index,1);
                    break;
                case  REVISION:
                    ui->tableView->model()->setData(index,1);
                    break;
                case  RAM_ADDR:
                    ui->tableView->model()->setData(index,"0xa00b0000");
                    break;
                case  CRC:
                case  PART_N:
                case  FILE_PATH:
                case  DESCRIPTION:
                default:break;
            }
        }
    }
}



void MainWindow::menuRequested(QPoint pos)
{
    auto childs = this->children();
    for (const auto& child:childs)
    {
        auto menu = dynamic_cast<QMenu*>(child);
        if (menu)
        {
            menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
            break;
        }
    }
}


void MainWindow::setRowData(bool flag)
{
    if (!flag)
    {
        auto list = ui->tableView->selectionModel()->selection().indexes();
        if (list.size() == 1)
        {
            auto cell = list.first();
            for (auto i = 0; i < ui->tableView->model()->rowCount();i++)
            {
                auto index = ui->tableView->model()->index(i,cell.column());
                ui->tableView->model()->setData(index,cell.data());
            }
        }
    }
}


void MainWindow::on_verify_triggered()
{
    emit verifyPathSetted(QFileDialog::getOpenFileName(this, tr("Открыть файл с идентификаторами"), " ", "file(*.txt),logs(*.log)"));
}

