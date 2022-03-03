#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogitemdelegate.h"
#include "calendaritemdelegate.h"
#include "tableview.h"

#include <QDebug>
#include <QStyle>

MainWindow::MainWindow(Generator* _gen, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    box(new QMessageBox(this))
{

    optionWindow = new OptionWindow();
    TableModel* t = new TableModel(this);


    ui->setupUi(this);
    ui->progressBar->setVisible(false);
    ui->dob->setIcon(style()->standardIcon(QStyle::SP_FileDialogStart));
    ui->rem->setIcon(style()->standardIcon(QStyle::SP_TrashIcon));
    ui->generate->setIcon(style()->standardIcon(QStyle::SP_DialogYesButton));
    ui->tableView->setItemDelegateForColumn(FILE_PATH,new DialogDelegate(this));
    ui->tableView->setItemDelegateForColumn(ID_DATE,new CalendarDelegate(this));
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(t);

    connect(ui->options, &QAction::triggered,optionWindow,&OptionWindow::show);
    connect(t,           &TableModel::tableUpdated,      Storage::load(),&Storage::sort);
    connect(this        ,&MainWindow::filePathSetted,   _gen,&Generator::readTblFile);                       ///< Соединенение главного окна с генератором с уведомлением о выборе файла для чтения
    connect(this        ,&MainWindow::saveFilePath,     _gen,&Generator::saveTblFile);                       ///< Соединенение главного окна с генератором с уведомлением о выборе файла для записи
    connect(ui->generate,&QAction::triggered,           _gen,&Generator::run);                               ///< Соединенение главного окна с генератором с уведомлением о начале работы
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
        if (it->column() == 0)  ui->tableView->model()->removeRows(it->row(),1,*it);
    }
}

void MainWindow::on_dob_triggered()
{
    ui->tableView->model()->insertRows(ui->tableView->model()->rowCount(),1);
}

void MainWindow::on_Open_triggered()
{
    emit filePathSetted(QFileDialog::getOpenFileName(this, tr("Открыть файл"), " ", tr("table(*.tbl)")));
}

void MainWindow::update()
{
    optionWindow->updateSettings();
    static_cast<TableModel*>(ui->tableView->model())->resetModel();
}

void MainWindow::on_Save_triggered()
{
    emit saveFilePath(QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "", tr("table(*.tbl)")));
}

void MainWindow::notify(const QString& result)
{
    box->setText(result);
    box->exec();
}
