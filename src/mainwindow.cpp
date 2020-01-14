#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("GMT-mini-GUI 0.2.0");

    psfname = ""; // 清空初始化ps文件文件名
    cmd_num = 0; // 命令数目清零

    ui->label->setScaledContents(true); // label要设置为自动缩放内容

    // 设置代码区字体
    QFont font1;
    font1.setFamily("Courier");
    font1.setPointSize(12);
    ui->cmd_list->setFont(font1);

    //初始化窗口大小，限制窗口最小尺寸
    this->setMinimumSize(WIDTH_init,HEIGHT_init);
    this->resize(WIDTH_init,HEIGHT_init);

    // 检查GMT版本，检查GMT是否存在
    check_gmt_version * check_GMT = new check_gmt_version;
    check_GMT->exec();
    if (check_GMT->send_exit_code() == 1){
        delete check_GMT;
        // 检查失败，退出程序
        QMetaObject::invokeMethod(this, "close", Qt::QueuedConnection); // 在constructor中关闭自己必须使用这种方法
                                                                        // 主窗口用这种方式似乎有问题，属于异常退出
    }
    delete check_GMT;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::resizeEvent(QResizeEvent *event) // 窗口大小改变事件，重新显示预览图片
{
    QMainWindow::resizeEvent(event);

    // 获取变化后的大小
    int ww = this->width();
    int hh = this->height();

    // 调整代码区大小
    int w_cmd = ui->cmd_list->width();
    int h_cmd = ui->cmd_list->height();
    h_cmd = H_CMD_init + hh - HEIGHT_init; // 垂直方向新增的高度，全部给代码区
    w_cmd = W_CMD_init + round(( ww - WIDTH_init ) / 3); // 水平方向新增的宽度，1/3给代码区
    ui->cmd_list->resize(w_cmd, h_cmd);

    // 调整按钮，标签，预览区的位置
    ui->export_cmd->move(X_export_cmd_init, Y_export_cmd_init +  hh - HEIGHT_init );
    ui->label_3->move( X_label_init + round(( ww - WIDTH_init ) / 3), Y_label_init );
    ui->label->move( X_preview_init + round(( ww - WIDTH_init ) / 3), Y_preview_init );

    // 调整预览区大小
    int w_preview = ui->label->width();
    int h_preview = ui->label->height();
    h_preview = H_PREVIEW_init + hh - HEIGHT_init; // 垂直方向新增的高度，全部给预览区
    w_preview = W_PREVIEW_init + round(( ww - WIDTH_init ) / 3 * 2); // 水平方向新增的宽度，2/3给预览区
    ui->label->resize( w_preview, h_preview );

    if ( cmd_num > 0 )
        display_preview(0); // 有命令执行过的情况下，才重新执行预览，
}


// 自定义函数，用于设置各个GMT绘图按钮是否有效
void MainWindow::set_gmt_button_enable(bool flag){
    ui->pscoast->setEnabled(flag);
    ui->psbasemap->setEnabled(flag);
    ui->psxy->setEnabled(flag);
    ui->pssac->setEnabled(flag);
    ui->pstext->setEnabled(flag);
    ui->gmtset->setEnabled(flag);
    ui->custom->setEnabled(flag);

    ui->endps->setEnabled(flag);

}

// 自定义函数，用于将ps转化为png
void MainWindow::convert2png(){

    //复制一份当前文件
    QDir *createfile     = new QDir;
    bool exist = createfile->exists(psfname+".tmp");
    if (exist){
            createfile->remove(psfname+".tmp");
     }
    if (!QFile::copy(psfname,psfname+".tmp")){
        return;
    }
    // 结束图像
    QString cmd = "gmt psxy -J -R -T -O >> "+psfname+".tmp";
    waiting_thread * waiting_thread_ui = new waiting_thread(this, cmd); //将类指针实例化，创建对话框，同时将cmd传给新对话款
    waiting_thread_ui->exec(); //显示窗口， 阻塞方式
    delete waiting_thread_ui;
    // 转换成png
    cmd = "gmt psconvert "+psfname+".tmp -Tg -Ftmp";
    waiting_thread_ui = new waiting_thread(this, cmd); //将类指针实例化，创建对话框，同时将cmd传给新对话款
    waiting_thread_ui->exec(); //显示窗口， 阻塞方式
    delete waiting_thread_ui;

    delete createfile;
}

