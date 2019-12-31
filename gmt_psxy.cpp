#include "gmt_psxy.h"
#include "ui_gmt_psxy.h"
#include <QFileDialog>
#include <QMessageBox> //显示提示信息

GMT_psxy::GMT_psxy(QWidget *parent,QString S) : //传入参数
    QDialog(parent,Qt::WindowTitleHint | Qt::CustomizeWindowHint), // 隐藏关闭按钮和帮助按钮
    psfname(S), // 传入参数赋值给ps文件名
    ui(new Ui::GMT_psxy)
{
    ui->setupUi(this);

    gmt_cmd = ""; // 清空初始化

    J_option = new GMT_J_option(this); // 添加-J选项
    J_option->show();
    R_option = new GMT_R_option(this); // 添加-R选项
    R_option->show();

    ui->J_Layout->addWidget(J_option);
    ui->R_Layout->addWidget(R_option);

    g_color.setRgb(0,255,0);
    ui->g_color->setStyleSheet(QString("background-color: %1").arg(g_color.name()));
    W_pen_color.setRgb(0,0,0);
    ui->W_pen_color->setStyleSheet(QString("color: %1").arg(W_pen_color.name()));
}

GMT_psxy::~GMT_psxy()
{
    delete ui;
}

void GMT_psxy::on_g_color_clicked()
{
    QColor tmpcolor = QColorDialog::getColor(g_color, this,
                                             "选择符号或多边形的填充色",
                                             QColorDialog::ShowAlphaChannel);
    if (tmpcolor.isValid()){
        g_color = tmpcolor;
        ui->g_color->setStyleSheet(QString("background-color: %1").arg(g_color.name()));
    }
}

void GMT_psxy::on_draw_symbol_clicked()
{
    if (ui->draw_symbol->isChecked()){
        ui->draw_line->setChecked(false);
        ui->L_option->setEnabled(false);
        ui->S_option->setEnabled(true);
        ui->size->setEnabled(true);
    }
}

void GMT_psxy::on_draw_line_clicked()
{
    if (ui->draw_line->isChecked()){
        ui->draw_symbol->setChecked(false);
        ui->S_option->setEnabled(false);
        ui->size->setEnabled(false);
        ui->L_option->setEnabled(true);
    }
}

void GMT_psxy::on_W_pen_color_clicked()
{
    QColor tmpcolor = QColorDialog::getColor(W_pen_color, this,
                                             "选择符号轮廓或线段的颜色",
                                             QColorDialog::ShowAlphaChannel);
    if (tmpcolor.isValid()){
        W_pen_color = tmpcolor;
        ui->W_pen_color->setStyleSheet(QString("color: %1").arg(W_pen_color.name()));
    }
}

void GMT_psxy::on_b_datafile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
            tr("选择数据文件"));
    ui->datafile->setText(filename);
}

void GMT_psxy::on_bexit_clicked()
{
    gmt_cmd = ""; // 清空
    // 关闭窗口
    this->close();
}

void GMT_psxy::on_bok_clicked()
{
    // 检查文件
    if  ( ui->datafile->text().isEmpty() ){
        QMessageBox msgBox;
        msgBox.setText("必须选择数据文件");
        msgBox.exec();
        return;
    }

    gmt_cmd = "gmt psxy -O -K ";
    gmt_cmd += J_option->sendData()+" ";
    gmt_cmd += R_option->sendData()+" ";
    gmt_cmd += "-G"+QString::number(g_color.red())+"/"+QString::number(g_color.green())+"/"+QString::number(g_color.blue())+" ";
    if (!ui->W_pen_w->text().isEmpty()){
        gmt_cmd += "-W"+ui->W_pen_w->text()+",";
        gmt_cmd += QString::number(W_pen_color.red())+"/"+QString::number(W_pen_color.green())+"/"+QString::number(W_pen_color.blue())+" ";
    }
    if (ui->draw_symbol->isChecked()){
        gmt_cmd += ui->S_option->currentText().split(' ').at(0)+ui->size->text()+" ";
    }
    if (ui->draw_line->isChecked()){
        if (ui->L_option->isChecked()){
            gmt_cmd += "-L ";
        }
    }
    gmt_cmd += ui->datafile->text()+" ";

    gmt_cmd += ui->other_options->text()+" ";

    gmt_cmd += ">> "+psfname;

    // 关闭窗口
    this->close();
}
