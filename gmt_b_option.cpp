#include "gmt_b_option.h"
#include "ui_gmt_b_option.h"

GMT_B_option::GMT_B_option(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GMT_B_option)
{
    ui->setupUi(this);

    this->setTabOrder(ui->all_axes,ui->annotation);
}

GMT_B_option::~GMT_B_option()
{
    delete ui;
}

void GMT_B_option::on_all_axes_stateChanged(int arg1)
{
    bool flag = true;
    if (arg1 == 2)
        flag = false;
    ui->w_axes->setEnabled(flag);
    ui->s_axes->setEnabled(flag);
    ui->e_axes->setEnabled(flag);
    ui->n_axes->setEnabled(flag);
    ui->annotation_w->setEnabled(flag);
    ui->annotation_s->setEnabled(flag);
    ui->annotation_n->setEnabled(flag);
    ui->annotation_e->setEnabled(flag);
    ui->a_stride_w->setEnabled(flag);
    ui->a_stride_s->setEnabled(flag);
    ui->a_stride_n->setEnabled(flag);
    ui->a_stride_e->setEnabled(flag);
    ui->frame_w->setEnabled(flag);
    ui->frame_s->setEnabled(flag);
    ui->frame_n->setEnabled(flag);
    ui->frame_e->setEnabled(flag);
    ui->f_stride_w->setEnabled(flag);
    ui->f_stride_e->setEnabled(flag);
    ui->f_stride_s->setEnabled(flag);
    ui->f_stride_n->setEnabled(flag);
    ui->grid_w->setEnabled(flag);
    ui->grid_s->setEnabled(flag);
    ui->grid_e->setEnabled(flag);
    ui->grid_n->setEnabled(flag);
    ui->g_stride_w->setEnabled(flag);
    ui->g_stride_s->setEnabled(flag);
    ui->g_stride_e->setEnabled(flag);
    ui->g_stride_n->setEnabled(flag);

    ui->annotation->setEnabled(!flag);
    ui->frame->setEnabled(!flag);
    ui->grid->setEnabled(!flag);
    ui->a_stride->setEnabled(!flag);
    ui->f_stride->setEnabled(!flag);
    ui->g_stride->setEnabled(!flag);

    if (ui->all_axes->isChecked()){
        ui->w_axes->setChecked(true);
        ui->s_axes->setChecked(true);
        ui->n_axes->setChecked(true);
        ui->e_axes->setChecked(true);
        ui->annotation_w->setChecked(ui->annotation->isChecked());
        ui->annotation_s->setChecked(ui->annotation->isChecked());
        ui->annotation_n->setChecked(ui->annotation->isChecked());
        ui->annotation_e->setChecked(ui->annotation->isChecked());
        ui->frame_w->setChecked(ui->frame->isChecked());
        ui->frame_s->setChecked(ui->frame->isChecked());
        ui->frame_n->setChecked(ui->frame->isChecked());
        ui->frame_e->setChecked(ui->frame->isChecked());
        ui->grid_w->setChecked(ui->grid->isChecked());
        ui->grid_s->setChecked(ui->grid->isChecked());
        ui->grid_n->setChecked(ui->grid->isChecked());
        ui->grid_e->setChecked(ui->grid->isChecked());
        ui->a_stride_w->setText(ui->a_stride->text());
        ui->a_stride_s->setText(ui->a_stride->text());
        ui->a_stride_n->setText(ui->a_stride->text());
        ui->a_stride_e->setText(ui->a_stride->text());
        ui->f_stride_w->setText(ui->f_stride->text());
        ui->f_stride_s->setText(ui->f_stride->text());
        ui->f_stride_n->setText(ui->f_stride->text());
        ui->f_stride_e->setText(ui->f_stride->text());
        ui->g_stride_w->setText(ui->g_stride->text());
        ui->g_stride_s->setText(ui->g_stride->text());
        ui->g_stride_n->setText(ui->g_stride->text());
        ui->g_stride_e->setText(ui->g_stride->text());
    }else{

    }
}

void GMT_B_option::on_annotation_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->a_stride->setText("0");
    }else{
        ui->a_stride->clear();
    }
}

