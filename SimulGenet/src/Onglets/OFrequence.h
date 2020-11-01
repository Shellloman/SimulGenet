#ifndef OFREQ_H
#define OFREQ_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDebug>
#include <QLCDNumber>
#include <QSlider>
#include <QTabWidget>
#include "../qt+/qdslider.h"
#include "../qt+/qlcdlabel.h"
#include "../Maths/modele.h"
#include "../Maths/stochastique.h"
#include "../qt+/buttonsys.h"

class OFrequence : public QWidget // On hérite de QWidget (IMPORTANT)
{
    Q_OBJECT

    public:
    OFrequence(QTabWidget *Main);// constructeur
    void Graph(); // construit le graph
    QLineSeries* ptr_tmp(int);// copy un ptr
    void setMainLayout();// affiche le graph
    void setstyle();//donne le style de la page

    public slots:
    void confirm();// demande si on veut vraiment quitter l'application
    void courbe_theo();//créer un objet de la class model
    void courbe_stocha();//créer un objet de la class stochastique
    void flip();// pass la pop du coeff 1 à 10
    void save();// stock la serie actuellment aficher pour la reafficher plus tard
    void vider_graph(); // delete les series stockée
    void NewWidget();

    private:
    QTabWidget *prin;
    int f10,nb_series,boucle_series;
    QPushButton *b_model,*b_save,*b_stocha,*fois10,*b_vider;
    QLabel *titre ,*image,*para;
    QPixmap *img;
    QLineSeries *serie;
    QLineSeries *series[3];
    QChart *chart;
    QChartView *chartView;
    QGridLayout* mainLayout,*sublayout,*subplayout;
    QLCDLabel *p_lcd,*gen_lcd,*pop_lcd,*sAA_lcd,*sAa_lcd,*saa_lcd;
    QLabel *p_lbl,*gen_lbl,*pop_lbl,*sAA_lbl,*sAa_lbl,*saa_lbl;
    QDSlider *p_slide,*gen_slide,*pop_slide,*sAA_slide,*sAa_slide,*saa_slide;
    bool layout;
    //test
    ButtonSys *test;

};

#endif // OFREQ_H
