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

private:
    // 辅助函数
    QTableWidgetItem *getTableWidgetItem(QFont font, int alignment, QString content);
    QTableWidgetItem *createCenteredItem(QString name);
    void styleAdjustment(QTableWidget *t);

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

};

#endif // SPREADSHEET_H
