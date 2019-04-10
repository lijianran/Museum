#include "ccontrolblock.h"

CControlBlock::CControlBlock(QObject *parent) : QObject(parent)
{

    CReadImage::checkDirectory();

    m_DataBase = new CDataBase();

    m_MainDialog = new MainWindow();
    m_LoginDialog = new CLoginDialog();
    m_DataShowDialog = new CDataShowDialog();
    m_RegsiterDialog = new CRegisterDialog();
    m_ToolForm = new CToolForm();

    m_Admin = false;

    //注册界面
    connect(m_RegsiterDialog,SIGNAL(signal_Message(Message)),this,SLOT(slot_Message(Message)));
    connect(m_LoginDialog,SIGNAL(signal_ConfirmUser(QString,QString)),m_DataBase,SLOT(slot_ConfirmUser(QString,QString)));
    connect(m_LoginDialog,SIGNAL(signal_ConfirmAdmin(QString,QString)),m_DataBase,SLOT(slot_ConfirmAdmin(QString,QString)));
    connect(m_LoginDialog,SIGNAL(signal_Register()),this,SLOT(slot_RegisterDialog()));
    connect(m_RegsiterDialog,SIGNAL(signal_RegisterUser(User)),m_DataBase,SLOT(slot_RegisterUser(User)));
    connect(m_RegsiterDialog,SIGNAL(signal_RegisterAdmin(User)),m_DataBase,SLOT(slot_RegisterAdmin(User)));

    //事务
    connect(m_DataBase,SIGNAL(signal_Message(Message)),this,SLOT(slot_Message(Message)));

    //更新人物、皇帝列表
    connect(m_MainDialog,SIGNAL(signal_GetListData()),m_DataBase,SLOT(slot_SetListData()));
    connect(m_DataBase,SIGNAL(signal_RefleshList(QList<QString>)),m_MainDialog,SLOT(slot_RefleshList(QList<QString>)));
    //查找
    connect(m_MainDialog,SIGNAL(signal_SerachData(QString)),m_DataBase,SLOT(slot_SearchData(QString)));
    connect(m_DataBase,SIGNAL(signal_ShowSearch(QList<QString>)),m_MainDialog,SLOT(slot_ShowSearchList(QList<QString>)));

    //用户操作
    connect(m_MainDialog,SIGNAL(signal_GetUserData()),m_DataBase,SLOT(slot_SetUserData()));
    connect(m_DataBase,SIGNAL(signal_ShowUser(User)),m_MainDialog,SLOT(slot_SetUser(User)));
    connect(m_DataBase,SIGNAL(signal_ShowUser(User)),m_LoginDialog,SLOT(slot_SetUser(User)));
    connect(m_MainDialog,SIGNAL(signal_UpdatePwds(QString)),m_DataBase,SLOT(slot_UpdatePwds(QString)));
    connect(m_MainDialog,SIGNAL(signal_UpdateUser(User)),m_DataBase,SLOT(slot_UpdateUser(User)));
    connect(m_MainDialog,SIGNAL(signal_Logout()),this,SLOT(slot_Logout()));


    //主界面
    connect(m_MainDialog,SIGNAL(signal_SetDataBase(QQmlContext&)),m_DataBase,SLOT(slot_SetDataBase(QQmlContext&)));
    connect(m_MainDialog,SIGNAL(signal_ToAddData()),m_DataShowDialog,SLOT(slot_ToAddData()));

    //显示人物信息
    connect(m_MainDialog,SIGNAL(signal_ShowData(QString)),m_DataBase,SLOT(slot_ShowData(QString)));
    connect(m_DataBase,SIGNAL(signal_ShowPerson(Person)),m_DataShowDialog,SLOT(slot_SetPerson(Person)));


    //人物信息框
    connect(m_DataShowDialog,SIGNAL(signal_UpdateData(Person,QString)),m_DataBase,SLOT(slot_UpdateData(Person,QString)));
    connect(m_DataShowDialog,SIGNAL(signal_AddData(Person)),m_DataBase,SLOT(slot_AddData(Person)));
    connect(m_DataShowDialog,SIGNAL(signal_DeleteData(QString)),m_DataBase,SLOT(slot_DeleteData(QString)));

    //提示框
    connect(m_LoginDialog,SIGNAL(signal_ToolForm(QString,QList<int>)),this,SLOT(slot_ToolForm(QString,QList<int>)));
    connect(m_RegsiterDialog,SIGNAL(signal_ToolForm(QString,QList<int>)),this,SLOT(slot_ToolForm(QString,QList<int>)));
    connect(m_MainDialog,SIGNAL(signal_ToolForm(QString,QList<int>)),this,SLOT(slot_ToolForm(QString,QList<int>)));
    connect(m_DataShowDialog,SIGNAL(signal_ToolForm(QString,QList<int>)),this,SLOT(slot_ToolForm(QString,QList<int>)));


    //警示框
    connect(m_DataShowDialog,SIGNAL(signal_WarningInfo(QString,QList<int>,bool&)),m_ToolForm,SLOT(WarningInfo(QString,QList<int>,bool&)));
    connect(m_MainDialog,SIGNAL(signal_WarningInfo(QString,QList<int>,bool&)),m_ToolForm,SLOT(WarningInfo(QString,QList<int>,bool&)));

    //登陆动画
    connect(m_LoginDialog,SIGNAL(signal_ToMainWindow()),this,SLOT(slot_Login()));


    connect(m_MainDialog,SIGNAL(signal_ChangeStyle(QString)),this,SLOT(slot_SetStyle(QString)));
    //开始
    m_LoginDialog->showWindow();
}


