#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
    ui->menuBar->hide();
    setWindowFlags(Qt::FramelessWindowHint);

    m_Max = false;
    flag = false;

    ui->comboBox_style->addItem("浅色");
    ui->comboBox_style->addItem("深色");

    ui->widget_title->installEventFilter(this);
    ui->label_main_title->installEventFilter(this);

    setEditType();
    setQmlWidget();
    setTableWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTableWidget()
{
    QStringList header;
    header<<"姓名"<<"简介";

    //总列表
    ui->tableWidget_total->setColumnCount(2);
    ui->tableWidget_total->setHorizontalHeaderLabels(header);
    ui->tableWidget_total->setColumnWidth(0,150);
    ui->tableWidget_total->setColumnWidth(1,500);

    //查询列表
    ui->tableWidget_search->setColumnCount(2);
    ui->tableWidget_search->setHorizontalHeaderLabels(header);
    ui->tableWidget_search->setColumnWidth(0,100);
    ui->tableWidget_search->setColumnWidth(1,400);

    //皇帝列表
    header.clear();
    header<<"谥号"<<"姓名";
    ui->tableWidget_emperor->setColumnCount(2);
    ui->tableWidget_emperor->setHorizontalHeaderLabels(header);
    ui->tableWidget_emperor->setColumnWidth(0,200);
    ui->tableWidget_emperor->setColumnWidth(1,200);
}
void MainWindow::setQmlWidget()
{
    ui->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    QUrl source("qrc:/res/qml/Main.qml");
    ui->quickWidget->setSource(source);
}
void MainWindow::setEditType()
{
    //中文输入
    QRegExp chinesetype("^[\u4e00-\u9fa5]{0,}$");
    QRegExpValidator *chinese = new QRegExpValidator(chinesetype,this);
    ui->lineEdit_search->setValidator(chinese);
    ui->lineEdit_newname->setValidator(chinese);
    //数字输入
    QRegExp numbertype("^[0-9]*$");
    QRegExpValidator *number = new QRegExpValidator(numbertype,this);
    ui->lineEdit_newtel->setValidator(number);
    //非中文输入
    QRegExp nochinesetype("[A-Za-z0-9]+$");
    QRegExpValidator *nochinese = new QRegExpValidator(nochinesetype,this);
    ui->lineEdit_newpwds->setValidator(nochinese);
    ui->lineEdit_oldpwds->setValidator(nochinese);
    //性别互斥
    m_pButtonGroup = new QButtonGroup(this);
    m_pButtonGroup->setExclusive(true);
    m_pButtonGroup->addButton(ui->radioButton_man_update);
    m_pButtonGroup->addButton(ui->radioButton_woman_update);
}
void MainWindow::getSize(QList<int>& pos)
{
    pos.push_back(this->geometry().x());
    pos.push_back(this->geometry().y());
    pos.push_back(this->geometry().width());
    pos.push_back(this->geometry().height());
}
bool MainWindow::check(QLineEdit* line)
{
    if(line->text().isEmpty())
    {
        shackWindow();
        return false;
    }
    return true;
}

