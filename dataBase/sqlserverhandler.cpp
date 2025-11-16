#include "SQLServerHandler.h"

SQLServerHandler::SQLServerHandler(QObject *parent) : QObject(parent)
{
}

bool SQLServerHandler::connectToDatabase()
{
       // 关闭现有连接
       if (m_db.isOpen()) {
           m_db.close();
       }

       // 检查是否已存在连接
      if (QSqlDatabase::contains("SQL_SERVER_CONNECTION")) {
          m_db = QSqlDatabase::database("SQL_SERVER_CONNECTION");

      }else{
          // 创建数据库连接
          m_db = QSqlDatabase::addDatabase("QODBC", "SQL_SERVER_CONNECTION");
      }

       // 构建连接字符串
//              m_db.setHostName("192.168.100.10");//客户现场网段192.168.130.2 192.168.100.1
//              m_db.setDatabaseName("QTSN64");
//              m_db.setUserName("LC");
//              m_db.setPassword("LCKJ2018@");


      QString connStr = QStringLiteral(
                "Driver={SQL Server};"  // 修改为13版本
                "Server=192.168.100.10;"
                "Database=EasyWeighDB;"
                "Uid=LC;"
                "Pwd=LCKJ2018@;");

        // 3. 把整串交给 Qt
        m_db.setDatabaseName(connStr);

//            QString connStr = QStringLiteral(
//                      "Driver={ODBC Driver 17 for SQL Server};"  // 修改为13版本
//                      "Server=192.168.100.13,1444;"
//                      "Database=EasyWeighDB;"
//                      "Uid=LC;"
//                      "Pwd=LCKJ2018@;");

              // 3. 把整串交给 Qt
//              m_db.setDatabaseName(connStr);



       if (!m_db.open()) {
           m_lastError = m_db.lastError().text();
           qDebug() << "Database connection error:" << m_lastError;
           return false;
       }

       qDebug() << "Successfully connected to database:";
       return true;

}

void SQLServerHandler::disconnectDatabase()
{
    if (m_db.isOpen()) {
        m_db.close();
        qDebug() << "Database connection closed";
    }
}

bool SQLServerHandler::isConnected() const
{
    return m_db.isOpen();
}

QVector<QMap<QString, QVariant>> SQLServerHandler::executeQuery(const QString &query)
{
    QVector<QMap<QString, QVariant>> results;

    if (!m_db.isOpen()) {
        m_lastError = "Database not connected";
        return results;
    }

    QSqlQuery sqlQuery(m_db);
    if (!sqlQuery.exec(query)) {
        m_lastError = sqlQuery.lastError().text();
        qDebug() << "Query error:" << m_lastError;
        return results;
    }

    // 获取结果
    while (sqlQuery.next()) {
        QMap<QString, QVariant> row;
        QSqlRecord record = sqlQuery.record();

        for (int i = 0; i < record.count(); ++i) {
            QString fieldName = record.fieldName(i);
            QVariant value = record.value(i);
            row[fieldName] = value;
        }

        results.append(row);
    }

    return results;
}

