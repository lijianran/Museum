#include "ctoolform.h"
#include "ui_ctoolform.h"

CToolForm::CToolForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CToolForm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    m_Apply = false;

}

CToolForm::~CToolForm()
{
    delete ui;
}


void CToolForm::closeWidow()
{
    QPropertyAnimation *close = new QPropertyAnimation(this);
    close->setPropertyName("windowOpacity");
    close->setDuration(300);
    close->setStartValue(1);
    close->setEndValue(0);
    close->start();
    connect(close,SIGNAL(finished()),this,SLOT(close()));
}

void CToolForm::MoveOut(QString str,int x,int y,int w,int h)
{
    show();
    ui->stackedWidget->setCurrentIndex(0);
    ui->label_tip->setText(str);
    move(x,y);
    resize(w-100,h/8);

    QPropertyAnimation *move = new QPropertyAnimation(this);
    move->setTargetObject(this);
    move->setPropertyName("pos");
    move->setDuration(1000);

    int start_x = x+w/2-width()/2;
    int start_y = y+h-2*height();
    int end_x = x+w/2-width()/2;
    int end_y = y+h-height();

    move->setStartValue(QPoint(start_x,start_y));
    move->setEndValue(QPoint(end_x,end_y));
    move->setEasingCurve(QEasingCurve::OutQuint);
    connect(move,SIGNAL(finished()),this,SLOT(close()));

    move->start();
}

void CToolForm::WarningInfo(QString str,int x,int y,int w,int h,bool& flag)
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->label_info->setText(str);
    resize(w/2,h/3);
    move(x+w/4,y+h/3);
    ui->buttonBox->button(QDialogButtonBox::Close)->setText("取消");
    ui->buttonBox->button(QDialogButtonBox::Apply)->setText("应用");
    exec();
    flag = m_Apply;
}

void CToolForm::WarningInfo(QString str,QList<int> size,bool& flag)
{
    int x = size[0];
    int y = size[1];
    int w = size[2];
    int h = size[3];
    WarningInfo(str,x,y,w,h,flag);
}



void CToolForm::on_buttonBox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Close) == button)
    {
        m_Apply = false;
        accept();
    }
    else
    {
        m_Apply = true;
        accept();
    }
}
