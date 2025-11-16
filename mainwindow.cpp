#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <QAxObject>
#include <QDir>
#include <QFont>
#include "QThread"
#include <QScreen>
#include "QtConcurrent"
#include <QKeyEvent>
#include <QMouseEvent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    buttonFlag = false;
    m_oldModel = nullptr;

    initDB();

    myT = new DatabaseWorker();
    thread = new QThread(this);
    myT->moveToThread(thread);

    sensorT = new DatabaseWorker();
    sensorThread = new QThread(this);
    sensorT->moveToThread(sensorThread);

    weighbridgeT=  new DatabaseWorker();
    weighbridgeThread = new QThread(this);
    weighbridgeT->moveToThread(weighbridgeThread);

    m_keepAliveTimer = new QTimer(this);
    spreadsheet.initPickProductTable(ui->tableWidget_Pickling);
    spreadsheet.initRawSandTable(ui->tableWidget_RowSand);

    connect(myT,SIGNAL(RawInspectcdataReady(QList<RawInspectionRow>)),
            this,SLOT(updateRawInspectTable(QList<RawInspectionRow>)),
            Qt::QueuedConnection);

    connect(myT,SIGNAL(pickedProducdataReady(QList<pickedProduct_Type>)),
            this,SLOT(updatePickedProductTable(QList<pickedProduct_Type>)),
            Qt::QueuedConnection);


    connect(sensorT,SIGNAL(sensorDataReady(QList<SensorData_Type>)),
            this,SLOT(updateSensorData(QList<SensorData_Type>)),
            Qt::QueuedConnection);

    connect(weighbridgeT,SIGNAL(WeighbridgeDataReady(QSqlQueryModel*)),
            this,SLOT(updateWeighbridgeData(QSqlQueryModel*)));

    connect(this,&MainWindow::startThread,myT,&DatabaseWorker::fetchLatestPickedProductData);//启动线程
    connect(this,&MainWindow::startThread,sensorT,&DatabaseWorker::fetchSensorData);//启动线程
    connect(this,&MainWindow::startThread,weighbridgeT,&DatabaseWorker::fetchWeighbridgeData);//启动线程

    connect(m_keepAliveTimer,SIGNAL(timeout()),this,SLOT(startKeepAlive()));
    thread->start();
    sensorThread->start();
    weighbridgeThread->start();
    m_keepAliveTimer->start(1000 * 10);

    showMaximized();
//    setWindowFlags(Qt::FramelessWindowHint);   // 去掉系统边框
    setWindowTitle("工业控制监控系统");
    emit startThread();

//    ui->statusBar->showMessage("双击切换全屏/最大化");

}

MainWindow::~MainWindow()
{
    m_keepAliveTimer->stop();
    if( thread->isRunning() == true ){
        thread->requestInterruption();
        thread->quit();
        thread->wait();
    }

    if( sensorThread->isRunning() == true ){
        sensorThread->requestInterruption();
        sensorThread->quit();
        sensorThread->wait();
    }

    if( weighbridgeThread->isRunning() == true ){
        weighbridgeThread->requestInterruption();
        weighbridgeThread->quit();
        weighbridgeThread->wait();
    }

    delete myT;
    delete sensorT;
    delete weighbridgeT;

    delete m_keepAliveTimer;
    delete ui;
}



bool MainWindow::initDB()
{
    MySQLDatabase* db = MySQLDatabase::instance();
    return db->open("QMainWindow");
}

