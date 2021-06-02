#include "myview.h"

#include <QResizeEvent>

MyView::MyView(QWidget *parent) : QAbstractItemView(parent)
{
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(QPalette::Background,Qt::white));
}

void MyView::printLegend(QPainter &painter)
{
    QAbstractItemModel *model = this->model();
    int modelSize = model->rowCount(QModelIndex());

    for(int i = 0; i < modelSize; i++)
    {
        painter.setPen(palet[i%12]);
        painter.setBrush(QBrush(palet[i%12],Qt::SolidPattern));
        QString text = model->data(model->index(i,0),Qt::DisplayRole).toString();
        text += " (" + model->data(model->index(i,2),Qt::DisplayRole).toString() + "%)";

        painter.drawRect(legendRect.x() + 5, legendRect.y() + 5 + 20*i,10,10);
        painter.setPen(Qt::black);
        painter.drawText(legendRect.x() + 20, legendRect.y() + 15 + 20*i,text);
    }
}

void MyView::resizeEvent(QResizeEvent *event)
{
    drawRect = QRect(5,5,(event->size().width()-15)*0.8,event->size().height()-10);
    legendRect = QRect(10 + drawRect.width(),5,(event->size().width()-15)*0.2,drawRect.height());
}
