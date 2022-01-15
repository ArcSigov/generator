#include "tableview.h"


int TableModel::rowCount(const QModelIndex &parent) const
{
    return 15;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return static_cast<int>(ColumnProp::COLUMN_COUNT);
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}
