#include "answindow.h"
#include "ui_answindow.h"
#include "math.h"
#include <QMessageBox>
#include <QDebug>
#include <ctime>

double x1, x2, x3;

double eps = 0.001;
double epsS = eps/3;
double epsP = eps/10000;

double pointsNum = 100000000;

double f1(double x, int d){
    if (d == 0){
        return exp(x)+2;
    } else {
        return exp(x);
    }
}
double f2(double x, int d){
    if (d == 0){
        return (-1/x);
    } else if (d == 1){
        return (1/(x*x));
    } else if (d == 2){
        return (-2/(x*x*x));
    }
}
double f3(double x , int d){
    if (d == 0){
       return ((-2.0/3)*x-2.0/3);
    } else if (d == 1){
        return (-2.0/3);
    } else if (d == 2){
        return 0;
    }

}

double AnsWindow::integral_simpson(double (*f)(double, int), double a, double b){
    double t1=epsS+1, t2=0;
       for (int i=2; (i<=4)||(abs(t2-t1)>epsS); i*=2)
       {
           double h, sum2=0, sum4=0, sum=0;
           h=(b-a)/(2*i);
           for (int j=1; j<=2*i-1; j+=2)
           {
               sum4+=f(a+h*j, 0);
               sum2+=f(a+h*(j+1), 0);
           }
           sum=f(a, 0)+4*sum4+2*sum2-f(b, 0);
           t1=t2;
           t2=(h/3)*sum;
       }
       return t2;
}

double root(double a, double b, double (*f1)(double, int), double (*f2)(double,int)){
    int i = 0;
    double d = 0,c = 0;
    int decisionC = 0, decisionD = 0;
    double middle = (b+a)/2;
    if ((f1(middle,1)-f2(middle,1)) *(f1(middle,2)-f2(middle,2)) >0){
        decisionC = 0;
        d = b - ((f1(b,0)-f2(b,0))/(f1(b,1)-f2(b,1)));
      //  qDebug() << "x0 = " << d << "\n";
    } else {
        decisionC = 1;
        d = a - ((f1(a,0)-f2(a,0))/(f1(a,1)-f2(a,1)));
        //qDebug() << "x0 = " << d << "\n";
    }
   // qDebug() << "decisionC = " << decisionC << "\n";
    while (abs(d-c)>epsP){
    c = (a* (f1(b,0) - f2(b,0)) - b* (f1(a,0)-f2(a,0)) )/( (f1(b,0) - f2(b,0)) - (f1(a,0) - f2(a,0)));
    d = d - ((f1(d,0)-f2(d,0))/(f1(d,1)-f2(d,1)));
    //qDebug() << d << " " << c << "\n";
    if (decisionC){
        b = c;
    } else {
        a = c;
    }
    }
    return c<d?(2*c+epsP)/2:(2*d+epsP)/2;
}


double AnsWindow::integral_monte(double (*f)(double,int), double a, double b){
    double s = 0;
    srand((unsigned)time(0));
    for (int i=0; i<pointsNum; i++){
    s += f(a + ((double) rand() / RAND_MAX * (b - a)) , 0);
    }
    s = s/pointsNum*(b-a);
    return s;
}
double AnsWindow::integral_monte_2(double (*f)(double,int), double a, double b, double miny, double maxy){
    double s = (b-a) * (maxy-miny);
    qsrand((unsigned)time(0));
	double k = 0;
	double genX, genY;
	for (int i = 0; i < pointsNum; ++i){
        genX = a + ((double) qrand() / RAND_MAX * (b - a));
        genY = miny + ((double) qrand() / RAND_MAX * (maxy - miny));
        if (genY<=f(genX,0)) ++k;
	}
	return s*(k/pointsNum);
}


AnsWindow::AnsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnsWindow)
{
    ui->setupUi(this);
    unsigned int start_time = clock();
    x1 = root(-5,-3,f1,f3);
    x2 = root(-2,-1,f2,f3);
    x3 = root(-1, -0.1, f1,f2);
    qDebug() << x1 << x2 << x3;
    double sv1 = integral_simpson(f1,x1,x3), sv2 = integral_simpson(f3,x1,x2),sv3 = integral_simpson(f2,x2,x3);
   // double mv1 = integral_monte(f1,x1,x3), mv2 = integral_monte(f3,x1,x2), mv3 = integral_monte(f2,x2,x3);
    double mv1 = integral_monte_2(f1,x1,x3, 0,3), mv2 = integral_monte_2(f3,x1,x2,0,3), mv3 = integral_monte_2(f2,x2,x3,0,3);
    double sS = sv1 - sv2 - sv3;
    double mS = mv1 - mv2 - mv3;
    unsigned int end_time = clock();

    QString text = "Loading progect Polynomials2...\n\nGraphics.....................OK\nCalculation..................OK\nLegend.......................OK\n\nOUTPUT:\n\n";
    text+="f1(x) = exp(2)+2\nf2(x) = -1/x\nf3(x) = -2(x+1)/3\n\n";
    text+="EPSILON = "+QString("").setNum(eps)+"\n\n";
    text+="Epsilon for points (E1) = " + QString("").setNum(epsP) + "\n\n";
    text+="f1(x) = f2(x); x = " + QString("").setNum(x1) + "\n";
    text+="f2(x) = f3(x); x = " + QString("").setNum(x2) + "\n";
    text+="f1(x) = f2(x); x = " + QString("").setNum(x3) + "\n\n";

    text+="FORMULA\n";
    text+="S = integral(f1(x), x1, x3) - integral(f3(x), x1, x2) - integral(f2(x),x2,x3)\n\n";
    text+="Epsilon for area (E2) = " + QString("").setNum(epsS) + "\n\n";
    text+="Simpson method\n";
    text+="S = " + QString("").setNum(sv1) +" - "+QString("").setNum(sv2) + " - "+QString("").setNum(sv3)+"\n";
    text+="S = " + QString("").setNum(sS) + "\n\n";
    text+="Monte Carlo method (N = "+QString("").setNum(pointsNum)+")\n";
    text+="S = " + QString("").setNum(mv1) + " - " + QString("").setNum(mv2) + " - " + QString("").setNum(mv3) + "\n";
    text+="S = " + QString("").setNum(mS)+"\n\n";
    text+="ANSWER: S(s) = " + QString("").setNum(sS)+"; S(m) = "+QString("").setNum(mS) + "\n\n";
    text+="Process returned 0 (0x0)\nExecution time : " + QString("").setNum(1.0*(end_time-start_time)/1000);
    ui->label->setText(text);
}

AnsWindow::~AnsWindow()
{
    delete ui;
}
