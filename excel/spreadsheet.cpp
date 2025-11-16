#include "spreadsheet.h"
#include <QHeaderView>
#include <QFontMetrics>
#include <QBrush>
#include <QColor>

SpreadSheet::SpreadSheet()
{
    int adjustmentRatio = 5;
    RawSandlevel1Font = 18 -adjustmentRatio;
    RawSandlevel2Font  = 14 - adjustmentRatio;
    RawSandlevel3Font  = 14 - adjustmentRatio;

    PickProduclevel1Font = 18 -adjustmentRatio;
    PickProduclevel2Font  = 11 - adjustmentRatio;
    PickProduclevel3Font  = 11 - adjustmentRatio;

    RawSandHeaderHeight = 18;
    RawSandContentHeight = 16;

    PickProductHeaderHeight = 18;
    PickProductContentHeight = 22;
}

void SpreadSheet::initPickProductTable(QTableWidget *t)
{
    int currentColum = 0;
    t->clear();
    t->setRowCount(4 + 11);   // 保持4行表头
    t->setColumnCount(19);

    // 隐藏表头
    t->horizontalHeader()->setVisible(false);
    t->verticalHeader()->setVisible(false);
    t->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    t->horizontalHeader()->setStretchLastSection(true);
    // 关键设置：启用文本换行和调整策略
    t->setWordWrap(true);
//    t->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    // 设置行高 - 表头行稍高，数据行正常
    for (int i = 0; i < t->rowCount(); ++i) {
        t->setRowHeight(i, (i < 4) ? PickProductHeaderHeight : PickProductContentHeight);
        if(i == 0 ){
            t->setRowHeight(i, 30);
        }
    }

    // 优化列宽设置 - 特别调整第一列宽度
    for (int i = 0; i < t->columnCount(); i++) {
        if (i == 0) { // 第一列特殊处理
            t->setColumnWidth(i, 70); // 缩小第一列宽度
        } else if (i < 8) {
            t->setColumnWidth(i, 90);
        } else if (i >= 11 && i < 13) {
            t->setColumnWidth(i, 200);
        } else if (i >= 13 && i < 17) {
            t->setColumnWidth(i, 95);
        }else if( i == 18){

        } else {
            t->setColumnWidth(i, 400);
        }
    }

    // 网格线样式
    t->setStyleSheet(
        "QTableWidget {"
        "   gridline-color: #d0d0d0;"
        "}"
        "QTableWidget::item {"
        "   padding: 3px;"
        "}"
    );

    // ===== 恢复原始合并结构 =====
    t->setSpan(0, 0, 1, 20);
    QFont font("Noto Sans", PickProduclevel1Font); // 减小字号确保显示
    font.setHintingPreference(QFont::PreferNoHinting); // 避免中文笔画粘连

    t->setItem(0, 0, getTableWidgetItem(font, Qt::AlignCenter, "渝津硅酸洗罐生产取样、成品排砂送样-分析明细表"));

    // 第一行：一级分类
    QFont font1("Noto Sans", PickProduclevel2Font);
    font1.setHintingPreference(QFont::PreferFullHinting);  // 完整Hinting
    font1.setStyleHint(QFont::SansSerif);  // 确保使用无衬线字体

    t->setSpan(1, 0, 1, 11);
    t->setItem(1, 0, getTableWidgetItem(font1, Qt::AlignCenter, "酸洗罐生产取样"));
    t->setSpan(1, 11, 1, 9); // 修正跨度 (11+9=20)
    t->setItem(1, 11, getTableWidgetItem(font1, Qt::AlignCenter, "成品排砂送样"));

    // 第二行：二级分类
    QFont font2("Noto Sans", PickProduclevel3Font);
    font2.setHintingPreference(QFont::PreferFullHinting);  // 完整Hinting
    font2.setStyleHint(QFont::SansSerif);  // 确保使用无衬线字体

    font2.setBold(false);
    QStringList secondRowLeft = {
        "酸洗罐号", "原砂进灌日期", "原砂进罐比例", "原砂进罐结束时间",
        "取样日期", "取样时间", "累计时间(小时)", "取样时温度℃"
    };

    // 恢复原始3行合并
    for (int i = 0; i < secondRowLeft.size(); ++i) {
        t->setSpan(2, i, 3, 1); // 恢复3行合并
        t->setItem(2, i, getTableWidgetItem(font2, Qt::AlignCenter, secondRowLeft[i]));
    }

    currentColum = secondRowLeft.length();
    t->setSpan(2, currentColum, 1, 3);
    t->setItem(2, currentColum, getTableWidgetItem(font2, Qt::AlignCenter, "元素成份分析"));

    QStringList elementalComposition = {
        "硅Si", "铁Fe", "钛Ti",
        "≥99.40%", "≤110ppm", "≤0.030%"
    };

    for (int i = 0; i < 3; i++) {
        t->setItem(3, currentColum, getTableWidgetItem(font2, Qt::AlignCenter, elementalComposition[i]));
        t->setItem(4, currentColum, getTableWidgetItem(font2, Qt::AlignCenter, elementalComposition[i + 3]));
        currentColum++;
    }

    // 成品排沙送样部分 - 恢复原始合并结构
    t->setSpan(2, 11, 2, 2); // 恢复2行合并
    t->setItem(2, 11, getTableWidgetItem(font2, Qt::AlignCenter, "成品送样"));
    t->setItem(4, 11, getTableWidgetItem(font2, Qt::AlignCenter, "日期")); // 第4行
    t->setItem(4, 12, getTableWidgetItem(font2, Qt::AlignCenter, "时间")); // 第4行

    t->setSpan(2, 13, 1, 3);
    t->setItem(2, 13, getTableWidgetItem(font2, Qt::AlignCenter, "颗粒度检测结果"));

    t->setItem(3, 13, getTableWidgetItem(font2, Qt::AlignCenter, "<25目"));
    t->setItem(3, 14, getTableWidgetItem(font2, Qt::AlignCenter, ">140目"));
    t->setItem(3, 15, getTableWidgetItem(font2, Qt::AlignCenter, ">150目"));

    // 长文本处理：手动添加换行符
    t->setItem(4, 13, getTableWidgetItem(font2, Qt::AlignCenter, "1-5粒合格/标准\n(不允许有)"));
    t->setItem(4, 14, getTableWidgetItem(font2, Qt::AlignCenter, "合格标准 ≤8%"));
    t->setItem(4, 15, getTableWidgetItem(font2, Qt::AlignCenter, "合格标准 ≤5%"));

    t->setSpan(2, 16, 1, 3);
    t->setItem(2, 16, getTableWidgetItem(font2, Qt::AlignCenter, "成份分析结果"));
    t->setItem(3, 16, getTableWidgetItem(font2, Qt::AlignCenter, "硅Si"));
    t->setItem(3, 17, getTableWidgetItem(font2, Qt::AlignCenter, "铁Fe"));
    t->setItem(3, 18, getTableWidgetItem(font2, Qt::AlignCenter, "钛Ti"));
    t->setItem(4, 16, getTableWidgetItem(font2, Qt::AlignCenter, "≥99.40%"));
    t->setItem(4, 17, getTableWidgetItem(font2, Qt::AlignCenter, "≤110ppm"));
    t->setItem(4, 18, getTableWidgetItem(font2, Qt::AlignCenter, "≤0.03%"));

    // ===== 样式设置 =====
    styleAdjustment(t);

    // ===== 最终尺寸调整 =====
    // 1. 针对特殊字符列增加额外宽度
    for (int col = 0; col < t->columnCount(); col++) {
        int currentWidth = t->columnWidth(col);

        // 检查列中是否包含特殊字符
        bool hasSpecialChar = false;
        for (int row = 0; row < 5; row++) {
            if (t->item(row, col) &&
               (t->item(row, col)->text().contains("≥") ||
                t->item(row, col)->text().contains("≤"))) {
                hasSpecialChar = true;
                break;
            }
        }

        // 增加额外宽度给特殊字符
        if (hasSpecialChar) {
            t->setColumnWidth(col, currentWidth + 10);
        }
    }

    // 2. 确保第一列不会过长
    if (t->columnWidth(0) > 100) {
        t->setColumnWidth(0, 60);
    }

    // 4. 处理特定单元格的显示问题
    for (int row = 3; row < 5; row++) {
        for (int col = secondRowLeft.length(); col < secondRowLeft.length() + 3; col++) {
            if (QTableWidgetItem* it = t->item(row, col)) {
                if (it->text().contains("%") || it->text().contains("ppm")) {
                    // 为特殊内容增加额外空间
                    QFontMetrics fm(it->font());
                    int textWidth = fm.width(it->text());
                    int colWidth = t->columnWidth(col);

                    if (textWidth > colWidth - 10) {
                        t->setColumnWidth(col, colWidth + 15);
                    }
                }
            }
        }
    }

}

