#include "mainwindow.h"
#include <QVBoxLayout>
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Rysowanie Okregu i Elipsy w Qt");
    resize(800,700);

    szer = 600;
    wys = 600;
    poczX = 25;
    poczY = 25;
    slot = 1;

    img = new QImage(szer,wys,QImage::Format_RGB32);
    img2 = new QImage(szer,wys,QImage::Format_RGB32);

    grupa = new QGroupBox("Sterowanie",this);

    grupa->setGeometry(QRect(poczX+szer+poczX,poczY,800-szer-2*poczX,poczY+100));

    // Tworzymy nowy layout pionowy
    QVBoxLayout *boxLayout = new QVBoxLayout;

    // Tworzymy 4 przyciski

    cleanButton = new QPushButton("Czysc");
    exitButton = new QPushButton("Wyjscie");
    slider1 = new QSlider(grupa);
    lcd = new QLCDNumber();



    // Dodajemy przyciski do layoutu
    boxLayout->addWidget(cleanButton);
    boxLayout->addWidget(exitButton);
    boxLayout->addWidget(slider1);
    boxLayout->addWidget(lcd);

    slider1->setGeometry(QRect(540, 300, 141, 22));
    slider1->setMinimum(3);
    slider1->setMaximum(100);
    slider1->setOrientation(Qt::Horizontal);
    lcd->display(3);

    grupa->setLayout(boxLayout);

    connect(exitButton,SIGNAL(clicked()),qApp,SLOT(quit()));

    connect(cleanButton,SIGNAL(clicked()),this,SLOT(slot_czysc()));

    connect(slider1,SIGNAL(valueChanged(int)),this,SLOT(changeValue()));
}

MainWindow::~MainWindow()
{
    delete img;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,*img);
}

void MainWindow::slot_czysc()
{

    czysc();
    update();
}

void MainWindow::changeValue(){
    lcd->display(slider1->value());       //slot changeValue do slidera
}

void MainWindow::czysc()
{
    unsigned char *ptr;

    ptr = img->bits();

    int i,j;

    for(i=0; i<wys; i++)
    {

        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j]=255;
            ptr[szer*4*i + 4*j + 1] = 255;
            ptr[szer*4*i + 4*j + 2] = 255;
        }
    }
}


void MainWindow::rysujKolo(int x0, int y0, int x1, int y1)
{
    int x = 0 , y;
    int color = 150;
    //unsigned char *ptr;
   // ptr = img->bits();
    double R = sqrt(pow(x1-x0, 2) + pow(y1-y0, 2));

    for(x=0; x<R/sqrt(2);x++){
        y = sqrt(pow(R, 2) - pow(x, 2));

        drawPixel(x+x0, y+y0, color,img);
        drawPixel(-x+x0, y+y0, color, img);
        drawPixel(x+x0, -y+y0, color, img);
        drawPixel(-x+x0, -y+y0, color, img);
        drawPixel(y+x0, x+y0, color, img);
        drawPixel(-y+x0, x+y0, color, img);
        drawPixel(y+x0, -x+y0, color, img);
        drawPixel(-y+x0, -x+y0, color, img);
    }


    update();
}

void MainWindow::rysujElipsa(int x0, int y0, int x1, int y1, int wierz)
{

   // unsigned char *ptr;
    //ptr = img->bits();

    float a=abs(x1-x0);
    float b=abs(y1-y0);
    float kat = 0;
    int x, y, xd, yd;

    for(int i=0; i<wierz; i++)
    {

        x = a*cos(kat);
        y = b*sin(kat);
        xd = a*cos(kat+(2*M_PI/wierz));
        yd = b*sin(kat+(2*M_PI/wierz));
        drawLine(x+x0,y+y0,xd+x0,yd+y0, 150,img);

        kat+=(2*M_PI/wierz);

    }

    update();
}

void MainWindow::drawPixel(int x, int y, int kolor, QImage *img)
{

    unsigned char *ptr;
    ptr = img->bits();


    if ((x>=0)&&(y>=0)&&(x<this->szer)&&(y<this->wys))
    {
        ptr[szer*4*y + 4*x] = kolor;
        ptr[szer*4*y + 4*x + 1] = kolor;
        ptr[szer*4*y + 4*x + 2] = kolor;
    }


    update();

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    MainWindow::copyImage(this->img2, this->img);
    this->x0 = event->position().x()-25;
    this->y0 = event->position().y()-25;


}

void MainWindow::mouseMoveEvent(QMouseEvent *event){

    MainWindow::copyImage(this->img, this->img2);
    int x = event->position().x()-poczX;
    int y = event->position().y()-poczY;
    lcd->display(slider1->value());
    if(event->buttons()==Qt::LeftButton) MainWindow::rysujKolo(this->x0, this->y0, x, y);
    else
    {
        MainWindow::rysujElipsa(this->x0, this->y0, x, y, slider1->value());

     }

    update();

}


void MainWindow::copyImage(QImage *img, QImage *img2){
    unsigned char *ptr, *ptr2;
    ptr = img->bits();
    ptr2 = img2->bits();

    int szerokosc = this->szer;
    int wysokosc = this->wys;

    for(int i = 0; i<szerokosc;i++){
        for(int j = 0; j<wysokosc;j++){

            ptr[szer*4*i + 4*j]=ptr2[szer*4*i + 4*j];
            ptr[szer*4*i + 4*j + 1] = ptr2[szer*4*i + 4*j + 1];
            ptr[szer*4*i + 4*j + 2] = ptr2[szer*4*i + 4*j + 2];

        }
    }
}

void MainWindow::drawLine(int sX,int sY,int eX,int eY,int color, QImage *img){

        float a=(eY-sY)/(float)(eX-sX);
        float b=sY-(a*sX);

        int x=0;
        int y=0;

        if(sX==eX){
            if(sY<eY){
               for (y=sY;y<eY;y++){
                   drawPixel(sX,y,color,img);
               }
            }
            else{
                for (y=sY;y>eY;y--){
                    drawPixel(sX,y,color,img);
                }
            }
        } else if(sY==eY){
            if(sX<eX){
               for (x=sX;x<eX;x++){
                   drawPixel(x,sY,color,img);
               }
            }
            else{
                for (x=sX;x>eX;x--){
                    drawPixel(x,sY,color,img);
                }
            }
        } else if(abs(sX-eX)<abs(sY-eY)){
             if(sY<eY){
                for (y=sY;y<eY;y++){
                    x=(y-b)/a;
                    drawPixel(x,y,color,img);
                }
             }
             else{
                 for (y=sY;y>eY;y--){
                     x=(y-b)/a;
                     drawPixel(x,y,color,img);
                 }
             }
        }
        else{
            if(sX<eX){
               for (x=sX;x<eX;x++){
                   y=a*x+b;
                   drawPixel(x,y,color,img);
               }
            }
            else{
                for (x=sX;x>eX;x--){
                    y=a*x+b;
                    drawPixel(x,y,color,img);
                }
            }
        }
}

double MainWindow::sinus(int x0, int y0, int x1, int y1){

    double c = sqrt(pow(x1-x0, 2) + pow(y1-y0, 2));
    double a = abs(y0-y1);
    double sinus = a/c;
    return sinus;


}

