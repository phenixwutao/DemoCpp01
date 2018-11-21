#include "stdafx.h"
#include "IT2QtBuildTool.h"

IT2QtBuildTool::IT2QtBuildTool(QWidget *parent)
    : QMainWindow(parent)
{
  ui.setupUi(this);
  //this->setBaseSize(1650, 1200);
  //this->setFixedSize(1630, 1100);
  on_ResetPB_clicked();
}

const QString IT2QtBuildTool::s_configFilename = "IT2QtBuildTool.config";
const QString IT2QtBuildTool::s_scriptFilename = "IT2QtBuildTool.bat";

void IT2QtBuildTool::on_DBServerEdit_editingFinished()
{
  m_DBServerName = ui.DBServerEdit->text();
}

void IT2QtBuildTool::on_DBNameEdit_editingFinished()
{
  m_DBName = ui.DBNameEdit->text();
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
  m_PrebuildFolderName = m_RootFolderName.append(QDir::separator()).append(R"(SCM_Source)");
  ui.PrebuildFolderEdit->setText(m_PrebuildFolderName);
}

void IT2QtBuildTool::on_PrebuildFolderEdit_editingFinished() 
{
  m_PrebuildFolderName = ui.PrebuildFolderEdit->text();
}

void IT2QtBuildTool::on_SavePB_clicked()
{
  if (CheckAllConfiguration() == false)
    return;

  GetAllConfig();

  if (this->CheckConfigFileExist(false) == false)
    return;

  GetMaskFromCheckBoxes();
  SaveConfigFile();
  NeedBuildSolutions();
}

void IT2QtBuildTool::on_ResetPB_clicked()
{
  if (this->CheckConfigFileExist(true) == false)
    return;

  ReadConfigFile();
  SetAllConfig();

  on_DeselectAllPB_clicked();
  SetMaskToCheckBoxes();
}

void IT2QtBuildTool::on_ClearPB_clicked()
{
  if (m_DBServerName.isEmpty()      == true &&
      m_DBName.isEmpty()            == true &&
      m_AppServerName.isEmpty()     == true &&
      m_WorkstationName.isEmpty()   == true &&
      m_RootFolderName.isEmpty()    == true &&
      m_PrebuildFolderName.isEmpty()== true)
    return;

  QString sTitle = "DB Server: "   + m_DBServerName + "; ";
  sTitle += "DB Name: "            + m_DBName + "; ";
  sTitle += "Application Server: " + m_AppServerName + "; ";
  sTitle += "Workstation: "        + m_WorkstationName + "\n";
  sTitle += "Root folder: "        + m_RootFolderName + "; ";
  sTitle += "Prebuild folder: "    + m_PrebuildFolderName;
  QMessageBox msg(QMessageBox::Icon::Warning, "Clear configuration?", sTitle,
                  QMessageBox::Yes | QMessageBox::No);
  auto wAnswer = msg.exec();
  if (wAnswer == QMessageBox::Yes)
  {
    ClearAllConfig();
    on_DeselectAllPB_clicked();
  }
}


void IT2QtBuildTool::on_DefaultPB_clicked()
{
  if (this->CheckConfigFileExist(true) == true)
  {
    ReadConfigFile();
    SetAllConfig();
  }
  on_SelectAllPB_clicked();
}

void IT2QtBuildTool::on_ClosePB_clicked()
{
  if (CheckAllConfiguration() == false)
    return;

  if (CheckConfigFileExist(false) == false)
    return;

  GetMaskFromCheckBoxes();
  SaveConfigFile();

  NeedBuildSolutions();

  this->close();
}

void IT2QtBuildTool::on_SelectAllPB_clicked()
{
  TickAllSolutions(true);
}

void IT2QtBuildTool::on_DeselectAllPB_clicked()
{
  TickAllSolutions(false);
}


void IT2QtBuildTool::on_BuildAllPB_clicked()
{
  if (CheckAllConfiguration() == false)
    return;

  if (NeedBuildSolutions() == false)
  {
    QMessageBox msg(QMessageBox::Icon::Information, "Build Information", "Please select solution(s) to build", QMessageBox::Ok);
    msg.exec();
    return;
  }

  //QString script(R"(dir d:\wutao)");
  QString sCommand = R"(call )" + s_scriptFilename;
  auto wExit = system(sCommand.toStdString().c_str());

  QString strText("Success");
  QMessageBox::Icon iconResult = QMessageBox::Icon::Information;
  if (wExit != EXIT_SUCCESS)
  {
    strText = "Failed with error";
    iconResult = QMessageBox::Icon::Critical;
  }
  QMessageBox msg(iconResult, "Build ...", strText, QMessageBox::Ok);
  msg.exec();
}

