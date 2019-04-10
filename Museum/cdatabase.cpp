#include "cdatabase.h"

CDataBase::CDataBase(QObject *parent) : QObject(parent)
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        m_database = QSqlDatabase::database("qt_sql_default_connection");
    else
        m_database = QSqlDatabase::addDatabase("QSQLITE");

    connectDB("users.db");
}

bool CDataBase::connectDB(QString db_name)
{
    m_database.setDatabaseName(db_name);

    if(db_name == "users.db")
        checkTables(db_name);
    return true;
}

void CDataBase::checkTables(QString db_name)
{
    if(db_name != "users.db")
        return;
    openDataBase();
    if(!m_database.tables().contains("users"))
    {
        QSqlQuery query;
        query.exec("CREATE TABLE users"
                   "(username VARCHAR(20) PRIMARY KEY,"
                   "name VARCHAR(10),"
                   "sex VARCHAR(4),"
                   "tel VARCHAR(12),"
                   "pwds VARCHAR(30),"
                   "registerdate VARCHAR(30))");
    }
    if(!m_database.tables().contains("admin"))
    {
        QSqlQuery query;
        query.exec("CREATE TABLE admin"
                   "(admin VARCHAR(20) PRIMARY KEY,"
                   "name VARCHAR(10),"
                   "sex VARCHAR(4),"
                   "tel VARCHAR(12),"
                   "pwds VARCHAR(30),"
                   "registerdate VARCHAR(30))");
    }
    closeDataBase();
}

bool CDataBase::openDataBase()
{
    if (!m_database.open()) {

        return false;
    }
    return true;
}

bool CDataBase::closeDataBase()
{
    if(!m_database.isOpen())
        return false;
    else
        m_database.close();
    return true;
}

QList<QString> CDataBase::person() const
{
    return m_PersonList;
}
void CDataBase::setPerson(QList<QString>& list)
{
    m_PersonList = list;
    emit personChanged();
}

QList<QString> CDataBase::images() const
{
    return m_ImagesList;
}
void CDataBase::setImages(QList<QString>& list)
{
    m_ImagesList = list;
    emit imagesChanged();
}

int CDataBase::personNum() const
{
    return m_PersonNum;
}
void CDataBase::setPersonNum(int &num)
{
    m_PersonNum = num;
    emit personNumChanged();
}


bool CDataBase::slot_SetDataBase(QQmlContext& content)
{
    content.setContextProperty("m_DataBase",this);

    connectDB("data.db");
    openDataBase();
    QSqlQuery query;

    query.exec("select name from celebrity;");
    QList<QString> person_list;
    while(query.next())
    {
        QString name = query.value(0).toString();
        person_list.push_back(name);
    }
    int num = person_list.size();
    QList<QString> images_list = CReadImage::setQmlImages(person_list);
    setPersonNum(num);
    setImages(images_list);
    setPerson(person_list);
    closeDataBase();
    return true;

}


bool CDataBase::slot_ConfirmUser(QString user,QString pwds)
{
    connectDB("users.db");
    openDataBase();
    QSqlQuery query;
    query.exec("select username from users;");
    while(query.next())
    {
        if(query.value(0).toString() == user)
        {
            query.exec("select pwds from users where username='"+user+"';");
            query.next();
            if(query.value(0).toString() == pwds)
            {
                m_username = user;
                m_userpwds = pwds;
                closeDataBase();
                slot_SetUserData();
                emit signal_Message(SUCCESS_CONFIRMUSER);
                return true;
            }
            else
            {
                closeDataBase();
                emit signal_Message(FAILURE_CONFIRMUSER_PWDS);
                return false;
            }
        }
    }
    closeDataBase();
    emit signal_Message(FAILURE_CONFIRMUSER_USER);
    return false;
}

bool CDataBase::slot_ConfirmAdmin(QString admin,QString pwds)
{
    connectDB("users.db");
    openDataBase();
    QSqlQuery query;
    query.exec("select admin from admin;");
    while(query.next())
    {
        if(query.value(0).toString() == admin)
        {
            query.exec("select pwds from admin where admin='"+admin+"';");
            query.next();
            if(query.value(0).toString() == pwds)
            {
                m_username = admin;
                m_userpwds = pwds;
                closeDataBase();
                emit signal_Message(SUCCESS_CONFIRMADMIN);
                return true;
            }
            else
            {
                closeDataBase();
                emit signal_Message(FAILURE_CONFIRMUSER_PWDS);
                return false;
            }
        }
    }
    closeDataBase();
    emit signal_Message(FAILURE_CONFIRMUSER_USER);
    return false;
}

