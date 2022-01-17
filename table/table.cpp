#include "table.h"
#include "ui_table.h"
#include <qdebug.h>
#include "tablerowprop.h"
#include "cfggenerator/cfggenerator.h"

Table::Table(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::Table)
{
    ui->setupUi(this);
//    ui->label->setText(QDir::currentPath()+"/out/sre");
//    ui->load_output_folder->setText(ui->label->text());
    Dialog = std::make_unique<QFileDialog>(this);
//    ui->save->setEnabled(false);
//    ui->Generate->setEnabled(false);
//    ui->remove->setEnabled(false);
//    ui->progressBar->setVisible(false);
//    ui->filestable->horizontalHeader()->setStretchLastSection(true);
//    ui->filestable->verticalHeader()->setStretchLastSection(true);
}

void IniGen::Run()
{
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
//        if (file.open(QIODevice::ReadWrite | QIODevice::Truncate))
//        {
//            auto str = QString::number(FileGen::GetNewSize(fileinfo.size())-4,16);
//            while (str.length() != 8) str.push_front('0');

//            text << "00000000" << "\r\n";
//            text << str        << "\r\n";
//            text << table->item(i,FILE_PATH)->text() << "\r\n";
//            text << folder+"/" + fileinfo.baseName()+outputformat << "\r\n";
//            text << " " << "\r\n";
//            text << (table->item(i,FILE_DESCRIPTION)->text().isEmpty() ? QString("Нет описания") : table->item(i,FILE_DESCRIPTION)->text()) << "\r\n";
//            text << (table->item(i,FILE_VERREV)->text().isEmpty()      ? QString("00 00")        : table->item(i,FILE_VERREV)->text()) << "\r\n";
//            file.close();
//        }
//        std::system(("cmd.exe /C " + QDir::currentPath().toStdString() + "/ID_Info_con.exe " +
//                     (QDir::currentPath().toStdString() + "/out/ini") +
//                     (table->item(i,FILE_TYPE)->text() == "Бинарный" ?   " -bs " :" ")   +
//                     (table->item(i,FILE_DATE)->text().isEmpty() ? " " : "-d " + table->item(i,FILE_DATE)->text().toStdString()+" ") +
//                     (table->item(i,FILE_CRC)->text().isEmpty() ? " "  : "-cs " + table->item(i,FILE_CRC)->text().toStdString()+" ") +
//                     (" > " + QDir::currentPath().toStdString() + "/out/log.crc")).c_str());

//        file.setFileName(QDir::currentPath() + "/out/log.crc");
//        if (file.open(QIODevice::ReadOnly))
//        {
//            name_po.clear();
//            while (!text.atEnd()) name_po.push_back(text.readLine());
//            file.close();
//        }

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
}

Table::~Table()
{
    Dialog.reset();
    delete ui;
}

void Table::InsertText(const QString& str)
{
   // ui->progressBar->setValue(ui->progressBar->value()+1);
  //  ui->textBrowser->insertPlainText(str);
}
void Table::_enable_buttons()
{
  //  ui->save->setEnabled(true);
  //  ui->Generate->setEnabled(true);
  //  ui->remove->setEnabled(true);
}

void Table::_add_raw_to_table(std::vector<QString> str)
{
//  //  ui->filestable->setRowCount(ui->filestable->rowCount()+1);
//    for (auto i = 0ull ; i < COLUMNS_COUNT;i++)
//    {
//      //  ui->filestable->setItem(ui->filestable->rowCount()-1,i,new QTableWidgetItem(str[i],0));
//    }
//  //  ui->filestable->sortByColumn(MODULE,Qt::SortOrder::AscendingOrder);
//  //  ui->filestable->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
//  //  ui->filestable->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);
}

void Table::_update_path(const QString& path)
{
  //  ui->label->setText(path);
  //  if (!ui->load_output_folder->isEnabled())
  //      ui->load_output_folder->setText( ui->label->text());
}

