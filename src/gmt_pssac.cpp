#include "gmt_pssac.h"
#include "ui_gmt_pssac.h"
#include <QFileDialog>
#include <QMessageBox> //显示提示信息
#include <QTextStream>

GMT_pssac::GMT_pssac(QWidget *parent,QString S) : //传入参数
     QDialog(parent,Qt::WindowTitleHint | Qt::CustomizeWindowHint), // 隐藏关闭按钮和帮助按钮
     psfname(S), // 传入参数赋值给ps文件名
    ui(new Ui::GMT_pssac)
{
    ui->setupUi(this);
    this->setWindowTitle("pssac");

    gmt_cmd = ""; // 清空初始化

    J_option = new GMT_J_option(this); // 添加-J选项
    J_option->show();
    R_option = new GMT_R_option(this); // 添加-R选项
    R_option->show();

    ui->J_Layout->addWidget(J_option);
    ui->R_Layout->addWidget(R_option);

    W_pen_color.setRgb(0,0,0);
    ui->W_pen_color->setStyleSheet(QString("color: %1").arg(W_pen_color.name()));
}

GMT_pssac::~GMT_pssac()
{
    delete ui;
}

void GMT_pssac::on_use_sac_clicked()
{
    if ( ui->use_sac->isChecked()){
        ui->use_list->setChecked(false);
        ui->choose_list->setEnabled(false);
        ui->saclist->setEnabled(false);
        ui->choose_sac->setEnabled(true);
        ui->sacfiles->setEnabled(true);
    }
}

void GMT_pssac::on_use_list_clicked()
{
    if ( ui->use_list->isChecked()){
        ui->use_sac->setChecked(false);
        ui->choose_sac->setEnabled(false);
        ui->sacfiles->setEnabled(false);
        ui->choose_list->setEnabled(true);
        ui->saclist->setEnabled(true);
    }
}

void GMT_pssac::on_choose_sac_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this,tr("选择SAC文件（可多选）"));
    ui->sacfiles->clear();
    for (int i = 0; i < files.size(); ++i){
        ui->sacfiles->addItem(files.at(i));
    }
}

void GMT_pssac::on_choose_list_clicked()
{
    filename_list = QFileDialog::getOpenFileName(this,
            tr("选择SAC文件列表，每行包含一个SAC文件名及其对应的控制参数。"));
    if (filename_list.isEmpty())
        return;
    QFile *file=new QFile;
    file->setFileName(filename_list);
    file->open(QIODevice::ReadOnly);
    QTextStream in(file);
    ui->saclist->setText(in.readAll());
    file->close();
    delete file;
}

void GMT_pssac::on_W_pen_color_clicked()
{
    QColor tmpcolor = QColorDialog::getColor(W_pen_color, this,
                                             "选择波形的颜色",
                                             QColorDialog::ShowAlphaChannel);
    if (tmpcolor.isValid()){
        W_pen_color = tmpcolor;
        ui->W_pen_color->setStyleSheet(QString("color: %1").arg(W_pen_color.name()));
    }
}

void GMT_pssac::on_bexit_clicked()
{
    gmt_cmd = ""; // 清空
    // 关闭窗口
    delete J_option;
    delete R_option;
    this->close();
}

void GMT_pssac::on_bok_clicked()
{
    if ( ui->use_sac->isChecked()){
        if ( ui->sacfiles->count() == 0 ){
            QMessageBox msgBox;
            msgBox.setText("必须选择SAC文件");
            msgBox.exec();
            return;
        }
    }
    if ( ui->use_list->isChecked() ){
        if ( ui->saclist->toPlainText().isEmpty() ){
            QMessageBox msgBox;
            msgBox.setText("SAC文件列表必须有内容");
            msgBox.exec();
            return;
        }
    }

    gmt_cmd = "gmt pssac -O -K ";
    gmt_cmd += J_option->sendData()+" ";
    gmt_cmd += R_option->sendData()+" ";

    if ( ui->use_sac->isChecked() ){
        for(int i = 0; i < ui->sacfiles->count(); i++){
            gmt_cmd += ui->sacfiles->item(i)->text()+" ";
        }
    }else{
        gmt_cmd += filename_list+" ";
    }

    if (!ui->c1->text().isEmpty() && !ui->c2->text().isEmpty()){
        gmt_cmd += "-C"+ui->c1->text()+"/"+ui->c2->text()+" ";
    }

    if (!ui->d1->text().isEmpty()){
        gmt_cmd += "-C"+ui->d1->text();
        if (!ui->d2->text().isEmpty()){
            gmt_cmd += "/"+ui->d2->text();
        }
        gmt_cmd += " ";
    }

    if (!ui->e->text().isEmpty()){
        gmt_cmd += "-E"+ui->e->text()+" ";
    }

    if (!ui->W_pen_w->text().isEmpty()){
        gmt_cmd += "-W"+ui->W_pen_w->text()+",";
        gmt_cmd += QString::number(W_pen_color.red())+"/"+QString::number(W_pen_color.green())+"/"+QString::number(W_pen_color.blue())+" ";
    }

    gmt_cmd += ui->other_options->text()+" ";

    gmt_cmd += ">> "+psfname;

    // 关闭窗口
    delete J_option;
    delete R_option;
    this->close();
}
