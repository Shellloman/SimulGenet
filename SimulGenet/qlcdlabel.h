#ifndef QLCDLABEL_H
#define QLCDLABEL_H

#include <QLabel>
#include <QString>

class QLCDLabel : public QLabel{
    Q_OBJECT
public:
    QLCDLabel(QString string,QWidget *parent,double d = 200.0);
    double Value()const;
public slots:
    void ChangeValue(double);
private:
    double value;
};

#endif // QLCDLABEL_H
