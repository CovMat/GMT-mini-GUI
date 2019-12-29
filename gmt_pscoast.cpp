#include "gmt_pscoast.h"
#include "ui_gmt_pscoast.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

GMT_pscoast::GMT_pscoast(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GMT_pscoast)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); // 去除问号帮助按钮

    J_option = new GMT_J_option(this); // 添加-J选项
    J_option->show();
    R_option = new GMT_R_option(this); // 添加-R选项
    R_option->show();
    B_option = new GMT_B_option(this); // 添加-B选项
    B_option->show();

    ui->J_Layout->addWidget(J_option);
    ui->R_Layout->addWidget(R_option);
    ui->B_Layout->addWidget(B_option);

    /*
    QVBoxLayout *vlayout = new QVBoxLayout(); // 新建垂直布局
    vlayout->addWidget(J_option); // 垂直布局中添加-J选项
    vlayout->addWidget(R_option);

    QHBoxLayout *bomLayout = new QHBoxLayout;
    QPushButton *btn_ok = new QPushButton(QWidget::tr("OK"), this);
    btn_ok->setDefault(true);
    QPushButton *btn_cancel = new QPushButton(QWidget::tr("Cancel"), this);
    bomLayout->addStretch();
    bomLayout->addWidget(btn_ok);
    bomLayout->addStretch();
    bomLayout->addWidget(btn_cancel);
    bomLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(vlayout);
    mainLayout->addLayout(bomLayout);

    this->setLayout(mainLayout);
    //this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    */
}

GMT_pscoast::~GMT_pscoast()
{
    delete ui;
}

void GMT_pscoast::on_sea_color_clicked()
{
    QColorDialog *m_pColor = new QColorDialog(this);
    m_pColor->show();
}
