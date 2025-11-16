/********************************************************************************
** Form generated from reading UI file 'distortsubwindow2.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTORTSUBWINDOW2_H
#define UI_DISTORTSUBWINDOW2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DistortsubWindow2
{
public:
    QGridLayout *gridLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout;
    QTableView *tableView_weighbridge;
    QWidget *page_2;
    QGridLayout *gridLayout_10;
    QTableWidget *tableWidget_RowSand;
    QWidget *page_3;
    QGridLayout *gridLayout_11;
    QTableWidget *tableWidget_Pickling;

    void setupUi(QDialog *DistortsubWindow2)
    {
        if (DistortsubWindow2->objectName().isEmpty())
            DistortsubWindow2->setObjectName(QStringLiteral("DistortsubWindow2"));
        DistortsubWindow2->resize(1004, 653);
        gridLayout_2 = new QGridLayout(DistortsubWindow2);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(DistortsubWindow2);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        stackedWidget->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setKerning(false);
        stackedWidget->setFont(font);
        stackedWidget->setFrameShadow(QFrame::Plain);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        gridLayout = new QGridLayout(page);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableView_weighbridge = new QTableView(page);
        tableView_weighbridge->setObjectName(QStringLiteral("tableView_weighbridge"));

        gridLayout->addWidget(tableView_weighbridge, 0, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        gridLayout_10 = new QGridLayout(page_2);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        tableWidget_RowSand = new QTableWidget(page_2);
        tableWidget_RowSand->setObjectName(QStringLiteral("tableWidget_RowSand"));
        tableWidget_RowSand->setStyleSheet(QString::fromUtf8("QTableCornerButton::section{background-color:#d1dff0;}\n"
"QTableView\n"
"{\n"
"\n"
"	background-color: rgba(255, 255, 255, 0); \n"
"	font:14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color:#677483;\n"
"	gridline-color: #ccddf0;\n"
"}\n"
" \n"
"QTableView::item\n"
"{	\n"
"	font:16px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color:#000000;\n"
"	gridline-color: #ccddf0; \n"
"}\n"
" \n"
"QTableView::item:selected\n"
"{	\n"
"	color:#677483;\n"
"}\n"
" \n"
"QHeaderView::section {	\n"
"	color: black;\n"
"	font:bold 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	text-align:center;\n"
"	height:32px;\n"
"	width :25px;\n"
"	background-color: #d1dff0;\n"
"	border:1px solid #8faac9;\n"
"	border-left:none;\n"
"\n"
"}\n"
" \n"
"// border-left:none;\351\230\262\346\255\242\344\270\255\351\227\264\350\241\250\345\244\264\347\232\204border\351\207\215\345\217\240\n"
"QHeaderView::section:first \n"
"{\n"
"	border-left:1px solid #8faac9;\n"
"}\n"
"\n"
"\n"
""));
        tableWidget_RowSand->horizontalHeader()->setVisible(false);
        tableWidget_RowSand->verticalHeader()->setVisible(false);

        gridLayout_10->addWidget(tableWidget_RowSand, 0, 0, 1, 1);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        gridLayout_11 = new QGridLayout(page_3);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        tableWidget_Pickling = new QTableWidget(page_3);
        tableWidget_Pickling->setObjectName(QStringLiteral("tableWidget_Pickling"));
        tableWidget_Pickling->setStyleSheet(QString::fromUtf8("QTableCornerButton::section{background-color:#d1dff0;}\n"
"QTableView\n"
"{\n"
"\n"
"	background-color: rgba(255, 255, 255, 0); \n"
"	font:14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color:#677483;\n"
"	gridline-color: #ccddf0;\n"
"}\n"
" \n"
"QTableView::item\n"
"{	\n"
"	font:16px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color:#000000;\n"
"	gridline-color: #ccddf0; \n"
"}\n"
" \n"
"QTableView::item:selected\n"
"{	\n"
"	color:#677483;\n"
"}\n"
" \n"
"QHeaderView::section {	\n"
"	color: black;\n"
"	font:bold 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	text-align:center;\n"
"	height:32px;\n"
"	width :25px;\n"
"	background-color: #d1dff0;\n"
"	border:1px solid #8faac9;\n"
"	border-left:none;\n"
"\n"
"}\n"
" \n"
"// border-left:none;\351\230\262\346\255\242\344\270\255\351\227\264\350\241\250\345\244\264\347\232\204border\351\207\215\345\217\240\n"
"QHeaderView::section:first \n"
"{\n"
"	border-left:1px solid #8faac9;\n"
"}\n"
"\n"
"\n"
""));

        gridLayout_11->addWidget(tableWidget_Pickling, 0, 0, 1, 1);

        stackedWidget->addWidget(page_3);

        gridLayout_2->addWidget(stackedWidget, 0, 0, 1, 1);


        retranslateUi(DistortsubWindow2);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DistortsubWindow2);
    } // setupUi

    void retranslateUi(QDialog *DistortsubWindow2)
    {
        DistortsubWindow2->setWindowTitle(QApplication::translate("DistortsubWindow2", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DistortsubWindow2: public Ui_DistortsubWindow2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTORTSUBWINDOW2_H
