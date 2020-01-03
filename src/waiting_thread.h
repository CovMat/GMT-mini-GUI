#ifndef WAITING_THREAD_H
#define WAITING_THREAD_H

#include <QDialog>
#include <QThread>
#include <QTimer>
#include "Run_GMT_CMD.h" // 在本窗口中启动新线程，运行Run_GMT_CMD的代码

namespace Ui {
class waiting_thread;
}

class waiting_thread : public QDialog
{
    Q_OBJECT

public:
    explicit waiting_thread(QWidget *parent,QString S);  // 构造函数, 由主窗口向本窗口传入 QString S
    ~waiting_thread();
    int send_exit_code(){return exit_code;} // 定义函数，用于返回退出码

private slots:
    void normally_exit();
    void on_stop_thread_clicked();
    void updateUI();

private:
    Ui::waiting_thread *ui;
    QString cmd; // 主窗口传入的参数赋值给cmd
    int exit_code; // 向主窗口返回的变量，0代表正常运行退出，1代表异常终止
    QThread * firstThread; // 线程
    Run_GMT_CMD *t;        // 工作代码
};

#endif // WAITING_THREAD_H
