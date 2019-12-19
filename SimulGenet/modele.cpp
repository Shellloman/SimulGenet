#include "modele.h"

Modele::Modele(double pp,unsigned int genn, double sAAA, double sAaa, double saaa)
{
    p = pp;gen = genn+1; sAA = sAAA; sAa = sAaa; saa = saaa;
    q = 1-p;
    series = new QLineSeries();
    chart = new QChart();
}

Modele::~Modele(){

}

void Modele::simulation(){
    for(unsigned int i;i<gen;i++){
        series->append(i,p);
        NewGeneration();
    }
}

QChartView* Modele::graph(){
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
void Modele::NewGeneration(){
    double AA = p*p*(1-sAA),Aa = 2*p*q*(1-sAa), aa = q*q*(1-saa);
    double W = AA + Aa + aa;
    p = (AA + 0.5*Aa)/W;
    q = 1- p;
}