void CControlBlock::slot_Message(Message message)
{
    QList<int> login;
    login.push_back(m_LoginDialog->geometry().x());
    login.push_back(m_LoginDialog->geometry().y());
    login.push_back(m_LoginDialog->geometry().width());
    login.push_back(m_LoginDialog->geometry().height());
    QList<int> regit;
    regit.push_back(m_RegsiterDialog->geometry().x());
    regit.push_back(m_RegsiterDialog->geometry().y());
    regit.push_back(m_RegsiterDialog->geometry().width());
    regit.push_back(m_RegsiterDialog->geometry().height());
    QList<int> data;
    data.push_back(m_DataShowDialog->geometry().x());
    data.push_back(m_DataShowDialog->geometry().y());
    data.push_back(m_DataShowDialog->geometry().width());
    data.push_back(m_DataShowDialog->geometry().height());
    QList<int> main;
    main.push_back(m_MainDialog->geometry().x());
    main.push_back(m_MainDialog->geometry().y());
    main.push_back(m_MainDialog->geometry().width());
    main.push_back(m_MainDialog->geometry().height());
    QList<int> pos;

    switch (message) {
    case SUCCESS_CONFIRMUSER:
        m_Admin = false;
        m_LoginDialog->userLogin();
        break;
    case SUCCESS_CONFIRMADMIN:
        m_Admin = true;
        m_LoginDialog->hide();
        m_MainDialog->showWindow(m_Admin);
        pos.push_back(m_MainDialog->geometry().x());
        pos.push_back(m_MainDialog->geometry().y());
        pos.push_back(m_MainDialog->geometry().width());
        pos.push_back(m_MainDialog->geometry().height());
        slot_ToolForm("管理员登录成功",pos);
        m_LoginDialog->clear(2);
        break;
    case FAILURE_CONFIRMUSER_USER:
        m_LoginDialog->shackWindow();
        slot_ToolForm("用户名不存在！",login);
        break;
    case FAILURE_CONFIRMUSER_PWDS:
        m_LoginDialog->shackWindow();
        slot_ToolForm("密码错误！",login);
        break;
    case SUCCESS_SETDATA_CELEBRITY://显示名人信息
        m_DataShowDialog->showWindow(m_Admin);
        break;
    case SUCCESS_SETDATA_EMPEROR://显示皇帝信息
        m_DataShowDialog->showWindow(m_Admin,true);
        break;
    case FAILURE_SETDATA:
        m_MainDialog->shackWindow();
        break;
    case SUCCESS_REGISTER_USER:
        slot_ToolForm("用户注册成功！",regit);
        m_RegsiterDialog->closeWindow();
        m_LoginDialog->showWindow();
        break;
    case SUCCESS_REGISTER_ADMIN:
        slot_ToolForm("管理员注册成功！",regit);
        m_RegsiterDialog->closeWindow();
        m_LoginDialog->showWindow();
        break;
    case FAILURE_REGISTER:
        m_LoginDialog->showWindow();
        slot_ToolForm("取消注册！",login);
        break;
    case FAILURE_REGISTER_REPEAT:
        m_RegsiterDialog->shackWindow();
        slot_ToolForm("用户名已被注册！",regit);
        break;
    case SUCCESS_ADDPERSON:
        m_DataShowDialog->closeWindow();
        slot_ToolForm("添加成功！",data);
        break;
    case FAILURE_ADDPERSON_REPEAT:
        m_DataShowDialog->shackWindow();
        slot_ToolForm("重复添加，操作失败！",data);
        break;
    case SUCCESS_DELETEPERSON:
        m_DataShowDialog->closeWindow();
        slot_ToolForm("删除成功！",data);
        break;
    case SUCCESS_UPDATE_USER:
        m_MainDialog->clear(5);
        slot_ToolForm("信息修改成功！",main);
        break;
    case SUCCESS_UPDATE_PWDS:
        m_MainDialog->clear(1);
        slot_ToolForm("密码修改成功！",main);
        break;
    case SUCCESS_UPDATE_PERSON:
        m_DataShowDialog->closeWindow();
        slot_ToolForm("更新成功！",main);
        break;
    case FAILURE_UPDATE_REPEAT:
        m_DataShowDialog->shackWindow();
        slot_ToolForm("同名更改失败！",data);
        break;
    case SUCCESS_SEARCH:
        slot_ToolForm("查询成功！",main);
        break;
    case FAILURE_SEARCH:
        m_MainDialog->shackWindow();
        slot_ToolForm("查无结果！",main);
        break;
    }
}

void CControlBlock::slot_ToolForm(QString str,QList<int> pos)
{
    m_ToolForm->MoveOut(str,pos[0],pos[1],pos[2],pos[3]);
}

void CControlBlock::slot_RegisterDialog()
{
    m_LoginDialog->hide();
    m_RegsiterDialog->showWindow();
}

void CControlBlock::slot_Logout()
{
    m_MainDialog->hide();
    m_MainDialog->clear(0);
    m_LoginDialog->showWindow();
    m_LoginDialog->clear(1);
}

void CControlBlock::slot_Login()
{
    m_MainDialog->showWindow(m_Admin);
    QList<int> main;
    main.push_back(m_MainDialog->geometry().x());
    main.push_back(m_MainDialog->geometry().y());
    main.push_back(m_MainDialog->geometry().width());
    main.push_back(m_MainDialog->geometry().height());
    slot_ToolForm("用户登录成功",main);
}

void CControlBlock::slot_SetStyle(QString style)
{
    QFile qss(":/res/qss/"+style+".qss");
    qss.open(QFile::ReadOnly);
    m_App->setStyleSheet(qss.readAll());
    qss.close();
}

void CControlBlock::getApp(QApplication &app)
{
    m_App = &app;
    QFile qss(":/res/qss/whitestyle.qss");
    qss.open(QFile::ReadOnly);
    m_App->setStyleSheet(qss.readAll());
    qss.close();
}