void IT2QtBuildTool::on_MDCResetPB_clicked()
{
  GetAllConfig();

  if (CheckAllConfiguration() == false)
    return;

  QString sCommand = m_RootFolderName;
  sCommand.append(QDir::separator()).append("IT2Source")
          .append(QDir::separator()).append("Bin")
          .append(QDir::separator()).append(m_buildMode)
          .append(QDir::separator()).append("MDCNEWDB.exe ").append(m_DBServerName).append(" ")
          .append(m_DBName).append(" ").append(" IT2_BOFA M byPassVersionCheck");
  auto wExit = system(sCommand.toStdString().c_str());

  QString strText("MDC Reset Success");
  QMessageBox::Icon iconResult = QMessageBox::Icon::Information;
  if (wExit != EXIT_SUCCESS)
  {
    strText = "MDC Reset Failed with error";
    iconResult = QMessageBox::Icon::Critical;
  }
  QMessageBox msg(iconResult, "MDCReset", strText, QMessageBox::Ok);
  msg.exec();
}


void IT2QtBuildTool::on_RootDirSelectPB_clicked()
{
  QString dir = QFileDialog::getExistingDirectory(this, tr("Select Root Directory"),
    m_RootFolderName, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  if (dir.isEmpty() == false)
  {
    m_RootFolderName = QDir::toNativeSeparators(dir);
    ui.RootFolderEdit->setText(m_RootFolderName);
    m_PrebuildFolderName = m_RootFolderName.append(QDir::separator()).append(R"(SCM_Source)");
    ui.PrebuildFolderEdit->setText(m_PrebuildFolderName);
  }
}

void IT2QtBuildTool::on_BuildOptionCBX_currentIndexChanged(const QString & text)
{
  m_buildMode = text;
}

void IT2QtBuildTool::StartCommand(const QString& sTitle, const QString& sCommand)
{
  auto wExit = system(sCommand.toStdString().c_str());
  if (wExit != EXIT_SUCCESS)
  {
    QString strText = "Failed with error";
    QMessageBox::Icon iconResult = QMessageBox::Icon::Critical;
    QMessageBox msg(iconResult, sTitle, strText, QMessageBox::Ok);
    msg.exec();
  }
}

void IT2QtBuildTool::on_StartAppServerPB_clicked()
{
  GetAllConfig();

  if (CheckAllConfiguration() == false)
    return;

  // change to folder and start command
  QString path("cd /d ");
  path.append(m_RootFolderName).append(QDir::separator())
    .append(R"(IT2Source)").append(QDir::separator())
    .append(R"(Bin)").append(QDir::separator())
    .append(m_buildMode).append(QDir::separator());

  QString cmd = path.append(R"( && )").append(R"(start )");
  cmd.append(m_RootFolderName).append(QDir::separator())
    .append(R"(IT2Source)").append(QDir::separator())
    .append(R"(Bin)").append(QDir::separator())
    .append(m_buildMode).append(QDir::separator()).append(R"(IT2SRVM.exe )");
  cmd.append(m_AppServerName).append(" ")
    .append(m_DBServerName).append(" ")
    .append(m_DBName);
  IT2QtBuildTool::StartCommand("AppServer", cmd);
}

void IT2QtBuildTool::on_StopAppServerPB_clicked()
{
  GetAllConfig();

  if (CheckAllConfiguration() == false)
    return;

  QString cmd = R"(@taskkill /IM it2srvm.exe /F )";
  IT2QtBuildTool::StartCommand("AppServer", cmd);
}

void IT2QtBuildTool::on_StartWorkStationPB_clicked()
{
  GetAllConfig();

  if (CheckAllConfiguration() == false)
    return;

  // BCG Lib path
  QString sBCGLib = R"(set path=%PATH%;)";
  sBCGLib.append(m_RootFolderName).append(QDir::separator()).append(R"(ThirdParty\Libs\BCGCBPro)");

  // change to folder and start command
  QString path("cd /d ");
  path.append(m_RootFolderName).append(QDir::separator())
    .append(R"(IT2Source)").append(QDir::separator())
    .append(R"(Bin)").append(QDir::separator())
    .append(m_buildMode).append(QDir::separator());

  QString cmd = sBCGLib.append("\n") + path.append(R"( && )").append(R"(start )");
  cmd.append(m_RootFolderName).append(QDir::separator())
    .append(R"(IT2Source)").append(QDir::separator())
    .append(R"(Bin)").append(QDir::separator())
    .append(m_buildMode).append(QDir::separator());
  if(m_buildMode == "Debug")
    cmd.append(R"(IT2StartmD.exe )");
  else
    cmd.append(R"(IT2Startm.exe )");
  cmd.append(m_AppServerName).append(" ")
    .append(m_DBServerName).append(" ")
    .append(m_DBName);
  IT2QtBuildTool::StartCommand("Workstation", cmd);
}

void IT2QtBuildTool::on_StopWorkStationPB_clicked()
{
  GetAllConfig();

  if (CheckAllConfiguration() == false)
    return;

  QString cmd;
  if (m_buildMode == "Debug")
    cmd = R"(@taskkill /IM IT2StartmD.exe /F )";
  else
    cmd = R"(@taskkill /IM IT2Startm.exe /F )";
  IT2QtBuildTool::StartCommand("Workstation", cmd);
}

bool IT2QtBuildTool::CheckAllConfiguration()
{
  if (ui.DBServerEdit->text().isEmpty() ||
    ui.DBNameEdit->text().isEmpty() ||
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
      else if (ui.DBNameEdit->text().isEmpty())
        ui.DBNameEdit->setFocus();
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

void IT2QtBuildTool::TickAllSolutions(bool fCheck)
{
  ui.IT2ParserCKB->setChecked(fCheck);
  ui.IT2BusinessCKB->setChecked(fCheck);
  ui.AXMSChartCKB->setChecked(fCheck);
  ui.CrystalReportCKB->setChecked(fCheck);
  ui.FONETCKB->setChecked(fCheck);
  ui.EBAMCKB->setChecked(fCheck);
  ui.MAPICKB->setChecked(fCheck);
  ui.ImportServiceCKB->setChecked(fCheck);
  ui.SCMSourceCKB->setChecked(fCheck);
  ui.IT2SourceCKB->setChecked(fCheck);
  ui.IT2ComponentsCKB->setChecked(fCheck);
  ui.AutomationCKB->setChecked(fCheck);
  ui.IT2SupportToolsCKB->setChecked(fCheck);
  ui.SCMTestCKB->setChecked(fCheck);
}


void IT2QtBuildTool::ClearAllConfig()
{
  ui.DBServerEdit->clear();
  ui.DBNameEdit->clear();
  ui.AppServerEdit->clear();
  ui.WorkStationEdit->clear();
  ui.RootFolderEdit->clear();
  ui.PrebuildFolderEdit->clear();
  ui.BuildOptionCBX->setCurrentText("Debug");

  m_DBServerName.clear();
  m_DBName.clear();
  m_AppServerName.clear();
  m_WorkstationName.clear();
  m_RootFolderName.clear();
  m_PrebuildFolderName.clear();
  m_buildMode = ui.BuildOptionCBX->currentText();
}

void IT2QtBuildTool::SetAllConfig()
{
  ui.DBServerEdit->setText(m_DBServerName);
  ui.DBNameEdit->setText(m_DBName);
  ui.AppServerEdit->setText(m_AppServerName);
  ui.WorkStationEdit->setText(m_WorkstationName);
  ui.RootFolderEdit->setText(m_RootFolderName);
  ui.PrebuildFolderEdit->setText(m_PrebuildFolderName);
  ui.BuildOptionCBX->setCurrentText(m_buildMode);
}

void IT2QtBuildTool::GetAllConfig()
{
  m_DBServerName = ui.DBServerEdit->text();
  m_DBName = ui.DBNameEdit->text();
  m_AppServerName = ui.AppServerEdit->text();
  m_WorkstationName = ui.WorkStationEdit->text();
  m_RootFolderName = ui.RootFolderEdit->text();
  m_PrebuildFolderName = ui.PrebuildFolderEdit->text();
  m_buildMode = ui.BuildOptionCBX->currentText();
}

bool IT2QtBuildTool::NeedBuildSolutions()
{
  QString strScript;
  QString sQuote = R"(")";
  QString sLineReturn = "\n\n";
  m_buildMode = ui.BuildOptionCBX->currentText();
  strScript.append(R"(set MYOPTION=/p:SkipInvalidConfigurations=true /p:Platform=x64 /p:Configuration=")" + m_buildMode + R"(" /t:build /m:8 /consoleloggerparameters:ErrorsOnly /nologo)").append(sLineReturn);
  QString strOption = R"( %MYOPTION% )";
  QString strMSBuild = R"(MSBuild.exe ")";
  bool fNeedBuild = false;
  if (ui.IT2ParserCKB->isChecked())
  {
    strScript.append(R"(echo Build IT2Parsers.sln)").append(sLineReturn);
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Parsers)").append(QDir::separator()).append(R"(IT2Parsers.sln)");
    strScript.append(sQuote).append(strOption).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.IT2BusinessCKB->isChecked())
  {
    strScript.append(R"(echo Build IT2Business.sln)").append(sLineReturn);
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(IT2Business.sln)");
    strScript.append(sQuote).append(strOption).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.AXMSChartCKB->isChecked())
  {
    strScript.append(R"(echo Build AxMSChart.sln)").append(sLineReturn);
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(AxMSChart)").append(QDir::separator())
      .append(R"(AxMSChart.sln)");
    strScript.append(sQuote).append(strOption).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.CrystalReportCKB->isChecked())
  {
    strScript.append(R"(echo Build CrystalReports.sln)").append(sLineReturn);
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(CrystalReports.sln)");
    strScript.append(sQuote).append(strOption).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.FONETCKB->isChecked())
  {
    strScript.append(R"(echo Build FONET Client.sln)").append(sLineReturn);
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(FONET Client)").append(QDir::separator())
      .append(R"(FONET Client.sln)");
    strScript.append(sQuote).append(strOption).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.EBAMCKB->isChecked())
  {
    strScript.append(R"(echo Build PortEBAMSigner.sln)").append(sLineReturn);
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(IT2Components)").append(QDir::separator())
      .append(R"(EBAM)").append(QDir::separator()).append(R"(PortEBAMSigner.sln)");
    strScript.append(sQuote).append(strOption).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.MAPICKB->isChecked())
  {
    strScript.append(R"(echo Build IT2MAPI.sln)").append(sLineReturn);
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(IT2Components)").append(QDir::separator())
      .append(R"(IT2MAPI)").append(QDir::separator()).append(R"(IT2MAPI.sln)");
    strScript.append(sQuote).append(strOption).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.ImportServiceCKB->isChecked())
  {
    strScript.append(R"(echo Build IT2ImportServices.sln)").append(sLineReturn);
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(IT2ImportServices.sln)");
    strScript.append(sQuote).append(strOption).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.SCMSourceCKB->isChecked())
  {
    strScript.append(R"(echo Build SCMSource.sln)").append(sLineReturn);
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(SCMSource.sln)");
    strScript.append(sQuote).append(strOption).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.IT2SourceCKB->isChecked())
  {
    strScript.append(R"(echo Build IT2Source.sln)").append(sLineReturn);
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(IT2Source.sln)");
    strScript.append(sQuote).append(strOption).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.IT2ComponentsCKB->isChecked())
  {
    strScript.append(R"(echo Build IT2Components.sln)").append(sLineReturn);
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(IT2Components.sln)");
    strScript.append(sQuote).append(strOption).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.AutomationCKB->isChecked())
  {
    strScript.append(R"(echo Build Automation.sln)").append(sLineReturn);
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Setup)").append(QDir::separator()).append(R"(Automation.sln)");
    strScript.append(sQuote).append(strOption).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.IT2SupportToolsCKB->isChecked())
  {
    strScript.append(R"(echo Build IT2SupportTools.sln)").append(sLineReturn);
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(IT2SupportTools.sln)");
    strScript.append(sQuote).append(strOption).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.SCMTestCKB->isChecked())
  {
    strScript.append(R"(echo Build SCMTest.sln)").append(sLineReturn);
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(SCMTest.sln)");
    strScript.append(sQuote).append(strOption).append(sLineReturn);
    fNeedBuild = true;
  }

  if (fNeedBuild == true)
  {
    strScript.append("pause").append(sLineReturn);
    //QString sCompiler = R"(call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Auxiliary\Build\vcvarsall.bat" x64)";
    //QString sCompiler = R"(call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat")";
    QString sCompiler;
    sCompiler.append(R"(::Automatically generated, do NOT modify!)").append(sLineReturn);
    sCompiler.append(R"(@ECHO OFF)").append(sLineReturn);
    sCompiler.append(R"(echo Start automatic build )").append(m_buildMode).append(sLineReturn);
    sCompiler.append(R"(call "E:\SoftwareTools\VS2017Pro\VC\Auxiliary\Build\vcvars64.bat")").append(sLineReturn);
    strScript.prepend(sCompiler);

    QFile file(IT2QtBuildTool::s_scriptFilename, this);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
      QMessageBox msg(QMessageBox::Icon::Critical, "Cannot open script file", IT2QtBuildTool::s_scriptFilename, QMessageBox::Ok);
      msg.exec();
    }
    else
    {
      QTextStream stream(&file);
      stream << strScript << endl;
    }
    file.close();
  }

  return fNeedBuild;
}


