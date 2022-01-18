#include "calendaritemdelegate.h"

CalendarDelegate::CalendarDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{

}

CalendarDelegate::~CalendarDelegate()
{

}

QWidget* CalendarDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QCalendarWidget* Calendar = new QCalendarWidget(parent);
    Calendar->setAutoFillBackground(true);
    Calendar->setGeometry(option.rect);
    return Calendar;
}

void CalendarDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QCalendarWidget* Calendar = static_cast<QCalendarWidget*>(editor);
    Calendar->setSelectedDate(index.data().toDate());
}

void CalendarDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QCalendarWidget* Calendar = static_cast<QCalendarWidget*>(editor);
    model->setData(index,Calendar->selectedDate());
}

void CalendarDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

void CalendarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter,option,index);
}
