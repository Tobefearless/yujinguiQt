#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "excel/spreadsheet.h"
#include "dataBase/mysqldatabase.h"
#include "dataBase/sqlserverhandler.h"
#include "thread/databaseworker.h"
#include <QTimer>
#include <QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


private:
    Ui::MainWindow *ui;

    bool buttonFlag;
    uint8_t currentPage = 1;
    QTimer *m_keepAliveTimer;

    DatabaseWorker *myT;
    QThread *thread;

    DatabaseWorker *sensorT;
    QThread *sensorThread;

    DatabaseWorker *weighbridgeT;
    QThread *weighbridgeThread;

    SpreadSheet spreadsheet; // 添加SpreadSheet成员
    QSqlQueryModel* m_oldModel;


    void updateValue();
    QTableWidgetItem * getTableWidgetItem(QFont font,int alignment,QString content);
    void styleAdjustment(QTableWidget *t);
    bool initDB();
    void initTableWidget();

    void configureTableView(QTableView *tableView);
    void setValveParameters(QString str);
    bool loadImageForLabel(QLabel *label, const QString &imagePath);


    void initAllWidgetStretch();
    void initFFontStretch(QWidget * w,int stretch);
    void setFontForAllChildren(QWidget *parentWidget,int stretch);

private slots:
       void updatePickedProductTable(const QList<pickedProduct_Type>& products);
       void updateRawInspectTable(const QList<RawInspectionRow>& products);
       void updateSensorData(const QList<SensorData_Type>& products);
       void updateWeighbridgeData(const QList<WeighRecordViewType>& products);
       void startKeepAlive();


protected:
       void mouseDoubleClickEvent(QMouseEvent *event) override;  // 双击事件
       void keyPressEvent(QKeyEvent *event) override;            // 可选：ESC退出全屏

signals:
        void startThread();
};

#endif // MAINWINDOW_H
