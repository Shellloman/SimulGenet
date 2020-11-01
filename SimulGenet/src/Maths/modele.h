#ifndef MODELE_H
#define MODELE_H

#include <QLineSeries>
#include <QChart>
#include <QChartView>
using namespace QtCharts;
class Modele
{
public:
    Modele(double p,unsigned int gen, double sAA, double sAa, double saa);// constructeur
    ~Modele(); // destructeur
    void simulation(); // création de la série
    QLineSeries* graph(); // return la série créée
private:
    void NewGeneration(); // calcul les fréquences de la génération n+1
    double q,p,sAA,sAa,saa;
    unsigned int gen;
    QLineSeries* series;
    QChart* chart;
    QChartView * chartView;

};

#endif // MODELE_H
