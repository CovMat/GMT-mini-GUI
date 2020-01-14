#ifndef GMT_PSTEXT_H
#define GMT_PSTEXT_H

#include <QDialog>
#include <QPixmap>
#include <QMouseEvent>
#include <QUrl>
#include <QDesktopServices>
#include <QColorDialog>
#include <QProcess>
#include <QMessageBox> //显示提示信息
#include <iostream>
#include <fstream>
#include <QProcess>
#include <QTextStream>
#include <QFileDialog>

#define WIDTH_init_pstext 1000
#define HEIGHT_init_pstext 500
#define W_PREVIEW_init_pstext 531
#define H_PREVIEW_init_pstext 471

namespace Ui {
class GMT_pstext;
}

class GMT_pstext : public QDialog
{
    Q_OBJECT

public:
    explicit GMT_pstext(QWidget *parent,QString S, float wi, float hi); // 传入参数
    ~GMT_pstext();
    QString send_gmt_cmd(){return gmt_cmd;} // 定义函数，用于向主窗体返回GMT命令字符串
    void mousePressEvent(QMouseEvent *event); // 鼠标按下事件
    void resizeEvent(QResizeEvent *event); // 窗口大小改变事件，重新显示预览图片

private slots:
    void on_checkfont_clicked();

    void on_check_justify_clicked();

    void on_text_color_clicked();

    void on_bexit_clicked();

    void on_bok_clicked();

    void on_use_input_clicked();

    void on_use_mouse_clicked();

    void on_use_file_clicked();

    void on_use_file_6_clicked();

    void on_b_datafile_clicked();

private:
    void display_preview(); // 显示预览。

private:
    Ui::GMT_pstext *ui;
    QString psfname;
    float image_w;
    float image_h;
    QString gmt_cmd; // 向主窗体返回的变量，生成的GMT命令字符串
    QColor text_color; // 记录文字颜色
};

#endif // GMT_PSTEXT_H
