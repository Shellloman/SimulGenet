#include "OVraisemblance.h"

OVraisemblance::OVraisemblance()
{
    setGeometry(335,140,1250, 800);
    serieS = nullptr; serie1 = nullptr; serie2 = nullptr;
    serieL = nullptr; serie3 = nullptr; serie4 = nullptr; serie5 = nullptr;
    chart = nullptr;chart2 = nullptr;
    chartView = nullptr;chartView2 = nullptr;
}

double OVraisemblance::fact(unsigned int i){
    unsigned long long _fact = 1;
    for(unsigned int k = 2; k<=i;++k){
        _fact *=k;
    }
    return _fact;
}

double OVraisemblance::facto(unsigned int i,unsigned int j){
    double _fact = 1;
    for(unsigned int k = i; k<=j;++k){
        _fact *=k;
    }
    return _fact;
}

double OVraisemblance::binome(unsigned int k, unsigned int n, unsigned int p){
   double tmp  = 1;
    if (k > n) tmp = 0;
    else if (k==1) tmp = n;
    else if(k==0) tmp = 1;
    else if (k==n) tmp = 1;
    else{
    switch(p){
        case 0 :
            for (unsigned int i=1;i<=k;++i){
                tmp = (n+1 - i)*tmp/(double)i;
            }
            break;
        case 1 :
            if(k>n-k) tmp = facto(k+1,n)/fact(n-k);
            else tmp = facto(n-k+1,n)/fact(k);
            break;
        case 2 :
            tmp = fact(n)/(fact(k)*fact(n-k));
            break;
        default :
            tmp = 0;
        }
    }
    return tmp;
}

double OVraisemblance::HyperG(unsigned int hm,unsigned int j,unsigned k){
    double tmp;
    if(hm <= k) tmp = 0;
    else tmp = binome(j,hm)*binome(k-j,100-hm)/(double)binome(k,100);
    return tmp;
}
void OVraisemblance::graph(){
    serieL = new QLineSeries();
    serieS = new QSplineSeries();
    double dmax = 0.0,dtmp = 0.0;
    unsigned int indice= 0;
    for(unsigned int i = 1;i<=100;++i){
        dtmp = HyperG(i,4,5);
        serieS->append(i,dtmp);
        if(dtmp > dmax){ dmax = dtmp; indice = i;}
    }
    serieL->append(indice,0);
    serieL->append(indice,dmax);

    chart = new QChart();
    chart2 = new QChart();

    chart->addSeries(serieS);
    chart->addSeries(serieL);

    Confiance_Gauss(100,0.8);
    if (serie1 == nullptr) qDebug()<<"serie1 vide pas ok";
    serie3 = new QLineSeries();
    serie3->setPen(Qt::DashLine);
    serie4->setPen(Qt::DotLine);
    serie5->setPen(Qt::DotLine);
    serie3->append(0,0.8);serie3->append(1,0.8);
    if (serie1 == nullptr) qDebug()<<"serie1 vide merde";
    chart2->addSeries(serie1);
    chart2->addSeries(serie2);
    chart2->addSeries(serie3);
    chart2->addSeries(serie4);
    chart2->addSeries(serie5);

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0,100);
    chart->axes(Qt::Vertical).first()->setRange(0,1);
    chart2->createDefaultAxes();
    chart2->axes(Qt::Horizontal).first()->setRange(0,1);
    chart2->axes(Qt::Vertical).first()->setRange(0,1);

    chartView = new QChartView(chart);
    chartView2 = new QChartView(chart2);
    mainLayout = new QGridLayout;
    mainLayout->addWidget(chartView, 0, 0);
    mainLayout->addWidget(chartView2, 1, 0);
    mainLayout->setContentsMargins(400,70,20,20);
    setLayout(mainLayout);
}
void OVraisemblance::test(){
    qDebug()<<"debut test";
    qDebug()<<binome(50,100);
    qDebug()<<binome(50,100,0);
    qDebug()<<binome(50,100,1);

}

void OVraisemblance::Confiance_Gauss(unsigned int n,double p){
    if (serie1 == nullptr) serie1 = new QLineSeries();
    else {delete serie1;serie1 = new QLineSeries();}
    if (serie2 == nullptr) serie2 = new QLineSeries();
    else {delete serie2;serie2 = new QLineSeries();}
    if (serie4 == nullptr) serie4 = new QLineSeries();
    else {delete serie4;serie4 = new QLineSeries();}
    if (serie5 == nullptr) serie5 = new QLineSeries();
    else {delete serie5;serie5 = new QLineSeries();}
    bool s1 = true; bool s2 = true;
    for (double t=0.01;t<1.0;t += 0.01){
        serie1->append(t,-1.96*qPow(t*(1-t)/n,0.5)+t);
        if (serie1->at(t*100-1).y()>=p && s1){s1 = false; serie4->append(t,0); serie4->append(t,p);}
        serie2->append(t,+1.96*qPow(t*(1-t)/n,0.5)+t);
        if (serie2->at(t*100-1).y()>=p && s2){s2 = false; serie5->append(t,0);serie5->append(t,p);}
    }
    if (serie1 != nullptr) qDebug()<< "serie1 ok";
}

