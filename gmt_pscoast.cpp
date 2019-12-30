#include "gmt_pscoast.h"
#include "ui_gmt_pscoast.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

GMT_pscoast::GMT_pscoast(QWidget *parent,QString S) : //传入参数
    QDialog(parent,Qt::WindowTitleHint | Qt::CustomizeWindowHint), // 隐藏关闭按钮和帮助按钮
    psfname(S), // 传入参数赋值给ps文件名
    ui(new Ui::GMT_pscoast)
{
    ui->setupUi(this);
    //setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); // 去除问号帮助按钮

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

    sea_color.setRgb(21,185,255);
    ui->sea_color->setStyleSheet(QString("background-color: %1").arg(sea_color.name()));
    dry_color.setRgb(255,236,196);
    ui->dry_color->setStyleSheet(QString("background-color: %1").arg(dry_color.name()));
    W_pen_color.setRgb(0,0,0);
    ui->W_pen_color->setStyleSheet(QString("color: %1").arg(W_pen_color.name()));

    /*
    QVBoxLayout *vlayout = new QVBoxLayout(); // 新建垂直布局
    vlayout->addWidget(J_option); // 垂直布局中添加-J选项
    vlayout->addWidget(R_option);

    QHBoxLayout *bomLayout = new QHBoxLayout;
    QPushButton *btn_ok = new QPushButton(QWidget::tr("OK"), this);
    btn_ok->setDefault(true);
    QPushButton *btn_cancel = new QPushButton(QWidget::tr("Cancel"), this);
    bomLayout->addStretch();
    bomLayout->addWidget(btn_ok);
    bomLayout->addStretch();
    bomLayout->addWidget(btn_cancel);
    bomLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(vlayout);
    mainLayout->addLayout(bomLayout);

    this->setLayout(mainLayout);
    //this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    */
}

GMT_pscoast::~GMT_pscoast()
{
    delete ui;
}

void GMT_pscoast::on_sea_color_clicked()
{
    QColor tmpcolor = QColorDialog::getColor(sea_color, this,
                                             "选择水系（海洋与湖泊）的颜色",
                                             QColorDialog::ShowAlphaChannel);
    if (tmpcolor.isValid()){
        sea_color = tmpcolor;
        ui->sea_color->setStyleSheet(QString("background-color: %1").arg(sea_color.name()));
    }
}

void GMT_pscoast::on_dry_color_clicked()
{
    QColor tmpcolor = QColorDialog::getColor(dry_color, this,
                                             "选择陆地的颜色",
                                             QColorDialog::ShowAlphaChannel);
    if (tmpcolor.isValid()){
        dry_color = tmpcolor;
        ui->dry_color->setStyleSheet(QString("background-color: %1").arg(dry_color.name()));
    }
}

void GMT_pscoast::on_W_pen_color_clicked()
{
    QColor tmpcolor = QColorDialog::getColor(W_pen_color, this,
                                             "选择海岸线的颜色",
                                             QColorDialog::ShowAlphaChannel);
    if (tmpcolor.isValid()){
        W_pen_color = tmpcolor;
        ui->W_pen_color->setStyleSheet(QString("color: %1").arg(W_pen_color.name()));
    }
}

void GMT_pscoast::on_bok_clicked()
{

    gmt_cmd = "gmt pscoast -O -K ";
    gmt_cmd += J_option->sendData()+" ";
    gmt_cmd += R_option->sendData()+" ";
    gmt_cmd += B_option->sendData()+" ";

    if (!ui->A_option->text().isEmpty())
        gmt_cmd += "-A"+ui->A_option->text()+" ";

    gmt_cmd += "-S"+QString::number(sea_color.red())+"/"+QString::number(sea_color.green())+"/"+QString::number(sea_color.blue())+" ";
    gmt_cmd += "-G"+QString::number(dry_color.red())+"/"+QString::number(dry_color.green())+"/"+QString::number(dry_color.blue())+" ";
    gmt_cmd += ui->D_option->currentText().split(' ').at(0)+" ";

    if (!ui->W_pen_w->text().isEmpty()){
        gmt_cmd += "-W"+ui->W_pen_w->text()+",";
        gmt_cmd += QString::number(W_pen_color.red())+"/"+QString::number(W_pen_color.green())+"/"+QString::number(W_pen_color.blue())+" ";
    }

    gmt_cmd += ui->other_options->text()+" ";

    gmt_cmd += ">> "+psfname;

    // 关闭窗口
    this->close();
}

void GMT_pscoast::on_bexit_clicked()
{
    gmt_cmd = ""; // 清空
    // 关闭窗口
    this->close();
}
