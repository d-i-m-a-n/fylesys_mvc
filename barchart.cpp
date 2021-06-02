#include "barchart.h"

#include "filesdatamodel.h"

BarChart::BarChart(QWidget *parent) : MyView(parent)
{
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(QPalette::Background,Qt::white));
}

void BarChart::drawChart(QPainter &painter)
{
    QAbstractItemModel *model = this->model();
    int modelSize = model->rowCount(QModelIndex());
    for(int i = 0; i < modelSize; i++)
    {
        painter.setPen(palet[i%12]);
        painter.setBrush(QBrush(palet[i%12],Qt::SolidPattern));
        double percent = model->data(model->index(i,2),Qt::DisplayRole).toDouble();
        painter.drawRect(drawRect.x() + 5 + 25*i, drawRect.height() - (drawRect.height() - 10) * percent / 100 ,
                         25, (drawRect.height() - 10) * percent / 100);
    }
}

void BarChart::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this->viewport());

    drawChart(painter);
    printLegend(painter);

}

