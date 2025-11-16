#include "distortsubwindow1.h"
#include "ui_distortsubwindow1.h"

DisTortSubWindow1::DisTortSubWindow1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisTortSubWindow1)
{
    ui->setupUi(this);
//    setWindowFlags(Qt::FramelessWindowHint);   // 去掉系统边框
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
}

DisTortSubWindow1::~DisTortSubWindow1()
{
    delete ui;
}
