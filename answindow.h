#ifndef ANSWINDOW_H
#define ANSWINDOW_H

#include <QWidget>

namespace Ui {
class AnsWindow;
}

class AnsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AnsWindow(QWidget *parent = nullptr);
    ~AnsWindow();
    /*double f1(double x);
    double f2(double x);
    double f3(double x);*/
    double integral_simpson(double (*f)(double, int), double a, double b);
    double integral_monte(double (*f)(double, int), double a, double b);
    double integral_monte_2(double (*f)(double, int), double a, double b, double miny, double maxy);
private:
    Ui::AnsWindow *ui;
};

#endif // ANSWINDOW_H
