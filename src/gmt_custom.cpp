#include "gmt_custom.h"
#include "ui_gmt_custom.h"

GMT_custom::GMT_custom(QWidget *parent) :
    QDialog(parent,Qt::WindowTitleHint | Qt::CustomizeWindowHint), // 隐藏关闭按钮和帮助按钮
    ui(new Ui::GMT_custom)
{
    ui->setupUi(this);
    this->setWindowTitle("手动输入GMT命令");

    gmt_cmd = ""; // 清空初始化
}

GMT_custom::~GMT_custom()
{
    delete ui;
}

void GMT_custom::on_bexit_clicked()
{
    gmt_cmd = ""; // 清空
    // 关闭窗口
    this->close();
}

void GMT_custom::on_bok_clicked()
{
    if (ui->cmd->text().isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("必须输入命令");
        msgBox.exec();
        return;
    }
    gmt_cmd = ui->cmd->text();
    // 关闭窗口
    this->close();
}
