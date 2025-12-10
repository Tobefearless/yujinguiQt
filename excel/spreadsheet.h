#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QObject>
#include "value_type.h"
#include <QTableWidget>
class SpreadSheet
{
public:
    SpreadSheet();

    // 初始化表头
   void initPickProductTable(QTableWidget *t);
   void initRawSandTable(QTableWidget *t);

   // 填充数据
   void fillMultiplePickedProducts(QTableWidget *t, const QList<pickedProduct_Type> &products);
   void fillRawInspectProducts(QTableWidget *t, const QList<RawInspectionRow> &products);

   // 表头初始化
   void initWeighRecordTable(QTableWidget *t);
   // 数据刷新
   void fillWeighRecordTable(QTableWidget *t,
                             const QList<WeighRecordViewType> &records);

   QString convertSamplingDateToString(const QString &originalDateStr,
                                       const QString &inputFormat = "yyyy年M月d日",
                                       const QString &outputFormat = "M月d日");


private:
    // 辅助函数
    QTableWidgetItem *getTableWidgetItem(QFont font, int alignment, QString content);
    QTableWidgetItem *createCenteredItem(QString name);
    void styleAdjustment(QTableWidget *t);

    // 智能调整列宽的函数
    void adjustColumnWidths(QTableWidget *t);

    QString formatByString(const QString &str);

    int RawSandlevel1Font;
    int RawSandlevel2Font;
    int RawSandlevel3Font;

    int PickProduclevel1Font;
    int PickProduclevel2Font;
    int PickProduclevel3Font;

    int RawSandHeaderHeight;
    int RawSandContentHeight;

    int PickProductHeaderHeight;
    int PickProductContentHeight;


    int strench;
};

#endif // SPREADSHEET_H
