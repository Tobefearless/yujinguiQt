/********************************************************************************
** Form generated from reading UI file 'distortmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTORTMAINWINDOW_H
#define UI_DISTORTMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DisTortMainWindow
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_BeltScaleWeight;
    QLabel *label_4;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_LiquidLevelgauge;
    QLabel *label_65;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_TemperatureH;
    QLabel *label_83;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_15;
    QHBoxLayout *horizontalLayout_42;
    QLabel *label_ImportedSteamValue;
    QSpacerItem *horizontalSpacer_41;
    QLabel *label_SteamValueE;
    QHBoxLayout *horizontalLayout_43;
    QLabel *label_QuletLiquidTemp;
    QSpacerItem *horizontalSpacer_42;
    QLabel *label_TemperatureE;
    QHBoxLayout *horizontalLayout_44;
    QLabel *label_CondensateS;
    QSpacerItem *horizontalSpacer_43;
    QLabel *label_Condensate;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_14;
    QHBoxLayout *horizontalLayout_40;
    QLabel *label_88;
    QSpacerItem *horizontalSpacer_39;
    QLabel *label_NaturalValueG;
    QHBoxLayout *horizontalLayout_38;
    QLabel *label_86;
    QSpacerItem *horizontalSpacer_37;
    QLabel *label_TemperatureG;
    QHBoxLayout *horizontalLayout_39;
    QLabel *label_87;
    QSpacerItem *horizontalSpacer_38;
    QLabel *label_SteamValueG;
    QHBoxLayout *horizontalLayout_37;
    QLabel *label_84;
    QSpacerItem *horizontalSpacer;
    QLabel *label_RunningStatus;

    void setupUi(QDialog *DisTortMainWindow)
    {
        if (DisTortMainWindow->objectName().isEmpty())
            DisTortMainWindow->setObjectName(QStringLiteral("DisTortMainWindow"));
        DisTortMainWindow->resize(1190, 232);
        gridLayout = new QGridLayout(DisTortMainWindow);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setVerticalSpacing(15);
        gridLayout->setContentsMargins(15, 15, -1, -1);
        groupBox = new QGroupBox(DisTortMainWindow);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 16777215));
        groupBox->setStyleSheet(QLatin1String("QGroupBox{\n"
"    border:1px solid #e0e0e0;\n"
"    border-radius:10px;\n"
"    margin-top:0;               \n"
"    padding-top:28px;           \n"
"    font-weight:500;     \n"
"    background-color:#ffffff;\n"
"   font-size: 24px;\n"
"}\n"
"QGroupBox::title{\n"
"    subcontrol-origin: padding; \n"
"    subcontrol-position: top left;\n"
"    left:8px;\n"
"    top:4px;\n"
"      \n"
"    font-family:\"Microsoft YaHei\";  \n"
"}"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_BeltScaleWeight = new QLabel(groupBox);
        label_BeltScaleWeight->setObjectName(QStringLiteral("label_BeltScaleWeight"));
        label_BeltScaleWeight->setStyleSheet(QString::fromUtf8("QLabel{\n"
"    font-family:\"Microsoft YaHei\";\n"
"    font-size:48px;\n"
"    color:#222222;\n"
"    font-weight:bold;\n"
"    qproperty-alignment:AlignCenter;\n"
"    background-color:#ffffff;   /* \350\203\214\346\231\257\350\256\276\344\270\272\347\231\275\350\211\262 */\n"
"}"));

        verticalLayout->addWidget(label_BeltScaleWeight);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setStyleSheet(QLatin1String("QLabel{\n"
"    font-family:\"Microsoft YaHei\";\n"
"    font-size:16px;\n"
"    color:#888888;\n"
"    font-weight:normal;\n"
"    background-color:#ffffff;\n"
"    qproperty-alignment:AlignCenter;\n"
"}"));

        verticalLayout->addWidget(label_4);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_6 = new QGroupBox(DisTortMainWindow);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setMaximumSize(QSize(16777215, 16777215));
        groupBox_6->setStyleSheet(QLatin1String("QGroupBox{\n"
"    border:1px solid #e0e0e0;\n"
"    border-radius:10px;\n"
"    margin-top:0;               \n"
"    padding-top:28px;           \n"
"    font-weight:500;     \n"
"    background-color:#ffffff;\n"
"   font-size: 24px;\n"
"}\n"
"QGroupBox::title{\n"
"    subcontrol-origin: padding; \n"
"    subcontrol-position: top left;\n"
"    left:8px;\n"
"    top:4px;\n"
"      \n"
"    font-family:\"Microsoft YaHei\";  \n"
"}"));
        gridLayout_3 = new QGridLayout(groupBox_6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label_LiquidLevelgauge = new QLabel(groupBox_6);
        label_LiquidLevelgauge->setObjectName(QStringLiteral("label_LiquidLevelgauge"));
        label_LiquidLevelgauge->setStyleSheet(QString::fromUtf8("QLabel{\n"
"    font-family:\"Microsoft YaHei\";\n"
"    font-size:48px;\n"
"    color:#222222;\n"
"    font-weight:bold;\n"
"    qproperty-alignment:AlignCenter;\n"
"    background-color:#ffffff;   /* \350\203\214\346\231\257\350\256\276\344\270\272\347\231\275\350\211\262 */\n"
"}"));

        verticalLayout_6->addWidget(label_LiquidLevelgauge);

        label_65 = new QLabel(groupBox_6);
        label_65->setObjectName(QStringLiteral("label_65"));
        label_65->setStyleSheet(QLatin1String("QLabel{\n"
"    font-family:\"Microsoft YaHei\";\n"
"    font-size:16px;\n"
"    color:#888888;\n"
"    font-weight:normal;\n"
"    background-color:#ffffff;\n"
"    qproperty-alignment:AlignCenter;\n"
"}"));

        verticalLayout_6->addWidget(label_65);


        gridLayout_3->addLayout(verticalLayout_6, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_6, 0, 1, 1, 1);

        groupBox_7 = new QGroupBox(DisTortMainWindow);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setMaximumSize(QSize(16777215, 16777215));
        groupBox_7->setStyleSheet(QLatin1String("QGroupBox{\n"
"    border:1px solid #e0e0e0;\n"
"    border-radius:10px;\n"
"    margin-top:0;               \n"
"    padding-top:28px;           \n"
"    font-weight:500;     \n"
"    background-color:#ffffff;\n"
"   font-size: 24px;\n"
"}\n"
"QGroupBox::title{\n"
"    subcontrol-origin: padding; \n"
"    subcontrol-position: top left;\n"
"    left:8px;\n"
"    top:4px;\n"
"      \n"
"    font-family:\"Microsoft YaHei\";  \n"
"}"));
        gridLayout_4 = new QGridLayout(groupBox_7);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        label_TemperatureH = new QLabel(groupBox_7);
        label_TemperatureH->setObjectName(QStringLiteral("label_TemperatureH"));
        label_TemperatureH->setStyleSheet(QString::fromUtf8("QLabel{\n"
"    font-family:\"Microsoft YaHei\";\n"
"    font-size:48px;\n"
"    color:#222222;\n"
"    font-weight:bold;\n"
"    qproperty-alignment:AlignCenter;\n"
"    background-color:#ffffff;   /* \350\203\214\346\231\257\350\256\276\344\270\272\347\231\275\350\211\262 */\n"
"}"));

        verticalLayout_9->addWidget(label_TemperatureH);

        label_83 = new QLabel(groupBox_7);
        label_83->setObjectName(QStringLiteral("label_83"));
        label_83->setStyleSheet(QLatin1String("QLabel{\n"
"    font-family:\"Microsoft YaHei\";\n"
"    font-size:16px;\n"
"    color:#888888;\n"
"    font-weight:normal;\n"
"    background-color:#ffffff;\n"
"    qproperty-alignment:AlignCenter;\n"
"}"));

        verticalLayout_9->addWidget(label_83);


        gridLayout_4->addLayout(verticalLayout_9, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_7, 0, 2, 1, 1);

        groupBox_9 = new QGroupBox(DisTortMainWindow);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        groupBox_9->setStyleSheet(QLatin1String("QGroupBox{\n"
"    border:1px solid #e0e0e0;\n"
"    border-radius:10px;\n"
"    margin-top:0;               \n"
"    padding-top:28px;           \n"
"    font-weight:500;     \n"
"    background-color:#ffffff;\n"
"   font-size: 24px;\n"
"}\n"
"QGroupBox::title{\n"
"    subcontrol-origin: padding; \n"
"    subcontrol-position: top left;\n"
"    left:8px;\n"
"    top:4px;\n"
"      \n"
"    font-family:\"Microsoft YaHei\";  \n"
"}"));
        gridLayout_15 = new QGridLayout(groupBox_9);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        horizontalLayout_42 = new QHBoxLayout();
        horizontalLayout_42->setObjectName(QStringLiteral("horizontalLayout_42"));
        label_ImportedSteamValue = new QLabel(groupBox_9);
        label_ImportedSteamValue->setObjectName(QStringLiteral("label_ImportedSteamValue"));
        label_ImportedSteamValue->setStyleSheet(QString::fromUtf8("QLabel{\n"
"    font-family:\"PingFang SC Medium\";\n"
"    font-size:16px;\n"
"    background:transparent;\n"
"    /* \346\263\250\346\204\217\357\274\232qproperty-alignment \345\234\250\346\240\267\345\274\217\350\241\250\344\270\255\346\227\240\346\225\210\357\274\214\351\234\200\344\273\243\347\240\201\351\207\214 setAlignment(Qt::AlignCenter) */\n"
"}"));

        horizontalLayout_42->addWidget(label_ImportedSteamValue);

        horizontalSpacer_41 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_42->addItem(horizontalSpacer_41);

        label_SteamValueE = new QLabel(groupBox_9);
        label_SteamValueE->setObjectName(QStringLiteral("label_SteamValueE"));
        label_SteamValueE->setStyleSheet(QLatin1String("\n"
" QLabel{\n"
"        font-family:PingFang SC Medium;\n"
"        font-size:18px;\n"
"        color:#333333;\n"
"        background:transparent;\n"
"        qproperty-alignment:AlignCenter;\n"
"    }"));

        horizontalLayout_42->addWidget(label_SteamValueE);


        gridLayout_15->addLayout(horizontalLayout_42, 0, 0, 1, 1);

        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setObjectName(QStringLiteral("horizontalLayout_43"));
        label_QuletLiquidTemp = new QLabel(groupBox_9);
        label_QuletLiquidTemp->setObjectName(QStringLiteral("label_QuletLiquidTemp"));
        label_QuletLiquidTemp->setStyleSheet(QString::fromUtf8("QLabel{\n"
"    font-family:\"PingFang SC Medium\";\n"
"    font-size:16px;\n"
"    background:transparent;\n"
"    /* \346\263\250\346\204\217\357\274\232qproperty-alignment \345\234\250\346\240\267\345\274\217\350\241\250\344\270\255\346\227\240\346\225\210\357\274\214\351\234\200\344\273\243\347\240\201\351\207\214 setAlignment(Qt::AlignCenter) */\n"
"}"));

        horizontalLayout_43->addWidget(label_QuletLiquidTemp);

        horizontalSpacer_42 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_43->addItem(horizontalSpacer_42);

        label_TemperatureE = new QLabel(groupBox_9);
        label_TemperatureE->setObjectName(QStringLiteral("label_TemperatureE"));
        label_TemperatureE->setStyleSheet(QLatin1String("\n"
" QLabel{\n"
"        font-family:PingFang SC Medium;\n"
"        font-size:18px;\n"
"        color:#333333;\n"
"        background:transparent;\n"
"        qproperty-alignment:AlignCenter;\n"
"    }"));

        horizontalLayout_43->addWidget(label_TemperatureE);


        gridLayout_15->addLayout(horizontalLayout_43, 1, 0, 1, 1);

        horizontalLayout_44 = new QHBoxLayout();
        horizontalLayout_44->setObjectName(QStringLiteral("horizontalLayout_44"));
        label_CondensateS = new QLabel(groupBox_9);
        label_CondensateS->setObjectName(QStringLiteral("label_CondensateS"));
        label_CondensateS->setStyleSheet(QString::fromUtf8("QLabel{\n"
"    font-family:\"PingFang SC Medium\";\n"
"    font-size:16px;\n"
"    background:transparent;\n"
"    /* \346\263\250\346\204\217\357\274\232qproperty-alignment \345\234\250\346\240\267\345\274\217\350\241\250\344\270\255\346\227\240\346\225\210\357\274\214\351\234\200\344\273\243\347\240\201\351\207\214 setAlignment(Qt::AlignCenter) */\n"
"}"));

        horizontalLayout_44->addWidget(label_CondensateS);

        horizontalSpacer_43 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_44->addItem(horizontalSpacer_43);

        label_Condensate = new QLabel(groupBox_9);
        label_Condensate->setObjectName(QStringLiteral("label_Condensate"));
        label_Condensate->setStyleSheet(QLatin1String("\n"
" QLabel{\n"
"        font-family:PingFang SC Medium;\n"
"        font-size:18px;\n"
"        color:#333333;\n"
"        background:transparent;\n"
"        qproperty-alignment:AlignCenter;\n"
"    }"));

        horizontalLayout_44->addWidget(label_Condensate);


        gridLayout_15->addLayout(horizontalLayout_44, 2, 0, 1, 1);


        gridLayout->addWidget(groupBox_9, 0, 3, 1, 1);

        groupBox_8 = new QGroupBox(DisTortMainWindow);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setStyleSheet(QLatin1String("QGroupBox{\n"
"    border:1px solid #e0e0e0;\n"
"    border-radius:10px;\n"
"    margin-top:0;               \n"
"    padding-top:28px;           \n"
"    font-weight:500;     \n"
"    background-color:#ffffff;\n"
"   font-size: 24px;\n"
"}\n"
"QGroupBox::title{\n"
"    subcontrol-origin: padding; \n"
"    subcontrol-position: top left;\n"
"    left:8px;\n"
"    top:4px;\n"
"      \n"
"    font-family:\"Microsoft YaHei\";  \n"
"}"));
        gridLayout_14 = new QGridLayout(groupBox_8);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        horizontalLayout_40 = new QHBoxLayout();
        horizontalLayout_40->setObjectName(QStringLiteral("horizontalLayout_40"));
        label_88 = new QLabel(groupBox_8);
        label_88->setObjectName(QStringLiteral("label_88"));
        label_88->setStyleSheet(QString::fromUtf8("QLabel{\n"
"    font-family:\"PingFang SC Medium\";\n"
"    font-size:16px;\n"
"    background:transparent;\n"
"    /* \346\263\250\346\204\217\357\274\232qproperty-alignment \345\234\250\346\240\267\345\274\217\350\241\250\344\270\255\346\227\240\346\225\210\357\274\214\351\234\200\344\273\243\347\240\201\351\207\214 setAlignment(Qt::AlignCenter) */\n"
"}"));

        horizontalLayout_40->addWidget(label_88);

        horizontalSpacer_39 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_40->addItem(horizontalSpacer_39);

        label_NaturalValueG = new QLabel(groupBox_8);
        label_NaturalValueG->setObjectName(QStringLiteral("label_NaturalValueG"));
        label_NaturalValueG->setStyleSheet(QLatin1String("\n"
" QLabel{\n"
"        font-family:PingFang SC Medium;\n"
"        font-size:18px;\n"
"        color:#333333;\n"
"        background:transparent;\n"
"        qproperty-alignment:AlignCenter;\n"
"    }"));

        horizontalLayout_40->addWidget(label_NaturalValueG);


        gridLayout_14->addLayout(horizontalLayout_40, 3, 0, 1, 1);

        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setObjectName(QStringLiteral("horizontalLayout_38"));
        label_86 = new QLabel(groupBox_8);
        label_86->setObjectName(QStringLiteral("label_86"));
        label_86->setStyleSheet(QString::fromUtf8("QLabel{\n"
"    font-family:\"PingFang SC Medium\";\n"
"    font-size:16px;\n"
"    background:transparent;\n"
"    /* \346\263\250\346\204\217\357\274\232qproperty-alignment \345\234\250\346\240\267\345\274\217\350\241\250\344\270\255\346\227\240\346\225\210\357\274\214\351\234\200\344\273\243\347\240\201\351\207\214 setAlignment(Qt::AlignCenter) */\n"
"}"));

        horizontalLayout_38->addWidget(label_86);

        horizontalSpacer_37 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_38->addItem(horizontalSpacer_37);

        label_TemperatureG = new QLabel(groupBox_8);
        label_TemperatureG->setObjectName(QStringLiteral("label_TemperatureG"));
        label_TemperatureG->setStyleSheet(QLatin1String("\n"
" QLabel{\n"
"        font-family:PingFang SC Medium;\n"
"        font-size:18px;\n"
"        color:#333333;\n"
"        background:transparent;\n"
"        qproperty-alignment:AlignCenter;\n"
"    }"));

        horizontalLayout_38->addWidget(label_TemperatureG);


        gridLayout_14->addLayout(horizontalLayout_38, 1, 0, 1, 1);

        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setObjectName(QStringLiteral("horizontalLayout_39"));
        label_87 = new QLabel(groupBox_8);
        label_87->setObjectName(QStringLiteral("label_87"));
        label_87->setStyleSheet(QString::fromUtf8("QLabel{\n"
"    font-family:\"PingFang SC Medium\";\n"
"    font-size:16px;\n"
"    background:transparent;\n"
"    /* \346\263\250\346\204\217\357\274\232qproperty-alignment \345\234\250\346\240\267\345\274\217\350\241\250\344\270\255\346\227\240\346\225\210\357\274\214\351\234\200\344\273\243\347\240\201\351\207\214 setAlignment(Qt::AlignCenter) */\n"
"}"));

        horizontalLayout_39->addWidget(label_87);

        horizontalSpacer_38 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_39->addItem(horizontalSpacer_38);

        label_SteamValueG = new QLabel(groupBox_8);
        label_SteamValueG->setObjectName(QStringLiteral("label_SteamValueG"));
        label_SteamValueG->setStyleSheet(QLatin1String("\n"
" QLabel{\n"
"        font-family:PingFang SC Medium;\n"
"        font-size:18px;\n"
"        color:#333333;\n"
"        background:transparent;\n"
"        qproperty-alignment:AlignCenter;\n"
"    }"));

        horizontalLayout_39->addWidget(label_SteamValueG);


        gridLayout_14->addLayout(horizontalLayout_39, 2, 0, 1, 1);

        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setObjectName(QStringLiteral("horizontalLayout_37"));
        label_84 = new QLabel(groupBox_8);
        label_84->setObjectName(QStringLiteral("label_84"));
        label_84->setStyleSheet(QString::fromUtf8("QLabel{\n"
"    font-family:\"PingFang SC Medium\";\n"
"    font-size:16px;\n"
"    background:transparent;\n"
"    /* \346\263\250\346\204\217\357\274\232qproperty-alignment \345\234\250\346\240\267\345\274\217\350\241\250\344\270\255\346\227\240\346\225\210\357\274\214\351\234\200\344\273\243\347\240\201\351\207\214 setAlignment(Qt::AlignCenter) */\n"
"}"));

        horizontalLayout_37->addWidget(label_84);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_37->addItem(horizontalSpacer);

        label_RunningStatus = new QLabel(groupBox_8);
        label_RunningStatus->setObjectName(QStringLiteral("label_RunningStatus"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_RunningStatus->sizePolicy().hasHeightForWidth());
        label_RunningStatus->setSizePolicy(sizePolicy);
        label_RunningStatus->setMinimumSize(QSize(0, 41));
        label_RunningStatus->setMaximumSize(QSize(71, 60));
        label_RunningStatus->setStyleSheet(QStringLiteral("background: transparent;"));
        label_RunningStatus->setPixmap(QPixmap(QString::fromUtf8(":/image/image/OperationStatusOpen.png")));
        label_RunningStatus->setScaledContents(true);

        horizontalLayout_37->addWidget(label_RunningStatus);


        gridLayout_14->addLayout(horizontalLayout_37, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_8, 0, 4, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnStretch(2, 1);
        gridLayout->setColumnStretch(3, 1);
        gridLayout->setColumnStretch(4, 1);

        retranslateUi(DisTortMainWindow);

        QMetaObject::connectSlotsByName(DisTortMainWindow);
    } // setupUi

    void retranslateUi(QDialog *DisTortMainWindow)
    {
        DisTortMainWindow->setWindowTitle(QApplication::translate("DisTortMainWindow", "Dialog", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("DisTortMainWindow", "\347\232\256\345\270\246\347\247\244\351\207\215\351\207\217", Q_NULLPTR));
        label_BeltScaleWeight->setText(QApplication::translate("DisTortMainWindow", "1", Q_NULLPTR));
        label_4->setText(QApplication::translate("DisTortMainWindow", "\345\220\250/\345\260\217\346\227\266", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("DisTortMainWindow", "\346\260\242\346\260\247\351\205\270\347\275\220", Q_NULLPTR));
        label_LiquidLevelgauge->setText(QApplication::translate("DisTortMainWindow", "5", Q_NULLPTR));
        label_65->setText(QApplication::translate("DisTortMainWindow", "pH", Q_NULLPTR));
        groupBox_7->setTitle(QApplication::translate("DisTortMainWindow", "\345\233\236\351\205\270\347\275\220", Q_NULLPTR));
        label_TemperatureH->setText(QApplication::translate("DisTortMainWindow", "25.3", Q_NULLPTR));
        label_83->setText(QApplication::translate("DisTortMainWindow", "\342\204\203", Q_NULLPTR));
        groupBox_9->setTitle(QApplication::translate("DisTortMainWindow", "\347\237\263\345\242\250\346\215\242\347\203\255\345\231\250", Q_NULLPTR));
        label_ImportedSteamValue->setText(QApplication::translate("DisTortMainWindow", "\350\277\233\345\217\243\350\222\270\346\261\275\345\216\213\345\212\233\345\200\274", Q_NULLPTR));
        label_SteamValueE->setText(QApplication::translate("DisTortMainWindow", "23\342\204\203", Q_NULLPTR));
        label_QuletLiquidTemp->setText(QApplication::translate("DisTortMainWindow", "\345\207\272\345\217\243\346\270\251\345\272\246\346\266\262\344\275\223\345\200\274", Q_NULLPTR));
        label_TemperatureE->setText(QApplication::translate("DisTortMainWindow", "5%", Q_NULLPTR));
        label_CondensateS->setText(QApplication::translate("DisTortMainWindow", "\345\206\267\345\207\235\346\260\264PH\345\200\274", Q_NULLPTR));
        label_Condensate->setText(QApplication::translate("DisTortMainWindow", "8%", Q_NULLPTR));
        groupBox_8->setTitle(QApplication::translate("DisTortMainWindow", "\347\207\203\346\260\224\351\224\205\347\202\211", Q_NULLPTR));
        label_88->setText(QApplication::translate("DisTortMainWindow", "\345\244\251\347\204\266\346\260\224\345\216\213\345\212\233\345\200\274", Q_NULLPTR));
        label_NaturalValueG->setText(QApplication::translate("DisTortMainWindow", "8%", Q_NULLPTR));
        label_86->setText(QApplication::translate("DisTortMainWindow", "\346\270\251\345\272\246\345\200\274", Q_NULLPTR));
        label_TemperatureG->setText(QApplication::translate("DisTortMainWindow", "23\342\204\203", Q_NULLPTR));
        label_87->setText(QApplication::translate("DisTortMainWindow", "\345\207\272\345\217\243\350\222\270\346\261\275\345\216\213\345\212\233\345\200\274", Q_NULLPTR));
        label_SteamValueG->setText(QApplication::translate("DisTortMainWindow", "5%", Q_NULLPTR));
        label_84->setText(QApplication::translate("DisTortMainWindow", "\350\277\220\350\241\214\347\212\266\346\200\201", Q_NULLPTR));
        label_RunningStatus->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DisTortMainWindow: public Ui_DisTortMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTORTMAINWINDOW_H
