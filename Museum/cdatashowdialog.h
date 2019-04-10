#ifndef CDATASHOWDIALOG_H
#define CDATASHOWDIALOG_H

#include <QDialog>
#include "cheader.h"

namespace Ui {
class CDataShowDialog;
}

class CDataShowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CDataShowDialog(QWidget *parent = nullptr);
    ~CDataShowDialog();

private:
    Ui::CDataShowDialog *ui;
    QStatusBar *statusbar;

protected:
    void paintEvent(QPaintEvent *);
    bool eventFilter(QObject *obj, QEvent *event);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    bool m_Max;
    QPoint last;
    bool flag;
    QString m_Name;
    QString m_PastName;//谥号

public:
    void showWindow(bool admin=false,bool emperor=false);
    void closeWindow();
    void shackWindow();

public slots:
    void slot_SetPerson(Person);
    void slot_ToAddData();

signals:
    void signal_WarningInfo(QString,QList<int>,bool&);
    void signal_UpdateData(Person,QString);
    void signal_AddData(Person);
    void signal_DeleteData(QString);
    void signal_ToolForm(QString,QList<int>);


private slots:
    void on_pushButton_close_clicked();
    void on_pushButton_readed_clicked();
    void on_pushButton_update_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_update_person_pic_clicked();
};

#endif // CDATASHOWDIALOG_H
