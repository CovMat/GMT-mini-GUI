#ifndef GMT_CUSTOM_H
#define GMT_CUSTOM_H

#include <QDialog>
#include <QMessageBox> //显示提示信息

namespace Ui {
class GMT_custom;
}

class GMT_custom : public QDialog
{
    Q_OBJECT

public:
    explicit GMT_custom(QWidget *parent = nullptr);
    ~GMT_custom();
    QString send_gmt_cmd(){return gmt_cmd;} // 定义函数，用于向主窗体返回GMT命令字符串

private slots:
    void on_bexit_clicked();

    void on_bok_clicked();

private:
    Ui::GMT_custom *ui;
    QString gmt_cmd; // 向主窗体返回的变量，生成的GMT命令字符串
};

#endif // GMT_CUSTOM_H
