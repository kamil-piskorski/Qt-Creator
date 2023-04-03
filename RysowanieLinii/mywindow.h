// Plik naglowkowy klasy MyWindow
// Obiekt tej klasy to glowne okno naszej aplikacji

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <math.h>

class MyWindow : public QWidget
{
    Q_OBJECT
public:

    MyWindow(QWidget *parent = 0);

    // Deklaracja destruktora
    ~MyWindow();

private:

    // Pole przechowujace obrazek
    QImage *img;
    QImage *img2;

    // Przyciski
    QPushButton *draw1Button;
    QPushButton *draw2Button;
    QPushButton *cleanButton;
    QPushButton *exitButton;

    // Grupa przyciskow
    QGroupBox *grupa;

    // Pola przechowujace szerokosc i wysokosc rysunku
    // oraz wspolrzedne jego lewego gornego naroznika
    int szer;
    int wys;
    int poczX;
    int poczY;
    bool isPressed;
    int x0, y0;
    int x1, y1;

    void czysc();
    void rysuj1();
    void rysuj2();
    double sinus(int, int, int, int);


private slots:
    void slot_czysc();
    void slot_rysuj1();
    void slot_rysuj2();
    void drawLine(int, int, int, int);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    void copyImage(QImage*, QImage*);
};
