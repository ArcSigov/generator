#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractItemModel>
#include "tableitemdelegate.h"
#include "tableview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TableModel*  m  = new TableModel(this);
    ItemDelegate* i = new ItemDelegate(this);

    //ui->tableView->setVisible(false);
    ui->tableView->setModel(m);
    ui->tableView->setItemDelegate(i);
    ui->progressBar->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setView(QAbstractTableModel* m)
{
    ui->tableView->setModel(m);
}
