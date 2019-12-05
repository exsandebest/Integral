#include "legend.h"
#include "ui_legend.h"

legend::legend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::legend)
{
    ui->setupUi(this);
}

legend::~legend()
{
    delete ui;
}
