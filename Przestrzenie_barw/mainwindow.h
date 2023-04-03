    #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QPainter>
#include <QImage>
#include <QSlider>
#include <QLCDNumber>
#include <QCheckBox>
#include <QLabel>
#include <QRadioButton>

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QImage *img;

    QGroupBox *grupaRGB;
    QGroupBox *grupaHSV;
    QGroupBox *wyjscie;

    QSlider *R;
    QSlider *G;
    QSlider *B;

    QSlider *H;
    QSlider *S;
    QSlider *V;

    QPushButton *exitButton;

    void convert(float H, float S, float V, int i, int j);

    int szer;
    int wys;
    int poczX;
    int poczY;
    double red;
    double green;
    double blue;

private slots:
    void paintEvent(QPaintEvent*);
    void paintNoRed(int k);
    void paintNoGreen(int k);
    void paintNoBlue(int k);
    void Hslider(int k);
    void Sslider(int k);
    void Vslider(int k);


};
#endif // MAINWINDOW_H
