#ifndef VALUE_TYPE_H
#define VALUE_TYPE_H
#include <QString>
#include <QMetaType>
#include <QDateTime>
//excel strucy
typedef  struct
{
        QString picklingTankNumber;      // 酸洗罐号
        QString originalSandInjectionDate; // 原砂进罐日期
        QString proportionRawSand;       // 原砂进罐比例
        QString endTimeRaw;              // 原砂进罐结束时间
        QString samplingDate;            // 取样日期
        QString samplingTime;            // 取样时间
        QString productionSamplingTime;  // 生产取样累计时间(小时)
        QString samplingTemperature;     // 取样时温度℃

        // 元素成分分析
        QString elementalAnalysisSi;     // Si
        QString elementalAnalysisFe;     // Fe
        QString elementalAnalysisTi;     // Ti

        // 成品送样
        QString finishedProductDate;     // 成品送样日期
        QString finishedProductTime;     // 成品送样时间

        // 颗粒度检测结果
        QString particleDetectionResults25;  // <25目
        QString particleDetectionResults140; // >140目
        QString particleDetectionResults150; // >150目

        // 成分分析结果
        QString compositionResultsSi;    // Si
        QString compositionResultsFe;    // Fe
        QString compositionResultsTi;    // Ti
}pickedProduct_Type;
Q_DECLARE_METATYPE(pickedProduct_Type)


/// 原砂检验单（一次来料检验）对应结构体
typedef struct
{
    QString supplier;                     // 供应商
    QString storageTime;                  // 入库时间
    QString wagonNumber;                  // 车号
    QString inspectionTime;               // 检验时间

    QString moistureDetectionResults;     // 水分检测结果
    QString particleSizeDetectionResults25;  // <25目粒度
    QString particleSizeDetectionResults140; // >140目粒度

    QString rawSandSi;                    // 原砂 Si
    QString rawSandFe;                    // 原砂 Fe
    QString rawSandTi;                    // 原砂 Ti

    QString acidWashingTestMethod;        // 酸洗试验方法
    QString acidpicklingSi;               // 酸洗后 Si
    QString acidpicklingFe;               // 酸洗后 Fe
    QString acidpicklingTi;               // 酸洗后 Ti

    QString experimentalResult;           // 实验结果结论
}RawInspectionRow;
Q_DECLARE_METATYPE(RawInspectionRow)

typedef struct
{
    QString runningNum;      // 流水号
    QString licensePlate;    // 车牌号
    QString driver;          // 司机
    QString businessType;    // 业务类型
    QString customerName;    // 客户
    QString supplierName;    // 供应商
    QString productName;     // 商品
    qreal   totalWeight = 0; // 毛重 kg
    qreal   tare        = 0; // 皮重 kg
    qreal   buckle      = 0; // 扣重 kg
    qreal   neatWeight  = 0; // 净重 kg
    QDateTime weighTime;     // 过磅时间
    QString sendCorpName;    // 发货单位
    QString recvCorpName;    // 收货单位

    // 方便调试或日志输出
    QString toString() const
    {
        return QStringLiteral(
            "WeightRecord{"
            "runningNum:%1, licensePlate:%2, driver:%3, "
            "businessType:%4, customer:%5, supplier:%6, "
            "product:%7, total:%8, tare:%9, buckle:%10, neat:%11, "
            "weighTime:%12, sender:%13, receiver:%14}")
            .arg(runningNum, licensePlate, driver,
                 businessType, customerName, supplierName,
                 productName)
            .arg(totalWeight).arg(tare).arg(buckle).arg(neatWeight)
            .arg(weighTime.toString(Qt::ISODate))
            .arg(sendCorpName, recvCorpName);
    }
}WeightRecord_Type;

// 若要直接用在 Qt 信号/槽、QVariant、QML 中，再注册即可
Q_DECLARE_METATYPE(WeightRecord_Type)


