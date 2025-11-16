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
     QList<pickedProduct_Type> pickedProducts;
     QList<RawInspectionRow> rawProducts;
     bool flag = false;
     m_db->open("PickedProductData");
     while( !QThread::currentThread()->isInterruptionRequested() ){
         if( !m_db->toDB() ){
             m_db->open("PickedProductData");
             QThread::sleep(20);
         }
         else{
            DatabaseWorker::mutex.lock();
            flag = !flag;
            if( flag ){
                if( m_db->getLatestRawProducts(rawProducts,4)){
                    emit RawInspectcdataReady(rawProducts);
                    qDebug() << "Fetched" << rawProducts.size() << "Rawproducts";
                }else{
                    qWarning() << "Failed to fetch Raw products";
                }
            }else{
                if( m_db->getLatestPickedProducts(pickedProducts,10)){
                    emit pickedProducdataReady(pickedProducts);
                    qDebug() << "Fetched" << pickedProducts.size() << "Picked products";
                }else{
                    qWarning() << "Failed to fetch Picked products";
                }
            }

            DatabaseWorker::mutex.unlock();
         }
         QThread::sleep(10);
     }
}

void DatabaseWorker::fetchSensorData()
{
    QList<SensorData_Type> sensorDataList;
    m_db->open("SensorData");
    while( !QThread::currentThread()->isInterruptionRequested() ){
        if( !m_db->toDB() ){
            m_db->open("SensorData");
            QThread::sleep(5);
        }
        else{
           DatabaseWorker::mutex.lock();
           sensorDataList.clear();
           sensorDataList.append(m_db->getAllRecords());
           if( !sensorDataList.isEmpty()){
               emit sensorDataReady(sensorDataList);
               qDebug() << "Fetched" << sensorDataList.size() << "SensorData";
           }else{
               qWarning() << "Failed to SensorData products";
           }
           DatabaseWorker::mutex.unlock();
        }
        QThread::sleep(3);
    }
}

void DatabaseWorker::fetchWeighbridgeData()
{

    while( !QThread::currentThread()->isInterruptionRequested() ){
        if( sqlServerHandler.isConnected()){
            QSqlQueryModel* queryModel =  sqlServerHandler.getLastNRecords(10, "RunningNum", true);
            if( queryModel != nullptr){
                emit WeighbridgeDataReady(queryModel);
            }
            QThread::sleep(10);
        }else{
            sqlServerHandler.connectToDatabase();
            QThread::sleep(20);
        }
    }

}