// 自定义函数，显示预览
void MainWindow::display_preview(int run_psconvert){
    if (run_psconvert == 1)
        convert2png();

    QPixmap pix("tmp.png");
    int hp = pix.size().height();
    int wp = pix.size().width();
    int hh = ui->label->size().height();
    int ww = ui->label->size().width();

    // 检查tmp.png是否存在
    if ( !QFile::exists("tmp.png") || hp == 0 || wp == 0 ){
        QMessageBox msgBox;
        QString str;
        str = "预览图片生成失败。可能原因:\n";
        str+= "1. 本机未安装Ghostscript或Ghostscript版本太低，请升级安装Ghostscript\n";
        str+= "2. tmp.png文件被删除\n";
        str+= "3. 您输入的GMT命令有误，请仔细检查并撤销\n";
        msgBox.setText(str);
        msgBox.exec();
        return;
    }

    if ( hp/wp > hh/ww )
        ww = hh*wp/hp;
    else
        hh = hp*ww/wp;

    ui->label->resize(ww,hh);
    //QPixmap dest=pix.scaled(label->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    // 注意不能使用QPixmap的等比例缩放，而要让label去适应pixmap的比例。因为实际使用发现使用前者会导致图片质量严重下降
    ui->label->setPixmap(pix);
}

void MainWindow::on_new_PS_file_clicked()
{
    new_ps_file * new_ps_file_ui = new new_ps_file; //将类指针实例化
    new_ps_file_ui->exec(); //显示窗口， 阻塞方式

    QString cmd = new_ps_file_ui->send_gmt_cmd(); // 获取第一条命令，建立空白画布

    if (cmd.isEmpty())
        return;

    // 删除gmt.history文件
    if (QFile::exists("gmt.history")){
        QFile::remove("gmt.history");
    }
    // 删除gmt.conf
    if (QFile::exists("gmt.conf")){
        QFile::remove("gmt.conf");
    }
    // 初始化配置
    MAP_FRAME_TYPE=MAP_FRAME_TYPE_default;
    MAP_FRAME_WIDTH=MAP_FRAME_WIDTH_default;
    MAP_FRAME_PEN=MAP_FRAME_PEN_default;
    MAP_TICK_LENGTH_PRIMARY=MAP_TICK_LENGTH_PRIMARY_default;
    MAP_ANNOT_OFFSET_PRIMARY=MAP_ANNOT_OFFSET_PRIMARY_default;
    MAP_LABEL_OFFSET=MAP_LABEL_OFFSET_default;
    FONT_ANNOT_PRIMARY=FONT_ANNOT_PRIMARY_default;
    FONT_LABEL=FONT_LABEL_default;

    waiting_thread * waiting_thread_ui = new waiting_thread(this, cmd); //将类指针实例化，创建对话框，同时将cmd传给新对话款
    waiting_thread_ui->exec(); //显示窗口， 阻塞方式
    if (waiting_thread_ui->send_exit_code() == 0 ){ // 如果是异常退出就不执行了
        ui->cmd_list->clear(); // 清除命令历史列表
        ui->cmd_list->addItem(cmd); // 将第一条命令添加到列表中
        cmd_num = 1; //命令初始化
        psfname = new_ps_file_ui->send_ps_fname(); // 获取文件名
        image_w = new_ps_file_ui->send_w().toFloat(); // 获取图片大小，单位英寸
        image_h = new_ps_file_ui->send_h().toFloat();

        // 将各个绘图按钮有效化
        set_gmt_button_enable(true);
        // ps导出按钮有效化
        ui->export_ps->setEnabled(true);
        // 脚本导出按钮有效化
        ui->export_cmd->setEnabled(true);
        // 预览
        display_preview(1);
        // 强制触发一次窗口大小变化事件，目的是重新调整预览区label大小
        this->resize(this->size() - QSize(1,1));
        this->resize(this->size() + QSize(1,1));
    }

    delete waiting_thread_ui;
    delete new_ps_file_ui;
}

