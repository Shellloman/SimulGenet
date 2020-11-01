#ifndef OINTERVALLEDC_H
#define OINTERVALLEDC_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDebug>
#include <QLCDNumber>
#include <QSlider>
#include <QLineSeries>
#include <QSplineSeries>
#include <QChart>
#include <QChartView>
#include "../qt+/qdslider.h"
#include "../qt+/qlcdlabel.h"
#include "../Maths/loi.h"

using namespace QtCharts;

class OVraisemblance : public QWidget // On hérite de QWidget (IMPORTANT)
{
    Q_OBJECT

public:
    OVraisemblance();
    void Confiance_Gauss(unsigned int n,double p);
    double fact(unsigned int i);
    double facto(unsigned int i,unsigned int j);
    double binome(unsigned int k,unsigned int n,unsigned int p = 0);
    double HyperG(unsigned int hm,unsigned int j,unsigned k);
    void graph();
    void test();
private:
    QSplineSeries *serieS;
    QLineSeries *serieL,*serie1,*serie2,*serie3,*serie4,*serie5;
    QChart *chart,*chart2;
    QChartView *chartView,*chartView2;
    QGridLayout* mainLayout;
};

#endif // OINTERVALLEDC_H
