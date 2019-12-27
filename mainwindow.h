#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "new_ps_file.h" // 引用类的声明，所引用的是新建ps文件窗口的类
#include "waiting_thread.h" // 引用类的声明，用于弹出等待线程运行的窗口

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void run_gmt_cmd(QString); // 用于运行GMT命令的函数

private slots:
    void on_new_PS_file_clicked();

private:
    Ui::MainWindow *ui;
    new_ps_file *new_ps_file_ui; //创建类的指针
    waiting_thread *waiting_thread_ui;
};
#endif // MAINWINDOW_H