bool IT2QtBuildTool::CheckConfigFileExist(bool fReady)
{
  bool fFileOK = true;
  QFile file(IT2QtBuildTool::s_configFilename, this);
  if (fReady)
  {
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
      fFileOK = false;
      QMessageBox msg(QMessageBox::Icon::Critical, "Cannot find config file", IT2QtBuildTool::s_configFilename, QMessageBox::Ok);
      msg.exec();
    }
  }
  else
  {
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
      fFileOK = false;
      QMessageBox msg(QMessageBox::Icon::Critical, "Cannot open config file", IT2QtBuildTool::s_configFilename, QMessageBox::Ok);
      msg.exec();
    }
  }

  return fFileOK;
}

void IT2QtBuildTool::ReadConfigFile()
{
  QFile file(IT2QtBuildTool::s_configFilename, this);
  file.open(QIODevice::ReadOnly);
  QXmlStreamReader xmlReader(&file);
  xmlReader.readNext();

  while (!xmlReader.atEnd())
  {
    if (xmlReader.isStartElement()) {
      if (xmlReader.name() == "Parameters")
      {
        xmlReader.readNext();
      }
      else if (xmlReader.name() == "DatabaseServer")
      {
        m_DBServerName = xmlReader.readElementText();
        xmlReader.readNext();
      }
      else if (xmlReader.name() == "DatabaseName")
      {
        m_DBName = xmlReader.readElementText();
        xmlReader.readNext();
      }
      else if (xmlReader.name() == "ApplicationServer")
      {
        m_AppServerName = xmlReader.readElementText();
        xmlReader.readNext();
      }
      else if (xmlReader.name() == "Workstation")
      {
        m_WorkstationName = xmlReader.readElementText();
        xmlReader.readNext();
      }
      else if (xmlReader.name() == "RootFolder")
      {
        m_RootFolderName = xmlReader.readElementText();
        xmlReader.readNext();
      }
      else if (xmlReader.name() == "PrebuildFolder")
      {
        m_PrebuildFolderName = xmlReader.readElementText();
        xmlReader.readNext();
      }
      else if (xmlReader.name() == "SolutionMask")
      {
        m_MaskBuild = xmlReader.readElementText().toInt();
        xmlReader.readNext();
      }
      else if (xmlReader.name() == "BuildMode")
      {
        m_buildMode = xmlReader.readElementText();
        xmlReader.readNext();
      }
      else {
        xmlReader.raiseError(QObject::tr("unknown option"));
      }
    }
    else
    {
      xmlReader.readNext();
    }
    file.close();
  }
}


