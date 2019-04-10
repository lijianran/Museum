#ifndef CHEADER_H
#define CHEADER_H

#include <QDialog>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QStatusBar>
#include <QFont>
#include <QDateTime>
#include <QVariant>
#include <QtQml>
#include <QString>
#include <QButtonGroup>
#include <QRegExpValidator>
#include <QFrame>
#include <QFileDialog>
#include "creadimage.h"
#include "ctoolform.h"


typedef enum _Message_Type
{
    SUCCESS_CONFIRMUSER,
    SUCCESS_CONFIRMADMIN,
    FAILURE_CONFIRMUSER_USER,
    FAILURE_CONFIRMUSER_PWDS,


    SUCCESS_SETDATA_CELEBRITY,
    SUCCESS_SETDATA_EMPEROR,
    FAILURE_SETDATA,

    SUCCESS_REGISTER_USER,
    SUCCESS_REGISTER_ADMIN,
    FAILURE_REGISTER,
    FAILURE_REGISTER_REPEAT,


    SUCCESS_ADDPERSON,
    FAILURE_ADDPERSON_REPEAT,

    SUCCESS_DELETEPERSON,

    SUCCESS_UPDATE_PWDS,
    SUCCESS_UPDATE_USER,
    SUCCESS_UPDATE_PERSON,
    FAILURE_UPDATE_REPEAT,


    SUCCESS_SEARCH,
    FAILURE_SEARCH,



}Message;

typedef struct _Person_Data
{
    QString name;
    QString title;
    QString date;
    QString describe;

}Person;

typedef struct _User_Data
{
    QString user;
    QString name;
    QString sex;
    QString tel;
    QString pwds;
    QString date;

}User;

#endif // CHEADER_H
