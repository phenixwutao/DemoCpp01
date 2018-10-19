#include "stdafx.h"
#include "IT2QtBuildTool.h"

IT2QtBuildTool::IT2QtBuildTool(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //this->setBaseSize(1650, 1350);
    this->setFixedSize(1630, 950);
}


void IT2QtBuildTool::on_DBServerEdit_editingFinished()
{
  m_DBServerName = ui.DBServerEdit->text();
}

void IT2QtBuildTool::on_AppServerEdit_editingFinished()
{
  m_AppServerName = ui.AppServerEdit->text();
}

void IT2QtBuildTool::on_WorkStationEdit_editingFinished()
{
  m_WorkstationName = ui.WorkStationEdit->text();
}

void IT2QtBuildTool::on_RootFolderEdit_editingFinished()
{
  m_RootFolderName = ui.RootFolderEdit->text();
}

void IT2QtBuildTool::on_PrebuildFolderEdit_editingFinished() 
{
  m_PrebuildFolderName = ui.PrebuildFolderEdit->text();
}

void IT2QtBuildTool::on_SavePB_clicked()
{
  if (CheckAllConfiguration() == false)
    return;

  m_DBServerName = ui.DBServerEdit->text();
  m_AppServerName = ui.AppServerEdit->text();
  m_WorkstationName = ui.WorkStationEdit->text();
  m_RootFolderName = ui.RootFolderEdit->text();
  m_PrebuildFolderName = ui.PrebuildFolderEdit->text();
  SaveFile();
}

void IT2QtBuildTool::on_ResetPB_clicked()
{
  LoadFile();
  ui.DBServerEdit->setText(m_DBServerName);
  ui.AppServerEdit->setText(m_AppServerName);
  ui.WorkStationEdit->setText(m_WorkstationName);
  ui.RootFolderEdit->setText(m_RootFolderName);
  ui.PrebuildFolderEdit->setText(m_PrebuildFolderName);
}

void IT2QtBuildTool::on_ClearPB_clicked()
{
  QString sTitle = "DB Server: "   + m_DBServerName + "; ";
  sTitle += "Application Server: " + m_AppServerName + "; ";
  sTitle += "Workstation: "        + m_WorkstationName + "\n";
  sTitle += "Root folder: "        + m_RootFolderName + "; ";
  sTitle += "Prebuild folder: "    + m_PrebuildFolderName;
  QMessageBox msg(QMessageBox::Icon::Warning, "Clear configuration?", sTitle,
                  QMessageBox::Yes | QMessageBox::No);
  auto wAnswer = msg.exec();
  if (wAnswer == QMessageBox::Yes)
  {
    ui.DBServerEdit->clear();
    ui.AppServerEdit->clear();
    ui.WorkStationEdit->clear();
    ui.RootFolderEdit->clear();
    ui.PrebuildFolderEdit->clear();
  }
}


void IT2QtBuildTool::on_DefaultPB_clicked()
{
}

void IT2QtBuildTool::on_ClosePB_clicked()
{
  this->close();
}


void IT2QtBuildTool::SaveFile()
{
}

void IT2QtBuildTool::LoadFile()
{
}

bool IT2QtBuildTool::CheckAllConfiguration()
{
  if (ui.DBServerEdit->text().isEmpty() ||
    ui.AppServerEdit->text().isEmpty() ||
    ui.WorkStationEdit->text().isEmpty() ||
    ui.RootFolderEdit->text().isEmpty() ||
    ui.PrebuildFolderEdit->text().isEmpty())
  {
    QString sTitle("Please check empty field");
    QMessageBox msg(QMessageBox::Icon::Warning, "Warning", sTitle, QMessageBox::Ok);
    auto wAnswer = msg.exec();
    if (wAnswer == QMessageBox::Ok)
    {
      if (ui.DBServerEdit->text().isEmpty())
        ui.DBServerEdit->setFocus();
      else if (ui.AppServerEdit->text().isEmpty())
        ui.AppServerEdit->setFocus();
      else if (ui.WorkStationEdit->text().isEmpty())
        ui.WorkStationEdit->setFocus();
      else if (ui.RootFolderEdit->text().isEmpty())
        ui.RootFolderEdit->setFocus();
      else if (ui.PrebuildFolderEdit->text().isEmpty())
        ui.PrebuildFolderEdit->setFocus();
    }
    return false;
  }
  else
    return true;
}
