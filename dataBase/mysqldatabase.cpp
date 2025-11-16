#include "mysqldatabase.h"

#include "MySQLDatabase.h"

// 初始化静态成员
MySQLDatabase* MySQLDatabase::m_instance = nullptr;
QMutex MySQLDatabase::m_mutex;

MySQLDatabase::MySQLDatabase(QObject *parent)
    : QObject(parent)
{
    // 构造函数私有化
    isopen = false;
}

MySQLDatabase* MySQLDatabase::instance()
{
    QMutexLocker locker(&m_mutex);
    if (!m_instance) {
        m_instance = new MySQLDatabase();
    }
    return m_instance;
}

bool MySQLDatabase::initialize(const QString& host, int port,
                              const QString& database,
                              const QString& user,
                              const QString& password)
{
    // 如果已有连接，先关闭
    if (m_db.isOpen()) {
        m_db.close();
    }

    // 创建数据库连接
    m_db = QSqlDatabase::addDatabase("QMYSQL", "mysql_connection");
    m_db.setHostName(host);
    m_db.setPort(port);
    m_db.setDatabaseName(database);
    m_db.setUserName(user);
    m_db.setPassword(password);
    m_db.setConnectOptions("MYSQL_OPT_RECONNECT=1;");
    // 尝试连接
    if (!m_db.open()) {
        qCritical() << "无法连接到MySQL数据库:" << m_db.lastError().text();
        return false;
    }

    qInfo() << "MySQL数据库连接成功，表已就绪";
    return true;
}

bool MySQLDatabase::insertProductData(const pickedProduct_Type& product)
{
    if (!m_db.isOpen()) {
        qWarning() << "数据库未连接";
        return false;
    }

    QSqlQuery query(m_db);
    query.prepare(R"(
        INSERT INTO `yujingui`.`pickledproduct`(
            `PicklingTankNumber`,
            `OriginalSandInjectionDate`,
            `ProportionRawSand`,
            `EndTimeRaw`,
            `SamplingDate`,
            `SamplingTime`,
            `productionSamplingTime`,
            `samplingTemperature`,
            `elementalAnalysisSi`,
            `elementalAnalysisFe`,
            `elementalAnalysisTi`,
            `FinishedProductDate`,
            `FinishedProductTime`,
            `ParticleDetectionResults25`,
            `ParticleDetectionResults140`,
            `ParticleDetectionResults150`,
            `CompositionResultsSi`,
            `CompositionResultsFe`,
            `CompositionResultsTi`
        ) VALUES (
            :PicklingTankNumber,
            :OriginalSandInjectionDate,
            :ProportionRawSand,
            :EndTimeRaw,
            :SamplingDate,
            :SamplingTime,
            :productionSamplingTime,
            :samplingTemperature,
            :elementalAnalysisSi,
            :elementalAnalysisFe,
            :elementalAnalysisTi,
            :FinishedProductDate,
            :FinishedProductTime,
            :ParticleDetectionResults25,
            :ParticleDetectionResults140,
            :ParticleDetectionResults150,
            :CompositionResultsSi,
            :CompositionResultsFe,
            :CompositionResultsTi
        )
    )");

    // 绑定参数
    query.bindValue(":PicklingTankNumber", product.picklingTankNumber);
    query.bindValue(":OriginalSandInjectionDate", product.originalSandInjectionDate);
    query.bindValue(":ProportionRawSand", product.proportionRawSand);
    query.bindValue(":EndTimeRaw", product.endTimeRaw);
    query.bindValue(":SamplingDate", product.samplingDate);
    query.bindValue(":SamplingTime", product.samplingTime);
    query.bindValue(":productionSamplingTime", product.productionSamplingTime);
    query.bindValue(":samplingTemperature", product.samplingTemperature);
    query.bindValue(":elementalAnalysisSi", product.elementalAnalysisSi);
    query.bindValue(":elementalAnalysisFe", product.elementalAnalysisFe);
    query.bindValue(":elementalAnalysisTi", product.elementalAnalysisTi);
    query.bindValue(":FinishedProductDate", product.finishedProductDate);
    query.bindValue(":FinishedProductTime", product.finishedProductTime);
    query.bindValue(":ParticleDetectionResults25", product.particleDetectionResults25);
    query.bindValue(":ParticleDetectionResults140", product.particleDetectionResults140);
    query.bindValue(":ParticleDetectionResults150", product.particleDetectionResults150);
    query.bindValue(":CompositionResultsSi", product.compositionResultsSi);
    query.bindValue(":CompositionResultsFe", product.compositionResultsFe);
    query.bindValue(":CompositionResultsTi", product.compositionResultsTi);

    if (!query.exec()) {
        qCritical() << "插入数据失败:" << query.lastError().text();
        qCritical() << "SQL错误:" << query.lastQuery();
        return false;
    }

    qInfo() << "产品数据插入成功, ID:" << query.lastInsertId().toString();
    return true;
}

