#include "buttonsys.h"

ButtonSys::ButtonSys(QWidget *parent) : QPushButton(parent)
{
    QObject::connect(this,SIGNAL(clicked()),this, SLOT(SYS()));
    code = QString("");
}
void ButtonSys::SYS() {
     emit Emit_Code(code);
}
void ButtonSys::setCode(QString _code){
    code = _code;
}
