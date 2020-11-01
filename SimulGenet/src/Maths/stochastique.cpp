#include "stochastique.h"

Stochastique::Stochastique(unsigned int popp,unsigned int genn,double pp,double sAAA,double sAaa,double saaa)
{
    // initialisation des données membres
    gen = genn+1;p = pp; q = 1-p;
    pop = popp;sAA = sAAA; sAa = sAaa; saa = saaa;
    // initialise le générateur de nombres aléatoire à partir du temps actuel
    // permet une série différentes à chaque fois, nécéssaire pour du pseudo aléatoire
    generator = QRandomGenerator(QDateTime::currentMSecsSinceEpoch() / 1000);
    series = new QLineSeries();
    chart = new QChart();
}
void Stochastique::derive(){ // la dérive génétique va d'une amplitude 0 (pop infinie) à 1 (pop ~ 1 personnes)
    double der =(generator.generateDouble()*2 - 1)*(1/qSqrt(pop*5)); // fonction permettant de simuler la dérive
    p += der; // generator.generateDouble() génère un double entre 0 et 1
    q = 1-p;
}
void Stochastique::NewGeneration(){
    // calcul de la fréquence de la générations suivante
    // en suivant les lois de Hardy Weinberg
    // où (1-sAA) est le fitness du génotype en question
    double AA = p*p*(1-sAA),Aa = 2*p*q*(1-sAa), aa = q*q*(1-saa);
    double W = AA + Aa + aa;
    p = (AA + 0.5*Aa)/W;
}
void Stochastique::simulation(){
    for(unsigned int i;i<gen;i++){
        series->append(i,p);
        NewGeneration(); // calcul des fréquence de la nouvelle génération
        if (p<1 && p>0) derive(); // il n'y a de la dérive que si l'allèle n'est pas fixé
        if (p>1) p = 1; // c.a.d quand la frequence != 0 et != 1
        if (p<0) p = 0;
        Q(); // update de q
    }
}

QLineSeries* Stochastique::graph(){
    return series; // retrun la série construite
}
void Stochastique::Q(){
    q = 1-p; // update de q
}
