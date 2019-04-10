#ifndef CREGISTERDIALOG_H
#define CREGISTERDIALOG_H

#include <QDialog>
#include "cheader.h"

namespace Ui {
class CRegisterDialog;
}

class CRegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CRegisterDialog(QWidget *parent = nullptr);
    ~CRegisterDialog();

private:
    Ui::CRegisterDialog *ui;

    QStatusBar *statusbar;
    QButtonGroup *m_pButtonGroup;
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    QPoint last;
    bool flag;

public:
    void showWindow();
    void closeWindow();
    void shackWindow();

signals:
    void signal_Message(Message);
    void signal_ToolForm(QString,QList<int>);
    void signal_RegisterUser(User);
    void signal_RegisterAdmin(User);

private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_close_clicked();
    void on_pushButton_confirm_clicked();
};

#endif // CREGISTERDIALOG_H
