#include "clogindialog.h"
#include "ui_clogindialog.h"

CLoginDialog::CLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CLoginDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    flag = false;

    statusbar = new QStatusBar(this);
    ui->verticalLayout->addWidget(statusbar);

    ui->lineEdit_UserName->setFocus();

    m_moveWidget = new QWidget(this);

    ui->label_register->installEventFilter(this);
    ui->label_admin->installEventFilter(this);
    ui->label_return->installEventFilter(this);

    ui->stackedWidget->setCurrentWidget(ui->page_user);
    m_User.user = "default";
}

CLoginDialog::~CLoginDialog()
{
    delete ui;
}

void CLoginDialog::clear(int code)
{
    if(code == 1)
    {
        ui->lineEdit_PassWord->clear();
        ui->lineEdit_UserName->setFocus();
    }
    if(code == 2)
    {
        ui->lineEdit_Admin_Pwds->clear();
        ui->lineEdit_Admin_User->clear();
    }

}

void CLoginDialog::mousePressEvent(QMouseEvent *e)
{
    QRect r = ui->widget_title->geometry();
    if(r.contains(e->pos()))
    {
        flag = true;
        last = e->globalPos();
    }

}
void CLoginDialog::mouseMoveEvent(QMouseEvent *e)
{
    if(!flag)
        return;
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    last = e->globalPos();
    move(x()+dx, y()+dy);
}
void CLoginDialog::mouseReleaseEvent(QMouseEvent *e)
{
    if(!flag)
        return;
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    move(x()+dx, y()+dy);
    flag = false;
}

bool CLoginDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->label_register)
    {
        if (event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                emit signal_Register();
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    else if(obj == ui->label_admin)
    {
        if (event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                ui->lineEdit_UserName->setFocus();
                ui->lineEdit_UserName->clear();
                ui->lineEdit_PassWord->clear();
                ui->stackedWidget->setCurrentWidget(ui->page_admin);
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    else if(obj == ui->label_return)
    {
        if (event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                ui->lineEdit_Admin_Pwds->clear();
                ui->lineEdit_Admin_User->clear();
                ui->lineEdit_Admin_User->setFocus();
                ui->stackedWidget->setCurrentWidget(ui->page_user);
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return CLoginDialog::eventFilter(obj, event);
}

void CLoginDialog::on_pushButton_close_clicked()
{
    closeWindow();
}

void CLoginDialog::on_pushButton_confirm_clicked()
{
    QList<int> pos;
    pos.push_back(this->geometry().x());
    pos.push_back(this->geometry().y());
    pos.push_back(this->geometry().width());
    pos.push_back(this->geometry().height());
    if(ui->lineEdit_UserName->text().isEmpty())
    {
        emit signal_ToolForm("请输入用户名！",pos);
        shackWindow();
        return;
    }
    if(ui->lineEdit_PassWord->text().isEmpty())
    {
        emit signal_ToolForm("请输入密码！",pos);
        shackWindow();
        return;
    }
    QString name = ui->lineEdit_UserName->text();
    QString pwds  = ui->lineEdit_PassWord->text();
    emit signal_ConfirmUser(name,pwds);
}

void CLoginDialog::on_pushButton_admin_confirm_clicked()
{
    QList<int> pos;
    pos.push_back(this->geometry().x());
    pos.push_back(this->geometry().y());
    pos.push_back(this->geometry().width());
    pos.push_back(this->geometry().height());
    if(ui->lineEdit_Admin_Pwds->text().isEmpty())
    {
        emit signal_ToolForm("请输入用户名！",pos);
        shackWindow();
        return;
    }
    if(ui->lineEdit_Admin_User->text().isEmpty())
    {
        emit signal_ToolForm("请输入密码！",pos);
        shackWindow();
        return;
    }
    QString name = ui->lineEdit_Admin_User->text();
    QString pwds  = ui->lineEdit_Admin_Pwds->text();
    emit signal_ConfirmAdmin(name,pwds);
}

void CLoginDialog::closeWindow()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation,SIGNAL(finished()),this,SLOT(close()));
    animation->start();
}

void CLoginDialog::showWindow()
{
    ui->lineEdit_UserName->show();
    ui->lineEdit_PassWord->show();
    ui->pushButton_confirm->show();
    ui->label_register->show();
    ui->label_admin->show();
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    show();
    CReadImage::setUserIcon(ui->label_icon,m_User.user);
}

void CLoginDialog::shackWindow()
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

void CLoginDialog::userLogin()
{
    CReadImage::setUserIcon(ui->label_icon,m_User.user);
    QTime t;
    t.start();
    while(t.elapsed()<300){}

    QPropertyAnimation *move = new QPropertyAnimation(this);
    move->setTargetObject(ui->frame_icon);
    move->setPropertyName("pos");
    move->setDuration(500);

    int w = ui->page_user->width();
    //int h = ui->page_user->height();
    int x = ui->frame_icon->x();
    int y = ui->frame_icon->y();
    int m = ui->frame_icon->width();

    ui->lineEdit_UserName->hide();
    ui->lineEdit_PassWord->hide();
    ui->pushButton_confirm->hide();
    ui->label_register->hide();
    ui->label_admin->hide();

    move->setStartValue(QPoint(x,y));
    move->setEndValue(QPoint(w/2-m/2,y));
    move->setEasingCurve(QEasingCurve::OutQuint);
    connect(move,SIGNAL(finished()),this,SLOT(closeWindow()));
    connect(move,SIGNAL(finished()),this,SLOT(toMainWindow()));
    move->start();
}

void CLoginDialog::toMainWindow()
{
    QTime t;
    t.start();
    while(t.elapsed()<300){}
    emit signal_ToMainWindow();
}

void CLoginDialog::slot_SetUser(User user)
{
    m_User = user;
}