// 称重记录结构体（所有字段均为字符串类型）
typedef struct WeighRecord {
    QString runningNum;       // 对应 [RunningNum]
    QString licenseplate;     // 对应 [Licenseplate]
    QString driver;           // 对应 [Driver]
    QString businessType;     // 对应 [BusinessType]
    QString customerName;     // 对应 [CustomerName]
    QString supplierName;     // 对应 [SupplierName]
    QString productName;      // 对应 [ProductName]
    QString totalWeight;      // 对应 [TotalWeight]（重量以字符串形式存储）
    QString tare;             // 对应 [Tare]（皮重以字符串形式存储）
    QString buckle;           // 对应 [Buckle]（扣重以字符串形式存储）
    QString neatWeight;       // 对应 [NeatWeight]（净重以字符串形式存储）
    QString weighTime;        // 对应 [WeighTime]（时间以字符串形式存储，保留原始格式）
    QString sendcorpName;     // 对应 [SendcorpName]
    QString recvcorpName;     // 对应 [RecvcorpName]
}WeighRecord;
Q_DECLARE_METATYPE(WeighRecord)


typedef enum{
    LowWeightRoom   = 0x01,   // 地磅房
    BeltScale       = 0x02,   // 皮带称
    BackAcidTin     = 0x03,   // 回酸罐
    HfTin           = 0x04,   // 氢氟酸罐
    Graphene        = 0x05,   // 石墨烯热换器
    ReactionStill   = 0x06,   // 反应釜
    BoilerRoom      = 0x07,   // 锅炉房
    DosingRoom      = 0x08    // 加药间
}DevLocation;

// 传感器类型
typedef enum{
    Temp               = 0x01,  // 温度
    Weigh              = 0x02,  // 重量
    LevelGauge         = 0x03,  // 液位计
    Barometer          = 0x04,  // 气压计
    LiquidThermometer  = 0x05,  // 液温计
    LiquidPh           = 0x06,  // 液体 PH
    Valve              = 0x07   // 阀门
}SensorType;


// 辅助：把枚举值转成中文描述
static inline QString devLocationToString(DevLocation loc) {
   switch (loc) {
   case DevLocation::LowWeightRoom:  return QStringLiteral("地磅房");
   case DevLocation::BeltScale:      return QStringLiteral("皮带称");
   case DevLocation::BackAcidTin:    return QStringLiteral("回酸罐");
   case DevLocation::HfTin:          return QStringLiteral("氢氟酸罐");
   case DevLocation::Graphene:       return QStringLiteral("石墨烯热换器");
   case DevLocation::ReactionStill:  return QStringLiteral("反应釜");
   case DevLocation::BoilerRoom:     return QStringLiteral("锅炉房");
   case DevLocation::DosingRoom:     return QStringLiteral("加药间");
   }
   return QStringLiteral("未知");
}

static inline QString sensorTypeToString(SensorType type) {
   switch (type) {
   case SensorType::Temp:              return QStringLiteral("温度");
   case SensorType::Weigh:             return QStringLiteral("重量");
   case SensorType::LevelGauge:        return QStringLiteral("液位计");
   case SensorType::Barometer:         return QStringLiteral("气压计");
   case SensorType::LiquidThermometer: return QStringLiteral("液温计");
   case SensorType::LiquidPh:          return QStringLiteral("液体PH");
   case SensorType::Valve:             return QStringLiteral("阀门");
   }
   return QStringLiteral("未知");
}

typedef struct {
    QString index;
    int type;
    int location;
    QString data;
    QDateTime time;
}SensorData_Type;
Q_DECLARE_METATYPE(SensorData_Type)

