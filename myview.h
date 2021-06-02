#ifndef MYVIEW_H
#define MYVIEW_H

#include <QAbstractItemView>
#include <QPainter>
#include <QRect>

class MyView : public QAbstractItemView
{
    Q_OBJECT
public:
    MyView(QWidget *parent);

    virtual QModelIndex indexAt(const QPoint &point) const override{return QModelIndex();}
    virtual void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) override{}
    virtual QRect visualRect(const QModelIndex &index) const override{return QRect();}

protected:

    virtual int horizontalOffset() const override{return 0;}
    virtual bool isIndexHidden(const QModelIndex &index) const override{return  true;}
    virtual QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override{return QModelIndex();}
    virtual void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) override{};
    virtual int verticalOffset() const override{return 0;}
    virtual QRegion visualRegionForSelection(const QItemSelection &selection) const override{return QRegion();}


    void changeColor(QPainter &painter, int color_id);

    virtual void drawChart(QPainter &painter) = 0;
    void printLegend(QPainter &painter);

    void resizeEvent(QResizeEvent *event) override;

    QRect drawRect;
    QRect legendRect;

    const QColor palet[12] = {Qt::red, Qt::blue, Qt::magenta, Qt::green, Qt::yellow, Qt::cyan, Qt::darkRed,
                           Qt::darkBlue, Qt::darkMagenta, Qt::darkYellow, Qt::darkGreen, Qt::darkCyan};

};

#endif // MYVIEW_H
