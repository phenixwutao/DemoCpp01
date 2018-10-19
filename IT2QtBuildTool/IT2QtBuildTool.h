#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_IT2QtBuildTool.h"

class IT2QtBuildTool : public QMainWindow
{
    Q_OBJECT

public:
    IT2QtBuildTool(QWidget *parent = Q_NULLPTR);

private:
  void SaveFile();
  void LoadFile();
  bool CheckAllConfiguration();

private:
    Ui::IT2QtBuildToolClass ui;
    QString m_DBServerName{};
    QString m_AppServerName{};
    QString m_WorkstationName{};
    QString m_RootFolderName{};
    QString m_PrebuildFolderName{};

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
};
