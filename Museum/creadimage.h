#ifndef CREADIMAGE_H
#define CREADIMAGE_H

#include <QLabel>
#include <QDir>
#include <QFile>
#include <QImage>

class CReadImage
{
public:
    CReadImage();

public:
    static void checkDirectory();

    static QStringList findnamelist(QString);

    static void copyUserImage(QString,QString);

    static void copyPersonImage(QString,QString);

    static QList<QString> setQmlImages(QList<QString>);

    static void setUserIcon(QLabel*,QString);

    static void setCelebrityPic(QLabel*,QString);

};

#endif // CREADIMAGE_H
