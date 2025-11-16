#ifndef SQLSERVERHANDLER_H
#define SQLSERVERHANDLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QMap>
#include <QVariant>
#include <QVector>
#include <QSqlQueryModel>
#include "value_type.h"

class SQLServerHandler : public QObject
{
    Q_OBJECT

public:
    // 构造函数
    explicit SQLServerHandler(QObject *parent = nullptr);

    // 连接数据库
    bool connectToDatabase();

    // 断开数据库连接
    void disconnectDatabase();

    // 检查连接状态
    bool isConnected() const;

    // 执行查询并返回结果集
    QVector<QMap<QString, QVariant>> executeQuery(const QString &query);

    // 执行查询并返回模型（用于QTableView）
    QSqlQueryModel* getQueryModel(const QString &query);

    // 执行无结果集的SQL语句（INSERT, UPDATE, DELETE）
    bool executeNonQuery(const QString &query);

    // 执行带参数的SQL语句
    bool executeParameterizedQuery(const QString &query,
                                  const QMap<QString, QVariant> &params);

    // 开始事务
    bool beginTransaction();

    // 提交事务
    bool commitTransaction();

    // 回滚事务
    bool rollbackTransaction();

    // 获取最后错误信息
    QString lastError() const;

    // 测试连接
    bool testConnection();

    // 获取表结构信息
    QVector<QMap<QString, QString>> getTableStructure(const QString &tableName);

    // 获取所有称重记录
   QVector<WeightRecord_Type> getAllWeighRecords();

   // 按流水号查询称重记录
   WeightRecord_Type getWeighRecordByRunningNum(const QString &runningNum);

   // 按车牌号查询称重记录
   QVector<WeightRecord_Type> getWeighRecordsByLicenseplate(const QString &licenseplate);

   // 按时间范围查询称重记录
   QVector<WeightRecord_Type> getWeighRecordsByDateRange(const QDateTime &startDate,
                                                  const QDateTime &endDate);

   // 按多个条件查询称重记录
   QVector<WeightRecord_Type> getWeighRecordsByFilter(const QString &licenseplate = QString(),
                                               const QString &driver = QString(),
                                               const QString &productName = QString(),
                                               const QDateTime &startDate = QDateTime(),
                                               const QDateTime &endDate = QDateTime(),
                                               const QString &businessType = QString());

    QSqlQueryModel* getLastNRecords(int n, const QString& orderField, bool isDesc);

private:
    QSqlDatabase m_db;
    QString m_lastError;

    // 从查询结果构建称重记录对象
   WeightRecord_Type createWeighRecordFromQuery(QSqlQuery &query);
};

#endif // SQLSERVERHANDLER_H
