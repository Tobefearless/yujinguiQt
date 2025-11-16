#include "distortmainwindow.h"
#include "ui_distortmainwindow.h"

DisTortMainWindow::DisTortMainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisTortMainWindow)
{
    ui->setupUi(this);
    showMaximized();
//    setWindowFlags(Qt::FramelessWindowHint);   // 去掉系统边框
    setWindowTitle("工业控制监控系统");
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
}

DisTortMainWindow::~DisTortMainWindow()
{
    delete ui;
}
