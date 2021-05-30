#ifndef MYVIEW_H
#define MYVIEW_H

#include <QWidget>
#include <QPainter>
#include <QRect>

class FilesDataModel;

class MyView : public QWidget
{
    Q_OBJECT
public:
    MyView(QWidget *parent);

    void setModel(FilesDataModel *model_);

protected:

    void changeColor(QPainter &painter, int color_id);

    virtual void drawChart(QPainter &painter) = 0;
    void printLegend(QPainter &painter);

    void resizeEvent(QResizeEvent *event) override;

    FilesDataModel *model;

    QRect drawRect;
    QRect legendRect;

    const QColor palet[12] = {Qt::red, Qt::blue, Qt::magenta, Qt::green, Qt::yellow, Qt::cyan, Qt::darkRed,
                           Qt::darkBlue, Qt::darkMagenta, Qt::darkYellow, Qt::darkGreen, Qt::darkCyan};

};

#endif // MYVIEW_H
