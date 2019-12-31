#ifndef GMT_PSXY_H
#define GMT_PSXY_H

#include <QDialog>
#include <QColorDialog>

#include "gmt_j_option.h"
#include "gmt_r_option.h"

namespace Ui {
class GMT_psxy;
}

class GMT_psxy : public QDialog
{
    Q_OBJECT

public:
    explicit GMT_psxy(QWidget *parent,QString S); // 传入参数
    ~GMT_psxy();
    QString send_gmt_cmd(){return gmt_cmd;} // 定义函数，用于向主窗体返回GMT命令字符串

private slots:
    void on_g_color_clicked();

    void on_draw_symbol_clicked();

    void on_draw_line_clicked();

    void on_W_pen_color_clicked();

    void on_b_datafile_clicked();

    void on_bexit_clicked();

    void on_bok_clicked();

private:
    Ui::GMT_psxy *ui;
    QString psfname;
    QString gmt_cmd; // 向主窗体返回的变量，生成的GMT命令字符串
    GMT_J_option * J_option;
    GMT_R_option * R_option;
    QColor g_color; //记录G颜色
    QColor W_pen_color; //记录线颜色
};

#endif // GMT_PSXY_H
