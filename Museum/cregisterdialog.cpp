#include "cregisterdialog.h"
#include "ui_cregisterdialog.h"

CRegisterDialog::CRegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRegisterDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    flag = false;

    QRegExp numbertype("^[0-9]*$");
    QRegExpValidator *number = new QRegExpValidator(numbertype,this);
    ui->lineEdit_tel->setValidator(number);

    QRegExp chinesetype("^[\u4e00-\u9fa5]{0,}$");
    QRegExpValidator *chinese = new QRegExpValidator(chinesetype,this);
    ui->lineEdit_name->setValidator(chinese);

    QRegExp nochinesetype("[A-Za-z0-9]+$");
    QRegExpValidator *nochinese = new QRegExpValidator(nochinesetype,this);
    ui->lineEdit_user->setValidator(nochinese);
    ui->lineEdit_password->setValidator(nochinese);

    m_pButtonGroup = new QButtonGroup(this);
    m_pButtonGroup->setExclusive(true);
    m_pButtonGroup->addButton(ui->radioButton_man);
    m_pButtonGroup->addButton(ui->radioButton_woman);
    ui->radioButton_man->setChecked(true);
    statusbar = new QStatusBar(this);
    ui->verticalLayout_2->addWidget(statusbar);

    QFont font;
    font.setPixelSize(13);
    setFont(font);
}

CRegisterDialog::~CRegisterDialog()
{
    delete ui;
}


void CRegisterDialog::mousePressEvent(QMouseEvent *e)
{
    QRect r = ui->widget_title->geometry();
    if(r.contains(e->pos()))
    {
        flag = true;
        last = e->globalPos();
    }
}
void CRegisterDialog::mouseMoveEvent(QMouseEvent *e)
{
    if(!flag)
        return;
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    last = e->globalPos();
    move(x()+dx, y()+dy);
}
void CRegisterDialog::mouseReleaseEvent(QMouseEvent *e)
{
    if(!flag)
        return;
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    move(x()+dx, y()+dy);
    flag = false;
}

void CRegisterDialog::showWindow()
{
    show();
    ui->lineEdit_user->setFocus();
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}

void CRegisterDialog::closeWindow()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation,SIGNAL(finished()),this,SLOT(close()));
    ui->lineEdit_user->clear();
    ui->lineEdit_name->clear();
    ui->lineEdit_tel->clear();
    ui->lineEdit_password->clear();
    ui->pushButton_confirm->setFocus();
}

void CRegisterDialog::shackWindow()
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

void CRegisterDialog::on_pushButton_cancel_clicked()
{
    closeWindow();
    emit signal_Message(FAILURE_REGISTER);
}

void CRegisterDialog::on_pushButton_close_clicked()
{
    closeWindow();
    emit signal_Message(FAILURE_REGISTER);
}

void CRegisterDialog::on_pushButton_confirm_clicked()
{
    QList<int> pos;
    pos.push_back(this->geometry().x());
    pos.push_back(this->geometry().y());
    pos.push_back(this->geometry().width());
    pos.push_back(this->geometry().height());
    if(ui->lineEdit_user->text().isEmpty())
    {
        emit signal_ToolForm("请输入用户名！",pos);
        shackWindow();
        return;
    }
    if(ui->lineEdit_name->text().isEmpty())
    {
        emit signal_ToolForm("请输入姓名！",pos);
        shackWindow();
        return;
    }
    if(ui->lineEdit_password->text().isEmpty())
    {
        emit signal_ToolForm("请输入密码！",pos);
        shackWindow();
        return;
    }
    if(ui->lineEdit_repassword->text().isEmpty())
    {
        emit signal_ToolForm("请确认密码！",pos);
        shackWindow();
        return;
    }
    if(ui->lineEdit_repassword->text() != ui->lineEdit_password->text())
    {
        emit signal_ToolForm("两次密码输入不同！",pos);
        shackWindow();
        return;
    }
    if(ui->lineEdit_tel->text().isEmpty())
    {
        emit signal_ToolForm("请输入电话！",pos);
        shackWindow();
        return;
    }
    User user;
    user.user = ui->lineEdit_user->text();
    user.name  = ui->lineEdit_name->text();
    user.tel  = ui->lineEdit_tel->text();
    user.pwds  = ui->lineEdit_password->text();
    user.sex = (m_pButtonGroup->checkedId()==-2?"男":"女");
    //QDateTime current_time = QDateTime::fromString(book.returndate, "yyyy-MM-dd");
    user.date = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    if(ui->lineEdit_admin->text()=="admin")
        emit signal_RegisterAdmin(user);
    else
        emit signal_RegisterUser(user);
}


