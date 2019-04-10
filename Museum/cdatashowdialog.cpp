#include "cdatashowdialog.h"
#include "ui_cdatashowdialog.h"

CDataShowDialog::CDataShowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDataShowDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    flag = false;
    statusbar = new QStatusBar(this);
    ui->verticalLayout->addWidget(statusbar);

    QRegExp chinesetype("^[\u4e00-\u9fa5]{0,}$");
    QRegExpValidator *chinese = new QRegExpValidator(chinesetype,this);
    ui->lineEdit_name->setValidator(chinese);

    m_Max = false;
    ui->widget_title->installEventFilter(this);

}

CDataShowDialog::~CDataShowDialog()
{
    delete ui;
}
//显示对话框（查阅、添加、更新）
void CDataShowDialog::showWindow(bool admin,bool emperor)
{
    if(!admin)
    {
        ui->label_showdata_title->setText("名人介绍");
        ui->stackedWidget->setCurrentWidget(ui->page_show);
    }
    else
    {
        ui->pushButton_update->setText("修改");
        ui->pushButton_delete->setText("删除");
        ui->label_showdata_title->setText("修改信息");
        ui->stackedWidget->setCurrentWidget(ui->page_addperson);
    }
    ui->pushButton_update_person_pic->setText("更新图片");
    ui->lineEdit_name->setEnabled(true);

    if(!emperor)
    {
        ui->pushButton_update->setText("修改");
        ui->lineEdit_name->setEnabled(true);
        ui->labeldate2->setText("时期：");
        ui->labeltitle2->setText("概要：");
        ui->labeldate->setText("时期：");
        ui->labeltitle->setText("概要：");
        ui->label_describe->show();
        ui->pushButton_delete->show();
        ui->textEdit_describe->show();
    }
    else
    {
        ui->pushButton_update->setText("更新");
        ui->lineEdit_name->setEnabled(false);
        ui->labeldate2->setText("在位时期：");
        ui->labeltitle2->setText("谥号：");
        ui->labeldate->setText("在位时期：");
        ui->labeltitle->setText("谥号：");
        ui->label_describe->hide();
        ui->pushButton_delete->hide();
        ui->textEdit_describe->hide();
    }
    show();
    CReadImage::setCelebrityPic(ui->label_person_pic,m_Name);
    CReadImage::setCelebrityPic(ui->label_update_pic,m_Name);
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}
//关闭对话框
void CDataShowDialog::closeWindow()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation,SIGNAL(finished()),this,SLOT(close()));

}
//震动对话框
void CDataShowDialog::shackWindow()
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
//接收人物信息
void CDataShowDialog::slot_SetPerson(Person person)
{
    CReadImage::setCelebrityPic(ui->label_person_pic,person.name);
    CReadImage::setCelebrityPic(ui->label_update_pic,person.name);

    m_Name = person.name;
    m_PastName = person.title;
    ui->label_name->setText(person.name);
    ui->label_title->setText(person.title);
    ui->label_date->setText(person.date.replace('(',' ').replace(')',' '));
    ui->label_describe->setText("\t介绍："+person.describe);

    ui->lineEdit_name->setText(person.name);
    ui->lineEdit_date->setText(person.date);
    ui->textEdit_title->setText(person.title);
    ui->textEdit_describe->setText(person.describe);
}
//开始添加数据
void CDataShowDialog::slot_ToAddData()
{
    ui->lineEdit_name->clear();
    ui->lineEdit_date->clear();
    ui->textEdit_title->clear();
    ui->textEdit_describe->clear();
    ui->pushButton_update->setText("添加");
    ui->pushButton_delete->setText("清空");
    ui->label_showdata_title->setText("添加人物");
    ui->pushButton_update_person_pic->setText("上传图片");
    ui->stackedWidget->setCurrentWidget(ui->page_addperson);
    show();
    ui->lineEdit_name->setEnabled(true);
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    CReadImage::setCelebrityPic(ui->label_update_pic,"default");
}
//重绘
void CDataShowDialog::paintEvent(QPaintEvent *)
{
//    CReadImage::setCelebrityPic(ui->label_person_pic,m_Name);
//    CReadImage::setCelebrityPic(ui->label_update_pic,m_Name);
}
//消息
bool CDataShowDialog::eventFilter(QObject *obj, QEvent *event)
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
    else
        return CDataShowDialog::eventFilter(obj, event);

}
//移动对话框
void CDataShowDialog::mousePressEvent(QMouseEvent *e)
{
    QRect r = ui->widget_title->geometry();
    if(r.contains(e->pos()))
    {
        flag = true;
        last = e->globalPos();
    }
}
void CDataShowDialog::mouseMoveEvent(QMouseEvent *e)
{
    if(!flag)
        return;
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    last = e->globalPos();
    move(x()+dx, y()+dy);
}
void CDataShowDialog::mouseReleaseEvent(QMouseEvent *e)
{
    if(!flag)
        return;
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    move(x()+dx, y()+dy);
    flag = false;
}
//关闭对话框
void CDataShowDialog::on_pushButton_close_clicked()
{
    closeWindow();
}
//已阅数据
void CDataShowDialog::on_pushButton_readed_clicked()
{
    closeWindow();
}
//更新数据
void CDataShowDialog::on_pushButton_update_clicked()
{
    if(ui->lineEdit_name->text().isEmpty())
    {
        shackWindow();
        QList<int> pos;
        pos.push_back(this->geometry().x());
        pos.push_back(this->geometry().y());
        pos.push_back(this->geometry().width());
        pos.push_back(this->geometry().height());
        emit signal_ToolForm("请输入姓名！",pos);
        return;
    }
    Person person;
    person.name = ui->lineEdit_name->text();
    if(ui->lineEdit_date->text().isEmpty())
        person.date = "?~?";
    else
        person.date = ui->lineEdit_date->text();
    if(ui->textEdit_title->toPlainText().isEmpty())
        person.title = "待添加";
    else
        person.title = ui->textEdit_title->toPlainText();
    if(ui->textEdit_describe->toPlainText().isEmpty())
        person.describe = "待添加";
    else
        person.describe = ui->textEdit_describe->toPlainText();

    if(ui->pushButton_update->text() == "修改")
    {
        QList<int> size;
        size.push_back(this->geometry().x());
        size.push_back(this->geometry().y());
        size.push_back(this->geometry().width());
        size.push_back(this->geometry().height());
        bool flag;
        emit signal_WarningInfo("确定要修改"+m_Name+"的资料？",size,flag);
        if(flag)
            emit signal_UpdateData(person,m_Name);
    }
    else if(ui->pushButton_update->text() == "更新")
    {
        QList<int> size;
        size.push_back(this->geometry().x());
        size.push_back(this->geometry().y());
        size.push_back(this->geometry().width());
        size.push_back(this->geometry().height());
        bool flag;
        person.describe = "";
        emit signal_WarningInfo("确定要更新"+m_Name+"的资料？",size,flag);
        if(flag)
            emit signal_UpdateData(person,m_PastName);
    }
    else
    {
        emit signal_AddData(person);
    }

}
//删除数据
void CDataShowDialog::on_pushButton_delete_clicked()
{
    if(ui->pushButton_delete->text() == "删除")
    {
        shackWindow();
        QList<int> size;
        size.push_back(this->geometry().x());
        size.push_back(this->geometry().y());
        size.push_back(this->geometry().width());
        size.push_back(this->geometry().height());
        bool flag;
        emit signal_WarningInfo("确定要删除"+m_Name+"的资料？",size,flag);
        if(flag)
            emit signal_DeleteData(m_Name);
    }
    else
    {
        ui->lineEdit_name->clear();
        ui->lineEdit_date->clear();
        ui->textEdit_title->clear();
        ui->textEdit_describe->clear();
    }

}


void CDataShowDialog::on_pushButton_update_person_pic_clicked()
{
    if(ui->pushButton_update_person_pic->text() == "更新头像")
    {
        QString path = QFileDialog::getOpenFileName(this,"选择头像","","PNG Files(*.png)");
        if(!path.isNull())
            CReadImage::copyPersonImage(path,m_Name);
        CReadImage::setCelebrityPic(ui->label_update_pic,m_Name);
    }
    else
    {
        if(ui->lineEdit_name->text().isEmpty())
        {
            QList<int> pos;
            pos.push_back(this->geometry().x());
            pos.push_back(this->geometry().y());
            pos.push_back(this->geometry().width());
            pos.push_back(this->geometry().height());
            shackWindow();
            emit signal_ToolForm("请先输入姓名！",pos);
        }
        else
        {
            ui->lineEdit_name->setEnabled(false);
            m_Name = ui->lineEdit_name->text();
            QString path = QFileDialog::getOpenFileName(this,"选择头像","","PNG Files(*.png)");
            if(!path.isNull())
                CReadImage::copyPersonImage(path,m_Name);
            CReadImage::setCelebrityPic(ui->label_update_pic,m_Name);
        }
    }
}

