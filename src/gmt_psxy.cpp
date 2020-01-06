#include "gmt_psxy.h"
#include "ui_gmt_psxy.h"
#include <QFileDialog>
#include <QMessageBox> //显示提示信息

GMT_psxy::GMT_psxy(QWidget *parent,QString S, int tw, int th, float wi, float hi) : //传入参数
    QDialog(parent,Qt::WindowTitleHint | Qt::CustomizeWindowHint), // 隐藏关闭按钮和帮助按钮
    psfname(S), // 传入参数赋值给ps文件名
    w(tw),
    h(th),
    image_w(wi),
    image_h(hi),
    ui(new Ui::GMT_psxy)
{
    ui->setupUi(this);
    this->setWindowTitle("psxy");

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

    ui->label->resize(w,h);
    ui->label->setScaledContents(true); // label要设置为自动缩放内容
    // 显示图像
    QPixmap pix("tmp.png");
    ui->label->setPixmap(pix);
}

GMT_psxy::~GMT_psxy()
{
    delete ui;
}

// 自定义鼠标按下事件处理
void GMT_psxy::mousePressEvent(QMouseEvent *event){
    // 如果是鼠标左键按下
    if(event->button() == Qt::LeftButton && ui->use_mouse->isChecked()){
        QPoint pt = mapFromGlobal(QCursor::pos()); //直接pos得到的是相对于屏幕的全局坐标，需要转换成相对于窗口的坐标，原点在窗口左上
        int labelx = ui->label->pos().x(); // 图片控件左上角的坐标
        int labely = ui->label->pos().y();
        int mx = pt.x(); // 鼠标点击坐标
        int my = pt.y();
        // 如果不在图片范围内则直接退出函数
        if ( mx < labelx || labelx + w < mx || my < labely || labely + h < my )
            return;
        //ui->position->setText(QString::number(mx)+" "+QString::number(my)+" "+QString::number(labelx)+" "+QString::number(labely));
        //将坐标原点转换到图片左下角
        mx = mx - labelx;
        my = h + labely - my;
        // 转换成GMT的坐标
        float xx = (float)mx / (float)w * image_w;
        float yy = (float)my / (float)h * image_h;
        ui->position->setText(QString::number(xx)+" "+QString::number(yy));
    }

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
        ui->g_color->setEnabled(true);

        ui->use_input->setEnabled(true);
        ui->use_mouse->setEnabled(true);
        ui->use_file->setEnabled(true);
        ui->use_input->setChecked(true);

        ui->position_input->setEnabled(true);
        ui->position->setEnabled(false);
        ui->datafile->setEnabled(false);
        ui->b_datafile->setEnabled(false);
    }
}

void GMT_psxy::on_draw_line_clicked()
{
    if (ui->draw_line->isChecked()){
        ui->draw_symbol->setChecked(false);
        ui->S_option->setEnabled(false);
        ui->size->setEnabled(false);
        ui->L_option->setEnabled(true);
        ui->g_color->setEnabled(false);
        if (ui->L_option->isChecked()){
            ui->g_color->setEnabled(true);
        }

        ui->use_input->setEnabled(false);
        ui->use_mouse->setEnabled(false);
        ui->use_file->setEnabled(true);
        ui->use_file->setChecked(true);

        ui->position_input->setEnabled(false);
        ui->position->setEnabled(false);
        ui->datafile->setEnabled(true);
        ui->b_datafile->setEnabled(true);
    }
}

void GMT_psxy::on_L_option_stateChanged(int arg1)
{
    if (ui->L_option->isChecked()){
        ui->g_color->setEnabled(true);
    }else{
        ui->g_color->setEnabled(false);
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

void GMT_psxy::on_use_input_clicked()
{
    ui->position_input->setEnabled(true);
    ui->position->setEnabled(false);
    ui->datafile->setEnabled(false);
    ui->b_datafile->setEnabled(false);
}

void GMT_psxy::on_use_mouse_clicked()
{
    ui->position_input->setEnabled(false);
    ui->position->setEnabled(true);
    ui->datafile->setEnabled(false);
    ui->b_datafile->setEnabled(false);
}

void GMT_psxy::on_use_file_clicked()
{
    ui->position_input->setEnabled(false);
    ui->position->setEnabled(false);
    ui->datafile->setEnabled(true);
    ui->b_datafile->setEnabled(true);
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
    delete J_option;
    delete R_option;
    this->close();
}

void GMT_psxy::on_bok_clicked()
{
    // 检查文件
    if  ( ui->use_file->isChecked() && ui->datafile->text().isEmpty() ){
        QMessageBox msgBox;
        msgBox.setText("必须选择数据文件");
        msgBox.exec();
        return;
    }
    // 检查输入
    if ( ui->use_input->isChecked() && ui->position_input->text().isEmpty() ){
        QMessageBox msgBox;
        msgBox.setText("必须输入坐标");
        msgBox.exec();
        return;
    }
    // 检查点击
    if ( ui->use_mouse->isChecked() && ui->position->toPlainText().isEmpty() ){
        QMessageBox msgBox;
        msgBox.setText("必须点击一个位置");
        msgBox.exec();
        return;
    }
    // 检查符号
    if ( ui->draw_symbol->isChecked() && ui->size->text().isEmpty() ){
        QMessageBox msgBox;
        msgBox.setText("必须输入符号大小");
        msgBox.exec();
        return;
    }

    if (ui->use_mouse->isChecked()){
        gmt_cmd = "echo "+ui->position->toPlainText()+" | gmt psxy -O -K ";
        gmt_cmd += "-JX"+QString::number(image_w)+"i/"+QString::number(image_h)+"i ";
        gmt_cmd += "-R0/"+QString::number(image_w)+"/0/"+QString::number(image_h)+" ";
        gmt_cmd += "-Xa-1i -Ya-1i ";
    }
    else if (ui->use_input->isChecked()){
        gmt_cmd = "echo "+ui->position_input->text()+" | gmt psxy -O -K ";
        gmt_cmd += J_option->sendData()+" ";
        gmt_cmd += R_option->sendData()+" ";
    }
    else if (ui->use_file->isChecked()){
        gmt_cmd = "gmt psxy -O -K "+ui->datafile->text()+" ";
        gmt_cmd += J_option->sendData()+" ";
        gmt_cmd += R_option->sendData()+" ";
    }

    if (!ui->W_pen_w->text().isEmpty()){
        gmt_cmd += "-W"+ui->W_pen_w->text()+",";
        gmt_cmd += QString::number(W_pen_color.red())+"/"+QString::number(W_pen_color.green())+"/"+QString::number(W_pen_color.blue())+" ";
    }
    if (ui->draw_symbol->isChecked()){
        gmt_cmd += "-G"+QString::number(g_color.red())+"/"+QString::number(g_color.green())+"/"+QString::number(g_color.blue())+" ";
        gmt_cmd += ui->S_option->currentText().split(' ').at(0)+ui->size->text()+" ";
    }
    if (ui->draw_line->isChecked()){
        if (ui->L_option->isChecked()){
            gmt_cmd += "-L ";
            gmt_cmd += "-G"+QString::number(g_color.red())+"/"+QString::number(g_color.green())+"/"+QString::number(g_color.blue())+" ";
        }
    }

    gmt_cmd += ui->other_options->text()+" ";

    gmt_cmd += ">> "+psfname;

    // 关闭窗口
    delete J_option;
    delete R_option;
    this->close();
}