void IT2QtBuildTool::SaveConfigFile()
{
  QFile file(IT2QtBuildTool::s_configFilename, this);
  file.open(QIODevice::WriteOnly);
  QXmlStreamWriter xmlWriter(&file);
  xmlWriter.setAutoFormatting(true);
  xmlWriter.writeStartDocument();
  xmlWriter.writeStartElement("Parameters");
  xmlWriter.writeTextElement("DatabaseServer", m_DBServerName);
  xmlWriter.writeTextElement("DatabaseName", m_DBName);
  xmlWriter.writeTextElement("ApplicationServer", m_AppServerName);
  xmlWriter.writeTextElement("Workstation", m_WorkstationName);
  xmlWriter.writeTextElement("RootFolder", m_RootFolderName);
  xmlWriter.writeTextElement("PrebuildFolder", m_PrebuildFolderName);
  xmlWriter.writeTextElement("SolutionMask", QString::number(m_MaskBuild));
  xmlWriter.writeTextElement("BuildMode", m_buildMode);
  xmlWriter.writeEndElement();
  xmlWriter.writeEndDocument();
  file.close();
}

void IT2QtBuildTool::GetMaskFromCheckBoxes()
{
  m_MaskBuild = 0;

  if (ui.IT2ParserCKB->isChecked())
  {
    m_MaskBuild |= SOLUTION_IT2PARSERS;
  }

  if (ui.IT2BusinessCKB->isChecked())
  {
    m_MaskBuild |= SOLUTION_IT2BUSINESS;
  }

  if (ui.AXMSChartCKB->isChecked())
  {
    m_MaskBuild |= SOLUTION_AXMSCHART;
  }

  if (ui.CrystalReportCKB->isChecked())
  {
    m_MaskBuild |= SOLUTION_CRYSTALREPORTS;
  }

  if (ui.FONETCKB->isChecked())
  {
    m_MaskBuild |= SOLUTION_FONETCLIENT;
  }

  if (ui.EBAMCKB->isChecked())
  {
    m_MaskBuild |= SOLUTION_PORTEBAM;
  }

  if (ui.MAPICKB->isChecked())
  {
    m_MaskBuild |= SOLUTION_IT2MAPI;
  }

  if (ui.ImportServiceCKB->isChecked())
  {
    m_MaskBuild |= SOLUTION_IMPORTSERVICES;
  }

  if (ui.SCMSourceCKB->isChecked())
  {
    m_MaskBuild |= SOLUTION_SCMSOURCE;
  }

  if (ui.IT2SourceCKB->isChecked())
  {
    m_MaskBuild |= SOLUTION_IT2SOURCE;
  }

  if (ui.IT2ComponentsCKB->isChecked())
  {
    m_MaskBuild |= SOLUTION_IT2COMPONENTS;
  }

  if (ui.AutomationCKB->isChecked())
  {
    m_MaskBuild |= SOLUTION_AUTOMATIONS;
  }

  if (ui.IT2SupportToolsCKB->isChecked())
  {
    m_MaskBuild |= SOLUTION_SUPPORTTOOLS;
  }

  if (ui.SCMTestCKB->isChecked())
  {
    m_MaskBuild |= SOLUTION_SCMTEST;
  }
}

