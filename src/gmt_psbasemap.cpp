#include "gmt_psbasemap.h"
#include "ui_gmt_psbasemap.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

GMT_psbasemap::GMT_psbasemap(QWidget *parent,QString S) : //传入参数
    QDialog(parent,Qt::WindowTitleHint | Qt::CustomizeWindowHint), // 隐藏关闭按钮和帮助按钮
    psfname(S), // 传入参数赋值给ps文件名
    ui(new Ui::GMT_psbasemap)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); // 去除问号帮助按钮
    this->setWindowTitle("psbasemap");

    gmt_cmd = ""; // 清空初始化

    J_option = new GMT_J_option(this); // 添加-J选项
    J_option->show();
    R_option = new GMT_R_option(this); // 添加-R选项
    R_option->show();
    B_option = new GMT_B_option(this); // 添加-B选项
    B_option->show();

    ui->J_Layout->addWidget(J_option);
    ui->R_Layout->addWidget(R_option);
    ui->B_Layout->addWidget(B_option);
}

GMT_psbasemap::~GMT_psbasemap()
{
    delete ui;
}

void GMT_psbasemap::on_bexit_clicked()
{
    gmt_cmd = ""; // 清空
    // 关闭窗口
    this->close();
}

void GMT_psbasemap::on_bok_clicked()
{
    gmt_cmd = "gmt psbasemap -O -K ";
    gmt_cmd += J_option->sendData()+" ";
    gmt_cmd += R_option->sendData()+" ";
    gmt_cmd += B_option->sendData()+" ";

    gmt_cmd += ui->other_options->text()+" ";

    gmt_cmd += ">> "+psfname;

    // 关闭窗口
    this->close();

}
