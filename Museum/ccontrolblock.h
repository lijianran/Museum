#ifndef CCONTROLBLOCK_H
#define CCONTROLBLOCK_H

#include <QObject>
#include <QApplication>
#include "mainwindow.h"
#include "clogindialog.h"
#include "cdatabase.h"
#include "cheader.h"
#include "cdatashowdialog.h"
#include "cregisterdialog.h"


class CControlBlock : public QObject
{
    Q_OBJECT
public:
    explicit CControlBlock(QObject *parent = nullptr);

protected:
    MainWindow *m_MainDialog;
    CLoginDialog *m_LoginDialog;
    CDataShowDialog *m_DataShowDialog;
    CRegisterDialog *m_RegsiterDialog;
    CToolForm *m_ToolForm;
    CDataBase *m_DataBase;
    bool m_Admin;
    QApplication *m_App;

public:
    void getApp(QApplication &app);

signals:

public slots:
    void slot_Message(Message);
    void slot_ToolForm(QString,QList<int>);
    void slot_RegisterDialog();
    void slot_Logout();
    void slot_Login();
    void slot_SetStyle(QString style);

};

#endif // CCONTROLBLOCK_H
