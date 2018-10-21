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
    QLabel *AppServerLabel;
    QSpacerItem *verticalSpacer_13;
    QLineEdit *DBServerEdit;
    QSpacerItem *verticalSpacer_12;
    QLineEdit *AppServerEdit;
    QLabel *DBServerLabel;
    QLabel *PrebuildLabel;
    QPushButton *SavePB;
    QSpacerItem *verticalSpacer_16;
    QLabel *RootFolderLabel;
    QSpacerItem *horizontalSpacer_9;
    QLabel *WorkStationLabel;
    QSpacerItem *verticalSpacer_14;
    QLineEdit *RootFolderEdit;
    QLineEdit *PrebuildFolderEdit;
    QSpacerItem *verticalSpacer_15;
    QLineEdit *WorkStationEdit;
    QPushButton *DefaultPB;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *ClearPB;
    QPushButton *ResetPB;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *RootDirSelectPB;
    QGroupBox *SolutionsGBX;
    QGridLayout *gridLayout_2;
    QCheckBox *MAPICKB;
    QPushButton *SelectAllPB;
    QSpacerItem *horizontalSpacer;
    QCheckBox *SCMTestCKB;
    QPushButton *BuildAllPB;
    QPushButton *MDCResetPB;
    QPushButton *DeselectAllPB;
    QPushButton *IDAllocatorPB;
    QPushButton *StartPrebuildPB;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *IT2ParserCKB;
    QCheckBox *IT2BusinessCKB;
    QCheckBox *SCMSourceCKB;
    QCheckBox *AXMSChartCKB;
    QCheckBox *CrystalReportCKB;
    QCheckBox *IT2ComponentsCKB;
    QCheckBox *AutomationCKB;
    QCheckBox *FONETCKB;
    QCheckBox *IT2SourceCKB;
    QCheckBox *EBAMCKB;
    QCheckBox *IT2SupportToolsCKB;
    QCheckBox *ImportServiceCKB;
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
        AppServerLabel = new QLabel(ConfigGBX);
        AppServerLabel->setObjectName(QStringLiteral("AppServerLabel"));

        gridLayout->addWidget(AppServerLabel, 2, 0, 1, 2);

        verticalSpacer_13 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_13, 3, 2, 1, 2);

        DBServerEdit = new QLineEdit(ConfigGBX);
        DBServerEdit->setObjectName(QStringLiteral("DBServerEdit"));

        gridLayout->addWidget(DBServerEdit, 0, 2, 1, 5);

        verticalSpacer_12 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_12, 1, 2, 1, 2);

        AppServerEdit = new QLineEdit(ConfigGBX);
        AppServerEdit->setObjectName(QStringLiteral("AppServerEdit"));

        gridLayout->addWidget(AppServerEdit, 2, 2, 1, 5);

        DBServerLabel = new QLabel(ConfigGBX);
        DBServerLabel->setObjectName(QStringLiteral("DBServerLabel"));

        gridLayout->addWidget(DBServerLabel, 0, 0, 1, 2);

        PrebuildLabel = new QLabel(ConfigGBX);
        PrebuildLabel->setObjectName(QStringLiteral("PrebuildLabel"));

        gridLayout->addWidget(PrebuildLabel, 8, 0, 1, 1);

        SavePB = new QPushButton(ConfigGBX);
        SavePB->setObjectName(QStringLiteral("SavePB"));

        gridLayout->addWidget(SavePB, 10, 0, 1, 1);

        verticalSpacer_16 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_16, 9, 2, 1, 2);

        RootFolderLabel = new QLabel(ConfigGBX);
        RootFolderLabel->setObjectName(QStringLiteral("RootFolderLabel"));

        gridLayout->addWidget(RootFolderLabel, 6, 0, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(17, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 10, 1, 1, 1);

        WorkStationLabel = new QLabel(ConfigGBX);
        WorkStationLabel->setObjectName(QStringLiteral("WorkStationLabel"));

        gridLayout->addWidget(WorkStationLabel, 4, 0, 1, 1);

        verticalSpacer_14 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_14, 5, 2, 1, 2);

        RootFolderEdit = new QLineEdit(ConfigGBX);
        RootFolderEdit->setObjectName(QStringLiteral("RootFolderEdit"));

        gridLayout->addWidget(RootFolderEdit, 6, 2, 1, 5);

        PrebuildFolderEdit = new QLineEdit(ConfigGBX);
        PrebuildFolderEdit->setObjectName(QStringLiteral("PrebuildFolderEdit"));
        PrebuildFolderEdit->setEnabled(true);
        PrebuildFolderEdit->setReadOnly(true);

        gridLayout->addWidget(PrebuildFolderEdit, 8, 2, 1, 5);

        verticalSpacer_15 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_15, 7, 2, 1, 2);

        WorkStationEdit = new QLineEdit(ConfigGBX);
        WorkStationEdit->setObjectName(QStringLiteral("WorkStationEdit"));

        gridLayout->addWidget(WorkStationEdit, 4, 2, 1, 5);

        DefaultPB = new QPushButton(ConfigGBX);
        DefaultPB->setObjectName(QStringLiteral("DefaultPB"));

        gridLayout->addWidget(DefaultPB, 10, 4, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(17, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 10, 3, 1, 1);

        ClearPB = new QPushButton(ConfigGBX);
        ClearPB->setObjectName(QStringLiteral("ClearPB"));

        gridLayout->addWidget(ClearPB, 10, 6, 1, 1);

        ResetPB = new QPushButton(ConfigGBX);
        ResetPB->setObjectName(QStringLiteral("ResetPB"));

        gridLayout->addWidget(ResetPB, 10, 2, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(17, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 10, 5, 1, 1);

        RootDirSelectPB = new QPushButton(ConfigGBX);
        RootDirSelectPB->setObjectName(QStringLiteral("RootDirSelectPB"));

        gridLayout->addWidget(RootDirSelectPB, 7, 6, 1, 1);


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
        MAPICKB = new QCheckBox(SolutionsGBX);
        MAPICKB->setObjectName(QStringLiteral("MAPICKB"));

        gridLayout_2->addWidget(MAPICKB, 6, 0, 1, 1);

        SelectAllPB = new QPushButton(SolutionsGBX);
        SelectAllPB->setObjectName(QStringLiteral("SelectAllPB"));

        gridLayout_2->addWidget(SelectAllPB, 7, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 9, 1, 1, 1);

        SCMTestCKB = new QCheckBox(SolutionsGBX);
        SCMTestCKB->setObjectName(QStringLiteral("SCMTestCKB"));

        gridLayout_2->addWidget(SCMTestCKB, 6, 1, 1, 2);

        BuildAllPB = new QPushButton(SolutionsGBX);
        BuildAllPB->setObjectName(QStringLiteral("BuildAllPB"));

        gridLayout_2->addWidget(BuildAllPB, 8, 2, 1, 1);

        MDCResetPB = new QPushButton(SolutionsGBX);
        MDCResetPB->setObjectName(QStringLiteral("MDCResetPB"));

        gridLayout_2->addWidget(MDCResetPB, 9, 0, 1, 1);

        DeselectAllPB = new QPushButton(SolutionsGBX);
        DeselectAllPB->setObjectName(QStringLiteral("DeselectAllPB"));

        gridLayout_2->addWidget(DeselectAllPB, 7, 2, 1, 1);

        IDAllocatorPB = new QPushButton(SolutionsGBX);
        IDAllocatorPB->setObjectName(QStringLiteral("IDAllocatorPB"));

        gridLayout_2->addWidget(IDAllocatorPB, 9, 2, 1, 1);

        StartPrebuildPB = new QPushButton(SolutionsGBX);
        StartPrebuildPB->setObjectName(QStringLiteral("StartPrebuildPB"));

        gridLayout_2->addWidget(StartPrebuildPB, 8, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(68, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 8, 1, 1, 1);

        IT2ParserCKB = new QCheckBox(SolutionsGBX);
        IT2ParserCKB->setObjectName(QStringLiteral("IT2ParserCKB"));

        gridLayout_2->addWidget(IT2ParserCKB, 0, 0, 1, 1);

        IT2BusinessCKB = new QCheckBox(SolutionsGBX);
        IT2BusinessCKB->setObjectName(QStringLiteral("IT2BusinessCKB"));

        gridLayout_2->addWidget(IT2BusinessCKB, 1, 0, 1, 1);

        SCMSourceCKB = new QCheckBox(SolutionsGBX);
        SCMSourceCKB->setObjectName(QStringLiteral("SCMSourceCKB"));

        gridLayout_2->addWidget(SCMSourceCKB, 1, 1, 1, 2);

        AXMSChartCKB = new QCheckBox(SolutionsGBX);
        AXMSChartCKB->setObjectName(QStringLiteral("AXMSChartCKB"));

        gridLayout_2->addWidget(AXMSChartCKB, 2, 0, 1, 1);

        CrystalReportCKB = new QCheckBox(SolutionsGBX);
        CrystalReportCKB->setObjectName(QStringLiteral("CrystalReportCKB"));

        gridLayout_2->addWidget(CrystalReportCKB, 3, 0, 1, 1);

        IT2ComponentsCKB = new QCheckBox(SolutionsGBX);
        IT2ComponentsCKB->setObjectName(QStringLiteral("IT2ComponentsCKB"));

        gridLayout_2->addWidget(IT2ComponentsCKB, 3, 1, 1, 2);

        AutomationCKB = new QCheckBox(SolutionsGBX);
        AutomationCKB->setObjectName(QStringLiteral("AutomationCKB"));

        gridLayout_2->addWidget(AutomationCKB, 4, 1, 1, 2);

        FONETCKB = new QCheckBox(SolutionsGBX);
        FONETCKB->setObjectName(QStringLiteral("FONETCKB"));

        gridLayout_2->addWidget(FONETCKB, 4, 0, 1, 1);

        IT2SourceCKB = new QCheckBox(SolutionsGBX);
        IT2SourceCKB->setObjectName(QStringLiteral("IT2SourceCKB"));

        gridLayout_2->addWidget(IT2SourceCKB, 2, 1, 1, 2);

        EBAMCKB = new QCheckBox(SolutionsGBX);
        EBAMCKB->setObjectName(QStringLiteral("EBAMCKB"));

        gridLayout_2->addWidget(EBAMCKB, 5, 0, 1, 1);

        IT2SupportToolsCKB = new QCheckBox(SolutionsGBX);
        IT2SupportToolsCKB->setObjectName(QStringLiteral("IT2SupportToolsCKB"));

        gridLayout_2->addWidget(IT2SupportToolsCKB, 5, 1, 1, 2);

        ImportServiceCKB = new QCheckBox(SolutionsGBX);
        ImportServiceCKB->setObjectName(QStringLiteral("ImportServiceCKB"));

        gridLayout_2->addWidget(ImportServiceCKB, 0, 1, 1, 2);


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
        AppServerLabel->setText(QApplication::translate("IT2QtBuildToolClass", "Application Server:", nullptr));
#ifndef QT_NO_TOOLTIP
        DBServerEdit->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        AppServerEdit->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        DBServerLabel->setText(QApplication::translate("IT2QtBuildToolClass", "Database Server:", nullptr));
        PrebuildLabel->setText(QApplication::translate("IT2QtBuildToolClass", "Prebuild folder:", nullptr));
#ifndef QT_NO_TOOLTIP
        SavePB->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        SavePB->setText(QApplication::translate("IT2QtBuildToolClass", "Save", nullptr));
        RootFolderLabel->setText(QApplication::translate("IT2QtBuildToolClass", "Root folder:", nullptr));
        WorkStationLabel->setText(QApplication::translate("IT2QtBuildToolClass", "Workstation:", nullptr));
#ifndef QT_NO_TOOLTIP
        RootFolderEdit->setToolTip(QApplication::translate("IT2QtBuildToolClass", "Root folder of source code", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        PrebuildFolderEdit->setToolTip(QApplication::translate("IT2QtBuildToolClass", "Setup Prebuild folder", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        WorkStationEdit->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        DefaultPB->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        DefaultPB->setText(QApplication::translate("IT2QtBuildToolClass", "Default", nullptr));
#ifndef QT_NO_TOOLTIP
        ClearPB->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        ClearPB->setText(QApplication::translate("IT2QtBuildToolClass", "Clear", nullptr));
#ifndef QT_NO_TOOLTIP
        ResetPB->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        ResetPB->setText(QApplication::translate("IT2QtBuildToolClass", "Reset", nullptr));
        RootDirSelectPB->setText(QApplication::translate("IT2QtBuildToolClass", "Select...", nullptr));
        SolutionsGBX->setTitle(QApplication::translate("IT2QtBuildToolClass", "IT2 Solutions", nullptr));
        MAPICKB->setText(QApplication::translate("IT2QtBuildToolClass", "IT2MAPI", nullptr));
        SelectAllPB->setText(QApplication::translate("IT2QtBuildToolClass", "Select All", nullptr));
        SCMTestCKB->setText(QApplication::translate("IT2QtBuildToolClass", "SCMTest", nullptr));
#ifndef QT_NO_TOOLTIP
        BuildAllPB->setToolTip(QApplication::translate("IT2QtBuildToolClass", "Build all selected solutions...", nullptr));
#endif // QT_NO_TOOLTIP
        BuildAllPB->setText(QApplication::translate("IT2QtBuildToolClass", "Build All", nullptr));
        MDCResetPB->setText(QApplication::translate("IT2QtBuildToolClass", "MDC Reset", nullptr));
        DeselectAllPB->setText(QApplication::translate("IT2QtBuildToolClass", "Deselect All", nullptr));
        IDAllocatorPB->setText(QApplication::translate("IT2QtBuildToolClass", "ID Allocator", nullptr));
        StartPrebuildPB->setText(QApplication::translate("IT2QtBuildToolClass", "Start Prebuild", nullptr));
#ifndef QT_NO_TOOLTIP
        IT2ParserCKB->setToolTip(QApplication::translate("IT2QtBuildToolClass", "Parser solution", nullptr));
#endif // QT_NO_TOOLTIP
        IT2ParserCKB->setText(QApplication::translate("IT2QtBuildToolClass", "IT2Parsers", nullptr));
        IT2BusinessCKB->setText(QApplication::translate("IT2QtBuildToolClass", "IT2Business", nullptr));
        SCMSourceCKB->setText(QApplication::translate("IT2QtBuildToolClass", "SCMSource", nullptr));
        AXMSChartCKB->setText(QApplication::translate("IT2QtBuildToolClass", "AxMSChart", nullptr));
        CrystalReportCKB->setText(QApplication::translate("IT2QtBuildToolClass", "CrystalReports", nullptr));
        IT2ComponentsCKB->setText(QApplication::translate("IT2QtBuildToolClass", "IT2Components", nullptr));
        AutomationCKB->setText(QApplication::translate("IT2QtBuildToolClass", "Automations", nullptr));
        FONETCKB->setText(QApplication::translate("IT2QtBuildToolClass", "FONET Client", nullptr));
        IT2SourceCKB->setText(QApplication::translate("IT2QtBuildToolClass", "IT2Source", nullptr));
        EBAMCKB->setText(QApplication::translate("IT2QtBuildToolClass", "PortEBAMSigner", nullptr));
        IT2SupportToolsCKB->setText(QApplication::translate("IT2QtBuildToolClass", "SupportTools", nullptr));
        ImportServiceCKB->setText(QApplication::translate("IT2QtBuildToolClass", "ImportServices", nullptr));
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
