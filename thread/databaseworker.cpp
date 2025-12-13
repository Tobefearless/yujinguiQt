#include "databaseworker.h"
#include <QThread>

QMutex DatabaseWorker::mutex;


DatabaseWorker::DatabaseWorker(QObject *parent) : QObject(parent)
{
    m_db = new MySQLDatabase();
}

DatabaseWorker::~DatabaseWorker()
{
    qDebug()<<QThread::currentThreadId()<<"结束";
    m_db->deleteLater();
}

void DatabaseWorker::fetchLatestPickedProductData()
{
    const QString connectionName = "PickedProductData";
    const int fetchInterval = 10; // 数据获取间隔(秒)
    const int reconnectInterval = 20; // 重连间隔(秒)

    if (!m_db->open(connectionName)) {
        qCritical() << "初始化数据库连接失败:" << connectionName;
        emit databaseError("初始化产品数据连接失败");
    }

    bool flag = false;
    QList<pickedProduct_Type> pickedProducts;
    QList<RawInspectionRow> rawProducts;

    while (!m_stopRequested.load() && !QThread::currentThread()->isInterruptionRequested()) {

        if (!checkAndReconnect(connectionName, reconnectInterval)) {
            continue;
        }

        QMutexLocker locker(&mutex);  // 使用QMutexLocker自动管理锁

        bool success = false;
        if (flag) {
            if (m_db->getLatestRawProducts(rawProducts, 4)) {
                emit RawInspectcdataReady(rawProducts);
                qDebug() << "成功获取" << rawProducts.size() << "条原砂检验数据";
                success = true;
            } else {
                qWarning() << "获取原砂检验数据失败";
                emit databaseError("获取原砂检验数据失败");
            }
        } else {
            if (m_db->getLatestPickedProducts(pickedProducts, 10)) {
                emit pickedProducdataReady(pickedProducts);
                qDebug() << "成功获取" << pickedProducts.size() << "条酸洗产品数据";
                success = true;
            } else {
                qWarning() << "获取酸洗产品数据失败";
                emit databaseError("获取酸洗产品数据失败");
            }
        }

        flag = !flag;  // 切换标志

        if (success) {
            safeSleep(fetchInterval);
        } else {
            safeSleep(5);  // 失败时短暂等待后重试
        }
    }

    qDebug() << "产品数据获取线程退出";
}

void DatabaseWorker::fetchSensorData()
{
    const QString connectionName = "SensorData";
    const int fetchInterval = 3;
    const int reconnectInterval = 5;

    if (!m_db->open(connectionName)) {
        qCritical() << "初始化传感器数据库连接失败:" << connectionName;
        emit databaseError("初始化传感器数据连接失败");
    }

    QList<SensorData_Type> sensorDataList;

    while (!m_stopRequested.load() && !QThread::currentThread()->isInterruptionRequested()) {

        if (!checkAndReconnect(connectionName, reconnectInterval)) {
            continue;
        }

        {
            QMutexLocker locker(&mutex);
            sensorDataList = m_db->getAllRecords();

            if (!sensorDataList.isEmpty()) {
                emit sensorDataReady(sensorDataList);
                qDebug() << "成功获取" << sensorDataList.size() << "条传感器数据";
            } else {
                qWarning() << "获取传感器数据为空";
                // 不发送错误，因为空数据可能是正常的
            }
        }

        safeSleep(fetchInterval);
    }

    qDebug() << "传感器数据获取线程退出";
}

void DatabaseWorker::fetchWeighbridgeData()
{
    const QString connectionName = "WeighbridgeData";
    const int fetchInterval = 10;
    const int reconnectInterval = 20;

    if (!m_db->open(connectionName)) {
        qCritical() << "初始化地磅数据库连接失败:" << connectionName;
        emit databaseError("初始化地磅数据连接失败");
    }

    QList<WeighRecordViewType> weighRecordDataList;

    while (!m_stopRequested.load() && !QThread::currentThread()->isInterruptionRequested()) {

        if (!checkAndReconnect(connectionName, reconnectInterval)) {
            continue;
        }

        {
            QMutexLocker locker(&mutex);
            if (m_db->getLatestWeighRecords(weighRecordDataList, 10)) {  // 添加limit参数
                emit weighbridgeDataReady(weighRecordDataList);
                qDebug() << "成功获取" << weighRecordDataList.size() << "条地磅数据";
            } else {
                qWarning() << "获取地磅数据失败";
                emit databaseError("获取地磅数据失败");
            }
        }

        safeSleep(fetchInterval);
    }

    qDebug() << "地磅数据获取线程退出";
}

void DatabaseWorker::stop()
{
    m_stopRequested.store(1);  // 修正为 store()
}

bool DatabaseWorker::checkAndReconnect(const QString& connectionName, int sleepSeconds)
{
    if (!m_db->toDB()) {
        qWarning() << "数据库连接异常，尝试重新连接:" << connectionName;
        if (!m_db->open(connectionName)) {
            qCritical() << "数据库重新连接失败:" << connectionName;
            emit databaseError(QString("数据库连接失败: %1").arg(connectionName));
            safeSleep(sleepSeconds);
            return false;
        }
        qInfo() << "数据库重新连接成功:" << connectionName;
    }
    return true;
}

void DatabaseWorker::safeSleep(int seconds)
{
    for (int i = 0; i < seconds * 10; ++i) {
        if (m_stopRequested.load()) {
            break;
        }
        QThread::msleep(100);
    }
}

