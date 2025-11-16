#include "excelreader.h"
#include <QDebug>
#include <QMessageBox>
#include <QException>
#include <QElapsedTimer> // 添加计时器
#include <QThread>
#include <QCoreApplication>
#include <QDateTime>
#include <memory>
#include <functional>
// 自定义异常类
class ExcelReadException : public std::runtime_error {
public:
    explicit ExcelReadException(const QString& message)
        : std::runtime_error(message.toStdString()) {}
};


ExcelReader::ExcelReader()
{

}

void ExcelReader::loadSampleRows(const QString &filePath,
                                                      QList<pickedProduct_Type> &pickedProductList,
                                                      QList<RawInspectionRow> &rawInspectProductList)
{
       QAxObject* workbook = nullptr;
       QAxObject* excel = nullptr;

       // 1. 立即创建并显示进度对话框
       QProgressDialog progress("正在启动Excel应用程序...", "取消", 0, 0, nullptr);
       progress.setWindowModality(Qt::WindowModal);
       progress.setMinimumDuration(0); // 立即显示进度条
       progress.setRange(0, 0); // 不确定进度模式
       progress.setValue(0);
       progress.show();
       QCoreApplication::processEvents(); // 强制立即显示进度条

    try {
           // 2. 启动 Excel Application
           progress.setLabelText("正在启动Excel...");
           QCoreApplication::processEvents();

           excel = new QAxObject("Excel.Application");
           if (!excel || excel->isNull()) {
               throw ExcelReadException("无法创建Excel应用程序实例");
           }

           progress.setLabelText("正在配置Excel设置...");
           QCoreApplication::processEvents();

           excel->setProperty("Visible", false);
           excel->setProperty("DisplayAlerts", false);

           // 3. 打开工作簿
           progress.setLabelText("正在打开工作簿...");
           QCoreApplication::processEvents();

           QAxObject *workbooks = excel->querySubObject("Workbooks");
           if (!workbooks) {
               throw ExcelReadException("无法访问Workbooks对象");
           }

           workbook = workbooks->querySubObject("Open(const QString&)", filePath);
           if (!workbook) {
               throw ExcelReadException("无法打开Excel文件: " + filePath);
           }

          pickedProductList.append(parsePickedProduct(workbook,progress));
          rawInspectProductList.append(rawInspectProduct(workbook, progress));
          QCoreApplication::processEvents();
          QThread::sleep(1); // 让用户看到完成消息
      }
      catch (const ExcelReadException& e) {
          qCritical() << "Excel读取错误:" << e.what();
          progress.setLabelText("读取失败: " + QString(e.what()));
          QCoreApplication::processEvents();
          QThread::sleep(2); // 让用户看到错误消息

          QMessageBox::critical(nullptr, "Excel读取错误",
                               QString("读取Excel文件时发生错误:\n%1").arg(e.what()));
      }
      catch (const std::exception& e) {
          qCritical() << "标准异常:" << e.what();
          progress.setLabelText("标准异常: " + QString(e.what()));
          QCoreApplication::processEvents();
          QThread::sleep(2);

          QMessageBox::critical(nullptr, "Excel读取错误",
                               QString("标准异常: %1").arg(e.what()));
      }
      catch (...) {
          qCritical() << "未知错误";
          progress.setLabelText("发生未知错误");
          QCoreApplication::processEvents();
          QThread::sleep(2);

          QMessageBox::critical(nullptr, "Excel读取错误", "发生未知错误");
      }



      if (workbook) {
          try {
              workbook->dynamicCall("Close(Boolean)", false);
          } catch (...) {
              qWarning() << "关闭工作簿时出错";
          }
          delete workbook;
      }

      if (excel) {
          try {
              excel->dynamicCall("Quit()");
          } catch (...) {
              qWarning() << "退出Excel时出错";
          }
          delete excel;
      }
}

