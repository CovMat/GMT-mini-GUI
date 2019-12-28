#ifndef GMT_PSCOAST_H
#define GMT_PSCOAST_H

#include <QDialog>

namespace Ui {
class GMT_pscoast;
}

class GMT_pscoast : public QDialog
{
    Q_OBJECT

public:
    explicit GMT_pscoast(QWidget *parent = nullptr);
    ~GMT_pscoast();

private:
    Ui::GMT_pscoast *ui;
};

#endif // GMT_PSCOAST_H
