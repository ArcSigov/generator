#include "dialogitemdelegate.h"


DialogDelegate::DialogDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{

}

DialogDelegate::~DialogDelegate()
{

}

QWidget* DialogDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    ItemPathWidget* i = new ItemPathWidget(parent);
    i->setAutoFillBackground(true);
    i->setGeometry(option.rect);
    i->show();
    return i;
}

void DialogDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    ItemPathWidget* i = static_cast<ItemPathWidget*>(editor);
    i->setText(index.data().toString());
}

void DialogDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    ItemPathWidget* i = static_cast<ItemPathWidget*>(editor);
    model->setData(index,i->text());
}

void DialogDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

void DialogDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter,option,index);
}
