#include "gmt_j_option.h"
#include "ui_gmt_j_option.h"
#include <QSizePolicy>

GMT_J_option::GMT_J_option(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GMT_J_option)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint); // 隐藏边框，便于嵌入pscoast， psbasemap等窗体
    hide();

    ui->paras->setPlaceholderText("参数与前一条命令相同");
    ui->paras->setFocusPolicy(Qt::NoFocus); // 不可获得焦点，禁止编辑

    ui->J_option->addItem("-J [空]与前一条命令相同");
    ui->J_option->addItem("-JM Mercator投影");
    ui->J_option->addItem("-JX 笛卡尔坐标投影");
    ui->J_option->addItem("-JA Lambert方位等面积投影");
    ui->J_option->addItem("-JB Albers圆锥等面积投影");
    ui->J_option->addItem("-JC Cassini圆柱投影");
    ui->J_option->addItem("-JCyl_stere 圆柱立体投影");
    ui->J_option->addItem("-JD 等距圆锥投影");
    ui->J_option->addItem("-JE 方位等距投影");
    ui->J_option->addItem("-JF 球心方位投影");
    ui->J_option->addItem("-JG 正交投影");
    ui->J_option->addItem("-JH 等面积Hammer投影");
    ui->J_option->addItem("-JI 正弦曲线投影");
    ui->J_option->addItem("-JJ Miller圆柱投影");
    ui->J_option->addItem("-JK Eckert投影");
    ui->J_option->addItem("-JL Lambert圆锥保角投影");
    ui->J_option->addItem("-JN Robinson投影");
    ui->J_option->addItem("-JQ 圆柱等距投影");
    ui->J_option->addItem("-JR Winkel Tripel投影");
    ui->J_option->addItem("-JS 立体等角投影");
    ui->J_option->addItem("-JT 横向Mercator投影");
    ui->J_option->addItem("-JV Van der Grinten投影");
    ui->J_option->addItem("-JW Mollweide投影");
    ui->J_option->addItem("-JY 圆柱等面积投影");

}

GMT_J_option::~GMT_J_option()
{
    delete ui;
}

void GMT_J_option::on_J_option_currentIndexChanged(int index)
{
    switch (index) {
        case 0:
            ui->paras->clear(); // 清除输入
            ui->paras->setPlaceholderText("参数与前一条命令相同");
            ui->paras->setFocusPolicy(Qt::NoFocus); // 不可获得焦点，禁止编辑
            break;
        case 1: ui->paras->setPlaceholderText("[<lon>[/<lat>]/]<width>"); break;
        case 2: ui->paras->setPlaceholderText("<width>/<height>"); break;
        case 3: ui->paras->setPlaceholderText("<lon>/<lat>/[<distance>/]<width>"); break;
        case 4: ui->paras->setPlaceholderText("<lon>/<lat>/<lat1>/<lat2>/<width>"); break;
        case 5: ui->paras->setPlaceholderText("<lon>/<lat>/<width>"); break;
        case 6: ui->paras->setPlaceholderText("/[<lon>[/<lat>]]/<width>"); break;
        case 7: ui->paras->setPlaceholderText("<lon>/<lat>/<lat1>/<lat2>/<width>"); break;
        case 8: ui->paras->setPlaceholderText("<lon>/<lat>[/<distance>]/<width>"); break;
        case 9: ui->paras->setPlaceholderText("<lon>/<lat>[/<distance>]/<width>"); break;
        case 10: ui->paras->setPlaceholderText("<lon>/<lat>[/<distance>]/<width>"); break;
        case 11: ui->paras->setPlaceholderText("[<lon>/]<width>"); break;
        case 12: ui->paras->setPlaceholderText("[<lon>/]<width>"); break;
        case 13: ui->paras->setPlaceholderText("<lon>/<width>"); break;
        case 14: ui->paras->setPlaceholderText("[f|s][<lon>/]<width>"); break;
        case 15: ui->paras->setPlaceholderText("<lon>/<lat>/<lat1>/<lat2>/<width>"); break;
        case 16: ui->paras->setPlaceholderText("[<lon>/]<width>"); break;
        case 17: ui->paras->setPlaceholderText("[<lon>/[<lat>]/]<width>"); break;
        case 18: ui->paras->setPlaceholderText("[<lon>/]<width>"); break;
        case 19: ui->paras->setPlaceholderText("<lon>/<lat>[/<distance>]/<width>"); break;
        case 20: ui->paras->setPlaceholderText("<lon>[/<lat>]/<width>"); break;
        case 21: ui->paras->setPlaceholderText("<lon>/<width>"); break;
        case 22: ui->paras->setPlaceholderText("[<lon>/]<width>"); break;
        case 23: ui->paras->setPlaceholderText("<lon>/<lat>/<width>"); break;
    }
  if (index > 0)
      ui->paras->setFocusPolicy(Qt::StrongFocus); // 重新获取焦点，允许编辑
}

QString GMT_J_option::sendData(){

    return ui->J_option->currentText().split(' ').at(0)+ui->paras->text();
}
