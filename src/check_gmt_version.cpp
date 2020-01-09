#include "check_gmt_version.h"
#include "ui_check_gmt_version.h"

#include <iostream>

check_gmt_version::check_gmt_version(QWidget *parent) :
    QDialog(parent,Qt::WindowTitleHint | Qt::CustomizeWindowHint), // 隐藏关闭按钮和帮助按钮
    ui(new Ui::check_gmt_version)
{
    ui->setupUi(this);

    this->setWindowTitle("正在检查GMT是否正确安装");

    exit_code = 0;

    //运行gmt --version，获取标准输出和标准错误信息
    QProcess p;
    QString stdout_info = "", stderr_info = "";
    int ret_code = 777;

    ret_code = p.execute("gmt --version");
    //p.start("gmt --version");
    //p.waitForFinished();
    //ret_code = p.error();


    //if (p.waitForStarted(-1)) {
        while(p.waitForReadyRead(-1)) {
            stdout_info += p.readAllStandardOutput();
            stderr_info += p.readAllStandardError();
        }
    //}

    //stdout_info = p.readAllStandardOutput();
    //stderr_info = p.readAllStandardError();

    if ( !stderr_info.isEmpty() || ret_code == -2 || ret_code == -1 ){
        ui->info->setText("检查失败，查找不到GMT，或GMT无法运行。可能原因:");
        ui->info->append("1. GMT未安装，或未正确安装");
        ui->info->append("2. 环境变量PATH未正确配置");
        ui->info->append("3. Linux/Mac用户没有从终端启动本程序，导致无法继承PATH");
        ui->bexit->setEnabled(true);
        exit_code = 1;
    }
    else{
        QMetaObject::invokeMethod(this, "close", Qt::QueuedConnection); // 在constructor中关闭自己必须使用这种方法
    }



}

check_gmt_version::~check_gmt_version()
{
    delete ui;
}

void check_gmt_version::on_bexit_clicked()
{
    this->close();
}