void SpreadSheet::initRawSandTable(QTableWidget *t)
{
    t->clear();
    t->setRowCount(4 + 25);   // 保持4行表头
    t->setColumnCount(15);

    // 隐藏表头
    t->horizontalHeader()->setVisible(false);

    t->verticalHeader()->setVisible(false);
    t->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    t->horizontalHeader()->setStretchLastSection(true);
    // 关键设置：启用文本换行和调整策略
    t->setWordWrap(true);
    t->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    // 设置行高 - 表头行稍高，数据行正常
    for (int i = 0; i < t->rowCount(); ++i) {
        t->setRowHeight(i, (i < 5) ? RawSandHeaderHeight : RawSandContentHeight);
        if( i == 0){
            t->setRowHeight(i,24);
        }
    }

    // 优化列宽设置 - 特别调整第一列宽度
    for (int i = 0; i < t->columnCount(); i++) {
        if (i == 0) { // 第一列特殊处理
            t->setColumnWidth(i, 70); // 缩小第一列宽度
        } else if (i < 8) {
            t->setColumnWidth(i, 90);
        } else if (i >= 11 && i < 13) {
            t->setColumnWidth(i, 80);
        } else if (i >= 13 && i < 17) {
            t->setColumnWidth(i, 95);
        } else {
            t->setColumnWidth(i, 85);
        }
    }

    // 网格线样式
    t->setStyleSheet(
        "QTableWidget {"
        "   gridline-color: #d0d0d0;"
        "}"
        "QTableWidget::item {"
        "   padding: 3px;"
        "}");

    // ===== 恢复原始合并结构 =====
    t->setSpan(0, 0, 1, 16);
    QFont font("Segoe UI", RawSandlevel1Font); // 减小字号确保显示
    font.setHintingPreference(QFont::PreferNoHinting); // 避免中文笔画粘连


    t->setItem(0, 0, getTableWidgetItem(font, Qt::AlignCenter, "重庆渝津硅水份、颗粒度、成份、酸洗试验分析检测明细表"));

    // 第一行：一级分类
    QFont font1("Segoe UI", RawSandlevel2Font);
    font1.setHintingPreference(QFont::PreferFullHinting);  // 完整Hinting
    font1.setStyleHint(QFont::SansSerif);  // 确保使用无衬线字体

    // 第二行：二级分类
    QFont font2("Segoe UI", RawSandlevel3Font);
    font2.setHintingPreference(QFont::PreferFullHinting);  // 完整Hinting
    font2.setStyleHint(QFont::SansSerif);  // 确保使用无衬线字体

    t->horizontalHeader()->setFont(font1);
    t->horizontalHeader()->setFixedHeight(RawSandHeaderHeight);

    t->setSpan(1, 0, 2, 4);
    t->setItem(1, 0, getTableWidgetItem(font1, Qt::AlignCenter, "原砂"));

    t->setSpan(3, 0, 2, 1);
    t->setItem(3, 0, getTableWidgetItem(font1, Qt::AlignCenter, "供应商"));

    t->setSpan(3, 1, 2, 1);
    t->setItem(3, 1, getTableWidgetItem(font1, Qt::AlignCenter, "入库时间"));

    t->setSpan(3, 2, 2, 1);
    t->setItem(3, 2, getTableWidgetItem(font1, Qt::AlignCenter, "车号"));

    t->setSpan(3, 3, 2, 1);
    t->setItem(3, 3, getTableWidgetItem(font1, Qt::AlignCenter, "检验时间"));

    t->setSpan(1, 4, 3, 1);
    t->setItem(1, 4, getTableWidgetItem(font1, Qt::AlignCenter, "水份检测结果"));
    t->setItem(4, 4, getTableWidgetItem(font1, Qt::AlignCenter, "合格标准≤5%"));

    t->setSpan(1, 5, 2, 2);
    t->setItem(1, 5, getTableWidgetItem(font1, Qt::AlignCenter, "颗粒度检测结果"));

    t->setItem(3, 5, getTableWidgetItem(font2, Qt::AlignCenter, "<25目"));
    t->setItem(3, 6, getTableWidgetItem(font2, Qt::AlignCenter, ">140目"));

    t->setItem(4, 5, getTableWidgetItem(font2, Qt::AlignCenter, "1-5粒合格/\n标准（不允许有）"));
    t->setItem(4, 6, getTableWidgetItem(font2, Qt::AlignCenter, "合格标准≤6%"));

    t->setSpan(1, 7, 2, 3);
    t->setItem(1, 7, getTableWidgetItem(font2, Qt::AlignCenter, "原砂-成份分析结果（%）"));
    t->setItem(3, 7, getTableWidgetItem(font2, Qt::AlignCenter, "硅Si"));
    t->setItem(3, 8, getTableWidgetItem(font2, Qt::AlignCenter, "铁Fe"));
    t->setItem(3, 9, getTableWidgetItem(font2, Qt::AlignCenter, "钛Ti"));
    t->setItem(4, 7, getTableWidgetItem(font2, Qt::AlignCenter, "≥99.00%"));
    t->setItem(4, 8, getTableWidgetItem(font2, Qt::AlignCenter, "≤500ppm"));
    t->setItem(4, 9, getTableWidgetItem(font2, Qt::AlignCenter, "≤0.015%"));

    t->setSpan(1, 10, 2, 1);
    t->setItem(1, 10, getTableWidgetItem(font1, Qt::AlignCenter, "酸洗试验方法"));
    t->setItem(3, 10, getTableWidgetItem(font2, Qt::AlignCenter, "1.草酸（99.60%）\n2.氢氟酸(50%)"));
    t->setItem(4, 10, getTableWidgetItem(font2, Qt::AlignCenter, "实验日期"));

    t->setSpan(1, 11, 2, 3);
    t->setItem(1, 11, getTableWidgetItem(font1, Qt::AlignCenter, "酸洗试验结果（%）"));
    t->setItem(3, 11, getTableWidgetItem(font2, Qt::AlignCenter, "硅Si"));
    t->setItem(3, 12, getTableWidgetItem(font2, Qt::AlignCenter, "铁Fe"));
    t->setItem(3, 13, getTableWidgetItem(font2, Qt::AlignCenter, "钛Ti"));
    t->setItem(4, 11, getTableWidgetItem(font2, Qt::AlignCenter, "≥99.20%"));
    t->setItem(4, 12, getTableWidgetItem(font2, Qt::AlignCenter, "≤110ppm"));
    t->setItem(4, 13, getTableWidgetItem(font2, Qt::AlignCenter, "≤0.015%"));

    t->setSpan(1, 14, 4, 1);
    t->setItem(1, 14, getTableWidgetItem(font1, Qt::AlignCenter, "实验结果"));


    t->setSpan(5, 0, 6, 1);
    t->setItem(5, 0, getTableWidgetItem(font2, Qt::AlignCenter, "衡昌骏源"));

    t->setSpan(11, 0, 6, 1);
    t->setItem(11, 0, getTableWidgetItem(font2, Qt::AlignCenter, "新源"));

    t->setSpan(17, 0, 6, 1);
    t->setItem(17, 0, getTableWidgetItem(font2, Qt::AlignCenter, "乐升"));

    t->setSpan(23, 0, 6, 1);
    t->setItem(23, 0, getTableWidgetItem(font2, Qt::AlignCenter, "黔来盛"));

    for(int i = 0; i < 4 ; i++){
        for(int j = 5 ; j < 15 ; j++){
            t->setSpan(5 + 6*i, j, 6, 1);
        }
    }

    // ===== 最终尺寸调整 =====
    // ===== 样式设置 =====
    styleAdjustment(t);

    // 2. 特殊处理长文本列
    QVector<int> longTextCols = {5, 11};
    foreach(int col, longTextCols) {
        t->resizeColumnToContents(col);
        t->setColumnWidth(col, t->columnWidth(col) + 10);
    }

    // 3. 特殊处理含特殊符号的列
    QVector<int> specialCharCols = {4, 8, 9, 10, 12, 13, 14};
    foreach(int col, specialCharCols) {
        t->resizeColumnToContents(col);
        t->setColumnWidth(col, t->columnWidth(col) + 15);
    }

    // 4. 确保第一列不会过长
    t->setColumnWidth(0, 80); // 固定第一列宽度


//    // 6. 处理酸洗试验方法单元格
//    if (QTableWidgetItem* it = t->item(3, 11)) {
//        if (it->text().contains("\n")) {
//            QFontMetrics fm(it->font());
//            QRect rect = fm.boundingRect(0, 0, t->columnWidth(11), 0,
//                          Qt::TextWordWrap, it->text());
//            if (rect.height() > t->rowHeight(3)) {
//                t->setRowHeight(3, rect.height() + 15);
//            }
//        }
//    }

    QHeaderView *header = t->horizontalHeader();
    for (int i = 0; i < header->count(); ++i) {
        header->setSectionResizeMode(i, QHeaderView::Stretch);
    }
}

