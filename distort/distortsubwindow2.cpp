#include "distortsubwindow2.h"
#include "ui_distortsubwindow2.h"
#include <QThread>
#include <QTimer>
DistortsubWindow2::DistortsubWindow2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DistortsubWindow2)
{
    ui->setupUi(this);

    myT = new DatabaseWorker();
    thread = new QThread(this);
    myT->moveToThread(thread);


    m_keepAliveTimer = new QTimer(this);
    spreadsheet.initPickProductTable(ui->tableWidget_Pickling);
    spreadsheet.initRawSandTable(ui->tableWidget_RowSand);

    connect(myT,SIGNAL(RawInspectcdataReady(QList<RawInspectionRow>)),
            this,SLOT(updateRawInspectTable(QList<RawInspectionRow>)),
            Qt::QueuedConnection);

    connect(myT,SIGNAL(pickedProducdataReady(QList<pickedProduct_Type>)),
            this,SLOT(updatePickedProductTable(QList<pickedProduct_Type>)),
            Qt::QueuedConnection);


    connect(this,&DistortsubWindow2::startThread,myT,&DatabaseWorker::fetchLatestPickedProductData);//启动线程

    connect(m_keepAliveTimer,SIGNAL(timeout()),this,SLOT(startKeepAlive()));
    thread->start();
    m_keepAliveTimer->start(1000 * 10);
    emit startThread();
//    setWindowFlags(Qt::FramelessWindowHint);   // 去掉系统边框
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);

}

DistortsubWindow2::~DistortsubWindow2()
{
    delete ui;
}

void DistortsubWindow2::configureTableView(QTableView *tableView)
{
    // 1. 设置表头行为：让列自动拉伸填充可用空间
       tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

       // 2. 可选：设置列之间的最小间隔（防止列太窄）
       tableView->horizontalHeader()->setMinimumSectionSize(50);

       // 3. 设置垂直表头为可调整大小
       tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);

       // 4. 设置表格大小策略：水平扩展
       tableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

       // 5. 设置表格填充整个可用空间
       tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

       // 6. 可选：设置交替行颜色，提高可读性
       tableView->setAlternatingRowColors(true);

       // 7. 可选：启用排序
       tableView->setSortingEnabled(true);

       // 8. 可选：设置选择行为
       tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
       tableView->setSelectionMode(QAbstractItemView::SingleSelection);

       // 9. 强制更新布局（确保计算正确的尺寸）
       tableView->resizeColumnsToContents();
       tableView->resizeRowsToContents();

       // 10. 设置等比缩放（如果父布局支持）
       QHeaderView *header = tableView->horizontalHeader();
       for (int i = 0; i < header->count(); ++i) {
           header->setSectionResizeMode(i, QHeaderView::Stretch);
       }
}

void DistortsubWindow2::updatePickedProductTable(const QList<pickedProduct_Type> &products)
{
    spreadsheet.fillMultiplePickedProducts(ui->tableWidget_Pickling,products);
}

void DistortsubWindow2::updateRawInspectTable(const QList<RawInspectionRow> &products)
{
    spreadsheet.fillRawInspectProducts(ui->tableWidget_RowSand,products);
}

void DistortsubWindow2::startKeepAlive()
{
    currentPage = (currentPage+1) %3;
    ui->stackedWidget->setCurrentIndex(currentPage);


    if( !MySQLDatabase::instance()->toDB()){
        MySQLDatabase::instance()->open("QMainWindow");
    }

//    sql server数据库测试
    if( sqlServerHandler.isConnected()){
        QVector<WeightRecord_Type> weightRecords = sqlServerHandler.getAllWeighRecords();
            ui->tableView_weighbridge->setModel(sqlServerHandler.getQueryModel(""));

            configureTableView(ui->tableView_weighbridge);
    }else{
        sqlServerHandler.connectToDatabase();
    }
}
