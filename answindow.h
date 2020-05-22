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
    double integral_simpson(double (*)(double, int), double, double);
    double integral_monte(double (*)(double, int), double, double, double, double);

private:
    Ui::AnsWindow *ui;
};

#endif // ANSWINDOW_H