QTableWidgetItem *SpreadSheet::getTableWidgetItem(QFont font, int alignment, QString content)
{
    QTableWidgetItem *item = new QTableWidgetItem(content);
    item->setFont(font);
    item->setTextAlignment(alignment);
    return item;
}

QTableWidgetItem *SpreadSheet::createCenteredItem(QString name)
{
    QTableWidgetItem *item = new QTableWidgetItem(name);
    QFont font1("宋体", RawSandlevel2Font);
    font1.setHintingPreference(QFont::PreferFullHinting);  // 完整Hinting
    font1.setStyleHint(QFont::SansSerif);  // 确保使用无衬线字体
    item->setTextAlignment(Qt::AlignCenter);
    item->setFont(font1);
    return item;
}

void SpreadSheet::styleAdjustment(QTableWidget *t)
{
    for (int row = 0; row < t->rowCount(); ++row) {
        for (int col = 0; col < t->columnCount(); ++col) {
            QTableWidgetItem *it = t->item(row, col);
            if (!it) {
                it = new QTableWidgetItem();
                it->setTextAlignment(Qt::AlignCenter | Qt::TextWordWrap);
                t->setItem(row, col, it);
            }

            // 特殊字符处理
            QString text = it->text();
            text.replace("&gt;", ">").replace("&lt;", "<");
            it->setText(text);

            // 表头样式（前4行）
            if (row < 5) {
                QFont f = it->font();
                f.setBold(true);
                it->setFont(f);
                it->setBackground(QBrush(QColor(240, 240, 240)));
            }
            // 数据行样式
            else {
                it->setBackground(QBrush(Qt::white));
            }

            it->setFlags(it->flags() ^ Qt::ItemIsEditable);
        }
    }
}