void Table::on_add_clicked()
{
//    auto filename = Dialog->getOpenFileName(this,tr("Добавить файл"), "",tr("ius_types (*.mot *.elf)"));
//    if (!filename.isEmpty())
//    {
//        QFileInfo file(filename);
//        _enable_buttons();
//        _add_raw_to_table({"",filename,file.completeSuffix() == "elf" ? "Бинарный" : "Загрузочный","","","","","",""});
//    }
}

void Table::on_ChangeFolder_clicked()
{
    //_update_path(Dialog->getExistingDirectory(this));
}

void Table::on_load_clicked()
{
//    QFile file(Dialog->getOpenFileName(this,tr("Открыть таблицу"), " ",tr("table(*.tbl)")));
//    std::vector<QString> vctr;
//    if (file.open(QIODevice::ReadOnly))
//    {
//        QTextStream tbl(&file);
//  //      ui->filestable->clearContents();
//  //      ui->filestable->setRowCount(0);
//        _enable_buttons();
//  //      ui->label->setText(tbl.readLine());
//  //      ui->load_output_folder->setText(tbl.readLine());
//        auto pos = tbl.readLine();
//  //      ui->bis->setChecked(pos == "1");
//  //      ui->bcvm->setChecked(pos == "2");
//  //      ui->bgs->setChecked(pos == "3");
//        while(!tbl.atEnd())
//        {
//            _make_raw(tbl.readLine().toStdString(),vctr);
//            _add_raw_to_table(vctr);
//            vctr.clear();
//        }
//    }
//    file.close();
}

void Table::on_save_clicked()
{
//    QFile file(Dialog->getSaveFileName(this,tr("Сохранить"),"",tr("table(*.tbl)")));
//    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate))
//    {
//        QTextStream out(&file);
//        out.setCodec("Windows-1251");
//        //out << ui->label->text() << "\r\n" << ui->load_output_folder->text()<<"\r\n";

//   //     if      (ui->bis->isChecked())  out << "1";
//  //      else if (ui->bcvm->isChecked()) out << "2";
//  //      else if (ui->bgs->isChecked())  out << "3";
//  //      else out << "0";

//        out << "\r\n";
////        for (auto i = 0 ; i < ui->filestable->rowCount();i++)
////        {
////            for (auto j = 0 ; j < ui->filestable->columnCount() ; j++)
////            {
////                out << ui->filestable->item(i,j)->text() << ";";
////            }
////            out<< "\r\n";
////        }
//        file.close();
//    }
}

void Table::on_filestable_cellChanged([[maybe_unused]] int row ,[[maybe_unused]] int column)
{
   // ui->filestable->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
   // ui->filestable->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);

}

void Table::_make_raw(const std::string& str, std::vector<QString>& columns)
{
//    auto pos = str.begin();
//    for (auto it = str.begin(); it!= str.end(); it++)
//    {
//        if (*it==';')
//        {
//            columns.emplace_back(QString::fromStdString(std::string(pos,it)));
//            pos = it+1;
//        }
//    }
}

void Table::on_remove_clicked()
{
//    for (auto i = 0 ; i < ui->filestable->rowCount();i++)
//    {
//        if (ui->filestable->item(i,0)->isSelected())
//        {
//            ui->filestable->removeRow(i);
//        }
//    }
}

void Table::WriteToTable(const QString& str,int row, int column)
{
  //  ui->filestable->item(row,column)->setText(str);
}

void Table::on_dir_synchr_pressed()
{
  //  ui->load_output_folder->setEnabled(ui->dir_synchr->isChecked());
  //  if (!ui->load_output_folder->isEnabled()) ui->load_output_folder->setText(ui->label->text());
}

void Table::EditItems(const bool& flag)
{
  //  ui->progressBar->setVisible(!flag);
  //  ui->Generate->setEnabled(flag);
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

void Table::on_filestable_doubleClicked(const QModelIndex &index)
{
}

