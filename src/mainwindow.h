#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <iostream>
#include <fstream>
#include <QColor>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QMainWindow>
#include <QString>
#include <QPixmap> //用来显示图片
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox> //显示提示信息
#include "new_ps_file.h" // 引用类的声明，所引用的是新建ps文件窗口的类
#include "waiting_thread.h" // 引用类的声明，用于弹出等待线程运行的窗口
#include "gmt_pscoast.h"
#include "gmt_psbasemap.h"
#include "gmt_psxy.h"
#include "gmt_pssac.h"
#include "gmt_pstext.h"
#include "gmt_set.h"
#include "gmt_custom.h"
#include "check_gmt_version.h"

#define MAP_FRAME_TYPE_default "fancy"
#define MAP_FRAME_WIDTH_default "5p"
#define MAP_FRAME_PEN_default "thicker,black"
#define MAP_TICK_LENGTH_PRIMARY_default "5p/2.5p"
#define MAP_ANNOT_OFFSET_PRIMARY_default "5p"
#define MAP_LABEL_OFFSET_default "8p"
#define FONT_ANNOT_PRIMARY_default "12p,Helvetica,black"
#define FONT_LABEL_default "16p,Helvetica,black"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_new_PS_file_clicked();

    void on_pscoast_clicked();

    void on_endps_clicked();

    void on_undo_clicked();

    void on_redo_clicked();

    void on_undo_confirm_clicked();

    void on_psbasemap_clicked();

    void on_export_ps_clicked();

    void on_export_cmd_clicked();

    void on_psxy_clicked();

    void on_pssac_clicked();

    void on_pstext_clicked();

    void on_pushButton_clicked();

    void on_gmtset_clicked();

    void on_custom_clicked();

private:
    void set_gmt_button_enable(bool); // 用于设置各个gmt绘图按钮是否有效
    void convert2png(); // 用于生成png文件进行预览
    void display_preview(); // 显示预览

private:
    Ui::MainWindow *ui;
    QString psfname; // ps文件文件名
    int cmd_num; // 记录当前的命令数目
    float image_w; // 记录图片的大小
    float image_h;
    QString MAP_FRAME_TYPE,
            MAP_FRAME_WIDTH,
            MAP_FRAME_PEN,
            MAP_TICK_LENGTH_PRIMARY,
            MAP_ANNOT_OFFSET_PRIMARY,
            MAP_LABEL_OFFSET,
            FONT_ANNOT_PRIMARY,
            FONT_LABEL;

};
#endif // MAINWINDOW_H
