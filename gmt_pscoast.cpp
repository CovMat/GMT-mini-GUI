#include "gmt_pscoast.h"
#include "ui_gmt_pscoast.h"

GMT_pscoast::GMT_pscoast(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GMT_pscoast)
{
    ui->setupUi(this);
}

GMT_pscoast::~GMT_pscoast()
{
    delete ui;
}
