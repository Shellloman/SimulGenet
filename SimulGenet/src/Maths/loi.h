#ifndef LOI_H
#define LOI_H

#include <QString>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QDebug>
#include <QLineSeries>
#include <QtMath>

using namespace QtCharts;

class Loi
{
public:
    Loi();
    void Confiance_Gauss(unsigned int n,QLineSeries* serie1,QLineSeries* serie2);
private:
    double* Gauss;
};

#endif // LOI_H