void MainWindow::on_endps_clicked()
{
    QString cmd = "gmt psxy -J -R -T -O >> "+psfname;
    waiting_thread * waiting_thread_ui = new waiting_thread(this, cmd); //将类指针实例化，创建对话框，同时将cmd传给新对话款
    waiting_thread_ui->exec(); //显示窗口， 阻塞方式
    if (waiting_thread_ui->send_exit_code() == 0 ){
        ui->cmd_list->addItem(cmd); // 将命令添加到列表中
        cmd_num++; //命令个数+1

        // 将各个绘图按钮无效化
        set_gmt_button_enable(false);
        /*
        // 三个撤销按钮无效化
        ui->undo->setEnabled(false);
        ui->redo->setEnabled(false);
        ui->undo_confirm->setEnabled(false);
        */
    }
    delete waiting_thread_ui;
}

void MainWindow::on_undo_clicked()
{
    if (cmd_num<=1)
        return;
    ui->cmd_list->item(cmd_num-1)->setForeground(QColor(210,210,210,255));
    cmd_num--;
    // 将各个绘图按钮无效化
    set_gmt_button_enable(false);
    // 将确认按钮有效化
    ui->undo_confirm->setEnabled(true);
}

void MainWindow::on_redo_clicked()
{
    if (ui->cmd_list->count() == 1)
        return;
    if (cmd_num == ui->cmd_list->count()) // 如果已经恢复到头了，就退出
        return;
    ui->cmd_list->item(cmd_num)->setForeground(QColor(0,0,0,255));
    cmd_num++;
    // 如果全部命令都已经恢复，则各个绘图按钮有效化,将确认按钮无效化
    if (cmd_num == ui->cmd_list->count()){
        set_gmt_button_enable(true);
        ui->undo_confirm->setEnabled(false);
    }
}

void MainWindow::on_undo_confirm_clicked()
{
    // 删除gmt.history文件
    if (QFile::exists("gmt.history")){
        QFile::remove("gmt.history");
    }
    // 删除gmt.conf
    if (QFile::exists("gmt.conf")){
        QFile::remove("gmt.conf");
    }
    // 初始化配置
    MAP_FRAME_TYPE=MAP_FRAME_TYPE_default;
    MAP_FRAME_WIDTH=MAP_FRAME_WIDTH_default;
    MAP_FRAME_PEN=MAP_FRAME_PEN_default;
    MAP_TICK_LENGTH_PRIMARY=MAP_TICK_LENGTH_PRIMARY_default;
    MAP_ANNOT_OFFSET_PRIMARY=MAP_ANNOT_OFFSET_PRIMARY_default;
    MAP_LABEL_OFFSET=MAP_LABEL_OFFSET_default;
    FONT_ANNOT_PRIMARY=FONT_ANNOT_PRIMARY_default;
    FONT_LABEL=FONT_LABEL_default;

    // 保存第 0 ~ cmd_num-1 条命令
    QString tmp_list[1024];
    int i;
    for( i = 0; i < cmd_num; i++){
        tmp_list[i] = ui->cmd_list->item(i)->text();
    }
    //
    ui->cmd_list->clear(); // 清除命令历史列表
    // 重头开始执行
    int tmp_cmd_num = 0;
    for( i = 0; i < cmd_num; i++ ){
        waiting_thread * waiting_thread_ui = new waiting_thread(this, tmp_list[i]); //将类指针实例化，创建对话框，同时将cmd传给新对话款
        waiting_thread_ui->exec(); //显示窗口， 阻塞方式
        if (waiting_thread_ui->send_exit_code() == 1 ) //如果中途中断，异常退出
        {
            delete waiting_thread_ui;
            break;
        }
        ui->cmd_list->addItem(tmp_list[i]);
        tmp_cmd_num++;
        delete waiting_thread_ui;
    }
    // 更新各个数据
    cmd_num = tmp_cmd_num;
    if (cmd_num == 0){ // 没有任何一条命令成功，回到初始状态
        // 将各个绘图按钮无效化
        set_gmt_button_enable(false);
    }else{ // 如果第一条命令成功了，则各个绘图按钮有效化
        // 将各个绘图按钮有效化
        set_gmt_button_enable(true);
    }
    // 将确认按钮无效化
    ui->undo_confirm->setEnabled(false);
    // 预览
    display_preview(1);
    // 强制触发一次窗口大小变化事件，目的是重新调整预览区label大小
    this->resize(this->size() - QSize(1,1));
    this->resize(this->size() + QSize(1,1));
}

