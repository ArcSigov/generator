#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tableitemdelegate.h"
#include "tableview.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ItemDelegate* i = new ItemDelegate(this);
    // ui->tableView->setItemDelegate(i);

    ui->setupUi(this);
    TableModel*  m  = new TableModel(this);
    ui->tableView->setModel(m);
    //ui->tableView->model()->insertRow()
    ui->progressBar->setVisible(false);
    connect(ui->dob,SIGNAL(triggered()),this,SLOT(addRowToTable()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addRowToTable()
{
    qDebug() << ui->tableView->model()->rowCount();
    ui->tableView->model()->insertRows(ui->tableView->model()->rowCount(),1);
    //ui->tableView-
}
