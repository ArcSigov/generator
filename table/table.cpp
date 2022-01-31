#include "table.h"
#include "ui_table.h"
#include <qdebug.h>
#include "tablerowprop.h"
#include "cfggenerator/cfggenerator.h"

Table::Table(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::Table)
{

}

//void IniGen::Run()
//{
//    emit TaskCompleted(false);
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName( "Windows-1251" ));
//    QDir dir;
//    std::vector<QString> name_po;
//    dir.mkpath("out/sre");
//    block->SetOutputDir(this->load_output_folder+"/");
//    for(auto i = 0 ; i <table->rowCount();i++)
//    {
//        QFileInfo fileinfo(table->item(i,FILE_PATH)->text());
//        auto outputformat = fileinfo.completeSuffix() == "elf" ? "_sum.sre" : "_sum.mot";
//        QFile  file(QString("out/ini.ini"));
//        QTextStream text(&file);


//        if (name_po.size() == 11)
//        {
//            if (table->item(i,FILE_CRC)->text().isEmpty())
//            {
//                emit SetToTable(name_po[9].right(8),i,FILE_CRC);
//            }
//            if (table->item(i,FILE_DATE)->text().isEmpty())
//            {
//                emit SetToTable(name_po[7].right(12).replace('.',':'),i,FILE_DATE);
//            }
//        }


//        block->Add(QFileInfo(table->item(i,FILE_PATH)->text()).baseName()+"_sum",
//                             table->item(i,MODULE)->text(),
//                             table->item(i,FILE_RAM_ADDR)->text(),
//                             table->item(i,FILE_TYPE)->text() == "Бинарный" ? L_FILE::BINARY : L_FILE::CONFIG,
//                             FileGen::GetNewSize(QFileInfo(table->item(i,FILE_PATH)->text()).size()),
//                             table->item(i,FILE_PART_NUM)->text().toUInt());

//        emit SetResult("Генерация " + fileinfo.baseName()+outputformat + " завершена c результатом: " + name_po[2] + "\r\n");
//    }
//    emit SetResult("Генерация загрузочных образов завершена.\r\n");
//    block->WriteToTable();
//    block->RunBatch();
//    emit SetResult("Генерация загрузочных файлов и конфигурации завершена.\r\n");
//    emit TaskCompleted(true);
//    delete block;
//}

Table::~Table()
{
    Dialog.reset();
    delete ui;
}


void Table::on_Generate_clicked()
{
//    std::unique_ptr<BaseCfgGen> block;
//    //gen    = new IniGen(ui->filestable);
//    thread = new QThread;

////    ui->progressBar->setMinimum(0);
////    ui->progressBar->setMaximum(ui->filestable->rowCount()+1);
////    ui->progressBar->reset();
////    ui->textBrowser->clear();


//    connect(gen,&IniGen::SetResult,this,&Table::InsertText);
//    connect(gen,&IniGen::TaskCompleted,this,&Table::EditItems);
//    connect(gen,&IniGen::SetToTable,this,&Table::WriteToTable);
//    connect(thread,&QThread::started,gen,&IniGen::Run);
//    connect(thread,&QThread::finished,gen,&QObject::deleteLater);
//    connect(thread,&QThread::finished,thread,&QObject::deleteLater);
//   // gen->SetFolders(ui->label->text(),ui->load_output_folder->text());

////    if (ui->bis->isChecked())        gen->SetBlock(new BisCfgGen(ui->label->text()+"/"));
////    else if (ui->bgs->isChecked())   gen->SetBlock(new BgsCfgGen(ui->label->text()+"/"));
////    else if (ui->bcvm->isChecked())  gen->SetBlock(new BcvmCfgGen(ui->label->text()+"/"));
////    else
////    {
////        QMessageBox* box = new QMessageBox;
////        box->setText("Задайте имя блока!");
////        box->exec();
////        delete box;
////        return;
////    }
////    gen->moveToThread(thread);
////    thread->start();
}


