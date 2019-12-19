#include "stochastique.h"

Stochastique::Stochastique(unsigned int popp,unsigned int genn,double pp,double sAAA,double sAaa,double saaa)
{
    gen = genn+1;p = pp; q = 1-p;
    pop = popp;sAA = sAAA; sAa = sAaa; saa = saaa;
    generator = QRandomGenerator(QDateTime::currentMSecsSinceEpoch() / 1000);
    series = new QLineSeries();
    chart = new QChart();
}
void Stochastique::derive(){
    double der =(generator.generateDouble()*2 - 1)*(1/qSqrt(pop*5));
    p += der;
    q = 1-p;
}
void Stochastique::NewGeneration(){
    double AA = p*p*(1-sAA),Aa = 2*p*q*(1-sAa), aa = q*q*(1-saa);
    double W = AA + Aa + aa;
    p = (AA + 0.5*Aa)/W;
}
void Stochastique::simulation(){
    for(unsigned int i;i<gen;i++){
        series->append(i,p);
        NewGeneration();
        if (p<1 && p>0) derive();
        if (p>1) p = 1;
        if (p<0) p = 0;
        Q();
    }
}

QChartView* Stochastique::graph(){
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Modèle théorique des variations de fréquence allélique");
    chart->axes(Qt::Vertical).first()->setRange(0,1);
    chart->legend()->setVisible(false);
    chart->setAnimationOptions(QChart::AllAnimations);
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}
void Stochastique::Q(){
    q = 1-p;
}
