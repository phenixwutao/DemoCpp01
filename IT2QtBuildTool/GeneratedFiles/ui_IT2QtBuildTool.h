/********************************************************************************
** Form generated from reading UI file 'IT2QtBuildTool.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IT2QTBUILDTOOL_H
#define UI_IT2QTBUILDTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IT2QtBuildToolClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QGroupBox *ConfigGBX;
    QGridLayout *gridLayout;
    QLabel *DBServerLabel;
    QLineEdit *DBServerEdit;
    QSpacerItem *verticalSpacer_12;
    QLabel *AppServerLabel;
    QLineEdit *AppServerEdit;
    QSpacerItem *verticalSpacer_13;
    QLabel *WorkStationLabel;
    QLineEdit *WorkStationEdit;
    QSpacerItem *verticalSpacer_14;
    QLabel *RootFolderLabel;
    QLineEdit *RootFolderEdit;
    QSpacerItem *verticalSpacer_15;
    QLabel *PrebuildLabel;
    QLineEdit *PrebuildFolderEdit;
    QSpacerItem *verticalSpacer_16;
    QPushButton *SavePB;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *ResetPB;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *DefaultPB;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *ClearPB;
    QGroupBox *SolutionsGBX;
    QGridLayout *gridLayout_2;
    QCheckBox *IT2ParserCKB;
    QCheckBox *checkBox_6;
    QSpacerItem *verticalSpacer_10;
    QSpacerItem *verticalSpacer_5;
    QCheckBox *checkBox_7;
    QSpacerItem *verticalSpacer_9;
    QSpacerItem *verticalSpacer_4;
    QCheckBox *checkBox_8;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_9;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_10;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer;
    QPushButton *SeleclAllPB;
    QPushButton *DeseleclAllPB;
    QPushButton *StartPrebuildPB;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *BuildAllPB;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBox_3;
    QCheckBox *IT2BusinessCKB;
    QSpacerItem *verticalSpacer_11;
    QGroupBox *RunIT2GBX;
    QGridLayout *gridLayout_4;
    QLabel *RunAppServerLabel;
    QPushButton *StartAppServerPB;
    QPushButton *StopAppServerPB;
    QPushButton *StartWorkStationPB;
    QPushButton *StopWorkStationPB;
    QLabel *RunWorkstationLabel;
    QFrame *line;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *ClosePB;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *IT2QtBuildToolClass)
    {
        if (IT2QtBuildToolClass->objectName().isEmpty())
            IT2QtBuildToolClass->setObjectName(QStringLiteral("IT2QtBuildToolClass"));
        IT2QtBuildToolClass->resize(705, 526);
        centralWidget = new QWidget(IT2QtBuildToolClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        ConfigGBX = new QGroupBox(centralWidget);
        ConfigGBX->setObjectName(QStringLiteral("ConfigGBX"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        ConfigGBX->setFont(font);
        gridLayout = new QGridLayout(ConfigGBX);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        DBServerLabel = new QLabel(ConfigGBX);
        DBServerLabel->setObjectName(QStringLiteral("DBServerLabel"));

        gridLayout->addWidget(DBServerLabel, 0, 0, 1, 2);

        DBServerEdit = new QLineEdit(ConfigGBX);
        DBServerEdit->setObjectName(QStringLiteral("DBServerEdit"));

        gridLayout->addWidget(DBServerEdit, 0, 2, 1, 5);

        verticalSpacer_12 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_12, 1, 2, 1, 2);

        AppServerLabel = new QLabel(ConfigGBX);
        AppServerLabel->setObjectName(QStringLiteral("AppServerLabel"));

        gridLayout->addWidget(AppServerLabel, 2, 0, 1, 2);

        AppServerEdit = new QLineEdit(ConfigGBX);
        AppServerEdit->setObjectName(QStringLiteral("AppServerEdit"));

        gridLayout->addWidget(AppServerEdit, 2, 2, 1, 5);

        verticalSpacer_13 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_13, 3, 2, 1, 2);

        WorkStationLabel = new QLabel(ConfigGBX);
        WorkStationLabel->setObjectName(QStringLiteral("WorkStationLabel"));

        gridLayout->addWidget(WorkStationLabel, 4, 0, 1, 1);

        WorkStationEdit = new QLineEdit(ConfigGBX);
        WorkStationEdit->setObjectName(QStringLiteral("WorkStationEdit"));

        gridLayout->addWidget(WorkStationEdit, 4, 2, 1, 5);

        verticalSpacer_14 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_14, 5, 2, 1, 2);

        RootFolderLabel = new QLabel(ConfigGBX);
        RootFolderLabel->setObjectName(QStringLiteral("RootFolderLabel"));

        gridLayout->addWidget(RootFolderLabel, 6, 0, 1, 1);

        RootFolderEdit = new QLineEdit(ConfigGBX);
        RootFolderEdit->setObjectName(QStringLiteral("RootFolderEdit"));

        gridLayout->addWidget(RootFolderEdit, 6, 2, 1, 5);

        verticalSpacer_15 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_15, 7, 2, 1, 2);

        PrebuildLabel = new QLabel(ConfigGBX);
        PrebuildLabel->setObjectName(QStringLiteral("PrebuildLabel"));

        gridLayout->addWidget(PrebuildLabel, 8, 0, 1, 1);

        PrebuildFolderEdit = new QLineEdit(ConfigGBX);
        PrebuildFolderEdit->setObjectName(QStringLiteral("PrebuildFolderEdit"));

        gridLayout->addWidget(PrebuildFolderEdit, 8, 2, 1, 5);

        verticalSpacer_16 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_16, 9, 2, 1, 2);

        SavePB = new QPushButton(ConfigGBX);
        SavePB->setObjectName(QStringLiteral("SavePB"));

        gridLayout->addWidget(SavePB, 10, 0, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(17, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 10, 1, 1, 1);

        ResetPB = new QPushButton(ConfigGBX);
        ResetPB->setObjectName(QStringLiteral("ResetPB"));

        gridLayout->addWidget(ResetPB, 10, 2, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(17, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 10, 3, 1, 1);

        DefaultPB = new QPushButton(ConfigGBX);
        DefaultPB->setObjectName(QStringLiteral("DefaultPB"));

        gridLayout->addWidget(DefaultPB, 10, 4, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(17, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 10, 5, 1, 1);

        ClearPB = new QPushButton(ConfigGBX);
        ClearPB->setObjectName(QStringLiteral("ClearPB"));

        gridLayout->addWidget(ClearPB, 10, 6, 1, 1);


        gridLayout_3->addWidget(ConfigGBX, 0, 0, 1, 1);

        SolutionsGBX = new QGroupBox(centralWidget);
        SolutionsGBX->setObjectName(QStringLiteral("SolutionsGBX"));
        SolutionsGBX->setAutoFillBackground(false);
        SolutionsGBX->setFlat(false);
        SolutionsGBX->setCheckable(false);
        gridLayout_2 = new QGridLayout(SolutionsGBX);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        IT2ParserCKB = new QCheckBox(SolutionsGBX);
        IT2ParserCKB->setObjectName(QStringLiteral("IT2ParserCKB"));

        gridLayout_2->addWidget(IT2ParserCKB, 0, 0, 1, 1);

        checkBox_6 = new QCheckBox(SolutionsGBX);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));

        gridLayout_2->addWidget(checkBox_6, 0, 3, 1, 1);

        verticalSpacer_10 = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_10, 1, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_5, 1, 3, 1, 1);

        checkBox_7 = new QCheckBox(SolutionsGBX);
        checkBox_7->setObjectName(QStringLiteral("checkBox_7"));

        gridLayout_2->addWidget(checkBox_7, 2, 3, 1, 1);

        verticalSpacer_9 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_9, 3, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 3, 3, 1, 1);

        checkBox_8 = new QCheckBox(SolutionsGBX);
        checkBox_8->setObjectName(QStringLiteral("checkBox_8"));

        gridLayout_2->addWidget(checkBox_8, 4, 3, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_8, 5, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 5, 3, 1, 1);

        checkBox_4 = new QCheckBox(SolutionsGBX);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));

        gridLayout_2->addWidget(checkBox_4, 6, 0, 1, 1);

        checkBox_9 = new QCheckBox(SolutionsGBX);
        checkBox_9->setObjectName(QStringLiteral("checkBox_9"));

        gridLayout_2->addWidget(checkBox_9, 6, 3, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_7, 7, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 7, 3, 1, 1);

        checkBox_5 = new QCheckBox(SolutionsGBX);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));

        gridLayout_2->addWidget(checkBox_5, 8, 0, 1, 1);

        checkBox_10 = new QCheckBox(SolutionsGBX);
        checkBox_10->setObjectName(QStringLiteral("checkBox_10"));

        gridLayout_2->addWidget(checkBox_10, 8, 3, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_6, 9, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 9, 3, 1, 1);

        SeleclAllPB = new QPushButton(SolutionsGBX);
        SeleclAllPB->setObjectName(QStringLiteral("SeleclAllPB"));

        gridLayout_2->addWidget(SeleclAllPB, 10, 0, 1, 1);

        DeseleclAllPB = new QPushButton(SolutionsGBX);
        DeseleclAllPB->setObjectName(QStringLiteral("DeseleclAllPB"));

        gridLayout_2->addWidget(DeseleclAllPB, 10, 3, 1, 1);

        StartPrebuildPB = new QPushButton(SolutionsGBX);
        StartPrebuildPB->setObjectName(QStringLiteral("StartPrebuildPB"));

        gridLayout_2->addWidget(StartPrebuildPB, 11, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(68, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 11, 1, 1, 2);

        BuildAllPB = new QPushButton(SolutionsGBX);
        BuildAllPB->setObjectName(QStringLiteral("BuildAllPB"));

        gridLayout_2->addWidget(BuildAllPB, 11, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(178, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 10, 1, 1, 2);

        checkBox_3 = new QCheckBox(SolutionsGBX);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        gridLayout_2->addWidget(checkBox_3, 4, 0, 1, 1);

        IT2BusinessCKB = new QCheckBox(SolutionsGBX);
        IT2BusinessCKB->setObjectName(QStringLiteral("IT2BusinessCKB"));

        gridLayout_2->addWidget(IT2BusinessCKB, 2, 0, 1, 1);


        gridLayout_3->addWidget(SolutionsGBX, 0, 1, 3, 2);

        verticalSpacer_11 = new QSpacerItem(20, 24, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_11, 1, 0, 1, 1);

        RunIT2GBX = new QGroupBox(centralWidget);
        RunIT2GBX->setObjectName(QStringLiteral("RunIT2GBX"));
        gridLayout_4 = new QGridLayout(RunIT2GBX);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        RunAppServerLabel = new QLabel(RunIT2GBX);
        RunAppServerLabel->setObjectName(QStringLiteral("RunAppServerLabel"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        RunAppServerLabel->setFont(font1);

        gridLayout_4->addWidget(RunAppServerLabel, 0, 0, 1, 1);

        StartAppServerPB = new QPushButton(RunIT2GBX);
        StartAppServerPB->setObjectName(QStringLiteral("StartAppServerPB"));

        gridLayout_4->addWidget(StartAppServerPB, 0, 1, 1, 1);

        StopAppServerPB = new QPushButton(RunIT2GBX);
        StopAppServerPB->setObjectName(QStringLiteral("StopAppServerPB"));

        gridLayout_4->addWidget(StopAppServerPB, 0, 2, 1, 1);

        StartWorkStationPB = new QPushButton(RunIT2GBX);
        StartWorkStationPB->setObjectName(QStringLiteral("StartWorkStationPB"));

        gridLayout_4->addWidget(StartWorkStationPB, 1, 1, 1, 1);

        StopWorkStationPB = new QPushButton(RunIT2GBX);
        StopWorkStationPB->setObjectName(QStringLiteral("StopWorkStationPB"));

        gridLayout_4->addWidget(StopWorkStationPB, 1, 2, 1, 1);

        RunWorkstationLabel = new QLabel(RunIT2GBX);
        RunWorkstationLabel->setObjectName(QStringLiteral("RunWorkstationLabel"));
        RunWorkstationLabel->setFont(font1);

        gridLayout_4->addWidget(RunWorkstationLabel, 1, 0, 1, 1);


        gridLayout_3->addWidget(RunIT2GBX, 2, 0, 1, 1);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line, 3, 0, 1, 3);

        horizontalSpacer_3 = new QSpacerItem(644, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 4, 0, 1, 2);

        ClosePB = new QPushButton(centralWidget);
        ClosePB->setObjectName(QStringLiteral("ClosePB"));

        gridLayout_3->addWidget(ClosePB, 4, 2, 1, 1);

        IT2QtBuildToolClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(IT2QtBuildToolClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 705, 22));
        IT2QtBuildToolClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(IT2QtBuildToolClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        IT2QtBuildToolClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(IT2QtBuildToolClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        IT2QtBuildToolClass->setStatusBar(statusBar);

        retranslateUi(IT2QtBuildToolClass);

        QMetaObject::connectSlotsByName(IT2QtBuildToolClass);
    } // setupUi

    void retranslateUi(QMainWindow *IT2QtBuildToolClass)
    {
        IT2QtBuildToolClass->setWindowTitle(QApplication::translate("IT2QtBuildToolClass", "IT2QtBuildTool", nullptr));
        ConfigGBX->setTitle(QApplication::translate("IT2QtBuildToolClass", "Configuration", nullptr));
        DBServerLabel->setText(QApplication::translate("IT2QtBuildToolClass", "Database Server:", nullptr));
#ifndef QT_NO_TOOLTIP
        DBServerEdit->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        AppServerLabel->setText(QApplication::translate("IT2QtBuildToolClass", "Application Server:", nullptr));
#ifndef QT_NO_TOOLTIP
        AppServerEdit->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        WorkStationLabel->setText(QApplication::translate("IT2QtBuildToolClass", "Workstation:", nullptr));
#ifndef QT_NO_TOOLTIP
        WorkStationEdit->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        RootFolderLabel->setText(QApplication::translate("IT2QtBuildToolClass", "Root folder:", nullptr));
#ifndef QT_NO_TOOLTIP
        RootFolderEdit->setToolTip(QApplication::translate("IT2QtBuildToolClass", "Root folder of source code", nullptr));
#endif // QT_NO_TOOLTIP
        PrebuildLabel->setText(QApplication::translate("IT2QtBuildToolClass", "Prebuild folder:", nullptr));
#ifndef QT_NO_TOOLTIP
        PrebuildFolderEdit->setToolTip(QApplication::translate("IT2QtBuildToolClass", "Setup Prebuild folder", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        SavePB->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        SavePB->setText(QApplication::translate("IT2QtBuildToolClass", "Save", nullptr));
#ifndef QT_NO_TOOLTIP
        ResetPB->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        ResetPB->setText(QApplication::translate("IT2QtBuildToolClass", "Reset", nullptr));
#ifndef QT_NO_TOOLTIP
        DefaultPB->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        DefaultPB->setText(QApplication::translate("IT2QtBuildToolClass", "Default", nullptr));
#ifndef QT_NO_TOOLTIP
        ClearPB->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        ClearPB->setText(QApplication::translate("IT2QtBuildToolClass", "Clear", nullptr));
        SolutionsGBX->setTitle(QApplication::translate("IT2QtBuildToolClass", "IT2 Solutions", nullptr));
#ifndef QT_NO_TOOLTIP
        IT2ParserCKB->setToolTip(QApplication::translate("IT2QtBuildToolClass", "Parser solution", nullptr));
#endif // QT_NO_TOOLTIP
        IT2ParserCKB->setText(QApplication::translate("IT2QtBuildToolClass", "IT2 Parser", nullptr));
        checkBox_6->setText(QApplication::translate("IT2QtBuildToolClass", "Mail API (MAPI)", nullptr));
        checkBox_7->setText(QApplication::translate("IT2QtBuildToolClass", "CheckBox", nullptr));
        checkBox_8->setText(QApplication::translate("IT2QtBuildToolClass", "CheckBox", nullptr));
        checkBox_4->setText(QApplication::translate("IT2QtBuildToolClass", "SCMSource", nullptr));
        checkBox_9->setText(QApplication::translate("IT2QtBuildToolClass", "CheckBox", nullptr));
        checkBox_5->setText(QApplication::translate("IT2QtBuildToolClass", "IT2Source", nullptr));
        checkBox_10->setText(QApplication::translate("IT2QtBuildToolClass", "CheckBox", nullptr));
        SeleclAllPB->setText(QApplication::translate("IT2QtBuildToolClass", "Select All", nullptr));
        DeseleclAllPB->setText(QApplication::translate("IT2QtBuildToolClass", "Deselect All", nullptr));
        StartPrebuildPB->setText(QApplication::translate("IT2QtBuildToolClass", "Start Prebuild", nullptr));
#ifndef QT_NO_TOOLTIP
        BuildAllPB->setToolTip(QApplication::translate("IT2QtBuildToolClass", "Build all selected solutions...", nullptr));
#endif // QT_NO_TOOLTIP
        BuildAllPB->setText(QApplication::translate("IT2QtBuildToolClass", "Build All", nullptr));
        checkBox_3->setText(QApplication::translate("IT2QtBuildToolClass", "Crystal Report", nullptr));
        IT2BusinessCKB->setText(QApplication::translate("IT2QtBuildToolClass", "IT2 Business", nullptr));
        RunIT2GBX->setTitle(QApplication::translate("IT2QtBuildToolClass", "Run IT2", nullptr));
        RunAppServerLabel->setText(QApplication::translate("IT2QtBuildToolClass", "Application Server", nullptr));
        StartAppServerPB->setText(QApplication::translate("IT2QtBuildToolClass", "Start", nullptr));
        StopAppServerPB->setText(QApplication::translate("IT2QtBuildToolClass", "Stop", nullptr));
        StartWorkStationPB->setText(QApplication::translate("IT2QtBuildToolClass", "Start", nullptr));
        StopWorkStationPB->setText(QApplication::translate("IT2QtBuildToolClass", "Stop", nullptr));
        RunWorkstationLabel->setText(QApplication::translate("IT2QtBuildToolClass", "Workstation", nullptr));
#ifndef QT_NO_TOOLTIP
        ClosePB->setToolTip(QApplication::translate("IT2QtBuildToolClass", "Close build tool", nullptr));
#endif // QT_NO_TOOLTIP
        ClosePB->setText(QApplication::translate("IT2QtBuildToolClass", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IT2QtBuildToolClass: public Ui_IT2QtBuildToolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IT2QTBUILDTOOL_H
