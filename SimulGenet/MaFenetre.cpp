#include "MaFenetre.h"

MaFenetre::MaFenetre() : QWidget()
{
    setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"/icon_adn.png"));
    // construction fenetre
    setGeometry(335,140,1250, 800);

    // construction texte
    titre = new QLabel(QString("Simulateur de fréquence allélique"),this);
    para = new QLabel(QString("Paramètres"),this);
    para->setGeometry(50,10,200,100);
    titre->setGeometry(600,10,500,100);

    // Construction du bouton
    b_model = new QPushButton("courbe théorique", this);
    b_model->setGeometry(50,90,300,36);
    b_stocha = new QPushButton("courbe stochastique", this);
    b_stocha->setGeometry(50,140,300,36);
    b_save= new QPushButton("sauvegarder courbe", this);
    b_save->setGeometry(50,190,300,36);
    b_vider = new QPushButton("réinitialiser graph",this);
    b_vider ->setGeometry(50,240,300,36);
    p_lcd = new QLCDLabel("0",this);
    p_lcd->setGeometry(180,300,50,35);
    p_slide = new QDSlider(this);
    p_slide->setGeometry(50,330,300,35);
    p_slide->setRange(0,100);
    p_lbl = new QLabel("fréquence :",this);
    p_lbl->setGeometry(50,300,100,35);
    gen_lcd = new QLCDLabel("200",this);
    gen_lcd->setGeometry(180,360,50,35);
    gen_slide = new QDSlider(this,0.1);
    gen_slide->setGeometry(50,390,300,35);
    gen_slide->setRange(0,100);
    gen_lbl = new QLabel("générations :",this);
    gen_lbl->setGeometry(50,360,120,35);
    pop_lcd = new QLCDLabel("200",this);
    pop_lcd->setGeometry(180,420,50,35);
    pop_slide = new QDSlider(this,0.1);
    pop_slide->setGeometry(50,450,300,35);
    pop_slide->setRange(0,100);
    pop_lbl = new QLabel("populations :",this);
    pop_lbl->setGeometry(50,420,120,35);
    fois10 = new QPushButton("x10", this);
    fois10->setGeometry(250,425,40,28);
    sAA_lcd = new QLCDLabel("0",this,0.0);
    sAA_lcd->setGeometry(180,480,50,35);
    sAA_slide = new QDSlider(this,100.0);
    sAA_slide->setGeometry(50,510,300,35);
    sAA_slide->setRange(0,50);
    sAA_lbl = new QLabel("séléction AA :",this);
    sAA_lbl->setGeometry(50,480,120,35);
    sAa_lcd = new QLCDLabel("0",this,0.0);
    sAa_lcd->setGeometry(180,540,50,35);
    sAa_slide = new QDSlider(this,100.0);
    sAa_slide->setGeometry(50,570,300,35);
    sAa_slide->setRange(0,50);
    sAa_lbl = new QLabel("séléction Aa :",this);
    sAa_lbl->setGeometry(50,540,120,35);
    saa_lcd = new QLCDLabel("0",this,0.0);
    saa_lcd->setGeometry(180,600,50,35);
    saa_slide = new QDSlider(this,100.0);
    saa_slide->setGeometry(50,630,300,35);
    saa_slide->setRange(0,50);
    saa_lbl = new QLabel("séléction aa :",this);
    saa_lbl->setGeometry(50,600,120,35);
    setstyle();
    fois10->setCheckable(true);
    fois10->setStyleSheet("QPushButton{background-color:grey;}QPushButton:checked{background-color:green;}");

    QObject::connect(sAA_slide, SIGNAL(doubleValueChanged(double)),sAA_lcd,SLOT(ChangeValue(double))) ;
    QObject::connect(sAa_slide, SIGNAL(doubleValueChanged(double)),sAa_lcd,SLOT(ChangeValue(double))) ;
    QObject::connect(saa_slide, SIGNAL(doubleValueChanged(double)),saa_lcd,SLOT(ChangeValue(double))) ;
    QObject::connect(pop_slide, SIGNAL(doubleValueChanged(double)),pop_lcd,SLOT(ChangeValue(double))) ;
    QObject::connect(p_slide, SIGNAL(doubleValueChanged(double)),p_lcd,SLOT(ChangeValue(double))) ;
    QObject::connect(gen_slide, SIGNAL(doubleValueChanged(double)),gen_lcd,SLOT(ChangeValue(double))) ;
    QObject::connect(b_save, SIGNAL(clicked()), this, SLOT(save()));
    QObject::connect(fois10, SIGNAL(clicked()), this, SLOT(flip()));
    QObject::connect(b_model, SIGNAL(clicked()), this, SLOT(courbe_theo()));
    QObject::connect(b_stocha, SIGNAL(clicked()), this, SLOT(courbe_stocha()));
    QObject::connect(b_vider, SIGNAL(clicked()), this, SLOT(vider_graph()));
    chart = nullptr;
    chartView = nullptr;
    layout = true;
    f10 = 1;
    nb_series = 0;
    boucle_series = 0;
    for (int i=0;i<3;i++) series[i]=new QLineSeries();
}
void MaFenetre::vider_graph(){
    for (int i=0;i<3;i++){delete series[i];series[i]=new QLineSeries();}
}
void MaFenetre::Graph(){
    if (chart == nullptr){ chart = new QChart();
    }else{delete chart;chart = new QChart();}
    chart->addSeries(serie);
    for (int i=0;i<nb_series;i++){
        chart->addSeries(ptr_tmp(i));
    }
    chart->createDefaultAxes();
    chart->setTitle("Modèle théorique des variations de fréquence allélique");
    chart->axes(Qt::Vertical).first()->setRange(0,1);
    chart->legend()->setVisible(false);
    chart->setAnimationOptions(QChart::AllAnimations);
    if (chartView == nullptr){ chartView = new QChartView(chart);
    }else{delete chartView;chartView = new QChartView(chart);}
    chartView->setRenderHint(QPainter::Antialiasing);
    setMainLayout();
    if (layout) layout = false;
}