void SpreadSheet::fillMultiplePickedProducts(QTableWidget *t, const QList<pickedProduct_Type> &products)
{
    // 清除旧数据行（保留表头）
    for (int row = 5; row < t->rowCount(); ++row) {
        for (int col = 0; col < t->columnCount(); ++col) {
            if (QTableWidgetItem* item = t->item(row, col)) {
                item->setText(""); // 清空内容但保留样式
            }
        }
    }

    // 添加新数据行
    for (int i = 0; i < products.size(); i++) {
        int dataRow = 5 + i;

        // 确保有足够的行
        if (dataRow >= t->rowCount()) {
            t->setRowCount(dataRow + 1);
        }

        // 填充数据
        const pickedProduct_Type& product = products[i];
        // 创建居中显示的函数
        auto createCenteredItem = [](const QString& text) -> QTableWidgetItem* {
            QTableWidgetItem *item = new QTableWidgetItem(text);
//            QFont font2("Noto Sans");
//            font2.setHintingPreference(QFont::PreferFullHinting);  // 完整Hinting
//            font2.setStyleHint(QFont::SansSerif);  // 确保使用无衬线字体
//            item->setFont(font2);
            item->setTextAlignment(Qt::AlignCenter);
            return item;
        };

        // 填充酸洗罐生产取样数据
        t->setItem(dataRow, 0, createCenteredItem(product.picklingTankNumber));
        t->setItem(dataRow, 1, createCenteredItem(product.originalSandInjectionDate));
        t->setItem(dataRow, 2, createCenteredItem(product.proportionRawSand));
        t->setItem(dataRow, 3, createCenteredItem(product.endTimeRaw));
        t->setItem(dataRow, 4, createCenteredItem(product.samplingDate));
        t->setItem(dataRow, 5, createCenteredItem(product.samplingTime));
        t->setItem(dataRow, 6, createCenteredItem(product.productionSamplingTime));
        t->setItem(dataRow, 7, createCenteredItem(product.samplingTemperature));

        // 填充元素成份分析数据
        t->setItem(dataRow, 8, createCenteredItem(product.elementalAnalysisSi));
        t->setItem(dataRow, 9, createCenteredItem(product.elementalAnalysisFe));
        t->setItem(dataRow, 10, createCenteredItem(product.elementalAnalysisTi));

        // 填充成品送样数据
        t->setItem(dataRow, 11, createCenteredItem(product.finishedProductDate));
        t->setItem(dataRow, 12, createCenteredItem(product.finishedProductTime));

        // 填充颗粒度检测结果
        t->setItem(dataRow, 13, createCenteredItem(product.particleDetectionResults25));
        t->setItem(dataRow, 14, createCenteredItem(product.particleDetectionResults140));
        t->setItem(dataRow, 15, createCenteredItem(product.particleDetectionResults150));

        // 填充成份分析结果
        t->setItem(dataRow, 16, createCenteredItem(product.compositionResultsSi));
        t->setItem(dataRow, 17, createCenteredItem(product.compositionResultsFe));
        t->setItem(dataRow, 18, createCenteredItem(product.compositionResultsTi));
    }

    // 自动调整列宽
    for (int col = 0; col < t->columnCount(); col++) {
        t->resizeColumnToContents(col);

        // 特殊列宽限制
        if (col == 0 && t->columnWidth(0) > 200) {
            t->setColumnWidth(0,80);
        } else if (col == 1
             || col == 2
             || col == 4
             || col == 11) {
            t->setColumnWidth(col,150);
        }
    }
}

