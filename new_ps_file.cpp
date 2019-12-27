#include "new_ps_file.h"
#include "ui_new_ps_file.h"

#include <QMessageBox> //显示提示信息
#include <QValidator> // 正则表达式

new_ps_file::new_ps_file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_ps_file)
{
    ui->setupUi(this);
    //限制只能输入正浮点数
    QRegExp regExp("^(?:[1-9]\\d*|0)?(?:\\.\\d+)?$");
    QRegExpValidator *pattern= new QRegExpValidator(regExp, this);
    ui->w_input->setValidator(pattern);
    ui->h_input->setValidator(pattern);
}

new_ps_file::~new_ps_file()
{
    delete ui;
}

void new_ps_file::on_ok_button_clicked()
{
    // 检查宽度
    QString w_input = ui->w_input->text();
    if  ( w_input.isEmpty() ){
        QMessageBox msgBox;
        msgBox.setText("宽度不可为空");
        msgBox.exec();
        return;
    }
    // 检查高度
    QString h_input = ui->h_input->text();
    if  ( h_input.isEmpty() ){
        QMessageBox msgBox;
        msgBox.setText("高度不可为空");
        msgBox.exec();
        return;
    }

    //gmt_cmd = "gmt basemap -JX"+w_input+"c/"+h_input+"c -R0/"+w_input+"/0/"+h_input+" -B1/1 -P -K > tmp.ps";
    gmt_cmd = "gmt psxy -JX1/1 -R0/1/0/1 -T -P ";
    gmt_cmd += "--PS_MEDIA="+w_input+"cx"+h_input+"c ";
    gmt_cmd += "> tmp.ps";

    // 关闭窗口
    this->close();
}
