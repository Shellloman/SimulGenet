#include "qlcdlabel.h"

QLCDLabel::QLCDLabel(QString string,QWidget *parent,double d) : QLabel(string,parent)
{
    value = d;
}
void QLCDLabel::ChangeValue(double d){
    setText(QString::number(d, 'f', 2));
    value = d;
}
double QLCDLabel::Value() const{
    return value;
}

void QLCDLabel::ChangeName(QString _name){
    setText(_name);
}
