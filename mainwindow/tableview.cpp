#include "tableview.h"
#include <QDebug>
TableModel::TableModel(QObject* parent) : QAbstractTableModel(parent)
{
    qDebug(__PRETTY_FUNCTION__);
    hash[0][0]= QString("");

}


int TableModel::rowCount(const QModelIndex &parent) const
{
    qDebug(__PRETTY_FUNCTION__);
    return hash.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return static_cast<int>(ColumnProp::COLUMN_COUNT);
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{

    qDebug(__PRETTY_FUNCTION__);
    if (!index.isValid())
        return QVariant();


    auto column = index.column();
    auto row    = index.row();

    switch(column)
    {
    case     MODULE_NUM:
    case     FILE_PATH:
    case     ID_DATE:
    case     VERSION:
    case     CRC:
    case     DESCRIPTION:
    case     RAM_ADDR:
    case     PART_N:

    }



    switch(role)
    {
        case Qt::DisplayRole	 : //  Ключевые данные, которые будут отображаться в виде текста. ( QString )
        {
            hash.at(row)[column] = "";
        }
        //case Qt::DecorationRole  : //  Данные для оформления в виде значка. ( QColor , QIcon или QPixmap )
        case Qt::EditRole        : //  Данные в форме удобной для редактирования в редакторе. ( QString )
        //case Qt::ToolTipRole     : //  Данные, отображаемые во всплывающей подсказке элемента. ( QString )
        //case Qt::StatusTipRole   : //  Данные отображаются в строке состояния. ( QString )
        //case Qt::WhatsThisRole   : //  Данные, отображаемые для элемента в разделе «Что это?» режим. ( QString )
        //case Qt::SizeHintRole    : //	Подсказка размера для элемента, который будет предоставлен представлениям. ( QРазмер )
        default : break;
    }


    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug(__PRETTY_FUNCTION__);
   // hash[index.row()] = value.toString();
    //return true;
}


//!< выполняет обработку флагов каждой конкретной ячейки
//!< если ячейка не валидна, то возвращает отсутствие флагов
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}


bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent,row,row+count-1);
    endInsertRows();

//    for (auto i = row; i < count; i++)
//    {
//        hash[i] = "";
//    }
    return true;
}
