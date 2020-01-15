#include "gmt_pstext.h"
#include "ui_gmt_pstext.h"

GMT_pstext::GMT_pstext(QWidget *parent,QString S, float wi, float hi) : //传入参数
    //QDialog(parent,Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowMaximizeButtonHint), // 隐藏关闭按钮和帮助按钮
    QDialog(parent,Qt::WindowMaximizeButtonHint),
    psfname(S), // 传入参数赋值给ps文件名
    image_w(wi),
    image_h(hi),
    ui(new Ui::GMT_pstext)
{
    ui->setupUi(this);
    this->setWindowTitle("pstext");

    gmt_cmd = ""; // 清空初始化

    //
    ui->datafile->setPlaceholderText("3列文件的格式为：x  y  text。 \n6列文件的格式为：x  y  font  angle  justify  text");

    ui->label->setScaledContents(true); // label要设置为自动缩放内容

    //初始化窗口大小，限制窗口最小尺寸
    this->setMinimumSize(WIDTH_init_pstext,HEIGHT_init_pstext);
    this->resize(WIDTH_init_pstext,HEIGHT_init_pstext);
    // 初始化预览区尺寸
    ui->label->resize(W_PREVIEW_init_pstext, H_PREVIEW_init_pstext);

    // 预览图像
    display_preview();

    // 设置颜色
    text_color.setRgb(0,0,0);
    ui->text_color->setStyleSheet(QString("color: %1").arg(text_color.name()));
}

GMT_pstext::~GMT_pstext()
{
    delete ui;
}

void GMT_pstext::resizeEvent(QResizeEvent *event) // 窗口大小改变事件，重新显示预览图片
{
    //GMT_pstext::resizeEvent(event);
    // dialog类型不能有这句话

    // 获取变化后的大小
    int ww = this->width();
    int hh = this->height();

    // 调整预览区大小
    int w_preview = ui->label->width();
    int h_preview = ui->label->height();
    h_preview = H_PREVIEW_init_pstext + hh - HEIGHT_init_pstext; // 垂直方向新增的高度，全部给预览区
    w_preview = W_PREVIEW_init_pstext + ww - WIDTH_init_pstext; // 水平方向新增的宽度，全部给预览区
    ui->label->resize( w_preview, h_preview );

    // 重新预览图像
    display_preview();
}

// 自定义函数，显示预览
void GMT_pstext::display_preview(){
    QPixmap pix("tmp.png");
    int hp = pix.size().height();
    int wp = pix.size().width();
    int hh = ui->label->size().height();
    int ww = ui->label->size().width();

    // 检查tmp.png是否存在
    if ( !QFile::exists("tmp.png") || hp == 0 || wp == 0 ){
        QMessageBox msgBox;
        QString str;
        str = "预览图片生成失败。可能原因:\n";
        str+= "1. 本机未安装Ghostscript或Ghostscript版本太低，请升级安装Ghostscript\n";
        str+= "2. tmp.png文件被删除\n";
        str+= "3. 您输入的GMT命令有误，请仔细检查并撤销\n";
        msgBox.setText(str);
        msgBox.exec();
        return;
    }

    if ( hp/wp > hh/ww )
        ww = hh*wp/hp;
    else
        hh = hp*ww/wp;

    ui->label->resize(ww,hh);
    //QPixmap dest=pix.scaled(label->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    // 注意不能使用QPixmap的等比例缩放，而要让label去适应pixmap的比例。因为实际使用发现使用前者会导致图片质量严重下降
    ui->label->setPixmap(pix);
}

