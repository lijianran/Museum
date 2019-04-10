#ifndef CTOOLFORM_H
#define CTOOLFORM_H

#include <QDialog>
#include <QPropertyAnimation>
#include <QAbstractButton>
#include <QPushButton>
#include <QTime>
#include <QStatusBar>

namespace Ui {
class CToolForm;
}

class CToolForm : public QDialog
{
    Q_OBJECT

public:
    explicit CToolForm(QWidget *parent = nullptr);
    ~CToolForm();

public slots:
    void closeWidow();
    void MoveOut(QString,int,int,int,int);
    void WarningInfo(QString,int,int,int,int,bool&);
    void WarningInfo(QString,QList<int>,bool&);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::CToolForm *ui;
    QPropertyAnimation *animation;
    bool m_Apply;
};

#endif // CTOOLFORM_H
