#ifndef MAFENETRE_H
#define MAFENETRE_H

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
#include "qdslider.h"
#include "qlcdlabel.h"
#include "modele.h"
#include "stochastique.h"

class MaFenetre : public QWidget // On hérite de QWidget (IMPORTANT)
{
    Q_OBJECT

    public:
    MaFenetre();

    public slots:
    void confirm();
    void courbe_theo();
    void courbe_stocha();
    void setstyle();
    void setMainLayout();
    void flip();

    private:
    int f10;
    QPushButton *b_model,*b_quitter,*b_stocha,*fois10;
    QLabel *titre ,*image,*para;
    QPixmap *img;
    QChartView *chartView;
    QGridLayout* mainLayout,*sublayout,*subplayout;
    QLCDLabel *p_lcd,*gen_lcd,*pop_lcd,*sAA_lcd,*sAa_lcd,*saa_lcd;
    QLabel *p_lbl,*gen_lbl,*pop_lbl,*sAA_lbl,*sAa_lbl,*saa_lbl;
    QDSlider *p_slide,*gen_slide,*pop_slide,*sAA_slide,*sAa_slide,*saa_slide;
    bool layout;

};

#endif // MAFENETRE_H
