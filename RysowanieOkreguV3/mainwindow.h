#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <math.h>
#include <qslider.h>
#include <qlcdnumber.h>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    QImage *img;
    QImage *img2;

    QPushButton *cleanButton;
    QPushButton *exitButton;
    QPushButton *okregButton;
    QPushButton *elipsaButton;
    QSlider *slider1;
    QGroupBox *grupa;
    QLCDNumber *lcd;

    int szer;
    int wys;
    int poczX;
    int poczY;
    int x0, y0;
    int x1, y1;
    bool slot;
    int wierz;

    void rysujKolo(int, int, int, int);
    void rysujElipsa(int, int, int, int, int);
    void czysc();
    void drawPixel(int x, int y, int kolor, QImage *img);
    void drawLine(int, int, int, int, int, QImage *img);
    double sinus(int, int, int, int);

private slots:
    void slot_czysc();
    void changeValue();
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);
 //   void mouseReleaseEvent(QMouseEvent *event);
    void copyImage(QImage*, QImage*);
};

#endif // MAINWINDOW_H
