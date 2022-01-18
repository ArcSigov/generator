#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogitemdelegate.h"
#include "calendaritemdelegate.h"
#include "tableview.h"

#include <QDebug>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setVisible(false);
    ui->dob->setIcon(style()->standardIcon(QStyle::SP_FileDialogStart));
    ui->rem->setIcon(style()->standardIcon(QStyle::SP_TrashIcon));
    ui->generate->setIcon(style()->standardIcon(QStyle::SP_DialogYesButton));

    DialogDelegate* i = new DialogDelegate(this);
    CalendarDelegate* c = new CalendarDelegate(this);

    ui->tableView->setItemDelegateForColumn(FILE_PATH,i);
    ui->tableView->setItemDelegateForColumn(ID_DATE,c);
    connect(ui->dob,SIGNAL(triggered()),this,SLOT(addRowToTable()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addRowToTable()
{
    ui->tableView->model()->insertRows(ui->tableView->model()->rowCount(),1);
}

void MainWindow::setModelToTable(QAbstractTableModel *m)
{
    ui->tableView->setModel(m);
}

void MainWindow::on_rem_triggered()
{
    //ui->tableView->model()->removeRows(ui->tableView->model().,1);
}

