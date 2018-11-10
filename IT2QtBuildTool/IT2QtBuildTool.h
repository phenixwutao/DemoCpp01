#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_IT2QtBuildTool.h"

#define SOLUTION_IT2PARSERS     0x000000001
#define SOLUTION_IT2BUSINESS    0x000000002
#define SOLUTION_AXMSCHART      0x000000004
#define SOLUTION_CRYSTALREPORTS 0x000000008
#define SOLUTION_FONETCLIENT    0x000000010
#define SOLUTION_PORTEBAM       0x000000020
#define SOLUTION_IT2MAPI        0x000000040
#define SOLUTION_IMPORTSERVICES 0x000000080
#define SOLUTION_SCMSOURCE      0x000000100
#define SOLUTION_IT2SOURCE      0x000000200
#define SOLUTION_IT2COMPONENTS  0x000000400
#define SOLUTION_AUTOMATIONS    0x000000800
#define SOLUTION_SUPPORTTOOLS   0x000001000
#define SOLUTION_SCMTEST        0x000002000

class IT2QtBuildTool : public QMainWindow
{
    Q_OBJECT

public:
    IT2QtBuildTool(QWidget *parent = Q_NULLPTR);

private:
  bool CheckAllConfiguration();
  void TickAllSolutions(bool fCheck);
  void ClearAllConfig();
  void SetAllConfig();
  void GetAllConfig();
  bool NeedBuildSolutions();
  bool CheckConfigFileExist(bool fReady);
  void ReadConfigFile();
  void SaveConfigFile();
  void GetMaskFromCheckBoxes();
  void SetMaskToCheckBoxes();

private:
    Ui::IT2QtBuildToolClass ui;
    QString m_DBServerName{};
    QString m_AppServerName{};
    QString m_WorkstationName{};
    QString m_RootFolderName{};
    QString m_PrebuildFolderName{};
    QString m_buildMode{"Debug"};
    int     m_MaskBuild = 0;
    const static QString s_configFilename;
    const static QString s_scriptFilename;

private slots:
    void on_DBServerEdit_editingFinished();
    void on_AppServerEdit_editingFinished();
    void on_WorkStationEdit_editingFinished();
    void on_RootFolderEdit_editingFinished();
    void on_PrebuildFolderEdit_editingFinished();

    void on_SavePB_clicked();
    void on_ResetPB_clicked();
    void on_ClearPB_clicked();
    void on_DefaultPB_clicked();
    void on_ClosePB_clicked();


    void on_SelectAllPB_clicked();
    void on_DeselectAllPB_clicked();
    void on_BuildAllPB_clicked();
    void on_RootDirSelectPB_clicked();
    void on_BuildOptionCBX_currentIndexChanged(const QString & text);
};
