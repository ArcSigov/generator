#ifndef CALENDAR_ITEM_DELEGATE_H
#define CALENDAR_ITEM_DELEGATE_H

#include <QStyledItemDelegate>
#include <QCalendarWidget>


class CalendarDelegate : public QStyledItemDelegate
{
    Q_OBJECT
        public:
                 explicit CalendarDelegate(QObject* parent = nullptr);
    ~CalendarDelegate();

    //Создает виджет редактора значения
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    //Описывает ячейку элемента
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    //Передает значение от модели в редактор
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    //Передает значение от редактора в модель
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    // Изменяет геометрию виджета
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif
