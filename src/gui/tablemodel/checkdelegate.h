#pragma once


#include <QStyledItemDelegate>


class CheckDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CheckDelegate(QObject* parent = nullptr);
    ~CheckDelegate() = default;

    //Создает виджет редактора значения
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    //Описывает ячейку элемента
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    //Передает значение от модели в редактор
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    //Передает значение от редактора в модель
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    // Изменяет геометрию виджета
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

