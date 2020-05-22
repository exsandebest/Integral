#include "legend.h"
#include "ui_legend.h"

legend::legend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::legend)
{
    ui->setupUi(this);
    this->setFixedSize(400, 100);
}

legend::~legend()
{
    delete ui;
}
