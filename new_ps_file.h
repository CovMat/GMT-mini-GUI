#ifndef NEW_PS_FILE_H
#define NEW_PS_FILE_H

#include <QDialog>
#include <QString>

namespace Ui {
class new_ps_file;
}

class new_ps_file : public QDialog
{
    Q_OBJECT

public:
    explicit new_ps_file(QWidget *parent = nullptr);
    ~new_ps_file();

private slots:
    void on_ok_button_clicked();

private:
    Ui::new_ps_file *ui;

// 定义对话框需要返回的变量以及取变量的函数
private:
    QString gmt_cmd;
public:
    QString send_gmt_cmd(){return gmt_cmd;}

};

#endif // NEW_PS_FILE_H
