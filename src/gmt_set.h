#ifndef GMT_SET_H
#define GMT_SET_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <vector>

namespace Ui {
class GMT_set;
}

class GMT_set : public QDialog
{
    Q_OBJECT

public:
    explicit GMT_set(QWidget *parent,
                     QString a1,
                     QString a2,
                     QString a3,
                     QString a4,
                     QString a5,
                     QString a6,
                     QString a7,
                     QString a8);
    ~GMT_set();
    QString send_gmt_cmd(){return gmt_cmd;} // 定义函数，用于向主窗体返回GMT命令字符串
    QVariant send_data(){return data_package;}

private slots:
    void on_bexit_clicked();

    void on_bok_clicked();

private:
    Ui::GMT_set *ui;
    QString MAP_FRAME_TYPE,
            MAP_FRAME_WIDTH,
            MAP_FRAME_PEN,
            MAP_TICK_LENGTH_PRIMARY,
            MAP_ANNOT_OFFSET_PRIMARY,
            MAP_LABEL_OFFSET,
            FONT_ANNOT_PRIMARY,
            FONT_LABEL;
    QString gmt_cmd; // 向主窗体返回的变量，生成的GMT命令字符串
    QVariant data_package;
};

#endif // GMT_SET_H
