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
signals:
    void pickedProducdataReady(const QList<pickedProduct_Type>& products);
    void RawInspectcdataReady(const QList<RawInspectionRow>& RawInspectionRow);
    void sensorDataReady(const QList<SensorData_Type>& products);
    void WeighbridgeDataReady(QSqlQueryModel* model );
public slots:

private:
    MySQLDatabase* m_db;
    SQLServerHandler sqlServerHandler;
    bool m_stop = false;
    bool m_initialized = false;
    static QMutex mutex;
};

#endif // DATABASEWORKER_H
