#include "creadimage.h"

CReadImage::CReadImage()
{

}

void CReadImage::checkDirectory()
{
    QDir dir;
    if(!dir.exists("./users"))
        dir.mkdir("./users");
    if(!dir.exists("./celebrity"))
        dir.mkdir("./celebrity");

}

QStringList CReadImage::findnamelist(QString path)
{
    QDir dir(path);
    QStringList nameFilters;
    nameFilters<<"*png";
    QStringList files = dir.entryList(nameFilters,QDir::Files,QDir::Name);
    return files;
}

void CReadImage::copyUserImage(QString oldpath,QString name)
{
    QString newpath = "./users/"+name+".png";
    QFile file(newpath);
    if(file.exists())
        file.remove();
    QFile::copy(oldpath,newpath);
}

void CReadImage::copyPersonImage(QString oldpath,QString name)
{
    QString newpath = "./celebrity/"+name+".png";
    QFile file(newpath);
    if(file.exists())
        file.remove();
    QFile::copy(oldpath,newpath);
}

QList<QString> CReadImage::setQmlImages(QList<QString> name)
{
    QStringList names = CReadImage::findnamelist("./celebrity");

    QList<QString> images_path;
    for(int i=0;i<name.size();i++)
    {
        if(!names.contains(name[i]+".png"))
            images_path.push_back("file:celebrity/default.png");
        else
            images_path.push_back("file:celebrity/"+name[i]+".png");
    }
    return images_path;
}

void CReadImage::setUserIcon(QLabel* frame,QString name)
{
    QStringList names = CReadImage::findnamelist("./users");
    QString path;
    if(!names.contains(name+".png"))
        path = "./users/default.png";
    else
        path = "./users/"+name+".png";
    QImage icon;
    icon.load(path);
    int width = frame->width();
    int height = frame->height();
    QPixmap map = QPixmap::fromImage(icon);
    QPixmap fitIcon = map.scaled(width,height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    frame->setPixmap(fitIcon);
}

void CReadImage::setCelebrityPic(QLabel* frame,QString name)
{
    QStringList names = CReadImage::findnamelist("./celebrity");
    QString path;
    if(!names.contains(name+".png"))
        path = "./celebrity/default.png";
    else
        path = "./celebrity/"+name+".png";
    QImage icon;
    icon.load(path);
    int width = frame->width();
    int height = frame->height();
    QPixmap map = QPixmap::fromImage(icon);
    QPixmap fitIcon = map.scaled(width,height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    frame->setPixmap(fitIcon);

}