QString ExcelReader::formatDateTimeToChinese(const QString &isoStr, bool *ok)
{
   if (ok)
           *ok = false;

   if (isoStr.isEmpty())
       return QString();

   // 解析 ISO-8601
   QDateTime dt = QDateTime::fromString(isoStr, Qt::ISODate);

   // 无效格式或非法日期（如 2023-02-30）都会使 dt 无效
   if (!dt.isValid()) {
       qWarning() << "Invalid ISO date-time:" << isoStr;
       return QString();
   }

   QString result = dt.toString("yyyy年M月d日");
   if (ok)
       *ok = true;
   return result;
}

QString ExcelReader::formatTimeToMMSS(const QString &src, bool *ok)
{
    if (ok) *ok = false;
    if (src.isEmpty()) return QString();

    QString trimmed = src.trimmed();

    // 1. 尝试解析为 OLE 数值
    bool doubleOk = false;
    double ole = trimmed.toDouble(&doubleOk);
    if (doubleOk && ole >= 0.0) {                // 有效 OLE 数值
        QDateTime dt = convertOleDateTime(ole);
        if (ok) *ok = true;
        return dt.toString("h:m");
    }

    // 2. 尝试解析为 "h:mm:ss" 文本
    QTime t = QTime::fromString(trimmed, "h:mm:ss");
    if (t.isValid()) {
        if (ok) *ok = true;
        return t.toString("h:m");
    }

    // 3. 失败
    qWarning() << "无法解析时间字符串:" << src;
    return QString();
}

QString ExcelReader::toPercentString(const QString &src, bool *ok)
{
   if (ok) *ok = false;

  if (src.isEmpty()) {
      qWarning() << "空字符串，无法转换";
      return QString();
  }

  bool convertOk = false;
  double value = src.toDouble(&convertOk);

  if (!convertOk || qIsNaN(value) || qIsInf(value)) {
      qWarning() << "非法数字：" << src;
      return QString();
  }

  if (ok) *ok = true;
  return QString::asprintf("%.2f%%", value * 100.0);
}

QDateTime ExcelReader::convertOleDateTime(double oleValue)
{
   const QDate baseDate(1899, 12, 30);
   const qint64 days      = static_cast<qint64>(oleValue);
   const double dayFrac   = oleValue - days;
   const int    secs      = static_cast<int>(dayFrac * 86400.0 + 0.5);

   return QDateTime(baseDate.addDays(days), QTime(0, 0).addSecs(secs));
}

