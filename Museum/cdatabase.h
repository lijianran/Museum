#ifndef CDATABASE_H
#define CDATABASE_H

#include <QObject>
#include "cheader.h"
#include <QSqlDatabase>
#include <QSqlQuery>

class CDataBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> person READ person WRITE setPerson NOTIFY personChanged)
    Q_PROPERTY(QList<QString> images READ images WRITE setImages NOTIFY imagesChanged)
    Q_PROPERTY(int personnum READ personNum WRITE setPersonNum NOTIFY personNumChanged)

public:
    explicit CDataBase(QObject *parent = nullptr);

public:
    QList<QString> person() const;
    void setPerson(QList<QString>&);

    QList<QString> images() const;
    void setImages(QList<QString>&);

    int personNum() const;
    void setPersonNum(int &);


protected:
    QString m_database_name;
    QSqlDatabase m_database;
    QString m_username;
    QString m_userpwds;

    QList<QString> m_PersonList;
    QList<QString> m_ImagesList;
    int m_PersonNum;

protected:
    bool connectDB(QString db_name);
    void checkTables(QString db_name);
    bool openDataBase();
    bool closeDataBase();


signals:
    void personChanged();
    void imagesChanged();
    void personNumChanged();

    void signal_Message(Message);
    void signal_RefleshList(QList<QString>);
    void signal_ShowUser(User);
    void signal_ShowPerson(Person);
    void signal_ShowSearch(QList<QString>);

protected slots:
    bool slot_SetDataBase(QQmlContext&);

    bool slot_ConfirmUser(QString,QString);
    bool slot_ConfirmAdmin(QString,QString);
    bool slot_RegisterUser(User);
    bool slot_RegisterAdmin(User);

    bool slot_SetUserData();
    bool slot_SetListData();
    bool slot_SearchData(QString);

    bool slot_ShowData(QString);
    bool slot_UpdatePwds(QString);
    bool slot_UpdateUser(User);

    bool slot_UpdateData(Person,QString);
    bool slot_AddData(Person);
    bool slot_DeleteData(QString);

};

#endif // CDATABASE_H
