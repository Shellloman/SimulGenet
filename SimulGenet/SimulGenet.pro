QT += widgets
QT += charts

SOURCES += \
    src/Maths/loi.cpp \
    src/Onglets/OFrequence.cpp \
    src/Onglets/OVraisemblance.cpp \
    src/qt+/buttonsys.cpp \
    src/main.cpp \
    src/Maths/modele.cpp \
    src/qt+/qdslider.cpp \
    src/qt+/qlcdlabel.cpp \
    src/Maths/stochastique.cpp \

HEADERS += \
    src/Maths/loi.h \
    src/Onglets/OFrequence.h \
    src/Onglets/OVraisemblance.h \
    src/qt+/buttonsys.h \
    src/Maths/modele.h \
    src/qt+/qdslider.h \
    src/qt+/qlcdlabel.h \
    src/Maths/stochastique.h \

DISTFILES += \
    data/courbe-gauss-0-4.09.txt
