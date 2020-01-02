#ifndef RUN_GMT_CMD_H
#define RUN_GMT_CMD_H

// Run_GMT_CMD_thread 以多线程方式启动GMT进行绘图

#include <QObject>
#include <QString>

class Run_GMT_CMD : public QObject
{
    Q_OBJECT
public:
    explicit Run_GMT_CMD(QString S);  // 构造函数, 向本线程传入 QString S。 注意不能定义父对象

public slots:
    void dowork(); // 工作代码。这部分代码在新线程中运行

signals:
    void close_ready(); // 自定义信号，代码运行结束后发出，表示线程准备结束。

private:
    QString cmd; // 传入参数，准备执行的GMT命令
};


#endif // RUN_GMT_CMD_H
