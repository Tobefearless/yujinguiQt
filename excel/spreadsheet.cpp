#include "spreadsheet.h"
#include <QHeaderView>
#include <QFontMetrics>
#include <QBrush>
#include <QColor>
#include <QDebug>

SpreadSheet::SpreadSheet()
{
    int adjustmentRatio = 0;

    RawSandlevel1Font = 32 -adjustmentRatio;
    RawSandlevel2Font  = 24 - adjustmentRatio;
    RawSandlevel3Font  = 20 - adjustmentRatio;

    PickProduclevel1Font = 42 -adjustmentRatio;
    PickProduclevel2Font  = 26 -adjustmentRatio;
    PickProduclevel3Font  = 32 -adjustmentRatio;

    RawSandHeaderHeight = 30;
    RawSandContentHeight = 28;

    PickProductHeaderHeight = 50;
    PickProductContentHeight = 40;

    strench = 75;
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
        if(i == 4 ){
            t->setRowHeight(i, PickProductHeaderHeight + 25);
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
    QFont font("Noto Sans"); // 减小字号确保显示
    font.setPixelSize(PickProduclevel1Font);
    font.setHintingPreference(QFont::PreferFullHinting);  // 完整Hinting
    font.setStyleHint(QFont::SansSerif);  // 确保使用无衬线字体
    font.setStretch(strench);


    t->setItem(0, 0, getTableWidgetItem(font, Qt::AlignCenter, "渝津硅酸洗罐生产取样、成品排砂送样-分析明细表"));

    // 第一行：一级分类
    QFont font1("Noto Sans");
    font1.setPixelSize(PickProduclevel2Font);
    font1.setHintingPreference(QFont::PreferFullHinting);  // 完整Hinting
    font1.setStyleHint(QFont::SansSerif);  // 确保使用无衬线字体
    font1.setStretch(strench);

    t->setSpan(1, 0, 1, 11);
    t->setItem(1, 0, getTableWidgetItem(font1, Qt::AlignCenter, "酸洗罐生产取样"));
    t->setSpan(1, 11, 1, 9); // 修正跨度 (11+9=20)
    t->setItem(1, 11, getTableWidgetItem(font1, Qt::AlignCenter, "成品排砂送样"));

    // 第二行：二级分类
    QFont font2("Noto Sans");
    font2.setPixelSize(PickProduclevel2Font);
    font2.setHintingPreference(QFont::PreferFullHinting);  // 完整Hinting
    font2.setStyleHint(QFont::SansSerif);  // 确保使用无衬线字体
    font2.setStretch(strench);

    font2.setBold(false);
    QStringList secondRowLeft = {
        "酸洗\n罐号", "原砂进灌日期", "原砂进罐比例", "原砂进罐结束时间",
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
    t->setItem(4, 13, getTableWidgetItem(font2, Qt::AlignCenter, "1-10粒合格/标准\n(不允许有)"));
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
    t->setRowCount(4 + 20);   // 保持4行表头
    t->setColumnCount(15);

    // 隐藏表头
    t->horizontalHeader()->setVisible(false);

    t->verticalHeader()->setVisible(false);
    t->horizontalHeader()->setStretchLastSection(true);
    // 关键设置：启用文本换行和调整策略
    t->setWordWrap(true);


    // 设置行高 - 表头行稍高，数据行正常
    for (int i = 0; i < t->rowCount(); ++i) {
        t->setRowHeight(i, (i < 5) ? RawSandHeaderHeight : RawSandContentHeight);
        if( i == 0){
            t->setRowHeight(i,32);
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
    QFont font("Segoe UI"); // 减小字号确保显示
    font.setPixelSize(RawSandlevel1Font);
    font.setHintingPreference(QFont::PreferNoHinting); // 避免中文笔画粘连
    font.setStretch(strench);


    t->setItem(0, 0, getTableWidgetItem(font, Qt::AlignCenter, "重庆渝津硅水分、颗粒度、成份、酸洗试验分析检测明细表"));

    // 第一行：一级分类
    QFont font1("Segoe UI");
    font1.setPixelSize(RawSandlevel2Font);
    font1.setHintingPreference(QFont::PreferFullHinting);  // 完整Hinting
    font1.setStyleHint(QFont::SansSerif);  // 确保使用无衬线字体
    font1.setStretch(strench);


    // 第二行：二级分类
    QFont font2("Segoe UI");
    font2.setPixelSize(RawSandlevel3Font);
    font2.setHintingPreference(QFont::PreferFullHinting);  // 完整Hinting
    font2.setStyleHint(QFont::SansSerif);  // 确保使用无衬线字体
    font2.setStretch(strench);

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

    t->setItem(4, 5, getTableWidgetItem(font2, Qt::AlignCenter, "1-10粒合格/\n标准(不允许有)"));
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

    int spanRow = 5;

    t->setSpan(5, 0, spanRow, 1);
    t->setItem(5, 0, getTableWidgetItem(font2, Qt::AlignCenter, "衡昌骏源"));

    t->setSpan(10, 0, spanRow, 1);
    t->setItem(10, 0, getTableWidgetItem(font2, Qt::AlignCenter, "新源"));

    t->setSpan(15, 0, spanRow, 1);
    t->setItem(15, 0, getTableWidgetItem(font2, Qt::AlignCenter, "乐升"));

    t->setSpan(20, 0, spanRow, 1);
    t->setItem(20, 0, getTableWidgetItem(font2, Qt::AlignCenter, "黔来盛"));

    for(int i = 0; i < 4 ; i++){
        for(int j = 5 ; j < 15 ; j++){
            t->setSpan(5 + spanRow*i, j, spanRow, 1);
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

//    QHeaderView *header = t->horizontalHeader();
//    for (int i = 0; i < header->count(); ++i) {
//        header->setSectionResizeMode(i, QHeaderView::Stretch);
//    }
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
    QFont font1("Noto Sans");
    font1.setPixelSize(32);
//    font1.setHintingPreference(QFont::PreferFullHinting);  // 完整Hinting
//    font1.setStyleHint(QFont::SansSerif);  // 确保使用无衬线字体
    font1.setStretch(strench);
    item->setFont(font1);
    item->setTextAlignment(Qt::AlignCenter);
    // 添加这一行来设置背景颜色为白色
    item->setBackground(QColor(Qt::white));
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

void SpreadSheet::adjustColumnWidths(QTableWidget *t)
{
    // 计算可用总宽度
        int totalWidth = t->viewport()->width();
        if (totalWidth <= 0) return;

        // 定义各列的权重（根据内容重要性分配）
        QVector<double> columnWeights = {
            0.07,  // 流水号
            0.08,  // 车牌号
            0.03,  // 司机
            0.05,  // 业务类型
            0.10,  // 客户名称
            0.10,  // 供应商
            0.10,  // 产品名称（最重要）
            0.05,  // 毛重
            0.05,  // 皮重
            0.05,  // 扣重
            0.05,  // 净重
            0.06,  // 称重时间
            0.10,  // 发货单位
            0.11   // 收货单位
        };

        // 应用权重分配宽度
        for (int i = 0; i < t->columnCount() && i < columnWeights.size(); ++i) {
            int width = totalWidth * columnWeights[i];
            t->setColumnWidth(i, width);
        }
}

QString SpreadSheet::formatByString(const QString &str)
{
    if (!str.contains('.')) return str + ".0";
      QStringList parts = str.split('.');
      if (parts.size() < 2) return str + ".0";
      QString decimal = parts[1].left(1); // 取第一位小数
      return parts[0] + "." + decimal;
}

// 把 "xx:xx" 转成 QTime，再格式化成 "hh:mm" 返回
QString SpreadSheet::toHHmm(const QString &hmStr)
{
    // 用 "h:m" 解析，允许 1~2 位数字
   QTime t = QTime::fromString(hmStr, "h:m");
   if (!t.isValid())            // 解析失败返回空串，可按需改抛异常
       return QString();

   return t.toString("hh:mm");  // 保证输出两位小时、两位分钟
}

void SpreadSheet::fillMultiplePickedProducts(QTableWidget *t, const QList<pickedProduct_Type> &products)
{
    int headerRow = 5;

    // 清除旧数据行（保留表头）
    for (int row = headerRow; row < t->rowCount(); ++row) {
        // 隐藏前n行，然后调整列宽

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
        auto createCenteredItem = [this](const QString& text) -> QTableWidgetItem* {
            QTableWidgetItem *item = new QTableWidgetItem(text);
            QFont font2("Noto Sans");
//            font2.setHintingPreference(QFont::PreferFullHinting);  // 完整Hinting
            font2.setPixelSize(PickProduclevel3Font);
//            font2.setStyleHint(QFont::SansSerif);  // 确保使用无衬线字体
            font2.setStretch(strench);
            item->setFont(font2);

            item->setBackground(QColor(Qt::white));
            item->setTextAlignment(Qt::AlignCenter);
            return item;
        };

        // 填充酸洗罐生产取样数据
        t->setItem(dataRow, 0, createCenteredItem(product.picklingTankNumber));
        t->setItem(dataRow, 1, createCenteredItem(product.originalSandInjectionDate));
        t->setItem(dataRow, 2, createCenteredItem(product.proportionRawSand));
        t->setItem(dataRow, 3, createCenteredItem(toHHmm(product.endTimeRaw)));


        t->setItem(dataRow, 4, createCenteredItem(convertSamplingDateToString(product.samplingDate)));

        t->setItem(dataRow, 5, createCenteredItem(toHHmm(product.samplingTime)));
        t->setItem(dataRow, 6, createCenteredItem(product.productionSamplingTime));
        t->setItem(dataRow, 7, createCenteredItem(product.samplingTemperature));

        // 填充元素成份分析数据
        t->setItem(dataRow, 8, createCenteredItem(product.elementalAnalysisSi));
        t->setItem(dataRow, 9, createCenteredItem(formatByString(product.elementalAnalysisFe)));
        t->setItem(dataRow, 10, createCenteredItem(formatByString(product.elementalAnalysisTi)));

        // 填充成品送样数据
        t->setItem(dataRow, 11, createCenteredItem(convertSamplingDateToString(product.finishedProductDate)));
        t->setItem(dataRow, 12, createCenteredItem(toHHmm(product.finishedProductTime)));

        // 填充颗粒度检测结果
        t->setItem(dataRow, 13, createCenteredItem(product.particleDetectionResults25));
        t->setItem(dataRow, 14, createCenteredItem(product.particleDetectionResults140));
        t->setItem(dataRow, 15, createCenteredItem(product.particleDetectionResults150));

        // 填充成份分析结果
        t->setItem(dataRow, 16, createCenteredItem(product.compositionResultsSi));
        t->setItem(dataRow, 17, createCenteredItem(product.compositionResultsFe));
        t->setItem(dataRow, 18, createCenteredItem(product.compositionResultsTi));
    }

    for(int i  = 0 ; i < headerRow;i++){
        t->hideRow(i);
    }
    // 自动调整列宽
    for (int col = 0; col < t->columnCount(); col++) {
        t->resizeColumnToContents(col);

        if( col == 3 && t->columnWidth(col) < 62){
            t->setColumnWidth(col,62);
        }

        else if( col == 6 && t->columnWidth(col) < 60){
            t->setColumnWidth(col,60);
        }

        else if( col == 7 && t->columnWidth(col) < 50){
            t->setColumnWidth(col,50);
        }

        else if( (col == 8 || col == 9 || col == 10) && t->columnWidth(col) < 100){
            t->setColumnWidth(col,100);
        }

        else if( col == 13 && t->columnWidth(col) < 135){
            t->setColumnWidth(col,135);
        }

        else if( col == 14 && t->columnWidth(col) < 85){
            t->setColumnWidth(col,85);
        }

        else if( col == 15 && t->columnWidth(col) < 85){
            t->setColumnWidth(col,85);
        }

        else if( (col == 16 || col == 17)&& t->columnWidth(col) < 100){
            t->setColumnWidth(col,100);
        }

    }

    for(int i  = 0 ; i < headerRow;i++){
        t->showRow(i);
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
        int dataRow = 5 + i*5;

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
        for(int i =0;i < storageTimeList.size() && i <5; i++){
            t->setItem(currentRow + i, 1,
                       createCenteredItem(storageTimeList.at(i)));
        }

        //车号
        QStringList wagonNumberList =  product.wagonNumber.split("&&");
        for(int i =0;i < wagonNumberList.size() && i <5; i++){
            t->setItem(currentRow + i, 2,
                       createCenteredItem(wagonNumberList.at(i)));
        }

        //检验时间
        QStringList inspectionTimeList =  product.inspectionTime.split("&&");
        for(int i =0;i < inspectionTimeList.size() && i <5; i++){
            t->setItem(currentRow + i, 3,
                       createCenteredItem(inspectionTimeList.at(i)));
        }

        //水分检测结果
        QStringList moistureDetectionResultsList =  product.moistureDetectionResults.split("&&");
        for(int i =0;i < moistureDetectionResultsList.size() && i <5; i++){
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

    int headerRow = 5;
    for(int i  = 0 ; i < headerRow;i++){
        t->hideRow(i);
    }
    // 自动调整列宽
    for (int col = 0; col < t->columnCount(); col++) {
        t->resizeColumnToContents(col);

        //t->columnWidth(col) < 62
//        qDebug()<< "col:" << col << " width:"<<t->columnWidth(col);
        if( col == 4  && t->columnWidth(col) < 150){
             t->setColumnWidth(col,150);
        }
        else if( col == 5  && t->columnWidth(col) < 200){
            t->setColumnWidth(col,200);
        }
        else if( col == 6  && t->columnWidth(col) < 120){
            t->setColumnWidth(col,120);
        }
        else if( (col == 7 || col == 8  || col == 9) && t->columnWidth(col) < 90){
            t->setColumnWidth(col,90);
        }
        else if( (col == 10)  && t->columnWidth(col) < 250){
            t->setColumnWidth(col,250);
        }
        else if( (col == 11 || col == 12  || col == 13) ){
            t->setColumnWidth(col,90);
        }
    }

    for(int i  = 0 ; i < headerRow;i++){
        t->showRow(i);
    }
}

void SpreadSheet::initWeighRecordTable(QTableWidget *t)
{

        QStringList headers = {
            "流水号", "车牌号", "业务类型",
            "客户名称", "供应商", "产品名称",
            "毛重", "皮重",  "净重",
            "称重时间", "发货单位", "收货单位"
        };

       t->clear();
       t->setRowCount(1);  // 表头1行
       t->setColumnCount(headers.length());

       // 隐藏默认表头
       t->horizontalHeader()->setVisible(false);
       t->verticalHeader()->setVisible(false);

       // 关键：设置列宽适应策略
//       t->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
       t->horizontalHeader()->setStretchLastSection(true);
       // 设置字体和行高
       QFont headerFont("Noto Sans");
       headerFont.setPixelSize(26);
       headerFont.setBold(true);

//       QStringList headers = {
//           "流水号", "车牌号", "司机", "业务类型",
//           "客户名称", "供应商", "产品名称",
//           "毛重", "皮重", "扣重", "净重",
//           "称重时间", "发货单位", "收货单位"
//       };



       // 填充表头
       for (int i = 0; i < headers.size(); ++i) {
           QTableWidgetItem *headerItem = new QTableWidgetItem(headers[i]);
           headerItem->setFont(headerFont);
           headerItem->setTextAlignment(Qt::AlignCenter);
           headerItem->setBackground(QColor(220, 230, 240));  // 浅蓝色背景
           t->setItem(0, i, headerItem);
       }

       // 设置行高和样式
       t->setRowHeight(0, 40);  // 表头稍高
       t->setAlternatingRowColors(true);  // 交替行颜色

       t->setStyleSheet(
           "QTableWidget {"
           "   gridline-color: #c0c0c0;"
           "   background-color: white;"
           "}"
           "QTableWidget::item {"
           "   padding: 4px;"
           "   border: 1px solid #d0d0d0;"
           "}"
           "QTableWidget::item:selected {"
           "   background-color: #e0f0ff;"
           "}"
       );
}

void SpreadSheet::fillWeighRecordTable(QTableWidget *t, const QList<WeighRecordViewType> &records)
{
    // 设置总行数：表头 + 数据
      int totalRows = 1 + records.size();
      t->setRowCount(totalRows);

      // 填充数据
      for (int i = 0; i < records.size(); i++) {
          int row = 1 + i;
          const WeighRecordViewType& record = records[i];

          // 创建数据项
          auto createDataItem = [this](const QString& text, bool isNumber = false) -> QTableWidgetItem* {
              QTableWidgetItem *item = new QTableWidgetItem(text);
              QFont dataFont("Noto Sans");
              dataFont.setPixelSize(26);
//              dataFont.setBold(true);
              dataFont.setStretch(strench);
              item->setFont(dataFont);

              if (isNumber) {
                  item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
              } else {
                  item->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
              }

              item->setBackground(QColor(Qt::white));
              item->setFlags(item->flags() ^ Qt::ItemIsEditable);
              return item;
          };

          // 填充所有列
          t->setItem(row, 0, createDataItem(record.RunningNum));
          t->setItem(row, 1, createDataItem(record.Licenseplate));
//          t->setItem(row, 2, createDataItem(record.Driver));
          t->setItem(row, 2, createDataItem(record.BusinessType));
          t->setItem(row, 3, createDataItem(record.CustomerName));
          t->setItem(row, 4, createDataItem(record.SupplierName));
          t->setItem(row, 5, createDataItem(record.ProductName));
          t->setItem(row, 6, createDataItem(QString::number(record.TotalWeight, 'f', 2), true));
          t->setItem(row, 7, createDataItem(QString::number(record.Tare, 'f', 2), true));
//          t->setItem(row, 8, createDataItem(QString::number(record.Buckle, 'f', 1), true));
          t->setItem(row, 8, createDataItem(QString::number(record.NeatWeight, 'f', 2), true));
          t->setItem(row, 9, createDataItem(record.WeighTime.toString("hh:mm"))); // 简化时间显示
          t->setItem(row, 10, createDataItem(record.SendcorpName));
          t->setItem(row, 11, createDataItem(record.RecvcorpName));

          // 设置数据行高
          t->setRowHeight(row, 60);
      }

      // 关键：调整列宽策略，确保填满空间
//      adjustColumnWidths(t);
      int headerRow = 1;
      for(int i  = 0 ; i < headerRow;i++){
          t->hideRow(i);
      }
      // 自动调整列宽
      for (int col = 0; col < t->columnCount(); col++) {
          t->resizeColumnToContents(col);

          //t->columnWidth(col) < 62
          qDebug()<< "col:" << col << " width:"<<t->columnWidth(col);
          if( col == 1  && t->columnWidth(col) < 110){
               t->setColumnWidth(col,110);
          }
//          else if( col == 2  && t->columnWidth(col) < 80){
//               t->setColumnWidth(col,80);
//          }

          else if( col == 2  && t->columnWidth(col) < 135){
               t->setColumnWidth(col,150);
          }

//          else if( col == 8  && t->columnWidth(col) < 80){
//               t->setColumnWidth(col,80);
//          }

          else if( col == 9  && t->columnWidth(col) < 135){
               t->setColumnWidth(col,140);
          }
      }

      for(int i  = 0 ; i < headerRow;i++){
          t->showRow(i);
      }
}

QString SpreadSheet::convertSamplingDateToString(const QString &originalDateStr, const QString &inputFormat, const QString &outputFormat)
{
       // 1. 空值校验：原始字符串为空时直接返回空
      if (originalDateStr.isEmpty()) {
          return "";
      }

      // 2. 将原始字符串转换为QDate对象
      QDate samplingDate = QDate::fromString(originalDateStr, inputFormat);

      // 3. 转换有效则返回指定格式，无效则返回原字符串
      if (samplingDate.isValid()) {
          return samplingDate.toString(outputFormat);
      } else {
          return originalDateStr;
      }
}

QString toHHmm(const QString &hmStr)
{
    // 用 "h:m" 解析，允许 1~2 位数字
    QTime t = QTime::fromString(hmStr, "h:m");
    if (!t.isValid())            // 解析失败返回空串，可按需改抛异常
        return QString();

    return t.toString("hh:mm");  // 保证输出两位小时、两位分钟
}


