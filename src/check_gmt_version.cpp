#include "check_gmt_version.h"
#include "ui_check_gmt_version.h"

check_gmt_version::check_gmt_version(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::check_gmt_version)
{
    ui->setupUi(this);
}

check_gmt_version::~check_gmt_version()
{
    delete ui;
}