QSqlQueryModel* SQLServerHandler::getQueryModel(const QString &query)
{
    if (!m_db.isOpen()) {
        m_lastError = "Database not connected";
        return nullptr;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM WeighRecordView", m_db);

    if (model->lastError().isValid()) {
        m_lastError = model->lastError().text();
        qDebug() << "Query model error:" << m_lastError;
        delete model;
        return nullptr;
    }

    return model;
}

bool SQLServerHandler::executeNonQuery(const QString &query)
{
    if (!m_db.isOpen()) {
        m_lastError = "Database not connected";
        return false;
    }

    QSqlQuery sqlQuery(m_db);
    if (!sqlQuery.exec(query)) {
        m_lastError = sqlQuery.lastError().text();
        qDebug() << "Non-query error:" << m_lastError;
        return false;
    }

    return true;
}

bool SQLServerHandler::executeParameterizedQuery(const QString &query,
                                               const QMap<QString, QVariant> &params)
{
    if (!m_db.isOpen()) {
        m_lastError = "Database not connected";
        return false;
    }

    QSqlQuery sqlQuery(m_db);
    sqlQuery.prepare(query);

    // 绑定参数
    QMapIterator<QString, QVariant> it(params);
    while (it.hasNext()) {
        it.next();
        sqlQuery.bindValue(it.key(), it.value());
    }

    if (!sqlQuery.exec()) {
        m_lastError = sqlQuery.lastError().text();
        qDebug() << "Parameterized query error:" << m_lastError;
        return false;
    }

    return true;
}

bool SQLServerHandler::beginTransaction()
{
    if (!m_db.isOpen()) {
        m_lastError = "Database not connected";
        return false;
    }

    if (!m_db.transaction()) {
        m_lastError = m_db.lastError().text();
        return false;
    }

    return true;
}

bool SQLServerHandler::commitTransaction()
{
    if (!m_db.isOpen()) {
        m_lastError = "Database not connected";
        return false;
    }

    if (!m_db.commit()) {
        m_lastError = m_db.lastError().text();
        return false;
    }

    return true;
}

bool SQLServerHandler::rollbackTransaction()
{
    if (!m_db.isOpen()) {
        m_lastError = "Database not connected";
        return false;
    }

    if (!m_db.rollback()) {
        m_lastError = m_db.lastError().text();
        return false;
    }

    return true;
}

QString SQLServerHandler::lastError() const
{
    return m_lastError;
}

bool SQLServerHandler::testConnection()
{
    if (!m_db.isOpen()) {
        return false;
    }

    QSqlQuery sqlQuery(m_db);
    return sqlQuery.exec("SELECT 1");
}

QVector<QMap<QString, QString>> SQLServerHandler::getTableStructure(const QString &tableName)
{
    QVector<QMap<QString, QString>> structure;

    if (!m_db.isOpen()) {
        m_lastError = "Database not connected";
        return structure;
    }

    QString query = QString("SELECT COLUMN_NAME, DATA_TYPE, CHARACTER_MAXIMUM_LENGTH, "
                           "IS_NULLABLE, COLUMN_DEFAULT "
                           "FROM INFORMATION_SCHEMA.COLUMNS "
                           "WHERE TABLE_NAME = '%1'").arg(tableName);

    QSqlQuery sqlQuery(m_db);
    if (!sqlQuery.exec(query)) {
        m_lastError = sqlQuery.lastError().text();
        return structure;
    }

    while (sqlQuery.next()) {
        QMap<QString, QString> columnInfo;
        columnInfo["name"] = sqlQuery.value("COLUMN_NAME").toString();
        columnInfo["type"] = sqlQuery.value("DATA_TYPE").toString();
        columnInfo["length"] = sqlQuery.value("CHARACTER_MAXIMUM_LENGTH").toString();
        columnInfo["nullable"] = sqlQuery.value("IS_NULLABLE").toString();
        columnInfo["default"] = sqlQuery.value("COLUMN_DEFAULT").toString();

        structure.append(columnInfo);
    }

    return structure;
}


// ================== 称重记录专用函数实现 ==================

QVector<WeightRecord_Type> SQLServerHandler::getAllWeighRecords()
{
    QVector<WeightRecord_Type> records;

    if (!m_db.isOpen()) {
        m_lastError = "Database not connected";
        return records;
    }

    QSqlQuery query(m_db);
    if (!query.exec("SELECT * FROM WeighRecordView")) {
        m_lastError = query.lastError().text();
        qDebug() << "Query error:" << m_lastError;
        return records;
    }

    while (query.next()) {
        records.append(createWeighRecordFromQuery(query));
    }

    return records;
}

WeightRecord_Type SQLServerHandler::getWeighRecordByRunningNum(const QString &runningNum)
{
    WeightRecord_Type record;

    if (!m_db.isOpen()) {
        m_lastError = "Database not connected";
        return record;
    }

    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM WeighRecordView WHERE RunningNum = :runningNum");
    query.bindValue(":runningNum", runningNum);

    if (!query.exec() || !query.next()) {
        m_lastError = query.lastError().text();
        if (m_lastError.isEmpty()) {
            m_lastError = "No record found with RunningNum: " + runningNum;
        }
        return record;
    }

    return createWeighRecordFromQuery(query);
}

QVector<WeightRecord_Type> SQLServerHandler::getWeighRecordsByLicenseplate(const QString &licenseplate)
{
    QVector<WeightRecord_Type> records;

    if (!m_db.isOpen()) {
        m_lastError = "Database not connected";
        return records;
    }

    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM WeighRecordView WHERE Licenseplate = :licenseplate");
    query.bindValue(":licenseplate", licenseplate);

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        return records;
    }

    while (query.next()) {
        records.append(createWeighRecordFromQuery(query));
    }

    return records;
}