void GMT_B_option::on_frame_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->f_stride->setText("0");
    }else{
        ui->f_stride->clear();
    }
}

void GMT_B_option::on_grid_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->g_stride->setText("0");
    }else{
        ui->g_stride->clear();
    }
}

void GMT_B_option::on_annotation_w_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->a_stride_w->setText("0");
    }else{
        ui->a_stride_w->clear();
    }
}

void GMT_B_option::on_frame_w_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->f_stride_w->setText("0");
    }else{
        ui->f_stride_w->clear();
    }
}

void GMT_B_option::on_grid_w_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->g_stride_w->setText("0");
    }else{
        ui->g_stride_w->clear();
    }
}

void GMT_B_option::on_annotation_s_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->a_stride_s->setText("0");
    }else{
        ui->a_stride_s->clear();
    }
}

void GMT_B_option::on_frame_s_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->f_stride_s->setText("0");
    }else{
        ui->f_stride_s->clear();
    }
}

void GMT_B_option::on_grid_s_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->g_stride_s->setText("0");
    }else{
        ui->g_stride_s->clear();
    }
}

void GMT_B_option::on_annotation_e_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->a_stride_e->setText("0");
    }else{
        ui->a_stride_e->clear();
    }
}

void GMT_B_option::on_frame_e_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->f_stride_e->setText("0");
    }else{
        ui->f_stride_e->clear();
    }
}

void GMT_B_option::on_grid_e_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->g_stride_e->setText("0");
    }else{
        ui->g_stride_e->clear();
    }
}

void GMT_B_option::on_annotation_n_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->a_stride_n->setText("0");
    }else{
        ui->a_stride_n->clear();
    }
}

void GMT_B_option::on_frame_n_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->f_stride_n->setText("0");
    }else{
        ui->f_stride_n->clear();
    }
}

void GMT_B_option::on_grid_n_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->g_stride_n->setText("0");
    }else{
        ui->g_stride_n->clear();
    }
}

void GMT_B_option::on_all_disable_stateChanged(int arg1)
{
    bool flag = true;
    if (arg1 == 2)
        flag = false;
    ui->all_axes->setEnabled(flag);
    ui->annotation->setEnabled(flag);
    ui->frame->setEnabled(flag);
    ui->grid->setEnabled(flag);
    ui->a_stride->setEnabled(flag);
    ui->f_stride->setEnabled(flag);
    ui->g_stride->setEnabled(flag);
    ui->w_axes->setEnabled(flag);
    ui->s_axes->setEnabled(flag);
    ui->e_axes->setEnabled(flag);
    ui->n_axes->setEnabled(flag);
    ui->annotation_w->setEnabled(flag);
    ui->annotation_s->setEnabled(flag);
    ui->annotation_n->setEnabled(flag);
    ui->annotation_e->setEnabled(flag);
    ui->a_stride_w->setEnabled(flag);
    ui->a_stride_s->setEnabled(flag);
    ui->a_stride_n->setEnabled(flag);
    ui->a_stride_e->setEnabled(flag);
    ui->frame_w->setEnabled(flag);
    ui->frame_s->setEnabled(flag);
    ui->frame_n->setEnabled(flag);
    ui->frame_e->setEnabled(flag);
    ui->f_stride_w->setEnabled(flag);
    ui->f_stride_e->setEnabled(flag);
    ui->f_stride_s->setEnabled(flag);
    ui->f_stride_n->setEnabled(flag);
    ui->grid_w->setEnabled(flag);
    ui->grid_s->setEnabled(flag);
    ui->grid_e->setEnabled(flag);
    ui->grid_n->setEnabled(flag);
    ui->g_stride_w->setEnabled(flag);
    ui->g_stride_s->setEnabled(flag);
    ui->g_stride_e->setEnabled(flag);
    ui->g_stride_n->setEnabled(flag);

    if (arg1 ==2) return;

    int cc;
    if (ui->all_axes->isChecked()){
        cc = 2;
    }else{
        cc = 0;
    }
    GMT_B_option::on_all_axes_stateChanged(cc);
}