#pragma pack(push, 1) // 禁用结构体对齐，确保紧凑布局
typedef struct  {
    // Byte0
    unsigned int SuctionAcidPumpAutoStatus: 1;                // Bit0 抽酸泵自动状态
    unsigned int SuctionAcidPumpInverterRunning: 1;           // Bit1 抽酸泵变频器运行信号
    unsigned int SuctionAcidPumpInverterFault: 1;             // Bit2 抽酸泵变频器故障信号
    unsigned int VacuumPumpAutoStatus: 1;                     // Bit3 真空泵自动状态
    unsigned int VacuumPumpRunning: 1;                        // Bit4 真空泵运行信号
    unsigned int VacuumPumpFault: 1;                          // Bit5 真空泵故障信号
    unsigned int SteamValveAutoStatus: 1;                     // Bit6 蒸汽阀自动状态
    unsigned int SteamValveOpen: 1;                           // Bit7 蒸汽阀打开到位

    // Byte1
    unsigned int SteamValveClosed: 1;                         // Bit0 蒸汽阀关闭到位
    unsigned int SteamValveFault: 1;                          // Bit1 蒸汽阀故障信号
    unsigned int BoilerAuto: 1;                               // Bit2 锅炉自动信号
    unsigned int BoilerRunning: 1;                            // Bit3 锅炉运行信号
    unsigned int BoilerFault: 1;                              // Bit4 锅炉故障信号
    unsigned int R1_LowAcidA13Auto: 1;                        // Bit5 1号反应罐下进酸A13阀自动
    unsigned int R1_LowAcidA13Open: 1;                        // Bit6 1号反应罐下进酸A13阀开到位
    unsigned int R1_LowAcidA13Closed: 1;                      // Bit7 1号反应罐下进酸A13阀关到位

    // Byte2
    unsigned int R1_HighAcidA12Auto: 1;                       // Bit0 1号反应罐上进酸A12阀自动
    unsigned int R1_HighAcidA12Open: 1;                       // Bit1 1号反应罐上进酸A12阀开到位
    unsigned int R1_HighAcidA12Closed: 1;                     // Bit2 1号反应罐上进酸A12阀关到位
    unsigned int R1_LowWaterB11Auto: 1;                       // Bit3 1号反应罐下进水B11阀自动
    unsigned int R1_LowWaterB11Open: 1;                       // Bit4 1号反应罐下进水B11阀开到位
    unsigned int R1_LowWaterB11Closed: 1;                     // Bit5 1号反应罐下进水B11阀关到位
    unsigned int R1_FlushWaterB12Auto: 1;                     // Bit6 1号反应罐冲洗水B12阀自动
    unsigned int R1_FlushWaterB12Open: 1;                     // Bit7 1号反应罐冲洗水B12阀开到位

    // Byte3
    unsigned int R1_FlushWaterB12Closed: 1;                   // Bit0 1号反应罐冲洗水B12阀关到位
    unsigned int R1_HighWaterB13Auto: 1;                      // Bit1 1号反应罐上进水B13阀自动
    unsigned int R1_HighWaterB13Open: 1;                      // Bit2 1号反应罐上进水B13阀开到位
    unsigned int R1_HighWaterB13Closed: 1;                    // Bit3 1号反应罐上进水B13阀关到位
    unsigned int R1_InletGasC1Auto: 1;                        // Bit4 1号反应罐进气C1阀自动
    unsigned int R1_InletGasC1Open: 1;                        // Bit5 1号反应罐进气C1阀开到位
    unsigned int R1_InletGasC1Closed: 1;                      // Bit6 1号反应罐进气C1阀关到位
    unsigned int R1_DrainAcidPS11Auto: 1;                     // Bit7 1号反应罐直排酸PS11阀自动

    // Byte4
    unsigned int R1_DrainAcidPS11Open: 1;                     // Bit0 1号反应罐直排酸PS11阀开到位
    unsigned int R1_DrainAcidPS11Closed: 1;                   // Bit1 1号反应罐直排酸PS11阀关到位
    unsigned int R5_DrainAcidPS21Auto: 1;                     // Bit2 5号直排酸PS21阀自动
    unsigned int R5_DrainAcidPS21Open: 1;                     // Bit3 5号直排酸PS21阀开到位
    unsigned int R5_DrainAcidPS21Closed: 1;                   // Bit4 5号直排酸PS21阀关到位
    unsigned int R1_SandDrainPS1Auto: 1;                      // Bit5 1号反应罐排沙PS1阀自动
    unsigned int R1_SandDrainPS1Open: 1;                      // Bit6 1号反应罐排沙PS1阀开
    unsigned int R1_SandDrainPS1Stop: 1;                      // Bit7 1号反应罐排沙PS1阀开停

    // Byte5
    unsigned int R1_SandDrainPS1Close: 1;                     // Bit0 1号反应罐排沙PS1阀关
    unsigned int R1_SandDrainPS1StopClose: 1;                 // Bit1 1号反应罐排沙PS1阀关停
    unsigned int R1_SandDrainPS1Fault: 1;                     // Bit2 1号反应罐排沙PS1阀故障
    unsigned int R2_LowAcidA23Auto: 1;                        // Bit3 2号反应罐下进酸A23阀自动
    unsigned int R2_LowAcidA23Open: 1;                        // Bit4 2号反应罐下进酸A23阀开
    unsigned int R2_LowAcidA23Close: 1;                       // Bit5 2号反应罐下进酸A23阀关
    unsigned int R2_HighAcidA22Auto: 1;                       // Bit6 2号反应罐上进酸A22阀自动
    unsigned int R2_HighAcidA22Open: 1;                       // Bit7 2号反应罐上进酸A22阀开到位

    // Byte6
    unsigned int R2_HighAcidA22Closed: 1;                     // Bit0 2号反应罐上进酸A22阀关到位
    unsigned int R2_LowWaterB21Auto: 1;                       // Bit1 2号反应罐下进水B21阀自动
    unsigned int R2_LowWaterB21Open: 1;                       // Bit2 2号反应罐下进水B21阀开到位
    unsigned int R2_LowWaterB21Closed: 1;                     // Bit3 2号反应罐下进水B21阀关到位
    unsigned int R2_FlushWaterB22Auto: 1;                     // Bit4 2号反应罐冲洗水B22阀自动
    unsigned int R2_FlushWaterB22Open: 1;                     // Bit5 2号反应罐冲洗水B22阀开到位
    unsigned int R2_FlushWaterB22Closed: 1;                   // Bit6 2号反应罐冲洗水B22阀关到位
    unsigned int R2_HighWaterB23Auto: 1;                      // Bit7 2号反应罐上进水B23阀自动

    // Byte7
    unsigned int R2_HighWaterB23Open: 1;                      // Bit0 2号反应罐上进水B23阀开到位
    unsigned int R2_HighWaterB23Closed: 1;                    // Bit1 2号反应罐上进水B23阀关到位
    unsigned int R2_InletGasC2Auto: 1;                        // Bit2 2号反应罐进气C2阀自动
    unsigned int R2_InletGasC2Open: 1;                        // Bit3 2号反应罐进气C2阀开到位
    unsigned int R2_InletGasC2Closed: 1;                      // Bit4 2号反应罐进气C2阀关到位
    unsigned int R2_DrainAcidPS12Auto: 1;                     // Bit5 2号反应罐直排酸PS12阀自动
    unsigned int R2_DrainAcidPS12Open: 1;                     // Bit6 2号反应罐直排酸PS12阀开到位
    unsigned int R2_DrainAcidPS12Closed: 1;                   // Bit7 2号反应罐直排酸PS12阀关到位

    // Byte8
    unsigned int R6_VacuumAcidPS22Auto: 1;                    // Bit0 6号真空排酸PS22阀自动
    unsigned int R6_VacuumAcidPS22Open: 1;                    // Bit1 6号真空排酸PS22阀开到位
    unsigned int R6_VacuumAcidPS22Closed: 1;                  // Bit2 6号真空排酸PS22阀关到位
    unsigned int R2_SandDrainPS2Auto: 1;                      // Bit3 2号反应罐排沙PS2阀自动
    unsigned int R2_SandDrainPS2Open: 1;                      // Bit4 2号反应罐排沙PS2阀开
    unsigned int R2_SandDrainPS2Stop: 1;                      // Bit5 2号反应罐排沙PS2阀开停
    unsigned int R2_SandDrainPS2Close: 1;                     // Bit6 2号反应罐排沙PS2阀关
    unsigned int R2_SandDrainPS2StopClose: 1;                 // Bit7 2号反应罐排沙PS2阀关停

    // Byte9
    unsigned int R2_SandDrainPS2Fault: 1;                     // Bit0 2号反应罐排沙PS2阀故障
    unsigned int R3_LowAcidA33Auto: 1;                        // Bit1 3号反应罐下进酸A33阀自动
    unsigned int R3_LowAcidA33Open: 1;                        // Bit2 3号反应罐下进酸A33阀开
    unsigned int R3_LowAcidA33Close: 1;                       // Bit3 3号反应罐下进酸A33阀关
    unsigned int R3_HighAcidA32Auto: 1;                       // Bit4 3号反应罐上进酸A32阀自动
    unsigned int R3_HighAcidA32Open: 1;                       // Bit5 3号反应罐上进酸A32阀开
    unsigned int R3_HighAcidA32Close: 1;                      // Bit6 3号反应罐上进酸A32阀关
    unsigned int R3_LowWaterB31Auto: 1;                       // Bit7 3号反应罐下进水B31阀自动

    // Byte10
    unsigned int R3_LowWaterB31Open: 1;                       // Bit0 3号反应罐下进水B31阀开
    unsigned int R3_LowWaterB31Close: 1;                      // Bit1 3号反应罐下进水B31阀关
    unsigned int R3_FlushWaterB32Auto: 1;                     // Bit2 3号反应罐冲洗水B32阀自动
    unsigned int R3_FlushWaterB32Open: 1;                     // Bit3 3号反应罐冲洗水B32阀开
    unsigned int R3_FlushWaterB32Close: 1;                    // Bit4 3号反应罐冲洗水B32阀关
    unsigned int R3_HighWaterB33Auto: 1;                      // Bit5 3号反应罐上进水B33阀自动
    unsigned int R3_HighWaterB33Open: 1;                      // Bit6 3号反应罐上进水B33阀开
    unsigned int R3_HighWaterB33Close: 1;                     // Bit7 3号反应罐上进水B33阀关

    // Byte11
    unsigned int R3_InletGasC3Open: 1;                        // Bit0 3号反应罐进气C3阀开
    unsigned int R3_InletGasC3Close: 1;                       // Bit1 3号反应罐进气C3阀关
    unsigned int R3_DrainAcidPS13Auto: 1;                     // Bit2 3号反应罐直排酸PS13阀自动
    unsigned int R3_DrainAcidPS13Open: 1;                     // Bit3 3号反应罐直排酸PS13阀开
    unsigned int R3_DrainAcidPS13Close: 1;                    // Bit4 3号反应罐直排酸PS13阀关
    unsigned int R3_VacuumAcidPS23Auto: 1;                    // Bit5 3号反应罐真空排酸PS23阀自动
    unsigned int R3_VacuumAcidPS23Open: 1;                    // Bit6 3号反应罐真空排酸PS23阀开
    unsigned int R3_InletGasC3Auto: 1;                        // Bit7 3号反应罐进气C3阀自动

    // Byte12
    unsigned int R3_VacuumAcidPS23Close: 1;                   // Bit0 3号反应罐真空排酸PS23阀关
    unsigned int R3_SandDrainPS3Auto: 1;                      // Bit1 3号反应罐排沙PS3阀自动
    unsigned int R3_SandDrainPS3Open: 1;                      // Bit2 3号反应罐排沙PS3阀开
    unsigned int R3_SandDrainPS3Stop: 1;                      // Bit3 3号反应罐排沙PS3阀开停
    unsigned int R3_SandDrainPS3Close: 1;                     // Bit4 3号反应罐排沙PS3阀关
    unsigned int R3_SandDrainPS3StopClose: 1;                 // Bit5 3号反应罐排沙PS3阀关停
    unsigned int R3_SandDrainPS3Fault: 1;                     // Bit6 3号反应罐排沙PS3阀故障
    unsigned int R4_LowAcidA43Auto: 1;                        // Bit7 4号反应罐下进酸A43阀自动

    // Byte13
    unsigned int R4_LowAcidA43Open: 1;                        // Bit0 4号反应罐下进酸A43阀开
    unsigned int R4_LowAcidA43Close: 1;                       // Bit1 4号反应罐下进酸A43阀关
    unsigned int R4_HighAcidA42Auto: 1;                       // Bit2 4号反应罐上进酸A42阀自动
    unsigned int R4_HighAcidA42Open: 1;                       // Bit3 4号反应罐上进酸A42阀开
    unsigned int R4_HighAcidA42Close: 1;                      // Bit4 4号反应罐上进酸A42阀关
    unsigned int R4_LowWaterB41Auto: 1;                       // Bit5 4号反应罐下进水B41阀自动
    unsigned int R4_LowWaterB41Open: 1;                       // Bit6 4号反应罐下进水B41阀开
    unsigned int R4_LowWaterB41Close: 1;                      // Bit7 4号反应罐下进水B41阀关

    // Byte14
    unsigned int R4_FlushWaterB42Auto: 1;                     // Bit0 4号反应罐冲洗水B42阀自动
    unsigned int R4_FlushWaterB42Open: 1;                     // Bit1 4号反应罐冲洗水B42阀开
    unsigned int R4_FlushWaterB42Close: 1;                    // Bit2 4号反应罐冲洗水B42阀关
    unsigned int R4_HighWaterB43Auto: 1;                      // Bit3 4号反应罐上进水B43阀自动
    unsigned int R4_HighWaterB43Open: 1;                      // Bit4 4号反应罐上进水B43阀开
    unsigned int R4_HighWaterB43Close: 1;                     // Bit5 4号反应罐上进水B43阀关
    unsigned int R4_InletGasC4Auto: 1;                        // Bit6 4号反应罐进气C4阀自动
    unsigned int R4_InletGasC4Open: 1;                        // Bit7 4号反应罐进气C4阀开

    // Byte15
    unsigned int R4_InletGasC4Close: 1;                       // Bit0 4号反应罐进气C4阀关
    unsigned int R4_DrainAcidPS14Auto: 1;                     // Bit1 4号反应罐直排酸PS14阀自动
    unsigned int R4_DrainAcidPS14Open: 1;                     // Bit2 4号反应罐直排酸PS14阀开
    unsigned int R4_DrainAcidPS14Close: 1;                    // Bit3 4号反应罐直排酸PS14阀关
    unsigned int R4_VacuumAcidPS24Auto: 1;                    // Bit4 4号反应罐真空排酸PS24阀自动
    unsigned int R4_VacuumAcidPS24Open: 1;                    // Bit5 4号反应罐真空排酸PS24阀开
    unsigned int R4_VacuumAcidPS24Close: 1;                   // Bit6 4号反应罐真空排酸PS24阀关
    unsigned int R4_SandDrainPS4Auto: 1;                      // Bit7 4号反应罐排沙PS4阀自动

    // Byte16
    unsigned int R4_SandDrainPS4Open: 1;                      // Bit0 4号反应罐排沙PS4阀开
    unsigned int R4_SandDrainPS4Stop: 1;                      // Bit1 4号反应罐排沙PS4阀开停
    unsigned int R4_SandDrainPS4Close: 1;                     // Bit2 4号反应罐排沙PS4阀关
    unsigned int R4_SandDrainPS4StopClose: 1;                 // Bit3 4号反应罐排沙PS4阀关停
    unsigned int R4_SandDrainPS4Fault: 1;                     // Bit4 4号反应罐排沙PS4阀故障
    unsigned int R1_SandInletOpen: 1;                         // Bit5 1号反应罐进沙阀开
    unsigned int R1_SandInletClose: 1;                        // Bit6 1号反应罐进沙阀关
    unsigned int R2_SandInletOpen: 1;                         // Bit7 2号反应罐进沙阀开

    // Byte17
    unsigned int R2_SandInletClose: 1;                        // Bit0 2号反应罐进沙阀关
    unsigned int R3_SandInletOpen: 1;                         // Bit1 3号反应罐进沙阀开
    unsigned int R3_SandInletClose: 1;                        // Bit2 3号反应罐进沙阀关
    unsigned int R4_SandInletOpen: 1;                         // Bit3 4号反应罐进沙阀开
    unsigned int R4_SandInletClose: 1;                        // Bit4 4号反应罐进沙阀关
    unsigned int Reserved1: 1;                                // Bit5 保留位1
    unsigned int Reserved2: 1;                                // Bit6 保留位2
    unsigned int Reserved3: 1;                                // Bit7 保留位3
}PLCValveStatus;


typedef union {
    uint32_t u;
    float f;
} FP_Type;
typedef struct {
    uint32_t status;     // 工作状态
    FP_Type totalWeight;   // 总累计量
    FP_Type monthWeight;   // 月累计量
    FP_Type dayWeight;     // 日累计量
    FP_Type shiftWeight;   // 班次累计量
} APT_BeltScaleData;     // 皮带秤数据

#pragma pack(pop) // 恢复默认对齐方式


uint32_t bigEndianToLittleEndian_qt(uint32_t value);
float intToFloat(uint32_t value);
float bigEndianToFloat(quint32 raw);

//十六进制的字符串转QByteArray
QByteArray HexStringToByteArray(QString hex, bool *ok);
//QByteArray的转16进制
QString ByteArrayToHexString(QString data);
#endif // VALUE_TYPE_H
