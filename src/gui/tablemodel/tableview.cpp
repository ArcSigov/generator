#include "tableview.h"
#include <QDebug>
TableModel::TableModel(QObject* parent) :
    QAbstractTableModel(parent)
{

}

int TableModel::rowCount([[maybe_unused]] const QModelIndex &parent) const
{
    return storage.size();
}

int TableModel::columnCount([[maybe_unused]] const QModelIndex &parent) const
{
    return COLUMN_COUNT;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto& s = storage.at(index.row());
    switch(role)
    {
        case Qt::DisplayRole:
        case Qt::EditRole:
        {
            if (index.column() == RAM_ADDR || index.column() == MODULE_NUM || index.column() == CRC)
                return QString::number(s.at(index.column()).toUInt(),16);
            else
                return s.at(index.column());
        }
        case Qt::BackgroundRole:
            if (index.column() == PART_N)
                return QBrush(Qt::transparent);
            else
                return QBrush((s.isValid(index.column()) ? Qt::yellow : Qt::transparent));
//        case Qt::TextAlignmentRole:
//            if (index.column() == FILE_PATH || index.column() == DESCRIPTION)
//                return int(Qt::AlignLeft | Qt::AlignBottom);
//            return Qt::AlignCenter;
        default:
            return QVariant();

    }
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        auto& s = storage.at(index.row());
        if (index.column() == RAM_ADDR || index.column() == MODULE_NUM || index.column() == CRC)
        {
            auto v = value.toString().toUInt(nullptr,16);
            s.set(QVariant(v),index.column());
        }
        else
            s.set(value,index.column());
        emit dataChanged(index,index);
        resetModel();
        return true;
    }
    return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    if (index.column() == PART_N && storage.at(index.row()).genericType())
        return Qt::NoItemFlags;
    else
        return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent,row,row+count-1);
    if (storage.size() <= static_cast<size_t>(row))
        storage.push_back(DataStorage());
    endInsertRows();
    resetModel();
    return true;
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(!parent.isValid())
        return false;

    beginRemoveRows(parent,row,row+count-1);
    storage.erase(storage.begin()+row);
    endRemoveRows();
    resetModel();
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

void TableModel::resetModel()
{
    emit tableUpdated();
    beginResetModel();
    endResetModel();
}
