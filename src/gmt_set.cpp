#include "gmt_set.h"
#include "ui_gmt_set.h"

using namespace std;
Q_DECLARE_METATYPE(vector<QString>) // 复杂的数据格式，需要Q_DECLARE_METATYPE向Qt元对象系统进行注册

GMT_set::GMT_set(QWidget *parent,
                 QString a1,
                 QString a2,
                 QString a3,
                 QString a4,
                 QString a5,
                 QString a6,
                 QString a7,
                 QString a8) :
    QDialog(parent,Qt::WindowTitleHint | Qt::CustomizeWindowHint), // 隐藏关闭按钮和帮助按钮
    MAP_FRAME_TYPE(a1),
    MAP_FRAME_WIDTH(a2),
    MAP_FRAME_PEN(a3),
    MAP_TICK_LENGTH_PRIMARY(a4),
    MAP_ANNOT_OFFSET_PRIMARY(a5),
    MAP_LABEL_OFFSET(a6),
    FONT_ANNOT_PRIMARY(a7),
    FONT_LABEL(a8),
    ui(new Ui::GMT_set)
{
    ui->setupUi(this);
    this->setWindowTitle("gmtset");

    gmt_cmd = ""; // 清空初始化
    data_package.clear();

    ui->MAP_FRAME_TYPE->setCurrentText(MAP_FRAME_TYPE);
    ui->MAP_FRAME_WIDTH->setText(MAP_FRAME_WIDTH);
    ui->MAP_FRAME_PEN->setText(MAP_FRAME_PEN);
    ui->MAP_TICK_LENGTH_PRIMARY->setText(MAP_TICK_LENGTH_PRIMARY);
    ui->MAP_ANNOT_OFFSET_PRIMARY->setText(MAP_ANNOT_OFFSET_PRIMARY);
    ui->MAP_LABEL_OFFSET->setText(MAP_LABEL_OFFSET);
    ui->FONT_ANNOT_PRIMARY->setText(FONT_ANNOT_PRIMARY);
    ui->FONT_LABEL->setText(FONT_LABEL);
}

GMT_set::~GMT_set()
{
    delete ui;
}

void GMT_set::on_bexit_clicked()
{
    gmt_cmd = ""; // 清空
    // 关闭窗口
    this->close();
}

void GMT_set::on_bok_clicked()
{
    gmt_cmd = "gmt gmtset ";
    gmt_cmd += "MAP_FRAME_TYPE="+ui->MAP_FRAME_TYPE->currentText()+" ";
    gmt_cmd += "MAP_FRAME_WIDTH="+ui->MAP_FRAME_WIDTH->text()+" ";
    gmt_cmd += "MAP_FRAME_PEN="+ui->MAP_FRAME_PEN->text()+" ";
    gmt_cmd += "MAP_TICK_LENGTH_PRIMARY="+ui->MAP_TICK_LENGTH_PRIMARY->text()+" ";
    gmt_cmd += "MAP_ANNOT_OFFSET_PRIMARY="+ui->MAP_ANNOT_OFFSET_PRIMARY->text()+" ";
    gmt_cmd += "MAP_LABEL_OFFSET="+ui->MAP_LABEL_OFFSET->text()+" ";
    gmt_cmd += "FONT_ANNOT_PRIMARY="+ui->FONT_ANNOT_PRIMARY->text()+" ";
    gmt_cmd += "FONT_LABEL="+ui->FONT_LABEL->text()+" ";

    // 封装数据
    vector<QString> list;
    list.push_back(ui->MAP_FRAME_TYPE->currentText());
    list.push_back(ui->MAP_FRAME_WIDTH->text());
    list.push_back(ui->MAP_FRAME_PEN->text());
    list.push_back(ui->MAP_TICK_LENGTH_PRIMARY->text());
    list.push_back(ui->MAP_ANNOT_OFFSET_PRIMARY->text());
    list.push_back(ui->MAP_LABEL_OFFSET->text());
    list.push_back(ui->FONT_ANNOT_PRIMARY->text());
    list.push_back(ui->FONT_LABEL->text());

    data_package.setValue(list); // 进行数据封装

    // 关闭窗口
    this->close();
}