QLineSeries* MaFenetre::ptr_tmp(int i){
    QLineSeries* tmp = new QLineSeries();
    for (int j=0;j<series[i]->count();j++) tmp->append(series[i]->at(j));
    return tmp;
}

void MaFenetre::setMainLayout(){
    if (layout){
        mainLayout = new QGridLayout;
        mainLayout->addWidget(chartView, 0, 0);
        mainLayout->setContentsMargins(400,70,20,20);
        setLayout(mainLayout);
    }else{
        mainLayout->addWidget(chartView, 0, 0);
    }
}

void MaFenetre::setstyle()
{
setStyleSheet("background-color: rgb(66,66,66);"
              "color : white;"
              "font-family : Bitstream Charter;"
              "font-size : 20px;");
}

void MaFenetre::confirm()
{
    int rep = QMessageBox::question(this, "Quitter", "Êtes vous sur de fermer le programme ?", QMessageBox::Yes | QMessageBox::No);
    if (rep == QMessageBox::Yes){
        qApp->quit();
    }
}

void MaFenetre::courbe_theo()
{
    Modele model(p_lcd->Value(),gen_lcd->Value(), sAA_lcd->Value(), sAa_lcd->Value(), saa_lcd->Value());
    model.simulation();
    serie = model.graph();
    Graph();
}
void MaFenetre::courbe_stocha()
{
    Stochastique stocha(pop_lcd->Value()*f10,gen_lcd->Value(),p_lcd->Value(), sAA_lcd->Value(), sAa_lcd->Value(), saa_lcd->Value());
    stocha.simulation();
    serie = stocha.graph();
    Graph();
}

void MaFenetre::save(){
    if (serie != nullptr){
        if (nb_series<3){
            for (int i=0;i<serie->count();i++) series[nb_series]->append(serie->at(i));
            nb_series ++;
        }else{
            delete series[boucle_series];
            series[boucle_series] = new QLineSeries();
            for (int i=0;i<serie->count();i++) series[boucle_series]->append(serie->at(i));
            boucle_series++;
            boucle_series = boucle_series % 3;
        }
    }
}

void MaFenetre::flip(){
    if (f10 ==1){
        f10 = 10;
    }else{
        f10 =1;
    }
    qDebug()<<f10;
}