//显示窗口
void MainWindow::showWindow(bool admin)
{
    emit signal_GetListData();
    if(!admin)
    {
        ui->stackedWidget_menu->setCurrentIndex(0);
        qint64 daynum = QDateTime::fromString(m_User.date, "yyyy-MM-dd").daysTo(QDateTime::currentDateTime())+1;
        QString welcome = "尊敬的用户"+
                m_User.name+"：\n\n"+
                "  今天是您登录的第"+
                QString::number(daynum)+"天！\n\n"+
                "  本系统已收录唐朝人物"+
                QString::number(m_PersonNum)+"位！";
        ui->label_welcome->setText(welcome);
    }
    else
    {
        ui->stackedWidget_menu->setCurrentIndex(1);
        ui->label_welcome->setText("尊敬的管理员：\n\t  您好！");
    }
    show();
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    ui->stackedWidget_center->setCurrentIndex(0);
}
//关闭窗口
void MainWindow::on_pushButton_close_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation,SIGNAL(finished()),this,SLOT(close()));
}
//震动窗口
void MainWindow::shackWindow()
{
    if(!m_Max)
    {
        QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
        animation->setDuration(500);
        animation->setKeyValueAt(0,QRect(QPoint(this->frameGeometry().x()-3,this->frameGeometry().y()),this->size()));
        animation->setKeyValueAt(0.1,QRect(QPoint(this->frameGeometry().x()+6,this->frameGeometry().y()),this->size()));
        animation->setKeyValueAt(0.2,QRect(QPoint(this->frameGeometry().x()-6,this->frameGeometry().y()),this->size()));
        animation->setKeyValueAt(0.3,QRect(QPoint(this->frameGeometry().x()+6,this->frameGeometry().y()),this->size()));
        animation->setKeyValueAt(0.4,QRect(QPoint(this->frameGeometry().x()-6,this->frameGeometry().y()),this->size()));
        animation->setKeyValueAt(0.5,QRect(QPoint(this->frameGeometry().x()+6,this->frameGeometry().y()),this->size()));
        animation->setKeyValueAt(0.6,QRect(QPoint(this->frameGeometry().x()-6,this->frameGeometry().y()),this->size()));
        animation->setKeyValueAt(0.7,QRect(QPoint(this->frameGeometry().x()+6,this->frameGeometry().y()),this->size()));
        animation->setKeyValueAt(0.8,QRect(QPoint(this->frameGeometry().x()-6,this->frameGeometry().y()),this->size()));
        animation->setKeyValueAt(0.9,QRect(QPoint(this->frameGeometry().x()+6,this->frameGeometry().y()),this->size()));
        animation->setKeyValueAt(1,QRect(QPoint(this->frameGeometry().x()-3,this->frameGeometry().y()),this->size()));
        animation->start();
    }
}
//清理内容
void MainWindow::clear(int code)
{
    if(code == 0)//清空查询列表
    {
        ui->tableWidget_search->setRowCount(0);
        ui->tableWidget_search->clearContents();
        ui->lineEdit_search->clear();
    }
    if(code == 1)//密码修改成功，登出
    {
        ui->lineEdit_oldpwds->clear();
        ui->lineEdit_confirmpwds->clear();
        ui->lineEdit_newpwds->clear();
        emit signal_Logout();
    }
    if(code == 3)//密码错误
    {
        ui->lineEdit_oldpwds->setFocus();
        ui->lineEdit_oldpwds->clear();
        ui->lineEdit_confirmpwds->clear();
        ui->lineEdit_newpwds->clear();
    }
    if(code == 2)//两次密码输入不同
    {
        ui->lineEdit_newpwds->setFocus();
        ui->lineEdit_confirmpwds->clear();
        ui->lineEdit_newpwds->clear();
    }
    if(code == 5)//信息修改成功
    {
        ui->toolBox_userdata->setCurrentIndex(0);
    }
}
//重绘
void MainWindow::paintEvent(QPaintEvent *)
{
    CReadImage::setUserIcon(ui->label_user_icon,m_User.user);
}
//鼠标事件
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    QRect r = ui->widget_title->geometry();
    QRect title = ui->label_main_title->geometry();
    if(!title.contains(e->pos())&&r.contains(e->pos())&&!m_Max)
    {
        flag = true;
        last = e->globalPos();
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(!flag)
        return;
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    last = e->globalPos();
    move(x()+dx, y()+dy);
}
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if(!flag)
        return;
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    move(x()+dx, y()+dy);
    flag = false;
}
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->widget_title)
    {
        if (event->type() == QEvent::MouseButtonDblClick)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                if(!m_Max)
                {
                    showMaximized();
                    m_Max = true;
                }
                else
                {
                    m_Max = false;
                    showNormal();
                }
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    else if (obj == ui->label_main_title)
    {
        if (event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                ui->stackedWidget_center->setCurrentIndex(0);
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return MainWindow::eventFilter(obj, event);

}
//接收列表信息
void MainWindow::slot_RefleshList(QList<QString> list)
{
    QList<QString> emperor;
    for(int i=0;i<22;i++)
    {
        QString title = list.back();
        list.pop_back();
        QString name = list.back();
        list.pop_back();
        emperor.push_front(title);
        emperor.push_front(name);
    }
    ui->tableWidget_emperor->setRowCount(22);
    for(int i=0;i<emperor.size();i+=2)
    {
        ui->tableWidget_emperor->setItem(i/2,0,new QTableWidgetItem(emperor[i+1]));
        ui->tableWidget_emperor->item(i/2,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget_emperor->setItem(i/2,1,new QTableWidgetItem(emperor[i]));
        ui->tableWidget_emperor->item(i/2,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }

    m_PersonNum = list.size()/2;
    ui->tableWidget_total->setRowCount(m_PersonNum);
    for(int i=0;i<list.size();i+=2)
    {
        ui->tableWidget_total->setItem(i/2,0,new QTableWidgetItem(list[i]));
        ui->tableWidget_total->item(i/2,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget_total->setItem(i/2,1,new QTableWidgetItem(list[i+1]));
    }
}
//接收查询信息
void MainWindow::slot_ShowSearchList(QList<QString> list)
{
    ui->tableWidget_search->clearContents();
    ui->tableWidget_search->setRowCount(list.size()/2);
    for(int i=0;i<list.size();i+=2)
    {
        ui->tableWidget_search->setItem(i/2,0,new QTableWidgetItem(list[i]));
        ui->tableWidget_search->item(i/2,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget_search->setItem(i/2,1,new QTableWidgetItem(list[i+1]));
        ui->tableWidget_search->item(i/2,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        if((i/2)%2 == 0)
        {
            ui->tableWidget_search->item(i/2,0)->setBackgroundColor(QColor("#f5f5f5"));
            ui->tableWidget_search->item(i/2,1)->setBackgroundColor(QColor("#f5f5f5"));
        }
    }
}
//接收用户信息
void MainWindow::slot_SetUser(User user)
{
    m_User = user;
    CReadImage::setUserIcon(ui->label_user_icon,user.user);
    ui->user_username->setText(m_User.user);
    ui->user_name->setText(m_User.name);
    ui->user_sex->setText(m_User.sex);
    ui->user_tel->setText(m_User.tel);
    ui->user_date->setText(m_User.date);
    ui->lineEdit_newname->setText(m_User.name);
    ui->lineEdit_newtel->setText(m_User.tel);
    if(m_User.sex == "男")
        ui->radioButton_man_update->setChecked(true);
    else
        ui->radioButton_woman_update->setChecked(true);
}

//菜单隐藏
void MainWindow::on_pushButton_left_clicked()
{
    if(ui->pushButton_left->text()=="<")
    {
        ui->stackedWidget_menu->hide();
        ui->horizontalLayout_content->setStretch(0,0);
        ui->pushButton_left->setText(">");
    }
    else
    {
        ui->stackedWidget_menu->show();
        ui->horizontalLayout_content->setStretch(0,1);
        ui->pushButton_left->setText("<");
    }
}
//用户菜单：人物列表
void MainWindow::on_pushButton_list_clicked()
{
    ui->tabWidget_list->setCurrentIndex(0);
    ui->stackedWidget_center->setCurrentIndex(1);
    emit signal_GetListData();
}
//用户菜单：人物图鉴
void MainWindow::on_pushButton_pics_clicked()
{
    on_pushButton_left_clicked();
    ui->stackedWidget_center->setCurrentIndex(2);
    emit signal_SetDataBase(*(ui->quickWidget->rootContext()));
}
//用户菜单：用户设置
void MainWindow::on_pushButton_userset_clicked()
{
    emit signal_GetUserData();
    ui->toolBox_userdata->setCurrentIndex(0);
    ui->stackedWidget_center->setCurrentIndex(3);
}
//管理员菜单：添加人物
void MainWindow::on_pushButton_addperson_clicked()
{
    emit signal_ToAddData();
}
//管理员菜单：更新资料
void MainWindow::on_pushButton_update_clicked()
{
    ui->tabWidget_list->setCurrentIndex(0);
    ui->stackedWidget_center->setCurrentIndex(1);
    emit signal_GetListData();
    on_pushButton_left_clicked();
}
//管理员登出
void MainWindow::on_pushButton_adminlogout_clicked()
{
    emit signal_Logout();
}
//用户登出
void MainWindow::on_pushButton_userlogout_clicked()
{
    emit signal_Logout();
}

//用户操作：更新密码
void MainWindow::on_pushButton_updatepwds_clicked()
{
    QList<int> pos;
    getSize(pos);
    if(!check(ui->lineEdit_oldpwds))
    {
        emit signal_ToolForm("请输入当前密码！",pos);
        return;
    }
    if(!check(ui->lineEdit_newpwds))
    {
        emit signal_ToolForm("请输入新密码！",pos);
        return;
    }
    if(!check(ui->lineEdit_confirmpwds))
    {
        emit signal_ToolForm("请再次输入新密码！",pos);
        return;
    }

    if(ui->lineEdit_confirmpwds->text() != ui->lineEdit_newpwds->text())
    {
        emit signal_ToolForm("两次输入不同！",pos);
        clear(2);
        shackWindow();
        return;
    }

    bool flag;
    emit signal_WarningInfo("确定要修改密码？",pos,flag);
    if(flag)
    {
        if(ui->lineEdit_oldpwds->text() != m_User.pwds)
        {
            emit signal_ToolForm("密码错误，修改失败！",pos);
            clear(3);
            shackWindow();
            return;
        }
        else
            emit signal_UpdatePwds(ui->lineEdit_newpwds->text());
    }
}
//用户操作：更新资料
void MainWindow::on_pushButton_updateuserdata_clicked()
{
    QList<int> pos;
    getSize(pos);
    if(!check(ui->lineEdit_newname))
    {
        emit signal_ToolForm("姓名不能为空！",pos);
        return;
    }
    if(!check(ui->lineEdit_newtel))
    {
        emit signal_ToolForm("请输入电话号码！",pos);
        return;
    }

    m_User.name = ui->lineEdit_newname->text();
    m_User.tel = ui->lineEdit_newtel->text();
    m_User.sex = (m_pButtonGroup->checkedId()==-2?"男":"女");

    bool flag;
    emit signal_WarningInfo("确定要更新信息？",pos,flag);
    if(flag)
        emit signal_UpdateUser(m_User);
}
//用户操作：查询
void MainWindow::on_pushButton_search_clicked()
{
    QList<int> pos;
    getSize(pos);
    if(check(ui->lineEdit_search))
    {
        emit signal_SerachData(ui->lineEdit_search->text().trimmed());
    }
    else
    {
        emit signal_ToolForm("请输入人物姓名！",pos);
        return;
    }

}

//双击事件显示信息
void MainWindow::on_tableWidget_total_itemDoubleClicked(QTableWidgetItem *item)
{
    QString name = ui->tableWidget_total->item(item->row(),0)->text();
    emit signal_ShowData(name);
}

void MainWindow::on_tableWidget_emperor_itemDoubleClicked(QTableWidgetItem *item)
{
    QString name = ui->tableWidget_emperor->item(item->row(),0)->text();
    emit signal_ShowData(name);
}

void MainWindow::on_tableWidget_search_itemDoubleClicked(QTableWidgetItem *item)
{
    QString name = ui->tableWidget_search->item(item->row(),0)->text();
    emit signal_ShowData(name);
}


void MainWindow::on_pushButton_update_user_icon_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"选择头像","","PNG Files(*.png)");
    if(!path.isNull())
        CReadImage::copyUserImage(path,m_User.user);
    emit signal_GetUserData();
}

void MainWindow::on_comboBox_style_currentTextChanged(const QString &arg1)
{
    if(arg1 == "浅色")
    {
        emit signal_ChangeStyle("whitestyle");
    }
    else
    {
        emit signal_ChangeStyle("blackstyle");
    }
}
