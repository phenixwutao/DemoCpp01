#include "stdafx.h"
#include "IT2QtBuildTool.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IT2QtBuildTool w;
    w.show();
    return a.exec();
}
