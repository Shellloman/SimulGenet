#include "loi.h"

Loi::Loi()
{
    Gauss = new double[400];
    QFile file("data/courbe-gauss-0-4.09.txt");
    file.open(QIODevice::ReadOnly);
    if (file.isOpen()) qDebug()<<"fichier bien ouvert";
    QTextStream in(&file);    // read the data serialized from the file
    double a = 0.0;
    unsigned int count = 0;
    while (!in.atEnd()){
        in >> a;
        if (count<400) Gauss[count] = a;
        ++count;
    }
    file.close();
}

void Loi::Confiance_Gauss(unsigned int n,QLineSeries *serie1,QLineSeries *serie2){
    if (serie1 == nullptr) serie1 = new QLineSeries();
    else {delete serie1;serie1 = new QLineSeries();}
    if (serie2 == nullptr) serie2 = new QLineSeries();
    else {delete serie2;serie2 = new QLineSeries();}
    for (double t=0.01;t<1.0;t += 0.01){
        serie1->append(t,-1.96*qPow(t*(1-t)/n,0.5)+t);
        serie2->append(t,+1.96*qPow(t*(1-t)/n,0.5)+t);
    }
    if (serie1 == nullptr) qDebug()<< "serie1 dans Loi nullptr";
}

