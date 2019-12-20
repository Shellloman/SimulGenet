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
    Stochastique(unsigned int ,unsigned int ,double, double , double , double);// constructeur
    void simulation(); // création de la série
    QLineSeries* graph();// return la série créée
private:
    void derive();// simule la dérive génétique
    void NewGeneration();// calcul les fréquences de la génération n+1
    void Q();// update la valeur de q à partir de p
    QRandomGenerator generator;
    double q,p,sAA,sAa,saa;
    unsigned int gen,pop;
    QLineSeries* series;
    QChart* chart;
    QChartView * chartView;
};

#endif // STOCHASTIQUE_H