bool MySQLDatabase::insertRawInspectionData(const RawInspectionRow &inspection)
{
    if (!m_db.isOpen()) {
           qWarning() << "数据库未连接";
           return false;
       }

       QSqlQuery query(m_db);
       query.prepare(R"(
           INSERT INTO `yujingui`.`rawsand` (
               `Supplier`,
               `StorageTime`,
               `WagonNumber`,
               `InspectionTime`,
               `MoistureDetectionResults`,
               `ParticleSizeDetectionResults25`,
               `ParticleSizeDetectionResults140`,
               `RawSandSi`,
               `RawSandFe`,
               `RawSandTi`,
               `AcidWashingTestMethod`,
               `AcidpicklingSi`,
               `AcidpicklingFe`,
               `AcidpicklingTi`,
               `ExperimentalResult`
           ) VALUES (
               :Supplier,
               :StorageTime,
               :WagonNumber,
               :InspectionTime,
               :MoistureDetectionResults,
               :ParticleSizeDetectionResults25,
               :ParticleSizeDetectionResults140,
               :RawSandSi,
               :RawSandFe,
               :RawSandTi,
               :AcidWashingTestMethod,
               :AcidpicklingSi,
               :AcidpicklingFe,
               :AcidpicklingTi,
               :ExperimentalResult
           )
       )");

       // 绑定参数
       query.bindValue(":Supplier", inspection.supplier);
       query.bindValue(":StorageTime", inspection.storageTime);
       query.bindValue(":WagonNumber", inspection.wagonNumber);
       query.bindValue(":InspectionTime", inspection.inspectionTime);
       query.bindValue(":MoistureDetectionResults", inspection.moistureDetectionResults);
       query.bindValue(":ParticleSizeDetectionResults25", inspection.particleSizeDetectionResults25);
       query.bindValue(":ParticleSizeDetectionResults140", inspection.particleSizeDetectionResults140);
       query.bindValue(":RawSandSi", inspection.rawSandSi);
       query.bindValue(":RawSandFe", inspection.rawSandFe);
       query.bindValue(":RawSandTi", inspection.rawSandTi);
       query.bindValue(":AcidWashingTestMethod", inspection.acidWashingTestMethod);
       query.bindValue(":AcidpicklingSi", inspection.acidpicklingSi);
       query.bindValue(":AcidpicklingFe", inspection.acidpicklingFe);
       query.bindValue(":AcidpicklingTi", inspection.acidpicklingTi);
       query.bindValue(":ExperimentalResult", inspection.experimentalResult);

       if (!query.exec()) {
           qCritical() << "插入原砂检验数据失败:" << query.lastError().text();
           qCritical() << "SQL错误:" << query.lastQuery();
           return false;
       }

       qInfo() << "原砂检验数据插入成功, ID:" << query.lastInsertId().toString();
       return true;
}

bool MySQLDatabase::open(const QString connnectname)
{
    if(QSqlDatabase::contains(connnectname)){
       m_db = QSqlDatabase::database(connnectname);
       isopen = true;
    }
    else{
       m_db = QSqlDatabase::addDatabase("QMYSQL",connnectname);
       m_db.setHostName("1.14.26.239");
       m_db.setPort(3306);
       m_db.setDatabaseName("user");
       m_db.setUserName("root");
       m_db.setPassword("czy123456");
       m_db.setConnectOptions("MYSQL_OPT_RECONNECT=1;");
    }
    isopen =  m_db.open();
    qDebug()<<isopen;
    return isopen;
}

void MySQLDatabase::close()
{
    if (m_db.isOpen()) {
        m_db.close();
        qInfo() << "MySQL数据库连接已关闭";
    }
}

bool MySQLDatabase::toDB()
{
    QString   sql;
    bool result;
    sql = QString("SELECT * from `toapp` ");
    QSqlQuery  query(m_db);
    result = query.exec(sql);

    return result;
}

