#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H

#include <QAbstractTableModel>
#include <QVector>
#include <QSize>
#include <QBrush>
#include "tablerowprop.h"
#include "datastorage.h"


class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject* parent = nullptr,QVector<DataStorage>* _hash = nullptr);
    ~TableModel();
    Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex())             const override;
    Q_INVOKABLE virtual int columnCount(const QModelIndex &parent = QModelIndex())          const override;
    Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Q_INVOKABLE virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    Q_INVOKABLE virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;    
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
private:
    QVector<DataStorage>* storage; // данные по каждой ячейке таблицы
};

#endif
