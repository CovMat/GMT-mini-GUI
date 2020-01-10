#ifndef NEW_PS_FILE_H
#define NEW_PS_FILE_H

#include <QDialog>
#include <QString>
#include "gmt_j_option.h"
#include "gmt_r_option.h"

namespace Ui {
class new_ps_file;
}

class new_ps_file : public QDialog
{
    Q_OBJECT

public:
    explicit new_ps_file(QWidget *parent = nullptr);
    ~new_ps_file();
    QString send_gmt_cmd(){return gmt_cmd;} // 定义函数，用于向主窗体返回GMT命令字符串
    QString send_ps_fname(){return psfilename;} // 定义函数，用于向主窗体返回ps文件名
    QString send_w(){ return w; } // 返回画布大小
    QString send_h(){ return h; }

private slots:
    void on_ok_button_clicked();

    void on_w_input_textEdited();

    void on_h_input_textEdited();

    void on_bexit_clicked();

    void on_w_input_cm_textEdited();

    void on_h_input_cm_textEdited();

    void on_A4_clicked();

private:
    Ui::new_ps_file *ui;
    QString gmt_cmd; // 向主窗体返回的变量，生成的GMT命令字符串
    QString psfilename; // 向主窗体返回ps文件的文件名
    QString w;
    QString h;
    GMT_J_option * J_option;
    GMT_R_option * R_option;
};

#endif // NEW_PS_FILE_H
