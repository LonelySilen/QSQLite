#ifndef SQLITE_H
#define SQLITE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QDateTime>

class Sqlite
{
public:
    Sqlite();
    explicit Sqlite(QString);
    ~Sqlite();
public:
    void openDB(QString);
    bool createTable(QString, QString);
    bool dropTable(QString);
    QSqlQuery queryRecById(QString, QString);
    QSqlQuery queryRecByTime(QString, QString);
    QSqlQuery queryRecord(QString, QString );
    long queryCount(QString);
    bool insertRecord(QString, QString);
    bool updateRecord(QString, QString);
    bool delRecord(QString, QString);
    bool clearTable(QString);
private:
    QSqlDatabase db;
    QTime t;
    long records;
    bool success;
};

#endif // SQLITE_H
