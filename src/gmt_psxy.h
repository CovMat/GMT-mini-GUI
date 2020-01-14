#ifndef GMT_PSXY_H
#define GMT_PSXY_H

#include <QDialog>
#include <QColorDialog>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMessageBox> //显示提示信息
#include <iostream>
#include <fstream>
#include <QProcess>
#include <QTextStream>

#define WIDTH_init_psxy 1000
#define HEIGHT_init_psxy 600
#define W_PREVIEW_init_psxy 531
#define H_PREVIEW_init_psxy 571

namespace Ui {
class GMT_psxy;
}

class GMT_psxy : public QDialog
{
    Q_OBJECT

public:
    explicit GMT_psxy(QWidget *parent,QString S, float wi, float hi); // 传入参数
    ~GMT_psxy();
    QString send_gmt_cmd(){return gmt_cmd;} // 定义函数，用于向主窗体返回GMT命令字符串
    void mousePressEvent(QMouseEvent *event); // 鼠标按下事件
    void resizeEvent(QResizeEvent *event); // 窗口大小改变事件，重新显示预览图片

private slots:
    void on_g_color_clicked();

    void on_draw_symbol_clicked();

    void on_draw_line_clicked();

    void on_W_pen_color_clicked();

    void on_b_datafile_clicked();

    void on_bexit_clicked();

    void on_bok_clicked();

    void on_L_option_stateChanged();

    void on_use_input_clicked();

    void on_use_mouse_clicked();

    void on_use_file_clicked();

    void on_use_G_stateChanged();

    void on_use_W_stateChanged();

private:
    void display_preview(); // 显示预览。

private:
    Ui::GMT_psxy *ui;
    QString psfname;
    float image_w;
    float image_h;
    QString gmt_cmd; // 向主窗体返回的变量，生成的GMT命令字符串
    QColor g_color; //记录G颜色
    QColor W_pen_color; //记录线颜色
};

#endif // GMT_PSXY_H
