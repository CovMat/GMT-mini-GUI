#ifndef GMT_PSBASEMAP_H
#define GMT_PSBASEMAP_H

#include <QDialog>

#include "gmt_j_option.h"
#include "gmt_r_option.h"
#include "gmt_b_option.h"

namespace Ui {
class GMT_psbasemap;
}

class GMT_psbasemap : public QDialog
{
    Q_OBJECT

public:
    explicit GMT_psbasemap(QWidget *parent,QString S); // 传入参数
    ~GMT_psbasemap();
    QString send_gmt_cmd(){return gmt_cmd;} // 定义函数，用于向主窗体返回GMT命令字符串

private slots:
    void on_bexit_clicked();

    void on_bok_clicked();

private:
    Ui::GMT_psbasemap *ui;
    QString psfname;
    QString gmt_cmd; // 向主窗体返回的变量，生成的GMT命令字符串
    GMT_J_option * J_option;
    GMT_R_option * R_option;
    GMT_B_option * B_option;
};

#endif // GMT_PSBASEMAP_H
