#ifndef PIECHART_H
#define PIECHART_H

#include "myview.h"

class PieChart : public MyView
{
    Q_OBJECT
public:
    PieChart(QWidget *parent);
    virtual ~PieChart() = default;

private:

    void drawChart(QPainter &painter) override;
};

#endif // PIECHART_H
