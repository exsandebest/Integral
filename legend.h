#ifndef LEGEND_H
#define LEGEND_H

#include <QWidget>

namespace Ui {
class legend;
}

class legend : public QWidget
{
    Q_OBJECT

public:
    explicit legend(QWidget *parent = nullptr);
    ~legend();

private:
    Ui::legend *ui;
};

#endif // LEGEND_H
