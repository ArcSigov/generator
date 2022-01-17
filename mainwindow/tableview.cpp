#include "tableview.h"
#include <QDebug>
TableModel::TableModel(QObject* parent, QVector<DataStorage> *_hash) :
    QAbstractTableModel(parent), storage(_hash)
{

}


int TableModel::rowCount(const QModelIndex &parent) const
{
    return storage ? storage->size() : 0;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return static_cast<int>(ColumnProp::COLUMN_COUNT);
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    QVariant v;


    if (!index.isValid() || !storage)
        return v;

    auto s = storage->begin()+index.row();

    switch(role)
    {
        case Qt::DisplayRole	 : //  Ключевые данные, которые будут отображаться в виде текста. ( QString )
        case Qt::EditRole        : //  Данные в форме удобной для редактирования в редакторе. ( QString )
             return s->GetValue(index.column());
        //case Qt::DecorationRole  : //  Данные для оформления в виде значка. ( QColor , QIcon или QPixmap )
        default:
            return QVariant();
    }

}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        auto p = storage->begin()+index.row();
        p->SetValue(value,index.column());
    }
}


//!< выполняет обработку флагов каждой конкретной ячейки
//!< если ячейка не валидна, то возвращает отсутствие флагов
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid() || !storage)
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
