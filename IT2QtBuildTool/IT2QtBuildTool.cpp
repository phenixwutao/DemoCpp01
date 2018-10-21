#include "stdafx.h"
#include "IT2QtBuildTool.h"

IT2QtBuildTool::IT2QtBuildTool(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //this->setBaseSize(1650, 1200);
    this->setFixedSize(1630, 1100);
    on_ResetPB_clicked();
}

const QString IT2QtBuildTool::s_buildOption = "x64";
const QString IT2QtBuildTool::s_configFilename = "IT2QtBuildTool.config";
const QString IT2QtBuildTool::s_scriptFilename = "IT2QtBuildTool.bat";

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

  GetAllConfig();

  if (this->CheckConfigFileExist(false) == false)
    return;

  SaveScriptFile();
}

void IT2QtBuildTool::on_ResetPB_clicked()
{
  if (this->CheckConfigFileExist(true) == false)
    return;

  ReadScriptFile();
  SetAllConfig();
}

void IT2QtBuildTool::on_ClearPB_clicked()
{
  if (m_DBServerName.isEmpty()      == true &&
      m_AppServerName.isEmpty()     == true &&
      m_WorkstationName.isEmpty()   == true &&
      m_RootFolderName.isEmpty()    == true &&
      m_PrebuildFolderName.isEmpty()== true)
    return;

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
    ClearAllConfig();
  }
}


void IT2QtBuildTool::on_DefaultPB_clicked()
{
}

void IT2QtBuildTool::on_ClosePB_clicked()
{
  if (CheckAllConfiguration() == false)
    return;

  if (CheckConfigFileExist(false) == false)
    return;

  SaveScriptFile();

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
    return;

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
  ui.AppServerEdit->clear();
  ui.WorkStationEdit->clear();
  ui.RootFolderEdit->clear();
  ui.PrebuildFolderEdit->clear();

  m_DBServerName.clear();
  m_AppServerName.clear();
  m_WorkstationName.clear();
  m_RootFolderName.clear();
  m_PrebuildFolderName.clear();
}

void IT2QtBuildTool::SetAllConfig()
{
  ui.DBServerEdit->setText(m_DBServerName);
  ui.AppServerEdit->setText(m_AppServerName);
  ui.WorkStationEdit->setText(m_WorkstationName);
  ui.RootFolderEdit->setText(m_RootFolderName);
  ui.PrebuildFolderEdit->setText(m_PrebuildFolderName);
}

void IT2QtBuildTool::GetAllConfig()
{
  m_DBServerName = ui.DBServerEdit->text();
  m_AppServerName = ui.AppServerEdit->text();
  m_WorkstationName = ui.WorkStationEdit->text();
  m_RootFolderName = ui.RootFolderEdit->text();
  m_PrebuildFolderName = ui.PrebuildFolderEdit->text();
}

bool IT2QtBuildTool::NeedBuildSolutions()
{
  QString strScript;
  QString sQuote = R"(")";
  QString sLineReturn = "\r\n";
  QString strOption = R"( /p )" + s_buildOption;
  QString strMSBuild = R"(MSBuild.exe ")";
  bool fNeedBuild = false;
  if (ui.IT2ParserCKB->isChecked())
  {
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Parsers)").append(QDir::separator()).append(R"(IT2Parsers.sln)");
    strScript.append(sQuote).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.IT2BusinessCKB->isChecked())
  {
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(IT2Business.sln)");
    strScript.append(sQuote).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.AXMSChartCKB->isChecked())
  {
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(AxMSChart)").append(QDir::separator())
      .append(R"(AxMSChart.sln)");
    strScript.append(sQuote).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.CrystalReportCKB->isChecked())
  {
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(CrystalReports.sln)");
    strScript.append(sQuote).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.FONETCKB->isChecked())
  {
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(FONET Client)").append(QDir::separator())
      .append(R"(FONET Client.sln)");
    strScript.append(sQuote).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.EBAMCKB->isChecked())
  {
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(IT2Components)").append(QDir::separator())
      .append(R"(EBAM)").append(QDir::separator()).append(R"(PortEBAMSigner.sln)");
    strScript.append(sQuote).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.MAPICKB->isChecked())
  {
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(IT2Components)").append(QDir::separator())
      .append(R"(IT2MAPI)").append(QDir::separator()).append(R"(IT2MAPI.sln)");
    strScript.append(sQuote).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.ImportServiceCKB->isChecked())
  {
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(IT2ImportServices.sln)");
    strScript.append(sQuote).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.SCMSourceCKB->isChecked())
  {
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(SCMSource.sln)");
    strScript.append(sQuote).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.IT2SourceCKB->isChecked())
  {
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(IT2Source.sln)");
    strScript.append(sQuote).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.IT2ComponentsCKB->isChecked())
  {
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(IT2Components.sln)");
    strScript.append(sQuote).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.AutomationCKB->isChecked())
  {
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Setup)").append(QDir::separator()).append(R"(Automation.sln)");
    strScript.append(sQuote).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.IT2SupportToolsCKB->isChecked())
  {
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(IT2SupportTools.sln)");
    strScript.append(sQuote).append(sLineReturn);
    fNeedBuild = true;
  }

  if (ui.SCMTestCKB->isChecked())
  {
    strScript.append(strMSBuild).append(m_RootFolderName).append(QDir::separator())
      .append(R"(IT2Source)").append(QDir::separator()).append(R"(SCMTest.sln)");
    strScript.append(strOption).append(sQuote).append(sLineReturn);
    fNeedBuild = true;
  }

  if (fNeedBuild == true)
  {
    strScript.append("pause").append(sLineReturn);
    //QString sCompiler = R"(call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Auxiliary\Build\vcvarsall.bat" x64)";
    QString sCompiler = R"(call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat")";
    strScript.prepend(sCompiler.append(sLineReturn));

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

void IT2QtBuildTool::ReadScriptFile()
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


void IT2QtBuildTool::SaveScriptFile()
{
  QFile file(IT2QtBuildTool::s_configFilename, this);
  file.open(QIODevice::WriteOnly);
  QXmlStreamWriter xmlWriter(&file);
  xmlWriter.setAutoFormatting(true);
  xmlWriter.writeStartDocument();
  xmlWriter.writeStartElement("Parameters");
  xmlWriter.writeTextElement("DatabaseServer", m_DBServerName);
  xmlWriter.writeTextElement("ApplicationServer", m_AppServerName);
  xmlWriter.writeTextElement("Workstation", m_WorkstationName);
  xmlWriter.writeTextElement("RootFolder", m_RootFolderName);
  xmlWriter.writeTextElement("PrebuildFolder", m_PrebuildFolderName);
  xmlWriter.writeEndElement();
  xmlWriter.writeEndDocument();
  file.close();
}
