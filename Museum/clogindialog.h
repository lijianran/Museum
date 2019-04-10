#ifndef CLOGINDIALOG_H
#define CLOGINDIALOG_H

#include <QDialog>
#include "cheader.h"

namespace Ui {
class CLoginDialog;
}

class CLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CLoginDialog(QWidget *parent = nullptr);
    ~CLoginDialog();


private:
    Ui::CLoginDialog *ui;

    QStatusBar *statusbar;

    QWidget *m_moveWidget;

public:
    void clear(int);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    bool eventFilter(QObject *obj, QEvent *event);
    QPoint last;
    bool flag;
    User m_User;

public slots:
    void closeWindow();
    void showWindow();
    void shackWindow();
    void userLogin();
    void toMainWindow();

protected slots:
    void slot_SetUser(User);

signals:
    void signal_ConfirmUser(QString,QString);
    void signal_ConfirmAdmin(QString,QString);
    void signal_Register();
    void signal_ToMainWindow();
    void signal_ToolForm(QString,QList<int>);

private slots:
    void on_pushButton_confirm_clicked();
    void on_pushButton_close_clicked();
    void on_pushButton_admin_confirm_clicked();
};

#endif // CLOGINDIALOG_H