void SpreadSheet::fillRawInspectProducts(QTableWidget *t, const QList<RawInspectionRow> &products)
{

    // 清除旧数据行（保留表头）
    for (int row = 5; row < t->rowCount(); ++row) {
        for (int col = 0; col < t->columnCount(); ++col) {
            if (QTableWidgetItem* item = t->item(row, col)) {
                item->setText(""); // 清空内容但保留样式
            }
        }
    }


    // 添加新数据行
    for (int i = 0; i < products.size(); i++) {
        int dataRow = 5 + i*6;

        // 确保有足够的行
        if (dataRow >= t->rowCount()) {
            t->setRowCount(dataRow + 1);
        }

        // 填充数据
        const RawInspectionRow& product = products[i];

        // 创建居中显示的函数
//        auto createCenteredItem = [](const QString& text) -> QTableWidgetItem* {
//            QTableWidgetItem *item = new QTableWidgetItem(text);
//            QFont font1("宋体", leve2Font, QFont::Normal);
//            item->setTextAlignment(Qt::AlignCenter);
//            item->setFont(font1);
//            return item;
//        };

        int currentRow = dataRow;
        //供应商
        t->setItem(currentRow, 0, createCenteredItem(product.supplier));

        //入库时间
        QStringList storageTimeList =  product.storageTime.split("&&");
        for(int i =0;i < storageTimeList.size() ; i++){
            t->setItem(currentRow + i, 1,
                       createCenteredItem(storageTimeList.at(i)));
        }

        //车号
        QStringList wagonNumberList =  product.wagonNumber.split("&&");
        for(int i =0;i < wagonNumberList.size() ; i++){
            t->setItem(currentRow + i, 2,
                       createCenteredItem(wagonNumberList.at(i)));
        }

        //检验时间
        QStringList inspectionTimeList =  product.inspectionTime.split("&&");
        for(int i =0;i < inspectionTimeList.size() ; i++){
            t->setItem(currentRow + i, 3,
                       createCenteredItem(inspectionTimeList.at(i)));
        }

        //水分检测结果
        QStringList moistureDetectionResultsList =  product.moistureDetectionResults.split("&&");
        for(int i =0;i < moistureDetectionResultsList.size() ; i++){
            t->setItem(currentRow + i, 4,
                       createCenteredItem(moistureDetectionResultsList.at(i)));
        }

        //颗粒检测结果
        t->setItem(currentRow, 5,
                   createCenteredItem(product.particleSizeDetectionResults25));
        t->setItem(currentRow, 6,
                   createCenteredItem(product.particleSizeDetectionResults140));

        //原纱-成分分析结果
        t->setItem(currentRow, 7,
                   createCenteredItem(product.rawSandSi));
        t->setItem(currentRow, 8,
                   createCenteredItem(product.rawSandFe));
        t->setItem(currentRow, 9,
                   createCenteredItem(product.rawSandTi));

        //酸洗实验方法
        t->setItem(currentRow, 10,
                   createCenteredItem(product.acidWashingTestMethod));

        //酸洗实验结果
        t->setItem(currentRow, 11,
                   createCenteredItem(product.acidpicklingSi));
        t->setItem(currentRow, 12,
                   createCenteredItem(product.acidpicklingFe));
        t->setItem(currentRow, 13,
                   createCenteredItem(product.acidpicklingTi));

        //实验结果
        t->setItem(currentRow, 14,
                   createCenteredItem(product.experimentalResult));
    }

    // 自动调整列宽
    for (int col = 0; col < t->columnCount(); col++) {
        t->resizeColumnToContents(col);

        // 特殊列宽限制
        if (col == 0 && t->columnWidth(0) > 200) {
            t->setColumnWidth(0,120);
        }
    }
}
