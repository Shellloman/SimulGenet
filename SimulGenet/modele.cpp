#include "modele.h"

Modele::Modele(double pp,unsigned int genn, double sAAA, double sAaa, double saaa)
{
    //initialisation des donnée membres
    p = pp;gen = genn+1; sAA = sAAA; sAa = sAaa; saa = saaa;
    q = 1-p;
    series = new QLineSeries();
}

Modele::~Modele(){
// il ne faut pas delete series
}

void Modele::simulation(){
    for(unsigned int i;i<gen;i++){ // calcul la fréquence de chaque génération
        series->append(i,p) ;// sur gen (int) génération
        NewGeneration();// calcul des fréquence de la nouvelle génération
    }
}

QLineSeries* Modele::graph(){
    return series; // return la série créée
}
void Modele::NewGeneration(){
    // calcul de la fréquence de la générations suivante
    // en suivant les lois de Hardy Weinberg
    // où (1-sAA) est le fitness du génotype en question
    double AA = p*p*(1-sAA),Aa = 2*p*q*(1-sAa), aa = q*q*(1-saa);
    double W = AA + Aa + aa;
    p = (AA + 0.5*Aa)/W;
    // on calcul seulement p et q est sont complémentaire
    q = 1- p;
}
