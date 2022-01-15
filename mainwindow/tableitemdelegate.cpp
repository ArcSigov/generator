#include "tableitemdelegate.h"
#include "tablerowprop.h"
#include <QDateEdit>
#include <QDebug>
#include <QDialog>

QWidget * ItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug() << "111";
    if (!index.isValid())
        return nullptr;


    switch(index.column())
    {
    case static_cast<int>(ColumnProp::ID_DATE) :
    {
        qDebug() << "111";
            return new QDateEdit(parent);
    }
    default :
        return nullptr;
    }
}
