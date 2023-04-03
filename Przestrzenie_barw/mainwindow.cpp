#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QString>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Przestrzenie barw");

    resize(800, 600);

    szer = 512;
    wys = 512;
    poczX = 25;
    poczY = 25;

    img = new QImage(szer,wys,QImage::Format_RGB32);

    grupaRGB = new QGroupBox("RGB",this);
    grupaHSV = new QGroupBox("HSV",this);
    wyjscie = new QGroupBox(this);

    grupaRGB->setGeometry(QRect(550,poczY,200,200));
    grupaHSV->setGeometry(QRect(550,poczY+250,200,200));
    wyjscie->setGeometry(QRect(600,poczY+480,100,60));

    QHBoxLayout *boxLayout = new QHBoxLayout;
    QHBoxLayout *boxLayout2 = new QHBoxLayout;
    QHBoxLayout *boxLayout3 = new QHBoxLayout;

    QLabel *rb1 = new QLabel("R", this);
    rb1->setGeometry(QRect(595,poczY+210,30,20));
    rb1->setStyleSheet("color: rgb(255,0,0);"
                          "font-weight: 700; ");

    QLabel *rb2 = new QLabel("G", this);
    rb2->setGeometry(QRect(643,poczY+210,30,20));
    rb2->setStyleSheet("color: rgb(0,255,0);"
                          "font-weight: 700; ");

    QLabel *rb3 = new QLabel("B", this);
    rb3->setGeometry(QRect(695,poczY+210,30,20));
    rb3->setStyleSheet("color: rgb(0,0,255);"
                          "font-weight: 700; ");

    QLabel *label4 = new QLabel("H", this);
    label4->setGeometry(QRect(595,poczY+460,10,10));
    QLabel *label5 = new QLabel("S", this);
    label5->setGeometry(QRect(643,poczY+460,10,10));
    QLabel *label6 = new QLabel("V", this);
    label6->setGeometry(QRect(695,poczY+460,10,10));


    exitButton = new QPushButton("Wyjscie");

    R = new QSlider(Qt::Vertical,this);
    R->setMinimum(0);
    R->setMaximum(255);
    G = new QSlider(Qt::Vertical,this);
    G->setRange(0,255);
    G->setSingleStep(1);
    B = new QSlider(Qt::Vertical,this);
    B->setRange(0,255);

    H = new QSlider(Qt::Vertical,this);
    H->setRange(0,360);
    S = new QSlider(Qt::Vertical,this);
    S->setRange(0,100);
    V = new QSlider(Qt::Vertical,this);
    V->setRange(0,100);

    boxLayout->addWidget(R);
    boxLayout->addWidget(G);
    boxLayout->addWidget(B);

    boxLayout2->addWidget(H);
    boxLayout2->addWidget(S);
    boxLayout2->addWidget(V);

    boxLayout3->addWidget(exitButton);

    grupaRGB->setLayout(boxLayout);
    grupaHSV->setLayout(boxLayout2);
    wyjscie->setLayout(boxLayout3);

    connect(exitButton,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(R,SIGNAL(valueChanged(int)),this,SLOT(paintNoRed(int)));
    connect(G,SIGNAL(valueChanged(int)),this,SLOT(paintNoGreen(int)));
    connect(B,SIGNAL(valueChanged(int)),this,SLOT(paintNoBlue(int)));
    connect(H,SIGNAL(valueChanged(int)),this,SLOT(Hslider(int)));
    connect(S,SIGNAL(valueChanged(int)),this,SLOT(Sslider(int)));
    connect(V,SIGNAL(valueChanged(int)),this,SLOT(Vslider(int)));

}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    p.drawImage(poczX,poczY,*img);

}


void MainWindow::paintNoRed(int k){

    unsigned char *ptr;

        ptr = img->bits();

        int i,j;
        for(i=0; i<wys; i++)
        {
            for(j=0; j<szer; j++)
            {
                ptr[szer*4*i + 4*j]=j/2; // Skladowa BLUE
                ptr[szer*4*i + 4*j + 1] = i/2; // Skladowa GREEN
                ptr[szer*4*i + 4*j + 2] = k; // Skladowa RED

            }
        }
        update();
    }

void MainWindow::paintNoGreen(int k){

    unsigned char *ptr;

        ptr = img->bits();

        int i,j;
        for(i=0; i<wys; i++)
        {
            for(j=0; j<szer; j++)
            {
                ptr[szer*4*i + 4*j]=i/2; // Skladowa BLUE
                ptr[szer*4*i + 4*j + 1] = k; // Skladowa GREEN
                ptr[szer*4*i + 4*j + 2] = j/2; // Skladowa RED
            }
        }
        update();
    }

void MainWindow::paintNoBlue(int k){

    unsigned char *ptr;

        ptr = img->bits();

        int i,j;
        for(i=0; i<wys; i++)
        {
            for(j=0; j<szer; j++)
            {
                ptr[szer*4*i + 4*j]=k; // Skladowa BLUE
                ptr[szer*4*i + 4*j + 1] = j/2; // Skladowa GREEN
                ptr[szer*4*i + 4*j + 2] = i/2; // Skladowa RED
            }
        }
        update();
    }

void MainWindow::Hslider(int k){

    int i,j;
    double s = 100;

    for(i=0;i<wys;i++){
        double v = 100;
        for(j=0;j<szer;j++){
            convert(k,s,v,i,j);
            v = v-(100.0/szer);
        }
        s=s-(100.0/wys);
    }

    update();
}

void MainWindow::Sslider(int k){

    int i,j;

    double v = 100;
    for(i=0;i<wys;i++){
        double h = 360;
        for(j=0;j<szer;j++){
            convert(h,k,v,i,j);
            h=h-(360.0/wys);
        }
        v=v-(100.0/szer);
    }
    update();
}

void MainWindow::Vslider(int k){

    int i,j;
    double h = 360;

    for(i=0;i<wys;i++){
        double s = 100;
        for(j=0;j<szer;j++){
            convert(h,s,k,j,i);
            s=s-(100.0/szer);
        }
        h=h-(360.0/wys);
    }
    update();
}

void MainWindow::convert(float H, float S, float V, int i, int j){

    float v = V/100.0;
    float s = S/100.0;
    float h = H/60;
    float C = v*s;
    float X = C*(1 - abs(fmod(h, 2) - 1));
    float m = v-C;
    float r,g,b;

    if(H >= 0 && H < 60){
            r = C; g = X; b = 0;
        }
        else if(H >= 60 && H <= 120){
            r = X; g = C; b = 0;
        }
        else if(H > 120 && H <= 180){
            r = 0; g = C; b = X;
        }
        else if(H > 180 && H <= 240){
            r = 0; g = X; b = C;
        }
        else if(H > 240 && H <= 300){
            r = X; g = 0; b = C;
        }
        else if(H > 300 && H <= 360){
            r = C;g = 0;b = X;
        } else {
        r=0; g=0; b=0;
    }

    red = (r+m)*255;
    green = (g+m)*255;
    blue = (b+m)*255;

    unsigned char *ptr;
    ptr = img->bits();

    ptr[szer*4*i + 4*j]=blue; // Skladowa BLUE
    ptr[szer*4*i + 4*j + 1] = green; // Skladowa GREEN
    ptr[szer*4*i + 4*j + 2] = red; // Skladowa RED

}
