#ifndef RUN_GMT_CMD_THREAD_H
#define RUN_GMT_CMD_THREAD_H

#include <QThread>
#include <QString>

class Run_GMT_CMD_thread : public QThread
{
    Q_OBJECT
public:
    explicit Run_GMT_CMD_thread(QObject *parent = nullptr);
    void run();
    void setarg(QString a){ cmd = a; }
signals:
private:
    QString cmd;
};


#endif // RUN_GMT_CMD_THREAD_H