void MainWindow::on_pscoast_clicked()
{
    GMT_pscoast * GMT_pscoast_ui = new GMT_pscoast(this, psfname); // 将文件名传给pscoast对话框
    GMT_pscoast_ui->exec();

    QString cmd = GMT_pscoast_ui->send_gmt_cmd();

    if (cmd.isEmpty())
        return;

    waiting_thread * waiting_thread_ui = new waiting_thread(this, cmd); //将类指针实例化，创建对话框，同时将cmd传给新对话款
    waiting_thread_ui->exec(); //显示窗口， 阻塞方式
    if (waiting_thread_ui->send_exit_code() == 0 ){ // 如果是异常退出就不执行了
        ui->cmd_list->addItem(cmd); // 将命令添加到列表中
        cmd_num++; //命令个数+1
        // 预览
        display_preview(1);
    }

    delete waiting_thread_ui;
    delete GMT_pscoast_ui;
}

void MainWindow::on_psbasemap_clicked()
{
    GMT_psbasemap * GMT_psbasemap_ui = new GMT_psbasemap(this, psfname); // 将文件名传给psbasemap对话框
    GMT_psbasemap_ui->exec();

    QString cmd = GMT_psbasemap_ui->send_gmt_cmd();

    if (cmd.isEmpty())
        return;

    waiting_thread * waiting_thread_ui = new waiting_thread(this, cmd); //将类指针实例化，创建对话框，同时将cmd传给新对话款
    waiting_thread_ui->exec(); //显示窗口， 阻塞方式
    if (waiting_thread_ui->send_exit_code() == 0 ){ // 如果是异常退出就不执行了
        ui->cmd_list->addItem(cmd); // 将命令添加到列表中
        cmd_num++; //命令个数+1
        // 预览
        display_preview(1);
    }

    delete waiting_thread_ui;
    delete GMT_psbasemap_ui;
}

void MainWindow::on_psxy_clicked()
{
    GMT_psxy * GMT_psxy_ui = new GMT_psxy(this, psfname, image_w, image_h); // 将文件名传给psxy对话框
    GMT_psxy_ui->exec();

    QString cmd = GMT_psxy_ui->send_gmt_cmd();

    if (cmd.isEmpty())
        return;

    waiting_thread * waiting_thread_ui = new waiting_thread(this, cmd); //将类指针实例化，创建对话框，同时将cmd传给新对话款
    waiting_thread_ui->exec(); //显示窗口， 阻塞方式
    if (waiting_thread_ui->send_exit_code() == 0 ){ // 如果是异常退出就不执行了
        ui->cmd_list->addItem(cmd); // 将命令添加到列表中
        cmd_num++; //命令个数+1
        // 预览
        display_preview(1);
    }

    delete waiting_thread_ui;
    delete GMT_psxy_ui;
}

void MainWindow::on_pssac_clicked()
{
    GMT_pssac * GMT_pssac_ui = new GMT_pssac(this, psfname); // 将文件名传给pssac对话框
    GMT_pssac_ui->exec();

    QString cmd = GMT_pssac_ui->send_gmt_cmd();

    if (cmd.isEmpty())
        return;

    waiting_thread * waiting_thread_ui = new waiting_thread(this, cmd); //将类指针实例化，创建对话框，同时将cmd传给新对话款
    waiting_thread_ui->exec(); //显示窗口， 阻塞方式
    if (waiting_thread_ui->send_exit_code() == 0 ){ // 如果是异常退出就不执行了
        ui->cmd_list->addItem(cmd); // 将命令添加到列表中
        cmd_num++; //命令个数+1
        // 预览
        display_preview(1);
    }

    delete waiting_thread_ui;
    delete GMT_pssac_ui;
}

