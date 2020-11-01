#ifndef QDSLIDER_H
#define QDSLIDER_H

#include <QApplication>
#include <QtGui>
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>

class QDSlider : public QSlider {
    Q_OBJECT
public:
    double pourcent;
    QDSlider(QWidget *parent = nullptr,double pourcentage = 100.0);

signals:
    void doubleValueChanged(double value);

public slots:
    void notifyValueChanged(int value);
};

#endif // QDSLIDER_H
