#include "qdslider.h"

QDSlider::QDSlider(QWidget *parent,double pourcentage) : QSlider(Qt::Horizontal,parent) {
    pourcent = pourcentage;
     QObject::connect(this, SIGNAL(valueChanged(int)),
        this, SLOT(notifyValueChanged(int)));
}

void QDSlider::notifyValueChanged(int value) {
    double doubleValue = value / pourcent;
     emit doubleValueChanged(doubleValue);
}

