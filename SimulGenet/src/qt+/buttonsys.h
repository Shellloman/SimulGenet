#ifndef BUTTONSYS_H
#define BUTTONSYS_H

#include <QPushButton>
#include <QString>

using namespace std;

class ButtonSys : public QPushButton
{
    Q_OBJECT
public:
    ButtonSys(QWidget *parent = nullptr);
    void setCode(QString _code);
private:
    QString code;
public slots:
    void SYS();
signals :
void Emit_Code(QString _name);
};

#endif // BUTTONSYS_H
