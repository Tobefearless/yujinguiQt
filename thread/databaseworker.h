#ifndef DATABASEWORKER_H
#define DATABASEWORKER_H

#include <QObject>
#include "dataBase/mysqldatabase.h"
#include "dataBase/sqlserverhandler.h"
class DatabaseWorker : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseWorker(QObject *parent = nullptr);
    ~DatabaseWorker();
    void fetchLatestPickedProductData();
    void fetchSensorData();
    void fetchWeighbridgeData();
    void stop();  // 添加停止方法
signals:
    void pickedProducdataReady(const QList<pickedProduct_Type>& products);
    void RawInspectcdataReady(const QList<RawInspectionRow>& RawInspectionRow);
    void sensorDataReady(const QList<SensorData_Type>& products);
    void weighbridgeDataReady(const QList<WeighRecordViewType>& weighRecords);

    void databaseError(const QString& errorMessage);  // 新增错误信号
public slots:

private:
    bool checkAndReconnect(const QString& connectionName, int sleepSeconds = 5);
    void safeSleep(int seconds);

private:
    MySQLDatabase* m_db;
    QAtomicInteger<int> m_stopRequested;  // 使用 QAtomicInteger 替代 QAtomicInt
    static QMutex mutex;
};

#endif // DATABASEWORKER_H
