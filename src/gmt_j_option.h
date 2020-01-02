#ifndef GMT_J_OPTION_H
#define GMT_J_OPTION_H

#include <QWidget>

namespace Ui {
class GMT_J_option;
}

class GMT_J_option : public QWidget
{
    Q_OBJECT

public:
    explicit GMT_J_option(QWidget *parent = nullptr);
    ~GMT_J_option();
    QString sendData(); // 向父窗口返回参数字符串

private slots:
    void on_J_option_currentIndexChanged(int index);

private:
    Ui::GMT_J_option *ui;
};

#endif // GMT_J_OPTION_H
