#include "gmt_pstext.h"
#include "ui_gmt_pstext.h"
#include <QMessageBox> //显示提示信息

GMT_pstext::GMT_pstext(QWidget *parent,QString S, int tw, int th, float wi, float hi) : //传入参数
    QDialog(parent,Qt::WindowTitleHint | Qt::CustomizeWindowHint), // 隐藏关闭按钮和帮助按钮
    psfname(S), // 传入参数赋值给ps文件名
    w(tw),
    h(th),
    image_w(wi),
    image_h(hi),
    ui(new Ui::GMT_pstext)
{
    ui->setupUi(this);
    this->setWindowTitle("pstext");

    gmt_cmd = ""; // 清空初始化

    ui->label->resize(w,h);
    ui->label->setScaledContents(true); // label要设置为自动缩放内容
    // 显示图像
    QPixmap pix("tmp.png");
    ui->label->setPixmap(pix);

    text_color.setRgb(0,0,0);
    ui->text_color->setStyleSheet(QString("color: %1").arg(text_color.name()));
}

GMT_pstext::~GMT_pstext()
{
    delete ui;
}

// 自定义鼠标按下事件处理
void GMT_pstext::mousePressEvent(QMouseEvent *event){
    // 如果是鼠标左键按下
    if(event->button() == Qt::LeftButton){
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

void GMT_pstext::on_checkfont_clicked()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://docs.gmt-china.org/5.4/_images/text-gmtplot-0.png")));
}

void GMT_pstext::on_check_justify_clicked()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://docs.gmt-china.org/5.4/_images/anchor-gmtplot-0.png")));
}

void GMT_pstext::on_text_color_clicked()
{
    QColor tmpcolor = QColorDialog::getColor(text_color, this,
                                             "选择文字的颜色",
                                             QColorDialog::ShowAlphaChannel);
    if (tmpcolor.isValid()){
        text_color = tmpcolor;
        ui->text_color->setStyleSheet(QString("color: %1").arg(text_color.name()));
    }
}

void GMT_pstext::on_bexit_clicked()
{
    gmt_cmd = ""; // 清空
    // 关闭窗口
    this->close();
}

void GMT_pstext::on_bok_clicked()
{
    QString w_input;
    // 检查文本position
    w_input = ui->position->toPlainText();
    if  ( w_input.isEmpty() ){
        QMessageBox msgBox;
        msgBox.setText("必须点击一个位置");
        msgBox.exec();
        return;
    }
    // 检查文本
    w_input = ui->usertext->text();
    if  ( w_input.isEmpty() ){
        QMessageBox msgBox;
        msgBox.setText("必须输入文本");
        msgBox.exec();
        return;
    }
    // 检查font
    w_input = ui->font->text();
    if  ( w_input.isEmpty() ){
        QMessageBox msgBox;
        msgBox.setText("必须输入字体");
        msgBox.exec();
        return;
    }
    // 检查size
    w_input = ui->size->text();
    if  ( w_input.isEmpty() ){
        QMessageBox msgBox;
        msgBox.setText("必须输入字体大小");
        msgBox.exec();
        return;
    }
    // 检查angle
    w_input = ui->angle->text();
    if  ( w_input.isEmpty() ){
        QMessageBox msgBox;
        msgBox.setText("必须输入旋转角");
        msgBox.exec();
        return;
    }
    // 检查justify
    w_input = ui->justify->text();
    if  ( w_input.isEmpty() ){
        QMessageBox msgBox;
        msgBox.setText("必须输入参考点相对于文本的位置");
        msgBox.exec();
        return;
    }

    gmt_cmd = "echo "+ui->position->toPlainText()+" "+ui->usertext->text()+" | ";
    gmt_cmd += "gmt pstext -O -K -Xa-1i -Ya-1i ";
    gmt_cmd += "-JX"+QString::number(image_w)+"i/"+QString::number(image_h)+"i ";
    gmt_cmd += "-R0/"+QString::number(image_w)+"/0/"+QString::number(image_h)+" ";
    gmt_cmd += "-F+f"+ui->size->text()+","+ui->font->text()+",";
    gmt_cmd += QString::number(text_color.red())+"/"+QString::number(text_color.green())+"/"+QString::number(text_color.blue());
    gmt_cmd += "+a"+ui->angle->text();
    gmt_cmd += "+j"+ui->justify->text()+" ";

    gmt_cmd += ui->other_options->text()+" ";

    gmt_cmd += ">> "+psfname;

    // 关闭窗口
    this->close();

}
