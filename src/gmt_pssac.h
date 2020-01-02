#ifndef GMT_PSSAC_H
#define GMT_PSSAC_H

#include <QDialog>
#include <QColorDialog>

#include "gmt_j_option.h"
#include "gmt_r_option.h"

namespace Ui {
class GMT_pssac;
}

class GMT_pssac : public QDialog
{
    Q_OBJECT

public:
    explicit GMT_pssac(QWidget *parent,QString S); // 传入参数
    ~GMT_pssac();
    QString send_gmt_cmd(){return gmt_cmd;} // 定义函数，用于向主窗体返回GMT命令字符串

private slots:
    void on_use_sac_clicked();

    void on_use_list_clicked();

    void on_choose_sac_clicked();

    void on_choose_list_clicked();

    void on_W_pen_color_clicked();

    void on_bexit_clicked();

    void on_bok_clicked();

private:
    Ui::GMT_pssac *ui;
    QString psfname;
    QString gmt_cmd; // 向主窗体返回的变量，生成的GMT命令字符串
    GMT_J_option * J_option;
    GMT_R_option * R_option;
    QColor W_pen_color; //记录线颜色
    QString filename_list;
};

#endif // GMT_PSSAC_H
