#ifndef NEW_PS_FILE_H
#define NEW_PS_FILE_H

#include <QDialog>
#include <QString>

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

private:
    Ui::new_ps_file *ui;
    QString gmt_cmd; // 向主窗体返回的变量，生成的GMT命令字符串
    QString psfilename; // 向主窗体返回ps文件的文件名
    QString w;
    QString h;
};

#endif // NEW_PS_FILE_H
