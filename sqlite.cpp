#include "sqlite.h"
/**
 * @brief Sqlite::Sqlite,无参声明
 * @param 无参初始化，需要调用openDB()初始化
 * @author silen
 */
Sqlite::Sqlite()
{

//    openDB("sqlite.db");//打开连接
//    createTable("test_table");//创建数据库表
//    insertRecord("test_table");
//    queryRecord(1);

}
/**
 * @brief Sqlite::Sqlite,含参声明
 * @param db,数据库名，默认'sqlite.db'
 * @author silen
 */
Sqlite::Sqlite(QString db)
{
    if(db.isNull() || db.isEmpty())
        db = "sqlite.db";
    openDB(db);//打开连接

}

Sqlite::~Sqlite()
{

}
/**
 * @brief Sqlite::openDB,打开数据库
 * @param db_name,数据库名，默认'sqlite.db'
 * @author silen
 */
void Sqlite::openDB(QString db_name)
{
    if(db_name.isNull() || db_name.isEmpty()){
        db_name = "sqlite.db";
    }
    db =QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("database-3313b0");          //设置数据库主机名
    db.setDatabaseName(db_name);              //设置数据库名
    db.setUserName("silen");                //设置数据库用户名
    db.setPassword("123456");
    db.setPort(8188);//设置数据库密码
    db.open();                             		//打开连接
}

/**
 * @brief Sqlite::createTable,创建表
 * @param tb_name,数据表名
 * @param columns,表结构,格式(字段 类型,字段 类型)，注意id和日期自动生成无需包含，例:"attribute varchar,type varchar"
 * @return true/false
 * @author silen
 */
bool Sqlite::createTable(QString tb_name, QString columns)
{
    QSqlQuery query;
    if(tb_name.isNull() || tb_name.isEmpty()){
        tb_name = "test_table";
    }
    if(columns.isNull() || columns.isEmpty()){
        columns = "attribute varchar,type varchar,nation varchar";
    }
    bool success=query.exec(QString("create table %1 (id varchar primary key,%2, time datetime)").arg(tb_name).arg(columns));
    if(success){
        qDebug()<<QObject::tr("数据库表创建成功！\n");
        return true;
    }
    else{
        qDebug()<<QObject::tr("数据库表创建失败！\n");
        return false;
    }
}

/**
 * @brief Sqlite::dropTable,删除表
 * @param tb_name,数据表名
 * @return true/false
 * @author silen
 */
bool Sqlite::dropTable(QString tb_name)
{
    QSqlQuery query;
    if(tb_name.isNull() || tb_name.isEmpty()){
        tb_name = "test_table";
    }
    bool success=query.exec("drop table "+tb_name+" ;");
    if(success){
        qDebug()<<QObject::tr("数据库表删除成功！\n");
        return true;
    }
    else{
        qDebug()<<QObject::tr("数据库表删除失败！\n");
        return false;
    }
}

/**
 * @brief Sqlite::queryRecById,按ID查询
 * @param tb_name,数据表名
 * @param id,主键id
 * @return query,查询结果集
 * @author silen
 */
QSqlQuery Sqlite::queryRecById(QString tb_name, QString id)
{
    //查询
    QSqlQuery query;
    if(tb_name.isNull() || tb_name.isEmpty()){
        tb_name = "test_table";
    }
    query.prepare(QString("select * from %1 where id=%2 order by time desc").arg(tb_name).arg(id));
    success=query.exec();
    if(!success)
    {
        QSqlError lastError=query.lastError();
        qDebug()<<lastError.driverText()<<QString(QObject::tr("查询失败"));
    }
    return query;
}

/**
 * @brief Sqlite::queryRecByTime,按time查询
 * @param tb_name,数据表名
 * @param time,时间,格式(时间字符串;时间字符串),注意日期要严格遵循样例格式，例:"1970-01-01;2016-01-15"
 * @return query,查询结果集
 * @author silen
 */
QSqlQuery Sqlite::queryRecByTime(QString tb_name, QString time)
{
    //查询
    QSqlQuery query;
    if(tb_name.isNull() || tb_name.isEmpty()){
        tb_name = "test_table";
    }
    if(time.isNull() || time.isEmpty()){
        time = "2016-01-15;2016-01-16";
    }

    QString time_pre = time.split(";").at(0);
    QString time_bh = time.split(";").at(1);
    QString sql = "select * from "+tb_name+" where ";
    bool is_insert = false;
    if(!time_pre.isNull() && !time_pre.isEmpty()){
        sql.append("(datetime(time)>=datetime('"+time_pre + "'))");
        is_insert = true;
    }
    if(!time_bh.isNull() && !time_bh.isEmpty()){
        if(is_insert == true)
            sql.append(" and ");
        sql.append("(datetime(time)<datetime('"+time_bh + "'))");
    }
    sql.append(" order by time desc");
qDebug()<<sql;
    success=query.exec(sql);
    if(!success)
    {
        QSqlError lastError=query.lastError();
        qDebug()<<lastError.driverText()<<QString(QObject::tr("查询失败"));
    }
    return query;
}

/**
 * @brief queryRecord,关键字查询
 * @param tb_name,数据表名
 * @param attribute,查询关键字,格式(字段名;字段值),注意id自动生成无需包含，例:"id;001"
 * @return query,查询结果集
 * @author silen
 */
