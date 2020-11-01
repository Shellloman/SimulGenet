#include <QTextCodec>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QTabWidget>
#include "Onglets/OFrequence.h"
#include "Onglets/OVraisemblance.h"
#include "Maths/loi.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // utilisation de "utf-8"
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    // passe Qt en francais par defaut
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);
    // creer la feneter principal
    QTabWidget Onglets;
    OFrequence freq(&Onglets);
    OVraisemblance vr;
    //vr.test();
    vr.graph();
    // l'affiche
    Onglets.setGeometry(335,140,1300, 850);
    Onglets.addTab(&freq,"Fréquence génétique");
    Onglets.addTab(&vr,"test Vraisemblance");
    Onglets.setStyleSheet("background-color: rgb(66,66,66);"
                          "color : white;"
                          "font-family : Bitstream Charter;"
                          "font-size : 20px;");
    Onglets.show();
    //home.show();
    // fin du programme
    return app.exec();
}
