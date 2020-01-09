#ifndef CHECK_GMT_VERSION_H
#define CHECK_GMT_VERSION_H

#include <QDialog>

namespace Ui {
class check_gmt_version;
}

class check_gmt_version : public QDialog
{
    Q_OBJECT

public:
    explicit check_gmt_version(QWidget *parent = nullptr);
    ~check_gmt_version();

private:
    Ui::check_gmt_version *ui;
};

#endif // CHECK_GMT_VERSION_H