QSqlQuery Sqlite::queryRecord(QString tb_name, QString attribute)
{
    //查询
    QSqlQuery query;
    if(tb_name.isNull() || tb_name.isEmpty()){
        tb_name = "test_table";
    }
    if(attribute.isNull() || attribute.isEmpty()){
        attribute = "id;001";
    }
    QStringList parts = attribute.split(";");
    query.prepare(QString("select * from %1 where %2=%3 order by time desc").arg(tb_name).arg(parts[0]).arg(parts[1]));
    success=query.exec();
    if(!success)
    {
        QSqlError lastError=query.lastError();
        qDebug()<<lastError.driverText()<<QString(QObject::tr("查询失败"));
    }
    qDebug()<<query.record().count();

    return query;
}

/**
 * @brief Sqlite::queryCount 未实现
 * @param tb_name,数据表名
 * @return true/false
 * @author silen
 */
long Sqlite::queryCount(QString tb_name)
{
    //查询总数
    QSqlQuery query;
    if(tb_name.isNull() || tb_name.isEmpty()){
        tb_name = "test_table";
    }
    query.exec("select count(*) from "+tb_name);

    int numRows=0;
    while (query.next())
    {
        if (db.driver()->hasFeature(QSqlDriver::QuerySize))
        {
            //驱动支持返回记录数
            numRows = query.size();
        }
        else
        {
            //驱动不支持返回记录数，只能循环查找
            query.last();
            numRows = query.at() + 1;
        }
    }
    qDebug() << QObject::tr("test_table表记录数：" )<< numRows;
    return numRows;
}

/**
 * @brief Sqlite::insertRecord,插入记录
 * @param tb_name,数据表名
 * @param columns,插入字符串,格式(字段值,字段值),注意id自动生成无需包含,例:"001,abc"
 * @return true/false
 * @author silen
 */
bool Sqlite::insertRecord(QString tb_name, QString columns)
{
    //插入记录
    QSqlQuery query;
    QTime t;
    t.restart();

    if(tb_name.isNull() || tb_name.isEmpty()){
        tb_name = "test_table";
    }
    if(columns.isNull() || columns.isEmpty()){
        columns = "属性,类型,100";
    }

    QString time_str = QDateTime::currentDateTime().toString("yyMMddHHmmssmmm");
    QStringList parts = columns.split(",");
    QString sql = "insert into "+tb_name+" values (";
    sql.append("'"+time_str+"'"+",");
    for(int i=0;i<parts.size();i++){

        sql.append("'"+parts[i]+"',");
//        if(i<parts.size()-1)
//            sql.append(",");
    }
    QString time=QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    sql.append("'"+time+"')");
    query.prepare(sql);

    success=query.exec();
    if(!success)
    {
        QSqlError lastError=query.lastError();
        qDebug()<<lastError.driverText()<<QString(QObject::tr("插入失败"));
        return false;
    }
//qDebug()<<sql;
    return true;
}

/**
 * @brief Sqlite::updateRecord,更新记录
 * @param tb_name,数据表名
 * @param columns,更新字符串,格式('id';字段名='字段值',字段名='字段值'),注意id自动生成无需包含,例:"'001';type='abc',attr='123'"
 * @return true/false
 * @author silen
 */
bool Sqlite::updateRecord(QString tb_name, QString columns)
{
    //更新记录
    QSqlQuery query;
    t.restart();

    if(tb_name.isNull() || tb_name.isEmpty()){
        tb_name = "test_table";
    }
    if(columns.isNull() || columns.isEmpty()){
        columns = "'16';attribute='属性',type='类型',nation='100'";
    }

    QStringList parts = columns.split(";");

    QString sql = "update "+tb_name+" set " + parts[1] + " where id=" + parts[0];
    query.clear();
    query.prepare(sql);

    success=query.exec();
    //qDebug()<<sql;
    if(!success)
    {
        QSqlError lastError=query.lastError();
        qDebug()<<lastError.driverText()<<QString(QObject::tr("更新失败"));
        return false;
    }

    return true;
}

/**
 * @brief Sqlite::delRecord,删除记录
 * @param tb_name,数据表名
 * @param id,关键字ID
 * @return true/false
 * @author silen
 */
bool Sqlite::delRecord(QString tb_name,QString id)
{
    //删除
    QSqlQuery query;
    t.restart();
    if(tb_name.isNull() || tb_name.isEmpty()){
        tb_name = "test_table";
    }
    if(id.isNull() || id.isEmpty()){
        id = "001";
    }
    query.prepare(QString("delete from %1"
                              " where id=%2").arg(tb_name).arg(id));
    success=query.exec();
    if(!success)
    {
        QSqlError lastError=query.lastError();
        qDebug()<<lastError.driverText()<<QString(QObject::tr("删除失败"));
        return false;
    }

    return true;
}

/**
 * @brief Sqlite::clearTable,清空表
 * @param tb_name,数据表名
 * @return true/false
 * @author silen
 */
bool Sqlite::clearTable(QString tb_name)
{
    //删除
    QSqlQuery query;
    t.restart();
    if(tb_name.isNull() || tb_name.isEmpty()){
        tb_name = "test_table";
    }

    query.prepare(QString("delete from %1").arg(tb_name));
    success=query.exec();
    if(!success)
    {
        QSqlError lastError=query.lastError();
        qDebug()<<lastError.driverText()<<QString(QObject::tr("删除失败"));
        return false;
    }

    return true;
}
