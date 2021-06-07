#ifndef BARCHART_H
#define BARCHART_H

#include "myview.h"

class BarChart : public MyView
{
    Q_OBJECT
public:
    BarChart(QWidget *parent);
    virtual ~BarChart() = default;

private:

    void drawChart(QPainter &painter) override;
};

#endif // BARCHART_H