void MainWindow::configureTableView(QTableView *tableView)
{
    if (!tableView) return; // 空指针保护

        // ===== 1. 启用单元格文本换行 =====
        tableView->setWordWrap(true);

        // ===== 2. 计算每列最小宽度 =====
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        QHeaderView *header = tableView->horizontalHeader();
        int columnCount = header->count();
        if (columnCount == 0) return;

        QVector<int> minWidths(columnCount);
        int totalMinWidth = 0;
        for (int i = 0; i < columnCount; ++i) {
            minWidths[i] = header->sectionSize(i);
            if (i == 4 || i == 12) {
                minWidths[i] += 20;
            }
            totalMinWidth += minWidths[i];
        }

        // ===== 3. 获取可用宽度 =====
        int availableWidth = tableView->parentWidget()->width() - 20;
        if (availableWidth <= 0) {
            availableWidth = tableView->width() - 20;
        }

        // ===== 4. 列宽分配策略（新增“铺满”逻辑）=====
        const int maxColumnWidth = availableWidth / 3; // 最大列宽限制
        QVector<int> columnWidths(columnCount); // 存储最终列宽

        // 第一步：按最小/最大宽度初步分配
        for (int i = 0; i < columnCount; ++i) {
            columnWidths[i] = minWidths[i];
            if (columnWidths[i] > maxColumnWidth) {
                columnWidths[i] = maxColumnWidth; // 超出最大宽度则截断（内容换行）
            }
        }

        // 第二步：计算初步分配后的总宽度
        int currentTotal = 0;
        for (int w : columnWidths) {
            currentTotal += w;
        }

        // 第三步：处理剩余空间（确保总宽度=可用宽度，实现铺满）
        int remaining = availableWidth - currentTotal;
        if (remaining > 0) {
            // 有剩余空间，均匀分配给所有列（可根据需求调整分配策略）
            int addPerColumn = remaining / columnCount; // 每列基础增加量
            int extra = remaining % columnCount; // 无法均分的剩余部分（优先分配给前几列）

            for (int i = 0; i < columnCount; ++i) {
                columnWidths[i] += addPerColumn;
                if (i < extra) {
                    columnWidths[i] += 1; // 分配剩余部分
                }

                // 确保分配后不超过最大宽度（可选，根据需求决定是否保留此限制）
                // if (columnWidths[i] > maxColumnWidth) {
                //     columnWidths[i] = maxColumnWidth;
                // }
            }

            // 重新计算总宽度（理论上应等于availableWidth）
            currentTotal = availableWidth;
        } else if (remaining < 0) {
            // 总宽度超了，缩减最后一列（保持之前的逻辑）
            int adjust = -remaining;
            int lastColWidth = columnWidths[columnCount - 1];
            columnWidths[columnCount - 1] = qMax(lastColWidth - adjust, 50);
        }

        // 应用最终列宽
        for (int i = 0; i < columnCount; ++i) {
            header->setSectionResizeMode(i, QHeaderView::Fixed);
            header->resizeSection(i, columnWidths[i]);
        }

        // ===== 5. 禁用水平滚动条=====
        tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        // ===== 6. 行高自动适应=====
        tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        tableView->verticalHeader()->setMinimumSectionSize(30);

        // ===== 7. 其他样式设置=====
        tableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        tableView->setAlternatingRowColors(true);
        tableView->setSortingEnabled(true);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void MainWindow::setValveParameters(QString str)
{
    bool ok;
    QByteArray temp = HexStringToByteArray(ByteArrayToHexString(str), &ok);
    PLCValveStatus plvValueStatus;
    char *rcv = temp.data();
    memcpy((char*)&plvValueStatus,rcv,sizeof(PLCValveStatus));
    //1号反应罐进沙阀门开关
    QString openPic = ":/image/image/ValveSwitch_Open1.png";
    QString closePic = ":/image/image/ValveSwitch_Close1.png";
    if( plvValueStatus.R1_SandInletOpen){
        loadImageForLabel(ui->label_SofaValue1,openPic);
    }else if( plvValueStatus.R1_SandInletClose){
        loadImageForLabel(ui->label_SofaValue1,closePic);
    }

    //2号反应罐进沙阀门开关
    if( plvValueStatus.R2_SandInletOpen){
        loadImageForLabel(ui->label_SofaValue1_2,openPic);
    }else if( plvValueStatus.R2_SandInletClose){
        loadImageForLabel(ui->label_SofaValue1_2,closePic);
    }

    //3号反应罐进沙阀门开关
    if( plvValueStatus.R3_SandInletOpen){
        loadImageForLabel(ui->label_SofaValue1_3,openPic);
    }else if( plvValueStatus.R3_SandInletClose){
        loadImageForLabel(ui->label_SofaValue1_3,closePic);
    }

    //4号反应罐进沙阀门开关
    if( plvValueStatus.R4_SandInletOpen){
        loadImageForLabel(ui->label_SofaValue1_4,openPic);
    }else if( plvValueStatus.R4_SandInletClose){
        loadImageForLabel(ui->label_SofaValue1_4,closePic);
    }

    //1号上进酸阀门
    if( plvValueStatus.R1_HighAcidA12Open){
        loadImageForLabel(ui->label_UpperAcidValue1,openPic);
    }else if( plvValueStatus.R1_HighAcidA12Closed){
        loadImageForLabel(ui->label_UpperAcidValue1,closePic);
    }

    //2号上进酸阀门
    if( plvValueStatus.R2_HighAcidA22Open){
        loadImageForLabel(ui->label_UpperAcidValue1_2,openPic);
    }else if( plvValueStatus.R2_HighAcidA22Closed){
        loadImageForLabel(ui->label_UpperAcidValue1_2,closePic);
    }

    //3号上进酸阀门
    if( plvValueStatus.R3_HighAcidA32Open){
        loadImageForLabel(ui->label_UpperAcidValue1_3,openPic);
    }else if( plvValueStatus.R3_HighAcidA32Close){
        loadImageForLabel(ui->label_UpperAcidValue1_3,closePic);
    }

    //4号上进酸阀门
    if( plvValueStatus.R4_HighAcidA42Open){
        loadImageForLabel(ui->label_UpperAcidValue1_4,openPic);
    }else if( plvValueStatus.R4_HighAcidA42Close){
        loadImageForLabel(ui->label_UpperAcidValue1_4,closePic);
    }

    //1号下进酸阀门
    if( plvValueStatus.R1_LowAcidA13Open){
        loadImageForLabel(ui->label_LowerAcidValue1,openPic);
    }else if( plvValueStatus.R1_LowAcidA13Closed){
        loadImageForLabel(ui->label_LowerAcidValue1,closePic);
    }

    //2号下进酸阀门
    if( plvValueStatus.R2_LowAcidA23Open){
        loadImageForLabel(ui->label_LowerAcidValue1_2,openPic);
    }else if( plvValueStatus.R2_LowAcidA23Close){
        loadImageForLabel(ui->label_LowerAcidValue1_2,closePic);
    }

    //3号下进酸阀门
    if( plvValueStatus.R3_LowAcidA33Open){
        loadImageForLabel(ui->label_LowerAcidValue1_3,openPic);
    }else if( plvValueStatus.R3_LowAcidA33Close){
        loadImageForLabel(ui->label_LowerAcidValue1_3,closePic);
    }

    //4号下进酸阀门
    if( plvValueStatus.R4_LowAcidA43Open){
        loadImageForLabel(ui->label_LowerAcidValue1_4,openPic);
    }else if( plvValueStatus.R4_LowAcidA43Close){
        loadImageForLabel(ui->label_LowerAcidValue1_4,closePic);
    }

    //1号上进水阀门开关
    if( plvValueStatus.R1_HighWaterB13Open){
        loadImageForLabel(ui->label_UpperWaterValue1,openPic);
    }else if( plvValueStatus.R1_HighWaterB13Closed){
        loadImageForLabel(ui->label_UpperWaterValue1,closePic);
    }

    //2号上进水阀门开关
    if( plvValueStatus.R2_HighWaterB23Open){
        loadImageForLabel(ui->label_UpperWaterValue1_2,openPic);
    }else if( plvValueStatus.R2_HighWaterB23Closed){
        loadImageForLabel(ui->label_UpperWaterValue1_2,closePic);
    }

    //3号上进水阀门开关
    if( plvValueStatus.R3_HighWaterB33Open){
        loadImageForLabel(ui->label_UpperWaterValue1_3,openPic);
    }else if( plvValueStatus.R3_HighWaterB33Close){
        loadImageForLabel(ui->label_UpperWaterValue1_3,closePic);
    }

    //4号上进水阀门开关
    if( plvValueStatus.R4_HighWaterB43Open){
        loadImageForLabel(ui->label_UpperWaterValue1_4,openPic);
    }else if( plvValueStatus.R4_HighWaterB43Close){
        loadImageForLabel(ui->label_UpperWaterValue1_4,closePic);
    }


    //1号下进水阀门开关
    if( plvValueStatus.R1_LowWaterB11Open){
        loadImageForLabel(ui->label_LowerWaterValue1,openPic);
    }else if( plvValueStatus.R1_LowWaterB11Closed){
        loadImageForLabel(ui->label_LowerWaterValue1,closePic);
    }

    //2号下进水阀门开关
    if( plvValueStatus.R2_LowWaterB21Open){
        loadImageForLabel(ui->label_LowerWaterValue1_2,openPic);
    }else if( plvValueStatus.R2_LowWaterB21Closed){
        loadImageForLabel(ui->label_LowerWaterValue1_2,closePic);
    }

    //3号下进水阀门开关
    if( plvValueStatus.R3_LowWaterB31Open){
        loadImageForLabel(ui->label_LowerWaterValue1_3,openPic);
    }else if( plvValueStatus.R3_LowWaterB31Open){
        loadImageForLabel(ui->label_LowerWaterValue1_3,closePic);
    }

    //4号下进水阀门开关
    if( plvValueStatus.R4_LowWaterB41Open){
        loadImageForLabel(ui->label_LowerWaterValue1_4,openPic);
    }else if( plvValueStatus.R4_LowWaterB41Open){
        loadImageForLabel(ui->label_LowerWaterValue1_4,closePic);
    }

    //1号 排沙阀门开关
    if( plvValueStatus.R1_SandDrainPS1Open){
        loadImageForLabel(ui->label_SandDischargeValue1,openPic);
    }else if( plvValueStatus.R1_SandDrainPS1Close){
        loadImageForLabel(ui->label_SandDischargeValue1,closePic);
    }

    //2号 排沙阀门开关
    if( plvValueStatus.R2_SandDrainPS2Open){
        loadImageForLabel(ui->label_SandDischargeValue1_2,openPic);
    }else if( plvValueStatus.R2_SandDrainPS2Close){
        loadImageForLabel(ui->label_SandDischargeValue1_2,closePic);
    }

    //3号 排沙阀门开关
    if( plvValueStatus.R3_SandDrainPS3Open){
        loadImageForLabel(ui->label_SandDischargeValue1_3,openPic);
    }else if( plvValueStatus.R3_SandDrainPS3Close){
        loadImageForLabel(ui->label_SandDischargeValue1_3,closePic);
    }

    //4号 排沙阀门开关
    if( plvValueStatus.R4_SandDrainPS4Open){
        loadImageForLabel(ui->label_SandDischargeValue1_4,openPic);
    }else if( plvValueStatus.R4_SandDrainPS4Close){
        loadImageForLabel(ui->label_SandDischargeValue1_4,closePic);
    }

    //1号 排酸阀门开关
    if( plvValueStatus.R1_DrainAcidPS11Open){
        loadImageForLabel(ui->label_AcidDischargeValue1,openPic);
    }else if( plvValueStatus.R1_DrainAcidPS11Closed){
        loadImageForLabel(ui->label_AcidDischargeValue1,closePic);
    }

    //2号 排酸阀门开关
    if( plvValueStatus.R2_DrainAcidPS12Open){
        loadImageForLabel(ui->label_AcidDischargeValue1_2,openPic);
    }else if( plvValueStatus.R2_DrainAcidPS12Closed){
        loadImageForLabel(ui->label_AcidDischargeValue1_2,closePic);
    }

    //3号 排酸阀门开关
    if( plvValueStatus.R3_DrainAcidPS13Open){
        loadImageForLabel(ui->label_AcidDischargeValue1_3,openPic);
    }else if( plvValueStatus.R3_DrainAcidPS13Close){
        loadImageForLabel(ui->label_AcidDischargeValue1_3,closePic);
    }

    //4号 排酸阀门开关
    if( plvValueStatus.R4_DrainAcidPS14Open){
        loadImageForLabel(ui->label_AcidDischargeValue1_4,openPic);
    }else if( plvValueStatus.R4_DrainAcidPS14Close){
        loadImageForLabel(ui->label_AcidDischargeValue1_4,closePic);
    }

}

bool MainWindow::loadImageForLabel(QLabel *label, const QString &imagePath)
{
    // 检查QLabel是否有效
      if (!label) {
          qWarning("Invalid QLabel pointer");
          return false;
      }

      // 检查文件是否存在且有效
      QFileInfo fileInfo(imagePath);
      if (!fileInfo.exists() || !fileInfo.isFile()) {
          qWarning("Image file does not exist or is invalid: %s", qUtf8Printable(imagePath));
          return false;
      }

      // 加载图片
      QPixmap pixmap(imagePath);
      if (pixmap.isNull()) {
          qWarning("Failed to load image from: %s", qUtf8Printable(imagePath));
          return false;
      }

      // 设置图片到QLabel
      label->setPixmap(pixmap);
      // 启用缩放以适应QLabel大小:cite[5]
      label->setScaledContents(true);

      return true;
}



void MainWindow::updatePickedProductTable(const QList<pickedProduct_Type> &products)
{
    spreadsheet.fillMultiplePickedProducts(ui->tableWidget_Pickling,products);
}

void MainWindow::updateRawInspectTable(const QList<RawInspectionRow> &products)
{
    spreadsheet.fillRawInspectProducts(ui->tableWidget_RowSand,products);
}

void MainWindow::updateSensorData(const QList<SensorData_Type> &products)
{
//   qDebug() << "=== SensorData dump begin ===";
   bool ok = false;
   uint32_t value;
   for (const SensorData_Type &p : products) {
       //回酸罐
       if( p.location  == DevLocation::BackAcidTin){
            //1.阀门
            if( p.type == SensorType::Valve ){
                setValveParameters(p.data);
            }
       }
       //氢氧酸罐 液位计
       else if( p.location == DevLocation::HfTin &&
                 p.type == SensorType::LevelGauge){
            value = p.data.toUInt(&ok, 16);   // 16 表示按 16 进制解析
            if( ok){

                qDebug()<<QString("氢氧酸罐 液位计")<<bigEndianToLittleEndian_qt(value);
                ui->label_LiquidLevelgauge->setText(QString::number(intToFloat(value)));
            }

       }
       //石墨烯换热器
       else if( p.location == DevLocation::Graphene){
            //1.进口蒸汽压力值
            if( p.type == SensorType::Barometer){
                value = p.data.toUInt(&ok, 16);   // 16 表示按 16 进制解析
                if( ok){
                    qDebug()<<QString("石墨烯换热器 进口蒸汽压力")<<bigEndianToLittleEndian_qt(value);
                    ui->label_ImportedSteamValue->setText(QString::number(intToFloat(value)));
                }
            }
            //2.出口液体温度
            else if( p.type == SensorType::LiquidThermometer ){
                value = p.data.toUInt(&ok, 16);   // 16 表示按 16 进制解析
                if( ok){
                    qDebug()<<QString("石墨烯换热器 出口液体温度")<<bigEndianToLittleEndian_qt(value);
                    ui->label_QuletLiquidTemp->setText(QString::number(intToFloat(value)));
                }
            }
            //3.出口冷凝水 PH值
            else if( p.type == SensorType::LiquidPh ){
                value = p.data.toUInt(&ok, 16);   // 16 表示按 16 进制解析
                if( ok){
                    qDebug()<<QString("石墨烯换热器 出口冷凝水")<<bigEndianToLittleEndian_qt(value);
                    ui->label_CondensateS->setText(QString::number(intToFloat(value)));
                }
            }
       }
       //锅炉房
       else if(p.location == DevLocation::BoilerRoom){
           //1.设备启停状态  目前还没确定具体参数形式

           //2.锅炉温度
           if( p.type == SensorType::Temp){
               value = p.data.toUInt(&ok, 16);   // 16 表示按 16 进制解析
               if( ok){
                   qDebug()<<QString("锅炉房 锅炉温度")<<bigEndianToLittleEndian_qt(value);
               }
           }
           //3.蒸汽压力值
           else if( (p.type == SensorType::Barometer) &&
                    (p.index == 0)){
               value = p.data.toUInt(&ok, 16);   // 16 表示按 16 进制解析
               if( ok){
                   qDebug()<<QString("锅炉房 蒸汽压力值")<<bigEndianToLittleEndian_qt(value);
               }
           }
           //4.天然气压力值
           else if( (p.type == SensorType::Barometer) &&
                    (p.index == 1)){
               value = p.data.toUInt(&ok, 16);   // 16 表示按 16 进制解析
               if( ok){
                   qDebug()<<QString("锅炉房 天然气压力值")<<bigEndianToLittleEndian_qt(value);
               }
           }
           //5.软水质量 目前没有确定具体的参数形式

           //重量
           else if(p.type == SensorType::Weigh){

                QByteArray temp = HexStringToByteArray(ByteArrayToHexString(p.data), &ok);
                APT_BeltScaleData beltScaleData;
                char *rcv = temp.data();
                memcpy((char*)&beltScaleData,rcv,sizeof(APT_BeltScaleData));
                float a  = bigEndianToLittleEndian_qt(beltScaleData.monthWeight.u);
//                beltScaleData.totalWeight.f = bigEndianToFloat(beltScaleData.totalWeight.u);
//                beltScaleData.monthWeight.f = bigEndianToFloat(beltScaleData.monthWeight.u);
//                beltScaleData.dayWeight.f = bigEndianToFloat(beltScaleData.dayWeight.u);
//                beltScaleData.shiftWeight.f = bigEndianToFloat(beltScaleData.shiftWeight.u);
//                qDebug() << "status:" << beltScaleData.status
//                         << "totalWeight:" << beltScaleData.totalWeight.f
//                         << "monthWeight:" << beltScaleData.monthWeight.f
//                         << "dayWeight:" << beltScaleData.dayWeight.f
//                         << "shiftWeight:" << beltScaleData.shiftWeight.f;
           }
           //液温计
           else if((p.type == SensorType::LiquidThermometer) &&
                   (p.index == "2")){
               value = p.data.toUInt(&ok, 16);   // 16 表示按 16 进制解析
               float analysiValue = bigEndianToLittleEndian_qt(value);
               if( ok){
                   qDebug()<<QString("锅炉房 液温计")<<analysiValue;
               }
           }


       }

//       qDebug() << "index   :" << p.index
//                << "type    :" << QString::number(p.type)
//                << "location:" << QString::number(p.location)
//                << "data    :" << p.data
//                << "time    :" << p.time.toString(Qt::ISODate);
   }
   //   qDebug() << "=== SensorData dump end   ===";
}

void MainWindow::updateWeighbridgeData(QSqlQueryModel* newModel)
{
    if (newModel == nullptr) {
            qDebug() << "Query failed, new model is null";
            return;
        }

        // 后续步骤：删除旧模型、设置新模型
        if (m_oldModel != nullptr) {
            if (ui->tableView_weighbridge->model() == m_oldModel) {
                ui->tableView_weighbridge->setModel(nullptr);
            }
            delete m_oldModel;
            m_oldModel = nullptr;
        }

        // 此时模型已在主线程，可安全设置父对象为 tableView（主线程对象）
        ui->tableView_weighbridge->setModel(newModel);
        configureTableView(ui->tableView_weighbridge);
        m_oldModel = newModel;
}

void MainWindow::startKeepAlive()
{


    currentPage = (currentPage+1) %3;
//    ui->stackedWidget->setCurrentIndex(currentPage);

    ui->stackedWidget->setCurrentIndex(0);


    if( !MySQLDatabase::instance()->toDB()){
        MySQLDatabase::instance()->open("QMainWindow");
    }

}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    // 判断当前是否处于全屏状态
       if (this->isFullScreen()) {
           // 如果是全屏，切换到最大化
           this->showMaximized();
           qDebug() << "切换到最大化";
       } else {
           // 如果不是全屏，切换到全屏
           this->showFullScreen();
           qDebug() << "切换到全屏";
       }

       // 调用父类事件处理（可选）
       QMainWindow::mouseDoubleClickEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && this->isFullScreen()) {
           this->showMaximized();  // 或 showNormal()
    }
    QMainWindow::keyPressEvent(event);
}
