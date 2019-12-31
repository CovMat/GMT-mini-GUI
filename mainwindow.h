#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPixmap> //用来显示图片
#include "new_ps_file.h" // 引用类的声明，所引用的是新建ps文件窗口的类
#include "waiting_thread.h" // 引用类的声明，用于弹出等待线程运行的窗口
#include "gmt_pscoast.h"
#include "gmt_psbasemap.h"
#include "gmt_psxy.h"
#include "gmt_pssac.h"

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

private:
    void set_gmt_button_enable(bool); // 用于设置各个gmt绘图按钮是否有效
    void convert2png(int); // 用于生成png文件进行预览
    void display_preview(); // 显示预览

private:
    Ui::MainWindow *ui;
    QString psfname; // ps文件文件名
    int cmd_num; // 记录当前的命令数目
    new_ps_file *new_ps_file_ui; //创建类的指针，私有变量，新建画布对话框的类
    waiting_thread *waiting_thread_ui; // 创建类的指针，私有变量，等待GMT绘图线程运行对话框的类
    GMT_pscoast *GMT_pscoast_ui;
    GMT_psbasemap *GMT_psbasemap_ui;
    GMT_psxy *GMT_psxy_ui;
    GMT_pssac *GMT_pssac_ui;
};
#endif // MAINWINDOW_H
