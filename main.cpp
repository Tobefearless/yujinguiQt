#include "mainwindow.h"
#include <QApplication>
#include <QMetaType>
#include "value_type.h"
#include <QScreen>
#include <QtEndian>
#include <QDebug>
#include <cstring>
#include <QFile>
#include "distort/distortmainwindow.h"
#include "distort/distortsubwindow1.h"
#include "distort/distortsubwindow2.h"


// 比较函数：按屏幕的x坐标排序（从左到右）
bool screenCompare(QScreen* s1, QScreen* s2) {
    return s1->geometry().x() < s2->geometry().x();
}

// 自定义消息处理器，将输出同时发送到控制台和文件
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();

    // 输出到控制台（如果存在）
    switch (type) {
    case QtDebugMsg:
        fprintf(stdout, "Debug: %s\n", localMsg.constData());
        break;
    case QtInfoMsg:
        fprintf(stdout, "Info: %s\n", localMsg.constData());
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s\n", localMsg.constData());
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s\n", localMsg.constData());
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s\n", localMsg.constData());
        abort();
    }

    // 同时输出到文件
    QFile file("app_log.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << " ";

        switch (type) {
        case QtDebugMsg: stream << "Debug"; break;
        case QtInfoMsg: stream << "Info"; break;
        case QtWarningMsg: stream << "Warning"; break;
        case QtCriticalMsg: stream << "Critical"; break;
        case QtFatalMsg: stream << "Fatal"; break;
        }

        stream << ": " << msg << "\n";
        file.close();
    }
}


int main(int argc, char *argv[])
{
//    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    // 安装自定义消息处理器
//    qInstallMessageHandler(messageHandler);

    QApplication a(argc, argv);

//    QFont font = a.font();
//    font.setPointSize(10); // 比默认稍大，适配4K屏
//    a.setFont(font);

    //注册数据类型
    qRegisterMetaType<pickedProduct_Type>();
    qRegisterMetaType<QList<pickedProduct_Type>>();
    qRegisterMetaType<RawInspectionRow>();
    qRegisterMetaType<QList<RawInspectionRow>>();
    qRegisterMetaType<SensorData_Type>();
    qRegisterMetaType<QList<SensorData_Type>>();
    qRegisterMetaType<QList<WeighRecordViewType>>();

    // 获取所有屏幕并排序（使用 QScreen）
    QList<QScreen*> screens = QApplication::screens();
//    std::sort(screens.begin(), screens.end(), screenCompare);

    // 检查是否有至少3个屏幕
    if(screens.size() < 3) {
        qWarning() << "需要至少3个屏幕，当前只有" << screens.size() << "个屏幕可用";
        // 回退到单屏显示
        MainWindow w;
        w.show();
        return a.exec();
    }

    // 计算三屏拼接区域
//    QRect videoWallRect;
//    for(int i = 0; i < 3; i++) {
//        QRect screenGeo = screens[i]->geometry();
//        if(i == 0) {
//            videoWallRect = screenGeo;
//        } else {
//            videoWallRect = videoWallRect.united(screenGeo);
//        }
//    }

//    qDebug() << "视频墙区域:" << videoWallRect;

//    MainWindow w;

//    // 设置窗口为无边框（可选）
//    w.setWindowFlags(w.windowFlags() | Qt::FramelessWindowHint);

//    // 设置窗口位置和大小
//    w.move(videoWallRect.topLeft());
//    w.resize(videoWallRect.width(), videoWallRect.height());

//    w.show();

    // 创建主窗口

   DisTortMainWindow *mainWindow = new DisTortMainWindow;

   // 创建子窗口，并设置主窗口为父对象
   DisTortSubWindow1 *subWindow1 = new DisTortSubWindow1(mainWindow); // 设置父对象
   DistortsubWindow2 *subWindow2 = new DistortsubWindow2(mainWindow); // 设置父对象

   // 移动到各自屏幕
   mainWindow->move(screens[0]->geometry().topLeft());
   subWindow1->move(screens[0]->geometry().topLeft());
   subWindow2->move(screens[0]->geometry().topLeft());

   // 显示窗口
   mainWindow->show();
   subWindow1->show();
   subWindow2->show();


    return a.exec();
}
