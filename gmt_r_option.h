#ifndef GMT_R_OPTION_H
#define GMT_R_OPTION_H

#include <QWidget>
#include <QDesktopServices>
#include <QUrl>

namespace Ui {
class GMT_R_option;
}

class GMT_R_option : public QWidget
{
    Q_OBJECT

public:
    explicit GMT_R_option(QWidget *parent = nullptr);
    ~GMT_R_option();
    QString sendData();

private slots:
    void on_open_url_clicked();

private:
    Ui::GMT_R_option *ui;
};

#endif // GMT_R_OPTION_H
