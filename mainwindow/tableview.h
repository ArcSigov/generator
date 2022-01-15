#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H

#include <QAbstractTableModel>
#include <QVector>
#include "tablerowprop.h"


class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}
    ~TableModel(){}
    Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex())             const override;
    Q_INVOKABLE virtual int columnCount(const QModelIndex &parent = QModelIndex())          const override;
    Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
private:
    //QVector<
};

#endif
