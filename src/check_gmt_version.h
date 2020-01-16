#ifndef CHECK_GMT_VERSION_H
#define CHECK_GMT_VERSION_H

#include <QDialog>
#include <QProcess>
#include <QRegExp>

namespace Ui {
class check_gmt_version;
}

class check_gmt_version : public QDialog
{
    Q_OBJECT

public:
    explicit check_gmt_version(QWidget *parent = nullptr);
    ~check_gmt_version();
    int send_exit_code(){return exit_code;}

private slots:
    void on_bexit_clicked();

private:
    Ui::check_gmt_version *ui;
    int exit_code; // 退出码，0表示正常退出， 1表示出现错误
};

#endif // CHECK_GMT_VERSION_H
