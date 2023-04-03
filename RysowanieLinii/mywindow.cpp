// Dolaczamy plik naglowkowy naszej klasy MyWindow
#include "mywindow.h"

// Dolaczamy plik naglowkowy komponentu layoutu pionowego
// Komponent ten sluzy do rozmieszczania elementow GUI w oknie
#include <QVBoxLayout>
#include <math.h>

// Definicja konstruktora, wywolujemy najpierw
// konstruktor klasy nadrzednej
MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    // Ustawiamy tytul okna
    setWindowTitle("Rysowanie pikseli w Qt");

    //Zmieniamy rozmiar okna
    resize(800,700);

    // Ustawiamy wymiary obrazka i wspolrzedne jego
    // lewego gornego naroznika ramki
    // (wzgledem glownego okna)
    szer = 600;
    wys = 600;
    poczX = 25;
    poczY = 25;

    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
    // (0xffRRGGBB).
    img = new QImage(szer,wys,QImage::Format_RGB32);
    img2 = new QImage(szer,wys,QImage::Format_RGB32);

    // Tworzymy grupe elementow
    // Drugi parametr konstruktora to rodzic elementu
    grupa = new QGroupBox("Sterowanie",this);

    // Ustawiamy wymiary tej grupy i jej polozenie wzgledem glownego okna
    grupa->setGeometry(QRect(poczX+szer+poczX,poczY,800-szer-2*poczX,poczY+100));

    // Tworzymy nowy layout pionowy
    QVBoxLayout *boxLayout = new QVBoxLayout;

    // Tworzymy 4 przyciski
    draw1Button = new QPushButton("Rysuj 1");
    draw2Button = new QPushButton("Rysuj 2");
    cleanButton = new QPushButton("Czysc");
    exitButton = new QPushButton("Wyjscie");

    // Dodajemy przyciski do layoutu
    boxLayout->addWidget(draw1Button);
    boxLayout->addWidget(draw2Button);
    boxLayout->addWidget(cleanButton);
    boxLayout->addWidget(exitButton);

    // Dodajemy layout do grupy
    grupa->setLayout(boxLayout);


    // Laczymy sygnal emitowany po nacisnieciu przycisku "Wyjscie"
    // ze slotem quit(). qApp to globalny wskaznik reprezentujacy aplikacje
    connect(exitButton,SIGNAL(clicked()),qApp,SLOT(quit()));

    // Laczymy sygnaly emitowane po nacisnieciu przyciskow z odpowiednimi slotami
    connect(cleanButton,SIGNAL(clicked()),this,SLOT(slot_czysc()));

    connect(draw1Button,SIGNAL(clicked()),this,SLOT(slot_rysuj1()));

    connect(draw2Button,SIGNAL(clicked()),this,SLOT(slot_rysuj2()));


}

// Definicja destruktora
MyWindow::~MyWindow()
{
    delete img;
}


// Funkcja "odmalowujaca" komponent
void MyWindow::paintEvent(QPaintEvent*)
{
    // Obiekt klasy QPainter pozwala nam rysowac na komponentach
    QPainter p(this);

    // Rysuje obrazek "img" w punkcie (poczX,poczY)
    // (tu bedzie lewy gorny naroznik)
    p.drawImage(poczX,poczY,*img);
}


// Funkcja (slot) wywolywana po nacisnieciu przycisku "Czysc" (cleanButton)
void MyWindow::slot_czysc()
{
    // Funkcja czysci (zamalowuje na bialo) obszar rysowania
    // definicja znajduje sie ponizej
    czysc();

    // Funkcja "update()" powoduje ponowne "namalowanie" calego komponentu
    // Wywoluje funkcje "paintEvent"
    update();
}


// Funkcja (slot) wywolywana po nacisnieciu przycisku "Rysuj 1" (draw1Button)
void MyWindow::slot_rysuj1()
{
    rysuj1();
    update();
}

// Funkcja (slot) wywolywana po nacisnieciu przycisku "Rysuj 2" (draw2Button)
void MyWindow::slot_rysuj2()
{
    rysuj2();
    update();
}

// Funkcja powoduje wyczyszczenie (zamalowanie na bialo)
// obszaru rysowania
void MyWindow::czysc()
{
    // Wskaznik za pomoca, ktorego bedziemy modyfikowac obraz
    unsigned char *ptr;

    // Funkcja "bits()" zwraca wskaznik do pierwszego piksela danych
    ptr = img->bits();

    int i,j;

    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        // Przechodzimy po pikselach danego wiersza
        // W kazdym wierszu jest "szer" pikseli (tzn. 4 * "szer" bajtow)
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j]=255; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 255; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 255; // Skladowa RED
        }
    }
}


