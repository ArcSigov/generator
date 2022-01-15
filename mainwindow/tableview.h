#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H

#include <QAbstractTableModel>
#include <QHash>

#include "tablerowprop.h"



class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject* parent = nullptr);
    ~TableModel(){}
    Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex())             const override;
    Q_INVOKABLE virtual int columnCount(const QModelIndex &parent = QModelIndex())          const override;
    Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Q_INVOKABLE virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
private:
    QHash<int,QVariant> hash; // данные по каждой ячейке таблицы
};

#endif