// 自定义鼠标按下事件处理
void GMT_pstext::mousePressEvent(QMouseEvent *event){
    // 如果是鼠标左键按下
    if(event->button() == Qt::LeftButton && ui->use_mouse->isChecked()){
        QPoint pt = mapFromGlobal(QCursor::pos()); //直接pos得到的是相对于屏幕的全局坐标，需要转换成相对于窗口的坐标，原点在窗口左上
        int labelx = ui->label->pos().x(); // 图片控件左上角的坐标
        int labely = ui->label->pos().y();
        int mx = pt.x(); // 鼠标点击坐标
        int my = pt.y();
        int w = ui->label->width();
        int h = ui->label->height();
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
        // 原点移动到（1i，1i）。注意这里要求 MAP_ORIGIN_X 和 MAP_ORIGIN_Y 保持默认值不变
        xx--;
        yy--;
        // 输出到临时文件
        QFile::remove("gmt-mini-coordinate.txt");
        std::ofstream out( "gmt-mini-coordinate.txt", std::ios_base::binary | std::ios_base::out);
        out << xx << " " << yy;
        out.close();
        // 换算到地理坐标
        QFile::remove("gmt-mini-project.txt");
        QProcess::execute("gmt mapproject -J -R -Di -I --IO_COL_SEPARATOR=space gmt-mini-coordinate.txt --FORMAT_FLOAT_OUT=%.6lg > gmt-mini-project.txt");
        // 读取转换后的地理坐标
        std::ifstream fin;
        fin.open("gmt-mini-project.txt");
        std::string str;
        std::getline(fin, str);
        ui->position->setText(QString::fromStdString(str));
        fin.close();
        // 删除临时文件
        QFile::remove("gmt-mini-project.txt");
        QFile::remove("gmt-mini-coordinate.txt");
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

void GMT_pstext::on_use_input_clicked()
{
    if ( ui->use_input->isChecked() ){
        ui->position_input->setEnabled(true);
        ui->position->setEnabled(false);
        ui->b_datafile->setEnabled(false);
        ui->datafile->setEnabled(false);

        ui->usertext->setEnabled(true);
        ui->font->setEnabled(true);
        ui->size->setEnabled(true);
        ui->text_color->setEnabled(true);
        ui->angle->setEnabled(true);
        ui->justify->setEnabled(true);
    }
}

void GMT_pstext::on_use_mouse_clicked()
{
    if ( ui->use_mouse->isChecked() ){
        ui->position->setEnabled(true);
        ui->position_input->setEnabled(false);
        ui->b_datafile->setEnabled(false);
        ui->datafile->setEnabled(false);

        ui->usertext->setEnabled(true);
        ui->font->setEnabled(true);
        ui->size->setEnabled(true);
        ui->text_color->setEnabled(true);
        ui->angle->setEnabled(true);
        ui->justify->setEnabled(true);
    }
}

void GMT_pstext::on_use_file_clicked()
{
    if ( ui->use_file->isChecked() ){
        ui->position->setEnabled(false);
        ui->position_input->setEnabled(false);
        ui->b_datafile->setEnabled(true);
        ui->datafile->setEnabled(true);

        ui->usertext->setEnabled(false);
        ui->font->setEnabled(true);
        ui->size->setEnabled(true);
        ui->text_color->setEnabled(true);
        ui->angle->setEnabled(true);
        ui->justify->setEnabled(true);
    }
}

void GMT_pstext::on_use_file_6_clicked()
{
    if ( ui->use_file_6->isChecked() ){
        ui->position->setEnabled(false);
        ui->position_input->setEnabled(false);
        ui->b_datafile->setEnabled(true);
        ui->datafile->setEnabled(true);

        ui->usertext->setEnabled(false);
        ui->font->setEnabled(false);
        ui->size->setEnabled(false);
        ui->text_color->setEnabled(false);
        ui->angle->setEnabled(false);
        ui->justify->setEnabled(false);
    }
}

void GMT_pstext::on_b_datafile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
            tr("选择数据文件"));
    ui->datafile->setText(filename);
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
    if (ui->use_mouse->isChecked()){
        w_input = ui->position->toPlainText();
        if  ( w_input.isEmpty() ){
            QMessageBox msgBox;
            msgBox.setText("必须点击一个位置");
            msgBox.exec();
            return;
        }
    }
    if (ui->use_input->isChecked()){
        w_input = ui->position_input->text();
        if (w_input.isEmpty()){
            QMessageBox msgBox;
            msgBox.setText("必须输入一个位置");
            msgBox.exec();
            return;
        }
    }
    if (ui->use_file->isChecked() || ui->use_file_6->isChecked()){
        w_input = ui->datafile->toPlainText();
        if (w_input.isEmpty()){
            QMessageBox msgBox;
            msgBox.setText("必须选择一个文件");
            msgBox.exec();
            return;
        }
    }
    // 检查文本
    w_input = ui->usertext->text();
    if  ( w_input.isEmpty() && !ui->use_file->isChecked() && !ui->use_file_6->isChecked() ){
        QMessageBox msgBox;
        msgBox.setText("必须输入文本");
        msgBox.exec();
        return;
    }
    // 检查font
    w_input = ui->font->text();
    if  ( w_input.isEmpty() && !ui->use_file_6->isChecked() ){
        QMessageBox msgBox;
        msgBox.setText("必须输入字体");
        msgBox.exec();
        return;
    }
    // 检查size
    w_input = ui->size->text();
    if  ( w_input.isEmpty() && !ui->use_file_6->isChecked() ){
        QMessageBox msgBox;
        msgBox.setText("必须输入字体大小");
        msgBox.exec();
        return;
    }
    // 检查angle
    w_input = ui->angle->text();
    if  ( w_input.isEmpty() && !ui->use_file_6->isChecked() ){
        QMessageBox msgBox;
        msgBox.setText("必须输入旋转角");
        msgBox.exec();
        return;
    }
    // 检查justify
    w_input = ui->justify->text();
    if  ( w_input.isEmpty() && !ui->use_file_6->isChecked() ){
        QMessageBox msgBox;
        msgBox.setText("必须输入参考点相对于文本的位置");
        msgBox.exec();
        return;
    }

    if (ui->use_mouse->isChecked()){
        gmt_cmd = "echo "+ui->position->toPlainText()+" ";
        gmt_cmd += ui->usertext->text()+" | gmt pstext -O -K -J -R -N ";
    }
    else if (ui->use_input->isChecked()){
        gmt_cmd = "echo "+ui->position_input->text()+" ";
        gmt_cmd += ui->usertext->text()+" | gmt pstext -O -K -J -R -N ";
    }
    else if (ui->use_file->isChecked() || ui->use_file_6->isChecked()){
        gmt_cmd = "gmt pstext "+ui->datafile->toPlainText()+" -O -K -J -R -N ";
    }

    if (!ui->use_file_6->isChecked()){
        gmt_cmd += "-F+f"+ui->size->text()+","+ui->font->text()+",";
        gmt_cmd += QString::number(text_color.red())+"/"+QString::number(text_color.green())+"/"+QString::number(text_color.blue());
        gmt_cmd += "+a"+ui->angle->text();
        gmt_cmd += "+j"+ui->justify->text()+" ";
    }else{
        gmt_cmd += "-F+f+a+j ";
    }

    gmt_cmd += ui->other_options->text()+" ";

    gmt_cmd += ">> "+psfname;

    // 关闭窗口
    this->close();

}
