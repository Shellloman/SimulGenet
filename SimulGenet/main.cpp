#include "MaFenetre.h"
#include <QTextCodec>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

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
    MaFenetre home;
    // l'affiche
    home.show();
    // fin du programme
    return app.exec();
}
