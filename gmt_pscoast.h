#ifndef GMT_PSCOAST_H
#define GMT_PSCOAST_H

#include <QDialog>
#include <QColorDialog>

#include "gmt_j_option.h"
#include "gmt_r_option.h"
#include "gmt_b_option.h"

namespace Ui {
class GMT_pscoast;
}

class GMT_pscoast : public QDialog
{
    Q_OBJECT

public:
    explicit GMT_pscoast(QWidget *parent,QString S); // 传入参数
    ~GMT_pscoast();
    QString send_gmt_cmd(){return gmt_cmd;} // 定义函数，用于向主窗体返回GMT命令字符串

private slots:
    void on_sea_color_clicked();

    void on_dry_color_clicked();

    void on_W_pen_color_clicked();

    void on_bok_clicked();

    void on_bexit_clicked();

private:
    Ui::GMT_pscoast *ui;
    QString psfname;
    QString gmt_cmd; // 向主窗体返回的变量，生成的GMT命令字符串
    GMT_J_option * J_option;
    GMT_R_option * R_option;
    GMT_B_option * B_option;
    QColor sea_color; //记录海洋颜色
    QColor dry_color; //记录陆地颜色
    QColor W_pen_color; //记录海岸线颜色
};
#endif // GMT_PSCOAST_H
