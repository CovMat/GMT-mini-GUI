#ifndef GMT_B_OPTION_H
#define GMT_B_OPTION_H

#include <QWidget>

namespace Ui {
class GMT_B_option;
}

class GMT_B_option : public QWidget
{
    Q_OBJECT

public:
    explicit GMT_B_option(QWidget *parent = nullptr);
    ~GMT_B_option();
    QString sendData(); // 向父窗口返回参数字符串

private slots:
    void on_all_axes_stateChanged(int arg1);

    void on_annotation_stateChanged(int arg1);

    void on_frame_stateChanged(int arg1);

    void on_grid_stateChanged(int arg1);

    void on_annotation_w_stateChanged(int arg1);

    void on_frame_w_stateChanged(int arg1);

    void on_grid_w_stateChanged(int arg1);

    void on_annotation_s_stateChanged(int arg1);

    void on_frame_s_stateChanged(int arg1);

    void on_grid_s_stateChanged(int arg1);

    void on_all_disable_stateChanged(int arg1);

private:
    Ui::GMT_B_option *ui;
};

#endif // GMT_B_OPTION_H
