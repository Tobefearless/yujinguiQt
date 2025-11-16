#ifndef DISTORTSUBWINDOW2_H
#define DISTORTSUBWINDOW2_H

#include <QDialog>
#include <QTableWidget>
#include "excel/spreadsheet.h"
#include "dataBase/mysqldatabase.h"
#include "dataBase/sqlserverhandler.h"
#include "thread/databaseworker.h"
namespace Ui {
class DistortsubWindow2;
}

class DistortsubWindow2 : public QDialog
{
    Q_OBJECT

public:
    explicit DistortsubWindow2(QWidget *parent = 0);
    ~DistortsubWindow2();

private:
    Ui::DistortsubWindow2 *ui;

    uint8_t currentPage = 1;
    QTimer *m_keepAliveTimer;

    DatabaseWorker *myT;
    QThread *thread;

    SpreadSheet spreadsheet; // 添加SpreadSheet成员

    SQLServerHandler sqlServerHandler;

    void configureTableView(QTableView *tableView);
private slots:
       void updatePickedProductTable(const QList<pickedProduct_Type>& products);
       void updateRawInspectTable(const QList<RawInspectionRow>& products);
       void startKeepAlive();
signals:
        void startThread();
};

#endif // DISTORTSUBWINDOW2_H
