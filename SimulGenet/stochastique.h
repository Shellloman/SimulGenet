#ifndef STOCHASTIQUE_H
#define STOCHASTIQUE_H

#include <QRandomGenerator>
#include <QDateTime>
#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <QtMath>
using namespace QtCharts;

class Stochastique
{
public:
    Stochastique(unsigned int ,unsigned int ,double, double , double , double);
    void simulation();
    QLineSeries* graph();
private:
    void derive();
    void NewGeneration();
    void Q();
    QRandomGenerator generator;
    double q,p,sAA,sAa,saa;
    unsigned int gen,pop;
    QLineSeries* series;
    QChart* chart;
    QChartView * chartView;
};

#endif // STOCHASTIQUE_H
