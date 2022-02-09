#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogitemdelegate.h"
#include "calendaritemdelegate.h"
#include "tableview.h"

#include <QDebug>
#include <QStyle>

MainWindow::MainWindow(QVector<DataStorage> *_s, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    s(_s),
    box(new QMessageBox(this)),
    options(new OptionWindow())
{



    TableModel* t = new TableModel(this,s);

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

    connect(ui->options,&QAction::triggered,options,&OptionWindow::show);
    connect(options, &OptionWindow::settingsUpdated,this,&MainWindow::readSettings);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rem_triggered()
{
    //ui->tableView->model()->removeRows(ui->tableView->model().,1);
}

void MainWindow::on_dob_triggered()
{
    ui->tableView->model()->insertRows(ui->tableView->model()->rowCount(),1);
}

void MainWindow::on_Open_triggered()
{
    emit filePathSetted(QFileDialog::getOpenFileName(this, tr("Открыть файл"), " ", tr("table(*.tbl)")));
}

void MainWindow::updateTable()
{
    ui->tableView->model()->removeRows(0,ui->tableView->model()->rowCount());
    static_cast<TableModel*>(ui->tableView->model())->updateRows(ui->tableView->model()->rowCount(),s->size());
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

void MainWindow::on_generate_triggered()
{
    emit generateActive(true);
}

void MainWindow::readSettings(const Settings& _settings)
{
    emit settingsUpdated(_settings);
}