// Funkcja powoduje zamalowanie obszaru rysowania pewnym wzorem
void MyWindow::rysuj1()
{
        unsigned char *ptr;
        ptr = img->bits();
        int szer = img->width();
        int wys = img->height();

        int i,j;
        for(i=0;i<wys;i++)
        {
                for(j=0;j<szer ;j++)
                {
                        ptr[szer*4*i + 4*j]=i;
                        ptr[szer*4*i + 4*j + 1] = j;
                        ptr[szer*4*i + 4*j + 2] = i*j;
                }
        }
}

// Funkcja powoduje zamalowanie obszaru rysowania pewnym wzorem
void MyWindow::rysuj2()
{
        unsigned char *ptr;
        ptr = img->bits();
        int szer = img->width();
        int wys = img->height();

        int i,j;
        for(i=0;i<wys;i++)
        {
                for(j=0;j<szer ;j++)
                {
                        ptr[szer*4*i + 4*j]=i;
                        ptr[szer*4*i + 4*j + 1] = j;
                        ptr[szer*4*i + 4*j + 2] = i+j;
                }
        }
}

double MyWindow::sinus(int x0, int y0, int x1, int y1){

    double c = sqrt(pow(x1-x0, 2) + pow(y1-y0, 2));
    double a = abs(y0-y1);
    double sinus = a/c;
    return sinus;


}

void MyWindow::drawLine(int x0, int y0, int x1, int y1){
    int kolor = 200;
    int x , y;
    unsigned char *ptr = img->bits();
    float a=(float)(y1-y0)/(x1-x0);
    float b=y0-(a*x0);

    if(x1>this->szer){
            x1=this->szer;
        }
        else if(x1<0){
            x1=0;
        }

        if(y1>this->wys){
            y1=this->wys;
        }
        else if(y1<0){
            y1=0;
        }

    if(MyWindow::sinus(x0, y0, x1, y1) < sqrt(2)/2 ){
        if(x0 < x1){
            for(int i = x0; i < x1; i++){
                y=i*a+b;
                if(y<this->szer && y>=0 && i<this->wys && i>=0){
                ptr[szer*4*y + 4*i]=kolor;
                ptr[szer*4*y + 4*i + 1] = kolor;
                ptr[szer*4*y + 4*i + 2] = kolor;
            } else break;
           }
        }
            else{
                for(int i = x0; i > x1; i--){
                    y=i*a+b;
                    if(y<this->szer && y>=0 && i<this->wys && i>=0){
                    ptr[szer*4*y+ 4*i]=kolor;
                    ptr[szer*4*y + 4*i + 1] = kolor;
                    ptr[szer*4*y + 4*i + 2] = kolor;
                  } else break;
            }

        }
    } else if(x0 == x1){
   //     int z = abs(y0-y1);
        if(y0 < y1){
            for(int i = y0; i < y1;i++){
                if(x0<this->szer && x0>=0 && i<this->wys && i>=0){
                ptr[szer*4*i + 4*x0]=kolor;
                ptr[szer*4*i + 4*x0 + 1] = kolor;
                ptr[szer*4*i + 4*x0 + 2] = kolor;
                } else break;
        }
    } else {
            for(int i = y0; i > y1;i--){
                if(x0<this->szer && x0>=0 && i<this->wys && i>=0){
                ptr[szer*4*i + 4*x0]=kolor;
                ptr[szer*4*i + 4*x0 + 1] = kolor;
                ptr[szer*4*i + 4*x0 + 2] = kolor;
                } else break;
            }
          }
        }
    else{
        if(y0 < y1){
        for(int i = y0; i < y1;i++){
            x=(i-b)/a;
            if(x<this->szer && x>=0 && i<this->wys && i>=0){
            ptr[szer*4*i + 4*x]=kolor;
            ptr[szer*4*i + 4*x + 1] = kolor;
            ptr[szer*4*i + 4*x + 2] = kolor;
            } else break;
        }
        }
        else {
            for(int i = y0; i > y1;i--){
                x=(i-b)/a;
                if(x<this->szer && x>=0 && i<this->wys && i>=0){
                ptr[szer*4*i + 4*x]=kolor;
                ptr[szer*4*i + 4*x + 1] = kolor;
                ptr[szer*4*i + 4*x + 2] = kolor;
         } else break;
       }
    }
}

    update();
}

// Funkcja (slot) wywolywana po nacisnieciu przycisku myszy (w glownym oknie)
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    MyWindow::copyImage(this->img2, this->img);
    this->x0 = event->x()-poczX;
    this->y0 = event->y()-poczY;

}

void MyWindow::mouseMoveEvent(QMouseEvent *event){

    MyWindow::copyImage(this->img, this->img2);
    int x = event->x()-poczX;
    int y = event->y()-poczY;
    MyWindow::drawLine(this->x0, this->y0, x, y);
    update();

}

void MyWindow::copyImage(QImage *img, QImage *img2){
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
