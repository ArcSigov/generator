#ifndef TABLE_ITEM_DELEGATE_H
#define TABLE_ITEM_DELEGATE_H

#include <QAbstractItemDelegate>


class ItemDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
    public:
    explicit ItemDelegate(QObject* parent = nullptr) : QAbstractItemDelegate(parent){}
    ~ItemDelegate(){}
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    // painting
    virtual void paint(QPainter *painter,
                       const QStyleOptionViewItem &option,
                       const QModelIndex &index) const override
    {

    }

    virtual QSize sizeHint(const QStyleOptionViewItem &option,
                           const QModelIndex &index) const override
    {
        return QSize();
    }

};


#endif
