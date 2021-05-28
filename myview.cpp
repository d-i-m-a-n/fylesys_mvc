#include "myview.h"

#include <QResizeEvent>

#include "filesdatamodel.h"

myView::myView(QWidget *parent) : QWidget(parent)
{
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(QPalette::Background,Qt::white));
}

void myView::printLegend(QPainter &painter)
{
    int modelSize = model->rowCount(QModelIndex());
    int k = 0;
    for(int i = 0; i < modelSize; i++)
    {
        if(k > 12)
            k = 0;
        painter.setPen(palet[k]);
        painter.setBrush(QBrush(palet[k],Qt::SolidPattern));
        k++;
        QString text = model->data(model->index(i,0),Qt::DisplayRole).toString();
        text += " (" + model->data(model->index(i,2),Qt::DisplayRole).toString() + "%)";

        painter.drawRect(legendRect.x() + 5, legendRect.y() + 5 + 20*i,10,10);
        painter.drawText(legendRect.x() + 20, legendRect.y() + 15 + 20*i,text);
    }
}

void myView::setModel(FilesDataModel *model_)
{
    model = model_;
}

void myView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black));
    painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));

    painter.drawRect(drawRect);

    printLegend(painter);
}

void myView::resizeEvent(QResizeEvent *event)
{
    drawRect = QRect(5,5,(event->size().width()-15)*0.8,event->size().height()-10);
    legendRect = QRect(10 + drawRect.width(),5,(event->size().width()-15)*0.2,drawRect.height());
}
