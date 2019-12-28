#include "gmt_j_option.h"
#include "ui_gmt_j_option.h"

GMT_J_option::GMT_J_option(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GMT_J_option)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint); // 隐藏边框，便于嵌入pscoast， psbasemap等窗体
    hide();
    ui->J_option->addItem("-JA");
}

GMT_J_option::~GMT_J_option()
{
    delete ui;
}
