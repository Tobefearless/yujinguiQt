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

//    initDB();
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

    initTableWidget();

    connect(myT,SIGNAL(RawInspectcdataReady(QList<RawInspectionRow>)),
            this,SLOT(updateRawInspectTable(QList<RawInspectionRow>)),
            Qt::QueuedConnection);

    connect(myT,SIGNAL(pickedProducdataReady(QList<pickedProduct_Type>)),
            this,SLOT(updatePickedProductTable(QList<pickedProduct_Type>)),
            Qt::QueuedConnection);


    connect(sensorT,SIGNAL(sensorDataReady(QList<SensorData_Type>)),
            this,SLOT(updateSensorData(QList<SensorData_Type>)),
            Qt::QueuedConnection);

    connect(weighbridgeT,SIGNAL(weighbridgeDataReady(QList<WeighRecordViewType>)),
            this,SLOT(updateWeighbridgeData(QList<WeighRecordViewType>)));

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



    ui->verticalLayout_9->setAlignment(ui->label_RunningStatus, Qt::AlignHCenter);
    initAllWidgetStretch();
}

MainWindow::~MainWindow()
{
    m_keepAliveTimer->stop();
    if( thread->isRunning() == true ){
        myT->stop();
        thread->requestInterruption();
        thread->quit();
        thread->wait();
    }

    if( sensorThread->isRunning() == true ){
        sensorT->stop();
        sensorThread->requestInterruption();
        sensorThread->quit();
        sensorThread->wait();
    }

    if( weighbridgeThread->isRunning() == true ){
        weighbridgeT->stop();
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

void MainWindow::initTableWidget()
{
    spreadsheet.initPickProductTable(ui->tableWidget_Pickling);
    spreadsheet.initRawSandTable(ui->tableWidget_RowSand);
    spreadsheet.initWeighRecordTable(ui->tableWidget_weighbridge);
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
    QString openPic = ":/image/image/ValveSwitch_OpenG1.png";
    QString closePic = ":/image/image/ValveSwitch_CloseG1.png";

    if( plvValueStatus.R1_SandInletOpen){
        loadImageForLabel(ui->lbl_R1_HighSandA1_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R1_HighSandA1_SW,closePic);
    }

    //2号反应罐进沙阀门开关
    if( plvValueStatus.R2_SandInletOpen){
        loadImageForLabel(ui->lbl_R2_HighSandA2_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R2_HighSandA2_SW,closePic);
    }

    //3号反应罐进沙阀门开关
    if( plvValueStatus.R3_SandInletOpen){
        loadImageForLabel(ui->lbl_R3_HighSandA3_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R3_HighSandA3_SW,closePic);
    }

    //4号反应罐进沙阀门开关
    if( plvValueStatus.R4_SandInletOpen){
        loadImageForLabel(ui->lbl_R4_HighSandA4_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R4_HighSandA4_SW,closePic);
    }

    //1号上进酸阀门
    if( plvValueStatus.R1_HighAcidA12Open){
        loadImageForLabel(ui->lbl_R1_HighAcidA12_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R1_HighAcidA12_SW,closePic);
    }

    //2号上进酸阀门
    if( plvValueStatus.R2_HighAcidA22Open){
        loadImageForLabel(ui->lbl_R2_HighAcidA22_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R2_HighAcidA22_SW,closePic);
    }

    //3号上进酸阀门
    if( plvValueStatus.R3_HighAcidA32Open){
        loadImageForLabel(ui->lbl_R3_HighAcidA32_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R3_HighAcidA32_SW,closePic);
    }

    //4号上进酸阀门
    if( plvValueStatus.R4_HighAcidA42Open){
        loadImageForLabel(ui->lbl_R4_HighAcidA42_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R4_HighAcidA42_SW,closePic);
    }

    //1号下进酸阀门
    if( plvValueStatus.R1_LowAcidA13Open){
        loadImageForLabel(ui->lbl_R1_LowAcidA13_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R1_LowAcidA13_SW,closePic);
    }

    //2号下进酸阀门
    if( plvValueStatus.R2_LowAcidA23Open){
        loadImageForLabel(ui->lbl_R2_LowAcidA23_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R2_LowAcidA23_SW,closePic);
    }

    //3号下进酸阀门
    if( plvValueStatus.R3_LowAcidA33Open){
        loadImageForLabel(ui->lbl_R3_LowAcidA33_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R3_LowAcidA33_SW,closePic);
    }

    //4号下进酸阀门
    if( plvValueStatus.R4_LowAcidA43Open){
        loadImageForLabel(ui->lbl_R4_LowAcidA43_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R4_LowAcidA43_SW,closePic);
    }

    //1号上进水阀门开关
    if( plvValueStatus.R1_HighWaterB13Open){
        loadImageForLabel(ui->lbl_R1_HighWaterB13_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R1_HighWaterB13_SW,closePic);
    }

    //2号上进水阀门开关
    if( plvValueStatus.R2_HighWaterB23Open){
        loadImageForLabel(ui->lbl_R2_HighWaterB23_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R2_HighWaterB23_SW,closePic);
    }

    //3号上进水阀门开关
    if( plvValueStatus.R3_HighWaterB33Open){
        loadImageForLabel(ui->lbl_R3_HighWaterB33_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R3_HighWaterB33_SW,closePic);
    }

    //4号上进水阀门开关
    if( plvValueStatus.R4_HighWaterB43Open){
        loadImageForLabel(ui->lbl_R4_HighWaterB43_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R4_HighWaterB43_SW,closePic);
    }


    //1号下进水阀门开关
    if( plvValueStatus.R1_LowWaterB11Open){
        loadImageForLabel(ui->lbl_R1_LowWaterB11_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R1_LowWaterB11_SW,closePic);
    }

    //2号下进水阀门开关
    if( plvValueStatus.R2_LowWaterB21Open){
        loadImageForLabel(ui->lbl_R2_LowWaterB21_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R2_LowWaterB21_SW,closePic);
    }

    //3号下进水阀门开关
    if( plvValueStatus.R3_LowWaterB31Open){
        loadImageForLabel(ui->lbl_R3_LowWaterB31_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R3_LowWaterB31_SW,closePic);
    }

    //4号下进水阀门开关
    if( plvValueStatus.R4_LowWaterB41Open){
        loadImageForLabel(ui->lbl_R4_LowWaterB41_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R4_LowWaterB41_SW,closePic);
    }

    //1号 排沙阀门开关
    if( plvValueStatus.R1_SandDrainPS1Open){
        loadImageForLabel(ui->lbl_R1_SandDrainPS1_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R1_SandDrainPS1_SW,closePic);
    }

    //2号 排沙阀门开关
    if( plvValueStatus.R2_SandDrainPS2Open){
        loadImageForLabel(ui->lbl_R2_SandDrainPS2_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R2_SandDrainPS2_SW,closePic);
    }

    //3号 排沙阀门开关
    if( plvValueStatus.R3_SandDrainPS3Open){
        loadImageForLabel(ui->lbl_R3_SandDrainPS3_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R3_SandDrainPS3_SW,closePic);
    }

    //4号 排沙阀门开关
    if( plvValueStatus.R4_SandDrainPS4Open){
        loadImageForLabel(ui->lbl_R4_SandDrainPS4_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R4_SandDrainPS4_SW,closePic);
    }

    //1号 排酸阀门开关
    if( plvValueStatus.R1_DrainAcidPS11Open){
        loadImageForLabel(ui->lbl_R1_DrainAcidPS11_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R1_DrainAcidPS11_SW,closePic);
    }

    //2号 排酸阀门开关
    if( plvValueStatus.R2_DrainAcidPS12Open){
        loadImageForLabel(ui->lbl_R2_DrainAcidPS12_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R2_DrainAcidPS12_SW,closePic);
    }

    //3号 排酸阀门开关
    if( plvValueStatus.R3_DrainAcidPS13Open){
        loadImageForLabel(ui->lbl_R3_DrainAcidPS13_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R3_DrainAcidPS13_SW,closePic);
    }

    //4号 排酸阀门开关
    if( plvValueStatus.R4_DrainAcidPS14Open){
        loadImageForLabel(ui->lbl_R4_DrainAcidPS14_SW,openPic);
    }else{
        loadImageForLabel(ui->lbl_R4_DrainAcidPS14_SW,closePic);
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
      label->setMaximumSize(71,60);
      return true;
}

void MainWindow::initAllWidgetStretch()
{
    int stretch = 75;
//    //抽酸泵压力值
//    initFFontStretch(ui->groupBox_7,stretch);
//    initFFontStretch(ui->label_acidPumpPressure,stretch);
//    initFFontStretch(ui->label_83,stretch);

//    //氢氟酸罐
//    initFFontStretch(ui->groupBox_6,stretch);
//    initFFontStretch(ui->label_ImportedSteamValue_6,stretch);
//    initFFontStretch(ui->label_ImportedSteamValue_7,stretch);
//    initFFontStretch(ui->label_hydrofluoricAcidTankOutletTemperature,stretch);
//    initFFontStretch(ui->label_hydrofluoricAcidTankLevel,stretch);

//    //皮带秤重量
//    initFFontStretch(ui->groupBox,stretch);
//    initFFontStretch(ui->label_ImportedSteamValue_2,stretch);
//    initFFontStretch(ui->label_ImportedSteamValue_3,stretch);
//    initFFontStretch(ui->label_ImportedSteamValue_4,stretch);
//    initFFontStretch(ui->label_ImportedSteamValue_5,stretch);
//    initFFontStretch(ui->groupBox_7,stretch);
//    initFFontStretch(ui->groupBox_7,stretch);

    setFontForAllChildren(ui->groupBox_7,stretch);

    setFontForAllChildren(ui->groupBox_6,stretch);

    setFontForAllChildren(ui->groupBox,stretch);

    setFontForAllChildren(ui->groupBox_9,stretch);

    setFontForAllChildren(ui->groupBox_8,stretch);

    setFontForAllChildren(ui->groupBox_4,stretch);

    setFontForAllChildren(ui->groupBox_5,stretch);

    setFontForAllChildren(ui->groupBox_2,stretch);

    setFontForAllChildren(ui->groupBox_3,stretch);
}

void MainWindow::initFFontStretch(QWidget * w,int stretch)
{
    QFont font = w->font();
    font.setStretch(stretch);
    font.setHintingPreference(QFont::PreferFullHinting);  // 完整Hinting
    font.setStyleHint(QFont::SansSerif);  // 确保使用无衬线字体
    w->setFont(font);
}

void MainWindow::setFontForAllChildren(QWidget *parentWidget, int stretch)
{
    if (!parentWidget) {
           return;
       }

   // 1. 先设置当前父控件的字体
   initFFontStretch(parentWidget,stretch);

   // 2. 遍历所有直接子控件
   foreach (QObject *child, parentWidget->children()) {
       // 尝试将子对象转换为 QWidget
       QWidget *childWidget = qobject_cast<QWidget*>(child);
       if (childWidget) {
           // 3. 如果转换成功，递归调用此函数，为子控件及其后代设置字体
           setFontForAllChildren(childWidget, stretch);
       }
   }
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
       QByteArray temp =  HexStringToByteArray(ByteArrayToHexString(p.data), &ok);
       //氢氟酸罐-坑底 温度
       if( p.location == HF_TIN_2 && p.type == TEMP ){
            value = p.data.toUInt(&ok, 16);   // 16 表示按 16 进制解析
            ui->label_hydrofluoricAcidTankOutletTemperature->setText(QString::number(intToFloat(value), 'f', 1));
       }
       //酸洗罐 顶部 温度 气压
       else if( p.location == HF_TIN_3 && p.type == TEMP ){
           HFTankTopData tankTopData;
           char *rcv = temp.data();
           memcpy((char*)&tankTopData,rcv,sizeof(HFTankTopData));

           ui->labelHFTankTopTemp->setText(QString::number(tankTopData.temperature, 'f', 1) + "℃");
           ui->labelHFTankTopPressure->setText(QString::number(tankTopData.pressure / 1000.0, 'f', 4) + "MPa");
       }//皮带秤 1.工作状态 2.总累计量 3.月累计量 4.日累计量 5.班次累计量
       else if( p.location == BELT_SCALE && p.type == WEIGH ){
           BeltScaleParams scaleParams;
           char *rcv = temp.data();
           memcpy((char*)&scaleParams,rcv,sizeof(BeltScaleParams));
           ui->labelTotalAccumulated->setText(QString::number(scaleParams.totalAccumulated, 'f', 1) + "t");
           ui->labelMonthlyAccumulated->setText(QString::number(scaleParams.monthlyAccumulated, 'f', 1) + "t");
           ui->labelDailyAccumulated->setText(QString::number(scaleParams.dailyAccumulated, 'f', 1) + "t");
           ui->labelShiftAccumulated->setText(QString::number(scaleParams.shiftAccumulated, 'f', 1) + "t");
       }//机房控制 AI模拟量
       else if( p.location == HF_TIN_1 && p.type == PLC_AI ){
           ProcessVariables variables =parseProcessVariables(p.data);

           QString text = QString::number(variables.pumpOutletPressure, 'f', 1);
//           text.replace(".", " .");
           ui->label_acidPumpPressure->setText(
                       text);

           ui->label_hydrofluoricAcidTankLevel->setText(
                       QString::number(variables.hydrofluoricAcidTankLevel, 'f', 1) + "m");


           ui->label_acidWashTank1_Temperature->setText(
                       QString::number(variables.reactor1Temperature, 'f', 1) + "℃");
           ui->label_acidWashTank2_Temperature->setText(
                       QString::number(variables.reactor2Temperature, 'f', 1) + "℃");
           ui->label_acidWashTank3_Temperature->setText(
                       QString::number(variables.reactor3Temperature, 'f', 1) + "℃");
           ui->label_acidWashTank4_Temperature->setText(
                       QString::number(variables.reactor4Temperature, 'f', 1) + "℃");
       }
       else if(p.location == HF_TIN_1 && p.type == PLC_DI){
           setValveParameters(p.data);
       }

   }

}

void MainWindow::updateWeighbridgeData(const QList<WeighRecordViewType>& products)
{
    spreadsheet.fillWeighRecordTable(ui->tableWidget_weighbridge,products);
}

void MainWindow::startKeepAlive()
{


    currentPage = (currentPage+1) %3;
    ui->stackedWidget->setCurrentIndex(currentPage);

//    ui->stackedWidget->setCurrentIndex(0);

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
