#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QLabel>
#include <QPainter>
#include "answindow.h"

int GFullSize = 800;
int GSize = GFullSize/2;
int block = GSize/10;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    painter.setPen(QPen(Qt::white,1,Qt::SolidLine, Qt::FlatCap));
    painter.translate(GSize, GSize);
    painter.scale(1,-1);
    for (int x = -GSize; x <=GSize; ++x){
        for (int y = -GSize; y <=GSize; ++y){
            painter.drawPoint(x,y);
        }
    }

    painter.setPen(QPen(Qt::black,1,Qt::SolidLine, Qt::FlatCap));

    for(int i = -GSize; i<=GSize; ++i){
        painter.drawPoint(i,0);
    }
    for (int i = -GSize; i<=GSize; ++i){
        painter.drawPoint(0,i);
    }
        painter.setPen(QPen(Qt::red,3,Qt::SolidLine, Qt::FlatCap));
    for (int x = -GSize; x <=GSize; ++x){
        for (int y = -GSize; y <=GSize; ++y){
            if ((abs(-3*y -2*x-2*block)<3)){
                painter.drawPoint(x,y);
            }
        }
    }
    painter.setPen(QPen(Qt::green,3,Qt::SolidLine, Qt::FlatCap));
    for (int x = -GSize; x <=GSize; ++x){
        for (int y = -GSize; y <=GSize; ++y){
            if (abs(x*y+block*block)<178){
                painter.drawPoint(x,y);
            }
        }
    }


    painter.setPen(QPen(Qt::blue,3,Qt::SolidLine, Qt::FlatCap));

    for (int x = -GSize; x<=GSize; ++x){
        for(int y = -GSize; y<=GSize; ++y){
            if((abs(block*exp(x*1.0/block) + 2*block - y)<1.7 && x <=0) ||(abs(block*exp(x*1.0/block) + 2*block - y)<3 && x >0) ){
                painter.drawPoint(x,y);
            }
        }
    }




}
