#ifndef MYSQLDATABASE_H
#define MYSQLDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMutex>
#include <QDebug>
#include "value_type.h"
class MySQLDatabase : public QObject
{
    Q_OBJECT

   public:

       explicit MySQLDatabase(QObject *parent = nullptr);
       // 获取单例实例
       static MySQLDatabase* instance();

       // 初始化数据库连接
       bool initialize(const QString& host, int port,
                      const QString& database,
                      const QString& user,
                      const QString& password);

       // 插入产品数据
       bool insertProductData(const pickedProduct_Type& product);

       bool insertRawInspectionData(const RawInspectionRow& inspection);


       //打开数据库
       bool open(const QString connnectname);

       // 关闭数据库连接
       void close();

       bool toDB();

       bool  getLatestPickedProducts(QList<pickedProduct_Type>& products, int limit);
       bool  getLatestRawProducts(QList<RawInspectionRow>& products, int limit);


       //获取传感器数据
       QList<SensorData_Type> getAllRecords();
   private:
       // 禁止复制和赋值
       MySQLDatabase(const MySQLDatabase&) = delete;
       MySQLDatabase& operator=(const MySQLDatabase&) = delete;

       // 静态单例实例
       static MySQLDatabase* m_instance;
       static QMutex m_mutex;
       bool isopen;

       // 数据库连接
       QSqlDatabase m_db;
};

#endif // MYSQLDATABASE_H