void IT2QtBuildTool::SetMaskToCheckBoxes()
{
  if ((m_MaskBuild & SOLUTION_IT2PARSERS) == SOLUTION_IT2PARSERS)
  {
    ui.IT2ParserCKB->setChecked(true);
  }

  if ((m_MaskBuild & SOLUTION_IT2BUSINESS) == SOLUTION_IT2BUSINESS)
  {
    ui.IT2BusinessCKB->setChecked(true);
  }

  if ((m_MaskBuild & SOLUTION_AXMSCHART) == SOLUTION_AXMSCHART)
  {
    ui.AXMSChartCKB->setChecked(true);
  }

  if ((m_MaskBuild & SOLUTION_CRYSTALREPORTS) == SOLUTION_CRYSTALREPORTS)
  {
    ui.CrystalReportCKB->setChecked(true);
  }

  if ((m_MaskBuild & SOLUTION_FONETCLIENT) == SOLUTION_FONETCLIENT)
  {
    ui.FONETCKB->setChecked(true);
  }

  if ((m_MaskBuild & SOLUTION_PORTEBAM) == SOLUTION_PORTEBAM)
  {
    ui.EBAMCKB->setChecked(true);
  }

  if ((m_MaskBuild & SOLUTION_IT2MAPI) == SOLUTION_IT2MAPI)
  {
    ui.MAPICKB->setChecked(true);
  }

  if ((m_MaskBuild & SOLUTION_IMPORTSERVICES) == SOLUTION_IMPORTSERVICES)
  {
    ui.ImportServiceCKB->setChecked(true);
  }

  if ((m_MaskBuild & SOLUTION_SCMSOURCE) == SOLUTION_SCMSOURCE)
  {
    ui.SCMSourceCKB->setChecked(true);
  }

  if ((m_MaskBuild & SOLUTION_IT2SOURCE) == SOLUTION_IT2SOURCE)
  {
    ui.IT2SourceCKB->setChecked(true);
  }

  if ((m_MaskBuild & SOLUTION_IT2COMPONENTS) == SOLUTION_IT2COMPONENTS)
  {
    ui.IT2ComponentsCKB->setChecked(true);
  }

  if ((m_MaskBuild & SOLUTION_AUTOMATIONS) == SOLUTION_AUTOMATIONS)
  {
    ui.AutomationCKB->setChecked(true);
  }

  if ((m_MaskBuild & SOLUTION_SUPPORTTOOLS) == SOLUTION_SUPPORTTOOLS)
  {
    ui.IT2SupportToolsCKB->setChecked(true);
  }

  if ((m_MaskBuild & SOLUTION_SCMTEST) == SOLUTION_SCMTEST)
  {
    ui.SCMTestCKB->setChecked(true);
  }
}