bool MySQLDatabase::getLatestRawProducts(QList<RawInspectionRow> &products, int limit)
{
        products.clear();

        if (!m_db.isOpen()) {
            qWarning() << "Database not connected";
            return false;
        }

        QSqlQuery query(m_db);
        query.prepare(R"(
                      SELECT r1.*
                      FROM `yujingui`.`rawsand` r1
                      INNER JOIN (
                          SELECT Supplier, MAX(`order`) AS max_order
                          FROM `yujingui`.`rawsand`
                          GROUP BY Supplier
                          ORDER BY max_order DESC
                          LIMIT :limit
                      ) r2 ON r1.Supplier = r2.Supplier AND r1.`order` = r2.max_order
                      ORDER BY r1.`order` DESC
            )");

        query.bindValue(":limit", limit);

        if (!query.exec()) {
            qCritical() << "Failed to fetch raw inspections:" << query.lastError().text();
            return false;
        }

        while (query.next()) {
            RawInspectionRow inspection;

            // 从查询结果填充结构体
            inspection.supplier = query.value("Supplier").toString();
            inspection.storageTime = query.value("StorageTime").toString();
            inspection.wagonNumber = query.value("WagonNumber").toString();
            inspection.inspectionTime = query.value("InspectionTime").toString();
            inspection.moistureDetectionResults = query.value("MoistureDetectionResults").toString();
            inspection.particleSizeDetectionResults25 = query.value("ParticleSizeDetectionResults25").toString();
            inspection.particleSizeDetectionResults140 = query.value("ParticleSizeDetectionResults140").toString();
            inspection.rawSandSi = query.value("RawSandSi").toString();
            inspection.rawSandFe = query.value("RawSandFe").toString();
            inspection.rawSandTi = query.value("RawSandTi").toString();
            inspection.acidWashingTestMethod = query.value("AcidWashingTestMethod").toString();
            inspection.acidpicklingSi = query.value("AcidpicklingSi").toString();
            inspection.acidpicklingFe = query.value("AcidpicklingFe").toString();
            inspection.acidpicklingTi = query.value("AcidpicklingTi").toString();
            inspection.experimentalResult = query.value("ExperimentalResult").toString();

            products.append(inspection);
        }

        return true;
}

QList<SensorData_Type> MySQLDatabase::getAllRecords()
{
   QList<SensorData_Type> list;
   QSqlQuery query(m_db);
   QString sql =QString(R"(SELECT `index`, `type`, `location`, `data`, `time` FROM `yujingui`.`devicedata`)");

   if (!query.exec(sql)) {
       qCritical() << "Query failed:" << query.lastError().text();
       return list;
   }

   while (query.next()) {
       SensorData_Type d;
       d.index     = query.value(0).toString();
       d.type      = query.value(1).toInt();
       d.location  = query.value(2).toInt();
       d.data      = query.value(3).toString();
       d.time      = query.value(4).toDateTime();
       list.append(d);
   }
   return list;
}


bool MySQLDatabase::getLatestPickedProducts(QList<pickedProduct_Type> &products, int limit)
{
    products.clear();

    if (!m_db.isOpen()) {
        qWarning() << "Database not connected";
        return false;
    }

    QSqlQuery query(m_db);
    query.prepare(R"(
          SELECT * FROM (
                     SELECT *
                     FROM `yujingui`.`pickledproduct`
                     ORDER BY `order` DESC
                     LIMIT :limit
                 ) AS sub
                 ORDER BY `order` ASC  -- 外层查询反转为正序
    )");

    query.bindValue(":limit", limit);

    if (!query.exec()) {
        qCritical() << "Failed to fetch products:" << query.lastError().text();
        return false;
    }

    while (query.next()) {
        pickedProduct_Type product;

        product.picklingTankNumber = query.value("PicklingTankNumber").toString();
        product.originalSandInjectionDate = query.value("OriginalSandInjectionDate").toString();
        product.proportionRawSand = query.value("ProportionRawSand").toString();
        product.endTimeRaw = query.value("EndTimeRaw").toString();
        product.samplingDate = query.value("SamplingDate").toString();
        product.samplingTime = query.value("SamplingTime").toString();
        product.productionSamplingTime = query.value("productionSamplingTime").toString();
        product.samplingTemperature = query.value("samplingTemperature").toString();
        product.elementalAnalysisSi = query.value("elementalAnalysisSi").toString();
        product.elementalAnalysisFe = query.value("elementalAnalysisFe").toString();
        product.elementalAnalysisTi = query.value("elementalAnalysisTi").toString();
        product.finishedProductDate = query.value("FinishedProductDate").toString();
        product.finishedProductTime = query.value("FinishedProductTime").toString();
        product.particleDetectionResults25 = query.value("ParticleDetectionResults25").toString();
        product.particleDetectionResults140 = query.value("ParticleDetectionResults140").toString();
        product.particleDetectionResults150 = query.value("ParticleDetectionResults150").toString();
        product.compositionResultsSi = query.value("CompositionResultsSi").toString();
        product.compositionResultsFe = query.value("CompositionResultsFe").toString();
        product.compositionResultsTi = query.value("CompositionResultsTi").toString();

        products.append(product);
    }

    return true;
}