void MainWindow::on_pstext_clicked()
{
    GMT_pstext * GMT_pstext_ui = new GMT_pstext(this, psfname, image_w, image_h); // 将文件名传给pstext对话框
    GMT_pstext_ui->exec();

    QString cmd = GMT_pstext_ui->send_gmt_cmd();

    if (cmd.isEmpty())
        return;

    waiting_thread * waiting_thread_ui = new waiting_thread(this, cmd); //将类指针实例化，创建对话框，同时将cmd传给新对话款
    waiting_thread_ui->exec(); //显示窗口， 阻塞方式
    if (waiting_thread_ui->send_exit_code() == 0 ){ // 如果是异常退出就不执行了
        ui->cmd_list->addItem(cmd); // 将命令添加到列表中
        cmd_num++; //命令个数+1
        // 预览
        display_preview(1);
    }

    delete waiting_thread_ui;
    delete GMT_pstext_ui;
}

void MainWindow::on_gmtset_clicked()
{
    GMT_set * GMT_set_ui = new GMT_set(this,
                                       MAP_FRAME_TYPE,
                                       MAP_FRAME_WIDTH,
                                       MAP_FRAME_PEN,
                                       MAP_TICK_LENGTH_PRIMARY,
                                       MAP_ANNOT_OFFSET_PRIMARY,
                                       MAP_LABEL_OFFSET,
                                       FONT_ANNOT_PRIMARY,
                                       FONT_LABEL);
    GMT_set_ui->exec();

    QString cmd = GMT_set_ui->send_gmt_cmd();

    if (cmd.isEmpty())
        return;

    waiting_thread * waiting_thread_ui = new waiting_thread(this, cmd); //将类指针实例化，创建对话框，同时将cmd传给新对话款
    waiting_thread_ui->exec(); //显示窗口， 阻塞方式
    if (waiting_thread_ui->send_exit_code() == 0 ){ // 如果是异常退出就不执行了
        ui->cmd_list->addItem(cmd); // 将命令添加到列表中
        cmd_num++; //命令个数+1

        // 记录各个配置项的值
        QVariant data_package = GMT_set_ui->send_data();
        vector<QString> list = data_package.value< vector<QString> >(); // 数据解包
        MAP_FRAME_TYPE = list.at(0);
        MAP_FRAME_WIDTH = list.at(1);
        MAP_FRAME_PEN = list.at(2);
        MAP_TICK_LENGTH_PRIMARY = list.at(3);
        MAP_ANNOT_OFFSET_PRIMARY = list.at(4);
        MAP_LABEL_OFFSET = list.at(5);
        FONT_ANNOT_PRIMARY = list.at(6);
        FONT_LABEL = list.at(7);
    }

    delete waiting_thread_ui;
    delete GMT_set_ui;
}

void MainWindow::on_custom_clicked()
{
    GMT_custom * GMT_custom_ui = new GMT_custom(); // 将文件名传给pstext对话框
    GMT_custom_ui->exec();

    QString cmd = GMT_custom_ui->send_gmt_cmd();

    if (cmd.isEmpty())
        return;

    waiting_thread * waiting_thread_ui = new waiting_thread(this, cmd); //将类指针实例化，创建对话框，同时将cmd传给新对话款
    waiting_thread_ui->exec(); //显示窗口， 阻塞方式
    if (waiting_thread_ui->send_exit_code() == 0 ){ // 如果是异常退出就不执行了
        ui->cmd_list->addItem(cmd); // 将命令添加到列表中
        cmd_num++; //命令个数+1
        // 预览
        display_preview(1);
    }

    delete waiting_thread_ui;
    delete GMT_custom_ui;
}

void MainWindow::on_export_ps_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,
            tr("导出ps文件"),
            psfname);
    if (QFile::exists(filename)){
        QFile::remove(filename);
    }
    QFile::copy(psfname,filename);
}

void MainWindow::on_export_cmd_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,
            tr("导出绘图脚本"),
            psfname+".txt");
    std::ofstream out( filename.toUtf8().constData(), std::ios_base::binary | std::ios_base::out);
    int i;
    for( i = 0; i < ui->cmd_list->count(); i++ ){
        QString qstr = ui->cmd_list->item(i)->text();
        out << qstr.toUtf8().constData() << "\n";
    }
    out.close();
}

void MainWindow::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://docs.gmt-china.org/5.4/")));
}