QVector<WeightRecord_Type> SQLServerHandler::getWeighRecordsByDateRange(const QDateTime &startDate,
                                                                const QDateTime &endDate)
{
    QVector<WeightRecord_Type> records;

    if (!m_db.isOpen()) {
        m_lastError = "Database not connected";
        return records;
    }

    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM WeighRecordView WHERE WeighTime BETWEEN :startDate AND :endDate");
    query.bindValue(":startDate", startDate);
    query.bindValue(":endDate", endDate);

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        return records;
    }

    while (query.next()) {
        records.append(createWeighRecordFromQuery(query));
    }

    return records;
}

QVector<WeightRecord_Type> SQLServerHandler::getWeighRecordsByFilter(const QString &licenseplate,
                                                              const QString &driver,
                                                              const QString &productName,
                                                              const QDateTime &startDate,
                                                              const QDateTime &endDate,
                                                              const QString &businessType)
{
    QVector<WeightRecord_Type> records;

    if (!m_db.isOpen()) {
        m_lastError = "Database not connected";
        return records;
    }

    QString queryStr = "SELECT * FROM WeighRecordView WHERE 1=1";
    QMap<QString, QVariant> params;

    // 添加过滤条件
    if (!licenseplate.isEmpty()) {
        queryStr += " AND Licenseplate LIKE :licenseplate";
        params[":licenseplate"] = "%" + licenseplate + "%";
    }

    if (!driver.isEmpty()) {
        queryStr += " AND Driver LIKE :driver";
        params[":driver"] = "%" + driver + "%";
    }

    if (!productName.isEmpty()) {
        queryStr += " AND ProductName LIKE :productName";
        params[":productName"] = "%" + productName + "%";
    }

    if (!businessType.isEmpty()) {
        queryStr += " AND BusinessType = :businessType";
        params[":businessType"] = businessType;
    }

    if (startDate.isValid() && endDate.isValid()) {
        queryStr += " AND WeighTime BETWEEN :startDate AND :endDate";
        params[":startDate"] = startDate;
        params[":endDate"] = endDate;
    }

    QSqlQuery query(m_db);
    query.prepare(queryStr);

    // 绑定参数
    QMapIterator<QString, QVariant> it(params);
    while (it.hasNext()) {
        it.next();
        query.bindValue(it.key(), it.value());
    }

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        return records;
    }

    while (query.next()) {
        records.append(createWeighRecordFromQuery(query));
    }

    return records;
}

