#ifndef GMT_PSTEXT_H
#define GMT_PSTEXT_H

#include <QDialog>
#include <QPixmap>
#include <QMouseEvent>
#include <QUrl>
#include <QDesktopServices>
#include <QColorDialog>

namespace Ui {
class GMT_pstext;
}

class GMT_pstext : public QDialog
{
    Q_OBJECT

public:
    explicit GMT_pstext(QWidget *parent,QString S,int tw, int th, float wi, float hi); // 传入参数
    ~GMT_pstext();
    QString send_gmt_cmd(){return gmt_cmd;} // 定义函数，用于向主窗体返回GMT命令字符串
    void mousePressEvent(QMouseEvent *event); // 鼠标按下事件

private slots:
    void on_checkfont_clicked();

    void on_check_justify_clicked();

    void on_text_color_clicked();

    void on_bexit_clicked();

    void on_bok_clicked();

private:
    Ui::GMT_pstext *ui;
    QString psfname;
    int w;
    int h;
    float image_w;
    float image_h;
    QString gmt_cmd; // 向主窗体返回的变量，生成的GMT命令字符串
    QColor text_color; // 记录文字颜色
};

#endif // GMT_PSTEXT_H
