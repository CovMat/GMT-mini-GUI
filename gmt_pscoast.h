#ifndef GMT_PSCOAST_H
#define GMT_PSCOAST_H

#include <QDialog>
#include <QColorDialog>

#include "gmt_j_option.h"
#include "gmt_r_option.h"
#include "gmt_b_option.h"

namespace Ui {
class GMT_pscoast;
}

class GMT_pscoast : public QDialog
{
    Q_OBJECT

public:
    explicit GMT_pscoast(QWidget *parent = nullptr);
    ~GMT_pscoast();

private slots:
    void on_sea_color_clicked();

private:
    Ui::GMT_pscoast *ui;
    GMT_J_option * J_option;
    GMT_R_option * R_option;
    GMT_B_option * B_option;
    QColor sea_color;//记录初始海洋颜色
    QColor sea_selectedColor;//记录按OK键后选中的颜色
};

#endif // GMT_PSCOAST_H