QSqlQueryModel* SQLServerHandler::getLastNRecords(int n, const QString& orderField, bool isDesc)
{
    // 1. 检查数据库连接状态
    if (!m_db.isOpen()) {
        m_lastError = "Database not connected";
        return nullptr;
    }

    // 2. 参数合法性校验
    if (n <= 0 || n > 10000) {  // 限制最大条数，避免一次加载过多数据
        m_lastError = QString("Invalid record count (must be 1~10000, got %1)").arg(n);
        return nullptr;
    }
    if (orderField.isEmpty()) {
        m_lastError = "Order field cannot be empty";
        return nullptr;
    }
    // 校验排序字段是否在允许的列表中（防SQL注入和无效字段）
    const QStringList validFields = {
        "RunningNum", "Licenseplate", "Driver", "BusinessType",
        "CustomerName", "SupplierName", "ProductName", "TotalWeight",
        "Tare", "Buckle", "NeatWeight", "WeighTime",
        "SendcorpName", "RecvcorpName"
    };
    if (!validFields.contains(orderField)) {
        m_lastError = QString("Invalid order field: %1").arg(orderField);
        return nullptr;
    }

    // 3. 构造查询（显式指定字段，避免SELECT *）
    QString queryStr = QString(
        "SELECT TOP (:n) "
        "RunningNum, Licenseplate, Driver, BusinessType, "
        "CustomerName, SupplierName, ProductName, TotalWeight, "
        "Tare, Buckle, NeatWeight, WeighTime, "
        "SendcorpName, RecvcorpName "
        "FROM [EasyWeighDB].[dbo].[WeighRecordView] "
        "ORDER BY %1 %2"
    ).arg(orderField)
     .arg(isDesc ? "DESC" : "ASC");

    // 4. 若排序字段有索引，可添加索引提示（需替换为实际索引名）
    // 示例：如果WeighTime有索引idx_weighrecordview_weightime，可开启下面一行
    // queryStr.insert(queryStr.indexOf("FROM"), "WITH(INDEX(idx_weighrecordview_weightime)) ");

    // 5. 参数化查询执行
    QSqlQuery sqlQuery(m_db);
    if (!sqlQuery.prepare(queryStr)) {
        m_lastError = sqlQuery.lastError().text();
        qDebug() << "Query prepare error:" << m_lastError;
        return nullptr;
    }
    // 绑定整数参数，显式指定类型避免隐式转换
    sqlQuery.bindValue(":n", n, QSql::In);

    if (!sqlQuery.exec()) {
        m_lastError = sqlQuery.lastError().text();
        qDebug() << "Query execution error:" << m_lastError;
        return nullptr;
    }

    // 6. 绑定结果到模型（移动语义避免二次执行）
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(std::move(sqlQuery));  // 关键：直接复用已执行的查询结果

    // 7. 检查模型错误
    if (model->lastError().isValid()) {
        m_lastError = model->lastError().text();
        qDebug() << "Model binding error:" << m_lastError;
        delete model;
        return nullptr;
    }

    return model;
}

WeightRecord_Type SQLServerHandler::createWeighRecordFromQuery(QSqlQuery &query)
{
    WeightRecord_Type record;
    QSqlRecord sqlRecord = query.record();

    record.runningNum = sqlRecord.value("RunningNum").toString();
    record.licensePlate = sqlRecord.value("Licenseplate").toString();
    record.driver = sqlRecord.value("Driver").toString();
    record.businessType = sqlRecord.value("BusinessType").toString();
    record.customerName = sqlRecord.value("CustomerName").toString();
    record.supplierName = sqlRecord.value("SupplierName").toString();
    record.productName = sqlRecord.value("ProductName").toString();
    record.totalWeight = sqlRecord.value("TotalWeight").toDouble();
    record.tare = sqlRecord.value("Tare").toDouble();
    record.buckle = sqlRecord.value("Buckle").toDouble();
    record.neatWeight = sqlRecord.value("NeatWeight").toDouble();
    record.weighTime = sqlRecord.value("WeighTime").toDateTime();
    record.sendCorpName = sqlRecord.value("SendcorpName").toString();
    record.recvCorpName = sqlRecord.value("RecvcorpName").toString();

    return record;
}