QList<pickedProduct_Type> ExcelReader::parsePickedProduct(QAxObject* workbook, QProgressDialog &progress)
{
    QList<pickedProduct_Type> rows;
    QElapsedTimer timer;
    QAxObject* sheet = nullptr;
    QAxObject* usedRange = nullptr;
    const QString sheetName =  QStringLiteral("生产酸洗成品");
    timer.start();

    bool ok;
    // 4. 获取工作表
    progress.setLabelText("正在定位工作表"+sheetName +"...");
    QCoreApplication::processEvents();

    QAxObject *sheets = workbook->querySubObject("Sheets");
    if (!sheets) {
        throw ExcelReadException("无法访问Sheets集合");
    }


    sheet = sheets->querySubObject("Item(const QString&)", sheetName);
    if (!sheet) {
        throw ExcelReadException("找不到工作表: " + sheetName);
    }

    // 5. 获取已用区域
    progress.setLabelText("正在获取数据范围...");
    QCoreApplication::processEvents();

    usedRange = sheet->querySubObject("UsedRange");
    if (!usedRange) {
        throw ExcelReadException("无法获取已用区域");
    }

    QAxObject *rowsObj = usedRange->querySubObject("Rows");
    QAxObject *colsObj = usedRange->querySubObject("Columns");

    if (!rowsObj || !colsObj) {
        throw ExcelReadException("无法获取行列信息");
    }

    int rowCount = rowsObj->property("Count").toInt();
    int colCount = colsObj->property("Count").toInt();

    // 删除临时对象
    delete rowsObj;
    delete colsObj;

    qDebug() << "Excel启动耗时:" << timer.elapsed() << "ms";
    timer.restart();

    // 6. 切换到确定性进度模式
    progress.setRange(2, rowCount);
    progress.setLabelText("正在读取数据...");
    QCoreApplication::processEvents();

    // 7. 行循环读取
   for (int r = 2; r <= rowCount; ++r) {
       // 检查是否取消操作
       if (progress.wasCanceled()) {
           throw ExcelReadException("用户取消了操作");
       }

       // 更新进度
       progress.setValue(r);
       if (r % 5 == 0 || r == rowCount) { // 每5行更新一次文本，减少UI更新频率
           progress.setLabelText(QString("正在读取第 %1/%2 行... (已耗时: %3秒)")
                                .arg(r-1)
                                .arg(rowCount-1)
                                .arg(timer.elapsed()/1000.0, 0, 'f', 1));
           QCoreApplication::processEvents();
       }

       try {
           pickedProduct_Type row;
           QVariantList line;

           // 读取整行数据
           for (int c = 1; c <= colCount; ++c) {
               QAxObject *cell = usedRange->querySubObject("Cells(int,int)", r, c);
               if (!cell) {
                   throw ExcelReadException(QString("无法读取单元格(%1,%2)").arg(r).arg(c));
               }

               QVariant v = cell->property("Value");
               delete cell;
               line.append(v);
           }

           // 跳过空行或无效行
           if (line.value(0).toString().isEmpty() || !isInt(line.value(0).toString())) {
               continue;
           }

          // 填充结构体 - 添加边界检查
          if (line.size() > 0) row.picklingTankNumber = line.value(0).toString();
          if (line.size() > 1) {
              row.originalSandInjectionDate =
                      formatDateTimeToChinese(line.value(1).toString(),&ok);
          }
          if (line.size() > 2) row.proportionRawSand = line.value(2).toString();
          if (line.size() > 3) {
              row.endTimeRaw = formatTimeToMMSS(line.value(3).toString(),&ok);
          }
          if (line.size() > 4) {
              row.samplingDate = formatDateTimeToChinese(line.value(4).toString(),&ok);
          }
          if (line.size() > 5) {

              QTime t  = line.value(5).toTime();
              QString txt = t.toString("hh:mm");
              qDebug()<<txt;
              row.samplingTime = formatTimeToMMSS(line.value(5).toString(),&ok);
          }

          if (line.size() > 6) row.productionSamplingTime = line.value(6).toString();
          if (line.size() > 7) row.samplingTemperature = line.value(7).toString();
          if (line.size() > 8) {
              row.elementalAnalysisSi = QString("%1").arg(line.value(8).toDouble(), 0, 'f', 2);
          }
          if (line.size() > 9) {
              row.elementalAnalysisFe = QString("%1").arg(line.value(9).toDouble(), 0, 'f', 4);
          }

          if (line.size() > 10) {
             row.elementalAnalysisTi = QString("%1").arg(line.value(10).toDouble(), 0, 'f', 4);
          }

          if (line.size() > 11) {
              row.finishedProductDate =
                      formatDateTimeToChinese(line.value(11).toString(),&ok);
          }
          if (line.size() > 12) {
              row.finishedProductTime = formatTimeToMMSS(line.value(12).toString(),&ok);
          }

          if (line.size() > 14) {
              row.particleDetectionResults25 = toPercentString(line.value(14).toString(),&ok);
          }
          if (line.size() > 15) {
              row.particleDetectionResults140 = toPercentString(line.value(15).toString(),&ok);
          }
          if (line.size() > 16) {
              row.particleDetectionResults150 = toPercentString(line.value(16).toString(),&ok);
          }
          if (line.size() > 17) {
              row.compositionResultsSi = toPercentString(line.value(17).toString(),&ok);
          }
          if (line.size() > 18) {
              row.compositionResultsFe = toPercentString(line.value(18).toString(),&ok);
          }
          if (line.size() > 19) {
              row.compositionResultsTi = toPercentString(line.value(19).toString(),&ok);
          }
          rows.append(row);
       }
       catch (const ExcelReadException& e) {
           qWarning() << "行处理错误:" << e.what();
           // 继续处理下一行
       }
       catch (...) {
           qWarning() << "未知的行处理错误";
       }
   }

   progress.setValue(rowCount);
   progress.setLabelText(QString("%1sheet的数据读取完成! 共读取 %2 行数据 (总耗时: %3秒)")
                        .arg(sheetName)
                        .arg(rows.size())
                        .arg(timer.elapsed()/1000.0, 0, 'f', 1));

   // 8. 资源清理
   if (usedRange) delete usedRange;
   if (sheet) delete sheet;
   return rows;
}