bool CDataBase::slot_RegisterUser(User user)
{
    connectDB("users.db");
    openDataBase();
    QSqlQuery query;
    QString str = "select count(*) from users where username='"+user.user+"';";
    query.exec(str);
    query.next();
    int n=query.value(0).toInt();
    if(n == 1)
    {
        emit signal_Message(FAILURE_REGISTER_REPEAT);
        return false;
    }
    str = "select count(*) from admin where admin='"+user.user+"';";
    query.exec(str);
    query.next();
    n=query.value(0).toInt();
    if(n == 1)
    {
        emit signal_Message(FAILURE_REGISTER_REPEAT);
        return false;
    }
    query.prepare("insert into users (username, name, sex, tel, pwds, registerdate)"
                  "values(:stuid, :name, :sex, :tel, :pwds, :date)");
    query.bindValue(":stuid",user.user);
    query.bindValue(":name",user.name);
    query.bindValue(":sex",user.sex);
    query.bindValue(":tel",user.tel);
    query.bindValue(":pwds",user.pwds);
    query.bindValue(":date",user.date);
    query.exec();

    closeDataBase();
    emit signal_Message(SUCCESS_REGISTER_USER);
    return true;
}

bool CDataBase::slot_RegisterAdmin(User admin)
{
    connectDB("users.db");
    openDataBase();
    QSqlQuery query;
    QString str = "select count(*) from admin where admin='"+admin.user+"';";
    query.exec(str);
    query.next();
    int n=query.value(0).toInt();
    if(n == 1)
    {
        emit signal_Message(FAILURE_REGISTER_REPEAT);
        return false;
    }
    str = "select count(*) from users where username='"+admin.user+"';";
    query.exec(str);
    query.next();
    n=query.value(0).toInt();
    if(n == 1)
    {
        emit signal_Message(FAILURE_REGISTER_REPEAT);
        return false;
    }
    query.prepare("insert into admin (admin, name, sex, tel, pwds, registerdate)"
                  "values(:stuid, :name, :sex, :tel, :pwds, :date)");
    query.bindValue(":stuid",admin.user);
    query.bindValue(":name",admin.name);
    query.bindValue(":sex",admin.sex);
    query.bindValue(":tel",admin.tel);
    query.bindValue(":pwds",admin.pwds);
    query.bindValue(":date",admin.date);
    query.exec();

    closeDataBase();
    emit signal_Message(SUCCESS_REGISTER_ADMIN);
    return true;
}

bool CDataBase::slot_SetUserData()
{
    connectDB("users.db");
    openDataBase();
    QSqlQuery query;

    query.exec("select * from users where username = '"+m_username+"';");
    User user;
    while(query.next())
    {
        user.user = query.value(0).toString();
        user.name = query.value(1).toString();
        user.sex = query.value(2).toString();
        user.tel = query.value(3).toString();
        user.pwds = query.value(4).toString();
        user.date = query.value(5).toString();
        emit signal_ShowUser(user);
        closeDataBase();
        return true;
    }

    query.exec("select * from admin where admin = '"+m_username+"';");
    while(query.next())
    {
        user.user = query.value(0).toString();
        user.name = query.value(1).toString();
        user.sex = query.value(2).toString();
        user.tel = query.value(3).toString();
        user.pwds = query.value(4).toString();
        user.date = query.value(5).toString();
        emit signal_ShowUser(user);
        closeDataBase();
        return true;
    }
    closeDataBase();
    return false;
}

bool CDataBase::slot_SetListData()
{
    connectDB("data.db");
    openDataBase();
    QSqlQuery query;

    query.exec("select name,title from celebrity;");
    QList<QString> person_list;
    while(query.next())
    {
        QString name = query.value(0).toString();
        QString title = query.value(1).toString();
        person_list.push_back(name);
        person_list.push_back(title);
    }

    query.exec("select name,pasttitle from emperor;");
    while(query.next())
    {
        QString name = query.value(0).toString();
        QString pasttitle = query.value(1).toString();
        person_list.push_back(name);
        person_list.push_back(pasttitle);
    }

    closeDataBase();
    emit signal_RefleshList(person_list);
    return true;
}

bool CDataBase::slot_SearchData(QString str)
{
    connectDB("data.db");
    openDataBase();
    QSqlQuery query;

    query.exec("select * from celebrity where name like '%"+str+"%';");
    Person person;
    QList<QString> person_list;
    while(query.next())
    {
        QString name = query.value(0).toString();
        QString title = query.value(1).toString();
        person_list.push_back(name);
        person_list.push_back(title);
    }
    if(person_list.size() == 0)
    {
        emit signal_Message(FAILURE_SEARCH);
        emit signal_ShowSearch(person_list);
        closeDataBase();
        return false;
    }
    else
    {
        emit signal_Message(SUCCESS_SEARCH);
        emit signal_ShowSearch(person_list);
        closeDataBase();
        return true;
    }
}

