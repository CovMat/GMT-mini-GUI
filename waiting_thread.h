#ifndef WAITING_THREAD_H
#define WAITING_THREAD_H

#include <QDialog>

namespace Ui {
class waiting_thread;
}

class waiting_thread : public QDialog
{
    Q_OBJECT

public:
    explicit waiting_thread(QWidget *parent = nullptr);
    ~waiting_thread();

private:
    Ui::waiting_thread *ui;
};

#endif // WAITING_THREAD_H
