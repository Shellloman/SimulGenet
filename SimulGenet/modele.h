#ifndef MODELE_H
#define MODELE_H

#include <QLineSeries>
#include <QChart>
#include <QChartView>
using namespace QtCharts;
class Modele
{
public:
    Modele(double p,unsigned int gen, double sAA, double sAa, double saa);
    ~Modele();
    void simulation();
    QChartView* graph();
private:
    void NewGeneration();
    double q,p,sAA,sAa,saa;
    unsigned int gen;
    QLineSeries* series;
    QChart* chart;
    QChartView * chartView;

};

#endif // MODELE_H
