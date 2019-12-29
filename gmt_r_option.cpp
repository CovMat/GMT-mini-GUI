#include "gmt_r_option.h"
#include "ui_gmt_r_option.h"

GMT_R_option::GMT_R_option(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GMT_R_option)
{
    ui->setupUi(this);

    ui->range->setPlaceholderText("不填表示与前一条使用相同范围");
}

GMT_R_option::~GMT_R_option()
{
    delete ui;
}

void GMT_R_option::on_open_url_clicked()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://api.map.baidu.com/lbsapi/getpoint/index.html")));
}
