#include "OFrequence.h"

OFrequence::OFrequence(QTabWidget *Main) : QWidget()
{
    prin = Main;
    // affichage de l'icon
    setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"data/icon_adn.png"));
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
    // Construction des Slides
    // fréquence de p
    p_lcd = new QLCDLabel("0",this);
    p_lcd->setGeometry(180,300,50,35);
    p_slide = new QDSlider(this);
    p_slide->setGeometry(50,330,300,35);
    p_slide->setRange(0,100);
    p_lbl = new QLabel("fréquence :",this);
    p_lbl->setGeometry(50,300,100,35);
    //générations
    gen_lcd = new QLCDLabel("200",this);
    gen_lcd->setGeometry(180,360,50,35);
    gen_slide = new QDSlider(this,0.1);
    gen_slide->setGeometry(50,390,300,35);
    gen_slide->setRange(0,100);
    gen_lbl = new QLabel("générations :",this);
    gen_lbl->setGeometry(50,360,120,35);
    //populations
    pop_lcd = new QLCDLabel("200",this);
    pop_lcd->setGeometry(180,420,50,35);
    pop_slide = new QDSlider(this,0.1);
    pop_slide->setGeometry(50,450,300,35);
    pop_slide->setRange(0,100);
    pop_lbl = new QLabel("populations :",this);
    pop_lbl->setGeometry(50,420,120,35);
    //bouton pour multiplier la pop par 10
    fois10 = new QPushButton("x10", this);
    fois10->setGeometry(250,425,40,28);
    // coefficient de selection du génotype AA
    sAA_lcd = new QLCDLabel("0",this,0.0);
    sAA_lcd->setGeometry(180,480,50,35);
    sAA_slide = new QDSlider(this,100.0);
    sAA_slide->setGeometry(50,510,300,35);
    sAA_slide->setRange(0,50);
    sAA_lbl = new QLabel("séléction AA :",this);
    sAA_lbl->setGeometry(50,480,120,35);
    // coefficient de selection du génotype Aa
    sAa_lcd = new QLCDLabel("0",this,0.0);
    sAa_lcd->setGeometry(180,540,50,35);
    sAa_slide = new QDSlider(this,100.0);
    sAa_slide->setGeometry(50,570,300,35);
    sAa_slide->setRange(0,50);
    sAa_lbl = new QLabel("séléction Aa :",this);
    sAa_lbl->setGeometry(50,540,120,35);
    // coefficient de selection du génotype aa
    saa_lcd = new QLCDLabel("0",this,0.0);
    saa_lcd->setGeometry(180,600,50,35);
    saa_slide = new QDSlider(this,100.0);
    saa_slide->setGeometry(50,630,300,35);
    saa_slide->setRange(0,50);
    saa_lbl = new QLabel("séléction aa :",this);
    saa_lbl->setGeometry(50,600,120,35);
    // le nom parle de lui même
    //setstyle();
    // permet le changement de couleur si activé ou non
    fois10->setCheckable(true);
    fois10->setStyleSheet("QPushButton{background-color:grey;}QPushButton:checked{background-color:green;}");

    //test
    test = new ButtonSys(this);
    test->setCode(QString("A35"));
    test->setText(QString("ButtonSys test"));
    test->setGeometry(50,700,200,50);

    QObject::connect(test, SIGNAL(clicked()), this, SLOT(NewWidget()));
    //fin test
    // connexion de chaque bouton avec un slot
    QObject::connect(b_save, SIGNAL(clicked()), this, SLOT(save()));
    QObject::connect(fois10, SIGNAL(clicked()), this, SLOT(flip()));
    QObject::connect(b_model, SIGNAL(clicked()), this, SLOT(courbe_theo()));
    QObject::connect(b_stocha, SIGNAL(clicked()), this, SLOT(courbe_stocha()));
    QObject::connect(b_vider, SIGNAL(clicked()), this, SLOT(vider_graph()));
    // connexion de chaque slide avec un QLCDLabel pour afficher le double
    QObject::connect(sAA_slide, SIGNAL(doubleValueChanged(double)),sAA_lcd,SLOT(ChangeValue(double))) ;
    QObject::connect(sAa_slide, SIGNAL(doubleValueChanged(double)),sAa_lcd,SLOT(ChangeValue(double))) ;
    QObject::connect(saa_slide, SIGNAL(doubleValueChanged(double)),saa_lcd,SLOT(ChangeValue(double))) ;
    QObject::connect(pop_slide, SIGNAL(doubleValueChanged(double)),pop_lcd,SLOT(ChangeValue(double))) ;
    QObject::connect(p_slide, SIGNAL(doubleValueChanged(double)),p_lcd,SLOT(ChangeValue(double))) ;
    QObject::connect(gen_slide, SIGNAL(doubleValueChanged(double)),gen_lcd,SLOT(ChangeValue(double))) ;
    //initialisation des parametres membres
    chart = nullptr;
    chartView = nullptr;
    layout = true;
    f10 = 1;
    nb_series = 0;
    boucle_series = 0;
    // initialisation du stockages de series à ajouter au graph
    for (int i=0;i<3;i++) series[i]=new QLineSeries();
}
void OFrequence::vider_graph(){ // vide les series stocker pour ne plus les afficher
    for (int i=0;i<3;i++){delete series[i];series[i]=new QLineSeries();}
}
void OFrequence::NewWidget(){
    QWidget *T = new QWidget;
    T->setGeometry(335,140,1250, 800);
    prin->addTab(T,"new Tab");
    qDebug()<<"prout add";
}
void OFrequence::Graph(){ // afficher les series stocker et/ou recuperer par les fonctions
    if (chart == nullptr){ chart = new QChart(); // initialise pour la premier fois chart
    }else{delete chart;chart = new QChart();}// si déjà existant on delete
    chart->addSeries(serie);
    for (int i=0;i<nb_series;i++){ // si une serie stockée on l'ajoute
        chart->addSeries(ptr_tmp(i)); // créer un ptr temporaire car le delete chart et chartView delete le ptr
    }
    chart->createDefaultAxes();
    chart->setTitle("Modèle théorique des variations de fréquence allélique");
    chart->axes(Qt::Vertical).first()->setRange(0,1);
    chart->legend()->setVisible(false);
    chart->setAnimationOptions(QChart::AllAnimations);
    if (chartView == nullptr){ chartView = new QChartView(chart);// initialise pour la premier fois chartView
    }else{delete chartView;chartView = new QChartView(chart);}// si déjà existant on delete
    chartView->setRenderHint(QPainter::Antialiasing);
    setMainLayout(); // place le graph sur la fenetre
    if (layout) layout = false; //utilisé pour le setMainLayout
}

