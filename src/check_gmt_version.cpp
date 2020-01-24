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
    //int ret_code = 777;

    p.start("gmt --version");
    p.waitForFinished();

    stdout_info = p.readAllStandardOutput();
    stderr_info = p.readAllStandardError();
    stdout_info.remove("\n");

    // 定义正则表达式匹配版本号
    QRegExp exp("^\\d\\.\\d\\.\\d"); // 去除对开发版的限制

    if ( !stderr_info.isEmpty() || stdout_info.isEmpty() ){
        ui->info->setText("检查失败，查找不到GMT，或GMT无法运行。可能原因:");
        ui->info->append("1. GMT未安装，或未正确安装");
        ui->info->append("2. 环境变量PATH未正确配置");
        ui->info->append("3. Linux/Mac用户没有从终端启动本程序，导致无法继承PATH");
        ui->info->append("");
        ui->info->append(stderr_info);
        ui->bexit->setEnabled(true);
        exit_code = 1;
    }
    else if ( stdout_info < "5.4.0" || !exp.exactMatch(stdout_info) ){
        //ui->info->setText("GMT版本太低，或您使用的是测试开发版。请升级到正式版GMT");
        ui->info->setText("GMT版本太低,请升级GMT");
        ui->info->append("GMT最低版本要求 5.4.0");
        ui->info->append("本机安装的版本： "+stdout_info);
        //ui->info->append("请注意正式版的版本号是三个被.隔开的数字，后面不带尾巴");
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
