#include <QCoreApplication>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
#include "sqlite.h"

#include <QApplication>
#include <QSettings>
int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);
//    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
//    Sqlite *sqlite = new Sqlite("sqlite.db");
//    //sqlite->openDB("");
//    sqlite->createTable("","");
//    sqlite->insertRecord("","");
//    QSqlQuery query;
//    query = sqlite->queryRecByTime("","");
//    while(query.next())
//    {
//    qDebug()<<query.value("time").toString();
//    }
//    return 0;

    QApplication a(argc, argv);
    QSettings *configIni = new QSettings("config.ini", QSettings::IniFormat, 0);
    configIni->beginGroup("angle1");
    configIni->setValue("angle", "5");
    configIni->endGroup();

    configIni->beginGroup("angle2");
    configIni->setValue("angle", "10");
    configIni->endGroup();
    delete configIni;



    QSettings *readIni = new QSettings("config.ini", QSettings::IniFormat, 0);
    readIni->beginGroup("angle1");
    QStringList keys = readIni->allKeys();
    for(int i=0; i<keys.size(); i++)
    {
        qDebug()<<keys[i]<<endl;
        QString str = readIni->value(keys[i]).toString();
        qDebug()<<"str = "<<str<<endl;
    }
    delete readIni;
    return a.exec();
}
