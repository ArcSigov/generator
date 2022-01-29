#include "tableview.h"
#include <QDebug>
TableModel::TableModel(QObject* parent, QVector<DataStorage> *_hash) :
    QAbstractTableModel(parent), storage(_hash)
{

}

TableModel::~TableModel()
{

}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return storage ? storage->size() : 0;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return COLUMN_COUNT;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto s = storage->begin()+index.row();
    switch(role)
    {
        case Qt::DisplayRole:
        case Qt::EditRole:
             return s->at(index.column());
        case Qt::BackgroundRole:
            return QBrush((s->isValid(index.column()) ? Qt::yellow : Qt::transparent));
        default:
            return QVariant();
    }
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        auto p = storage->begin()+index.row();
        p->set(value,index.column());
        emit dataChanged(index,index);
        return true;
    }
    return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent,row,row+count-1);
    if (storage->size() <= row)
        storage->push_back(DataStorage());
    endInsertRows();
    return true;
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(!parent.isValid())
        return false;

    beginRemoveRows(parent,row,row+count-1);
    for (auto i = 0 ; i < count ; i++)
    {
        storage->erase(storage->begin()+row+i);
    }
    endRemoveRows();
    return true;
}


QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole )
    {
        if (orientation == Qt::Horizontal)
            return DataStorage::name(section);
        else
            return section;
    }
    return QVariant();
}

