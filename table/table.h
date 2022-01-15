#ifndef TABLE_H
#define TABLE_H

#include <QWidget>
#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QTableWidgetItem>
#include <QDebug>
#include <QThread>
#include <QMessageBox>
#include <memory>
#include "cfggenerator/cfggenerator.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <mutex>
#include <thread>
#include <atomic>


namespace Ui {
class Table;
}

//enum column_pos
//{
//    MODULE = 0,
//    FILE_PATH,
//    FILE_TYPE,
//    FILE_DATE,
//    FILE_VERREV,
//    FILE_CRC,
//    FILE_DESCRIPTION,
//    FILE_RAM_ADDR,
//    FILE_PART_NUM,
//    COLUMNS_COUNT
//};


class FileGen
{
public:
    FileGen(){};
    ~FileGen(){};
    static auto GetNewSize(size_t filesize){
        auto newsize = filesize+80;
        auto div = 4096;
        while (newsize % div != 0 )
        {
            newsize++;
        }
        return newsize;
    }
};

class IniGen: public QObject
{
    Q_OBJECT
public:
    IniGen(QTableWidget * tbl) : table(tbl){};
    ~IniGen(){
        delete block;
    }
public:
    void Run();
    void SetFolders(const QString& _folder, const QString& _load_folder) {
        folder = _folder;
        load_output_folder = _load_folder;
    }
    void SetBlock(BaseCfgGen* _block) {
        block = _block;
    }
signals:
    void SetResult(const QString& str);
    void SetToTable(const QString& str, int row, int column);
    void TaskCompleted(const bool& flag);
private:
    QTableWidget* table;
    BaseCfgGen*   block;
    QString folder,load_output_folder;
};

class Table : public QMainWindow
{
    Q_OBJECT
    Ui::Table *ui;
    QThread*        thread;
    IniGen*         gen;
    std::unique_ptr<QFileDialog>    Dialog;
public:
    explicit Table(QMainWindow *parent = nullptr);
    ~Table();
private slots:
    void on_add_clicked();
    void on_ChangeFolder_clicked();
    void on_load_clicked();
    void on_save_clicked();
    void on_filestable_cellChanged(int row, int column);
    void on_remove_clicked();
    void on_dir_synchr_pressed();
    void on_Generate_clicked();
    void on_filestable_doubleClicked(const QModelIndex &index);

public slots:
    void InsertText(const QString& str);
    void EditItems(const bool& flag);
    void WriteToTable(const QString& str, int row, int column);
private:
    void _add_raw_to_table(std::vector<QString> str);
    void _enable_buttons();
    void _make_raw(const std::string& str, std::vector<QString>& columns);
    void _update_path(const QString& path);

};



#endif // TABLE_H