bool CDataBase::slot_ShowData(QString name)
{
    connectDB("data.db");
    openDataBase();
    QSqlQuery query;

    query.exec("select * from celebrity where name = '"+name+"';");
    Person person;
    while(query.next())
    {
        person.name = query.value(0).toString();
        person.title = query.value(1).toString();
        person.date = query.value(2).toString();
        person.describe = query.value(3).toString();

        closeDataBase();
        emit signal_ShowPerson(person);
        emit signal_Message(SUCCESS_SETDATA_CELEBRITY);
        return true;
    }

    query.exec("select * from emperor where pasttitle = '"+name+"';");
    while(query.next())
    {
        person.name = query.value(0).toString();
        person.title = query.value(1).toString();
        person.date = query.value(2).toString();
        person.describe = "";

        closeDataBase();
        emit signal_ShowPerson(person);
        emit signal_Message(SUCCESS_SETDATA_EMPEROR);
        return true;
    }

    emit signal_Message(FAILURE_SETDATA);
    closeDataBase();
    return false;
}

bool CDataBase::slot_UpdatePwds(QString pwds)
{
    connectDB("users.db");
    openDataBase();
    QSqlQuery query;

    query.exec("update users set pwds = '"+pwds+"' where username ='"+m_username+"';");

    closeDataBase();
    emit signal_Message(SUCCESS_UPDATE_PWDS);
    return true;
}

bool CDataBase::slot_UpdateUser(User user)
{
    connectDB("users.db");
    openDataBase();
    QSqlQuery query;

    query.exec("update users set name = '"+user.name+"' where username ='"+m_username+"';");
    query.exec("update users set sex = '"+user.sex+"' where username ='"+m_username+"';");
    query.exec("update users set tel = '"+user.tel+"' where username ='"+m_username+"';");

    closeDataBase();
    emit slot_SetUserData();
    emit signal_Message(SUCCESS_UPDATE_USER);
    return true;
}

bool CDataBase::slot_UpdateData(Person person,QString name)
{
    connectDB("data.db");
    openDataBase();
    QSqlQuery query;

    if(person.describe == "")
    {
        query.exec("update emperor set pasttitle = '"+person.title+"' where pasttitle ='"+name+"';");
        query.exec("update emperor set period = '"+person.date+"' where pasttitle ='"+name+"';");

        closeDataBase();
        slot_SetListData();
        emit signal_Message(SUCCESS_UPDATE_PERSON);
        return true;
    }

    if(person.name != name)
    {
        QString str = "select count(*) from celebrity where name='"+person.name+"';";
        query.exec(str);
        query.next();
        int n=query.value(0).toInt();
        if(n == 1)
        {
            slot_ShowData(name);
            emit signal_Message(FAILURE_UPDATE_REPEAT);
            return false;
        }
    }

    query.exec("update celebrity set title = '"+person.title+"' where name ='"+name+"';");
    query.exec("update celebrity set date = '"+person.date+"' where name ='"+name+"';");
    query.exec("update celebrity set desc = '"+person.describe+"' where name ='"+name+"';");
    query.exec("update celebrity set name = '"+person.name+"' where name ='"+name+"';");

    closeDataBase();
    slot_SetListData();
    emit signal_Message(SUCCESS_UPDATE_PERSON);
    return true;
}

bool CDataBase::slot_AddData(Person person)
{
    connectDB("data.db");
    openDataBase();
    QSqlQuery query;
    QString str = "select count(*) from celebrity where name='"+person.name+"';";
    query.exec(str);
    query.next();
    int n=query.value(0).toInt();
    if(n == 1)
    {
        emit signal_Message(FAILURE_ADDPERSON_REPEAT);
        return false;
    }
    query.prepare("insert into celebrity(name, title, date, desc)"
                  "values(:name, :title, :date, :desc)");
    query.bindValue(":name",person.name);
    query.bindValue(":title",person.title);
    query.bindValue(":date",person.date);
    query.bindValue(":desc",person.describe);
    query.exec();

    closeDataBase();
    slot_SetListData();
    emit signal_Message(SUCCESS_ADDPERSON);
    return true;
}

bool CDataBase::slot_DeleteData(QString name)
{
    connectDB("data.db");
    openDataBase();
    QSqlQuery query;

    query.exec("delete from celebrity where name = '"+name+"';");

    closeDataBase();
    slot_SetListData();
    emit signal_Message(SUCCESS_DELETEPERSON);
    return true;
}



