#ifndef EXCELREADER_H
#define EXCELREADER_H

#include "value_type.h"
#include <QList>
#include <QString>
#include <QAxObject>
#include <QProgressDialog>
class ExcelReader
{
public:
    ExcelReader();
    // 唯一对外接口：传入文件路径即可拿到全部 SampleRow
    static void loadSampleRows(const QString &filePath,
                               QList<pickedProduct_Type> &pickedProductList,
                               QList<RawInspectionRow> &rawInspectProductList);
    static QString formatDateTimeToChinese(const QString& isoStr, bool* ok = nullptr);

    static QString formatTimeToMMSS(const QString& src, bool* ok = nullptr);

    static QString toPercentString(const QString& src, bool* ok = nullptr);

    static QDateTime convertOleDateTime(double oleValue);

    static QList<pickedProduct_Type> parsePickedProduct(QAxObject* workbook,QProgressDialog &progress);
    static QList<RawInspectionRow> rawInspectProduct(QAxObject* workbook,QProgressDialog &progress);

private:
    static isInt(QString s);
};



#endif // EXCELREADER_H
