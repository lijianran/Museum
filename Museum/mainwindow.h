#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cheader.h"
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected://重载
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    bool eventFilter(QObject *obj, QEvent *event);

protected:
    QPoint last;//移动窗口
    bool flag;//移动窗口
    bool m_Max;//最大化
    User m_User;//用户
    int m_PersonNum;//列表人数
    QButtonGroup *m_pButtonGroup;//互斥按钮

protected://内部函数
    void setTableWidget();
    void setQmlWidget();
    void setEditType();
    void getSize(QList<int>&);
    bool check(QLineEdit*);

public:
    void showWindow(bool);
    void shackWindow();
    void clear(int);

signals:
    void signal_SetDataBase(QQmlContext&);
    void signal_ToolForm(QString,QList<int>);
    void signal_WarningInfo(QString,QList<int>,bool&);

    //列表操作
    void signal_GetUserData();
    void signal_GetListData();
    void signal_SerachData(QString);
    void signal_ShowData(QString);

    //用户操作
    void signal_UpdatePwds(QString);
    void signal_UpdateUser(User);
    void signal_Logout();
    void signal_ToAddData();
    void signal_ChangeStyle(QString style);

protected slots:
    void slot_RefleshList(QList<QString>);
    void slot_ShowSearchList(QList<QString>);
    void slot_SetUser(User);

private slots:
    void on_pushButton_close_clicked();

    void on_pushButton_list_clicked();

    void on_pushButton_pics_clicked();

    void on_tableWidget_total_itemDoubleClicked(QTableWidgetItem *item);

    void on_pushButton_left_clicked();

    void on_pushButton_addperson_clicked();

    void on_pushButton_userset_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_adminlogout_clicked();

    void on_pushButton_userlogout_clicked();

    void on_pushButton_updatepwds_clicked();

    void on_pushButton_updateuserdata_clicked();

    void on_tableWidget_emperor_itemDoubleClicked(QTableWidgetItem *item);

    void on_pushButton_search_clicked();

    void on_tableWidget_search_itemDoubleClicked(QTableWidgetItem *item);

    void on_pushButton_update_user_icon_clicked();

    void on_comboBox_style_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
