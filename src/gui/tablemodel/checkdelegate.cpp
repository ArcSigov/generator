#include "checkdelegate.h"
#include <QCheckBox>
#include <QApplication>
#include <QDebug>
CheckDelegate::CheckDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{

}


QWidget* CheckDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QCheckBox* btn = new QCheckBox(parent);
    btn->setAutoFillBackground(true);
    btn->setCheckable(true);
    btn->show();
    return btn;
}

void CheckDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QCheckBox* btn = static_cast<QCheckBox*>(editor);
    btn->setChecked(index.data().toBool());
}

void CheckDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QCheckBox* btn = static_cast<QCheckBox*>(editor);
    model->setData(index,btn->isChecked());
}

void CheckDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

void CheckDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionButton btn;
    btn.rect = option.rect;
    btn.state = QStyle::State_Enabled | (index.data().toBool() ? QStyle::State_On : QStyle::State_Off);
    QApplication::style()->drawControl(QStyle::CE_CheckBox,&btn,painter);
}

