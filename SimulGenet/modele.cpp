#include "modele.h"

Modele::Modele(double pp,unsigned int genn, double sAAA, double sAaa, double saaa)
{
    p = pp;gen = genn+1; sAA = sAAA; sAa = sAaa; saa = saaa;
    q = 1-p;
    series = new QLineSeries();
}

Modele::~Modele(){

}

void Modele::simulation(){
    for(unsigned int i;i<gen;i++){
        series->append(i,p);
        NewGeneration();
    }
}

QLineSeries* Modele::graph(){
    return series;
}
void Modele::NewGeneration(){
    double AA = p*p*(1-sAA),Aa = 2*p*q*(1-sAa), aa = q*q*(1-saa);
    double W = AA + Aa + aa;
    p = (AA + 0.5*Aa)/W;
    q = 1- p;
}
