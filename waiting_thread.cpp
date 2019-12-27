#include "waiting_thread.h"
#include "ui_waiting_thread.h"

waiting_thread::waiting_thread(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::waiting_thread)
{
    ui->setupUi(this);
}

waiting_thread::~waiting_thread()
{
    delete ui;
}