QList<RawInspectionRow> ExcelReader::rawInspectProduct(QAxObject *workbook, QProgressDialog &progress)
{
    QList<RawInspectionRow> rows;
    QElapsedTimer timer;
    QAxObject* sheet = nullptr;
    QAxObject* usedRange = nullptr;
    const QString sheetName =  QStringLiteral("原砂入库");
    timer.start();

    bool ok;
    // 4. 获取工作表
    progress.setLabelText("正在定位工作表"+sheetName +"...");
    QCoreApplication::processEvents();

    QAxObject *sheets = workbook->querySubObject("Sheets");
    if (!sheets) {
        throw ExcelReadException("无法访问Sheets集合");
    }


    sheet = sheets->querySubObject("Item(const QString&)", sheetName);
    if (!sheet) {
        throw ExcelReadException("找不到工作表: " + sheetName);
    }

    // 5. 获取已用区域
    progress.setLabelText("正在获取数据范围...");
    QCoreApplication::processEvents();

    usedRange = sheet->querySubObject("UsedRange");
    if (!usedRange) {
        throw ExcelReadException("无法获取已用区域");
    }

    QAxObject *rowsObj = usedRange->querySubObject("Rows");
    QAxObject *colsObj = usedRange->querySubObject("Columns");

    if (!rowsObj || !colsObj) {
        throw ExcelReadException("无法获取行列信息");
    }

    int rowCount = rowsObj->property("Count").toInt();
    int colCount = colsObj->property("Count").toInt();

    // 删除临时对象
    delete rowsObj;
    delete colsObj;

    qDebug() << "Excel启动耗时:" << timer.elapsed() << "ms";
    timer.restart();

    // 6. 切换到确定性进度模式
    progress.setRange(2, rowCount);
    progress.setLabelText("正在读取数据...");
    QCoreApplication::processEvents();


   QString currentSupplier;
   QString storageTime = "";
   QString wagonNumber = "";
   QString inspectionTime = "";
   QString moistureDetectionResults = "";

   RawInspectionRow currentRow;
    // 7. 行循环读取
   for (int r = 5; r <= rowCount; ++r) {
       // 检查是否取消操作
       if (progress.wasCanceled()) {
           throw ExcelReadException("用户取消了操作");
       }

       // 更新进度
       progress.setValue(r);
       if (r % 5 == 0 || r == rowCount) { // 每5行更新一次文本，减少UI更新频率
           progress.setLabelText(QString("正在读取第 %1/%2 行... (已耗时: %3秒)")
                                .arg(r-1)
                                .arg(rowCount-1)
                                .arg(timer.elapsed()/1000.0, 0, 'f', 1));
           QCoreApplication::processEvents();
       }

       try {
           QVariantList line;

           // 读取整行数据
           for (int c = 1; c <= colCount; ++c) {
               QAxObject *cell = usedRange->querySubObject("Cells(int,int)", r, c);
               if (!cell) {
                   throw ExcelReadException(QString("无法读取单元格(%1,%2)").arg(r).arg(c));
               }

               QVariant v = cell->property("Value");
               delete cell;
               line.append(v);
           }

           // 跳过空行或无效行
           if (line.value(1).toString().isEmpty()) {
               continue;
           }

           if (line.size() <= 0) continue;

          QString rowSupplier = line.value(0).toString();
          // 填充结构体 - 添加边界检查
          if(!rowSupplier.isEmpty()){

             if (!currentSupplier.isEmpty()) {
                 rows.append(currentRow);
             }
             currentRow = RawInspectionRow();  // 重置为新行
             currentSupplier = line.value(0).toString();
             currentRow.supplier =currentSupplier;

             if (line.size() > 6){
                currentRow.particleSizeDetectionResults25 = toPercentString(line.value(6).toString(),&ok);
             }

             if (line.size() > 7){
                currentRow.particleSizeDetectionResults140 = toPercentString(line.value(7).toString(),&ok);
             }

             if (line.size() > 8){
                currentRow.rawSandSi = QString("%1").arg(line.value(8).toDouble(), 0, 'f', 2);
             }

             if (line.size() > 9){
                currentRow.rawSandFe = QString("%1").arg(line.value(9).toDouble(), 0, 'f', 4);
             }

             if (line.size() > 10){
                 currentRow.rawSandTi = QString("%1").arg(line.value(10).toDouble(), 0, 'f', 4);
             }

             if (line.size() > 11){
                 currentRow.acidWashingTestMethod = formatDateTimeToChinese(line.value(11).toString(),&ok);
             }

             if (line.size() > 12){
                currentRow.acidpicklingSi = QString("%1").arg(line.value(12).toDouble(), 0, 'f', 2);
             }

             if (line.size() > 13){
                currentRow.acidpicklingFe = QString("%1").arg(line.value(13).toDouble(), 0, 'f', 4);
             }

             if (line.size() > 14){
                currentRow.acidpicklingTi = QString("%1").arg(line.value(14).toDouble(), 0, 'f', 4);
             }

             if (line.size() > 15){
                currentRow.experimentalResult = line.value(15).toString();
             }

          }

          if (line.size() > 1) {
              if (currentRow.storageTime.isEmpty()) {
                  currentRow.storageTime = formatDateTimeToChinese(line.value(1).toString(), &ok);
                  // [初始化其他共享字段...]
              } else {
                  // 追加共享数据
                  currentRow.storageTime += "&&" + formatDateTimeToChinese(line.value(1).toString(), &ok);
              }
          }

          if (line.size() > 2){
              if (currentRow.wagonNumber.isEmpty()) {
                  currentRow.wagonNumber = line.value(2).toString();
                  // [初始化其他共享字段...]
              } else {
                  // 追加共享数据
                  currentRow.wagonNumber += "&&" + line.value(2).toString();
              }
          }

          if (line.size() > 3){
              if( currentRow.inspectionTime.isEmpty()){
                  currentRow.inspectionTime = formatDateTimeToChinese(line.value(3).toString(),&ok);
              }else{
                  currentRow.inspectionTime += "&&" + formatDateTimeToChinese(line.value(3).toString(),&ok);
              }
          }

          if (line.size() > 4){
              if( currentRow.moistureDetectionResults.isEmpty()){
                    currentRow.moistureDetectionResults = toPercentString(line.value(4).toString(),&ok);
              }else{
                    currentRow.moistureDetectionResults += "&&" + toPercentString(line.value(4).toString(),&ok);
              }
          }


       }
       catch (const ExcelReadException& e) {
           qWarning() << "行处理错误:" << e.what();
           // 继续处理下一行
       }
       catch (...) {
           qWarning() << "未知的行处理错误";
       }
   }

   // 添加最后一个供应商的行
   if (!currentSupplier.isEmpty()) {
       rows.append(currentRow);
   }

   progress.setValue(rowCount);
   progress.setLabelText(QString("%1sheet的数据读取完成! 共读取 %2 行数据 (总耗时: %3秒)")
                        .arg(sheetName)
                        .arg(rows.size())
                        .arg(timer.elapsed()/1000.0, 0, 'f', 1));

   // 8. 资源清理
   if (usedRange) delete usedRange;
   if (sheet) delete sheet;
   return rows;
}


ExcelReader::isInt(QString s)
{
    bool ok = false;
    s.toInt(&ok);
    return ok;
}