QLineSeries* OFrequence::ptr_tmp(int i){ // créer un ptr temporaire car le delete chart ..
    QLineSeries* tmp = new QLineSeries();// et chartView delete aussi les series
    for (int j=0;j<series[i]->count();j++) tmp->append(series[i]->at(j));
    return tmp;
}

void OFrequence::setMainLayout(){
    if (layout){// la premiere fois que la fonction est executer layout ==true
        mainLayout = new QGridLayout;
        mainLayout->addWidget(chartView, 0, 0);
        mainLayout->setContentsMargins(400,70,20,20);
        setLayout(mainLayout);
    }else{ // les autres fois uniquement besoin d'update chartView
        mainLayout->addWidget(chartView, 0, 0);
    }
}

void OFrequence::setstyle() // style de la fenetre
{
setStyleSheet("background-color: rgb(66,66,66);"
              "color : white;"
              "font-family : Bitstream Charter;"
              "font-size : 20px;");
}

void OFrequence::confirm() // fonction pour l'instant inutiliser qui demande si..
{                        // on est sur de vouloir quitter
    int rep = QMessageBox::question(this, "Quitter", "Êtes vous sur de fermer le programme ?", QMessageBox::Yes | QMessageBox::No);
    if (rep == QMessageBox::Yes){
        qApp->quit();
    }
}

void OFrequence::courbe_theo()// création d'une courbe théorique
{
    Modele model(p_lcd->Value(),gen_lcd->Value(), sAA_lcd->Value(), sAa_lcd->Value(), saa_lcd->Value());
    model.simulation(); // calcul des frequences par generation
    serie = model.graph(); // récupere le ptr de la serie créer
    Graph(); // affiche le graph créer
}
void OFrequence::courbe_stocha()// création d'une courbe "réel" basée sur un model stochastique
{
    Stochastique stocha(pop_lcd->Value()*f10,gen_lcd->Value(),p_lcd->Value(), sAA_lcd->Value(), sAa_lcd->Value(), saa_lcd->Value());
    stocha.simulation(); // calcul des frequences par generation
    serie = stocha.graph();// récupere le ptr de la serie créer
    Graph(); // affiche le graph créer
}

void OFrequence::save(){ // stock le serie actuellement afficher pour la réafficher la prochaine fois
    if (serie != nullptr){ // ne fait rien si aucune serie créer
        if (nb_series<3){ // on ne stock que 3 series max pour 4 afficher au total
            for (int i=0;i<serie->count();i++) series[nb_series]->append(serie->at(i));
            nb_series ++;
        }else{ // si 3 series sont dejà stockée on ecrase la suivante
            delete series[boucle_series];
            series[boucle_series] = new QLineSeries();
            for (int i=0;i<serie->count();i++) series[boucle_series]->append(serie->at(i));
            boucle_series++;
            boucle_series = boucle_series % 3;
        }
    }
}

void OFrequence::flip(){// permet de multiplier la pop par 10 ou 1 selon l'état du bouton
    if (f10 ==1){
        f10 = 10;
    }else{
        f10 =1;
    }
    qDebug()<<f10;
}
