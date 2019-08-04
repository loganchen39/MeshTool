/********************************************************************************
** Form generated from reading ui file 'meshtool.ui'
**
** Created: Wed Jul 16 20:22:59 2008
**      by: Qt User Interface Compiler version 4.2.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MESHTOOL_H
#define UI_MESHTOOL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

class Ui_MTMainWindow
{
public:
    QAction *action_New;
    QAction *actionLoad_Mesh;
    QAction *actionClose_All;
    QAction *actionSave_BkgGS;
    QAction *actionSave_BkgGS_as;
    QAction *actionSave_Mesh;
    QAction *actionSave_Mesh_As;
    QAction *actionRecent_Files;
    QAction *action_Close_All;
    QAction *action_Exit;
    QAction *actionControl_Panel;
    QAction *actionOutput_Panel;
    QAction *actionTool_Bar;
    QAction *actionStatus_Bar;
    QAction *actionVertex_Normal_Compute;
    QAction *actionMesh_Analysis;
    QAction *action_Font;
    QAction *action_Backgroud_Color;
    QAction *action_Font_2;
    QAction *actionAbout_MeshTool;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu_Help;
    QMenu *menu_Tools;
    QMenu *menuFile;
    QMenu *menu_View;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MTMainWindow)
    {
    MTMainWindow->setObjectName(QString::fromUtf8("MTMainWindow"));
    action_New = new QAction(MTMainWindow);
    action_New->setObjectName(QString::fromUtf8("action_New"));
    actionLoad_Mesh = new QAction(MTMainWindow);
    actionLoad_Mesh->setObjectName(QString::fromUtf8("actionLoad_Mesh"));
    actionClose_All = new QAction(MTMainWindow);
    actionClose_All->setObjectName(QString::fromUtf8("actionClose_All"));
    actionSave_BkgGS = new QAction(MTMainWindow);
    actionSave_BkgGS->setObjectName(QString::fromUtf8("actionSave_BkgGS"));
    actionSave_BkgGS_as = new QAction(MTMainWindow);
    actionSave_BkgGS_as->setObjectName(QString::fromUtf8("actionSave_BkgGS_as"));
    actionSave_Mesh = new QAction(MTMainWindow);
    actionSave_Mesh->setObjectName(QString::fromUtf8("actionSave_Mesh"));
    actionSave_Mesh_As = new QAction(MTMainWindow);
    actionSave_Mesh_As->setObjectName(QString::fromUtf8("actionSave_Mesh_As"));
    actionRecent_Files = new QAction(MTMainWindow);
    actionRecent_Files->setObjectName(QString::fromUtf8("actionRecent_Files"));
    action_Close_All = new QAction(MTMainWindow);
    action_Close_All->setObjectName(QString::fromUtf8("action_Close_All"));
    action_Exit = new QAction(MTMainWindow);
    action_Exit->setObjectName(QString::fromUtf8("action_Exit"));
    actionControl_Panel = new QAction(MTMainWindow);
    actionControl_Panel->setObjectName(QString::fromUtf8("actionControl_Panel"));
    actionOutput_Panel = new QAction(MTMainWindow);
    actionOutput_Panel->setObjectName(QString::fromUtf8("actionOutput_Panel"));
    actionTool_Bar = new QAction(MTMainWindow);
    actionTool_Bar->setObjectName(QString::fromUtf8("actionTool_Bar"));
    actionStatus_Bar = new QAction(MTMainWindow);
    actionStatus_Bar->setObjectName(QString::fromUtf8("actionStatus_Bar"));
    actionVertex_Normal_Compute = new QAction(MTMainWindow);
    actionVertex_Normal_Compute->setObjectName(QString::fromUtf8("actionVertex_Normal_Compute"));
    actionMesh_Analysis = new QAction(MTMainWindow);
    actionMesh_Analysis->setObjectName(QString::fromUtf8("actionMesh_Analysis"));
    action_Font = new QAction(MTMainWindow);
    action_Font->setObjectName(QString::fromUtf8("action_Font"));
    action_Backgroud_Color = new QAction(MTMainWindow);
    action_Backgroud_Color->setObjectName(QString::fromUtf8("action_Backgroud_Color"));
    action_Font_2 = new QAction(MTMainWindow);
    action_Font_2->setObjectName(QString::fromUtf8("action_Font_2"));
    actionAbout_MeshTool = new QAction(MTMainWindow);
    actionAbout_MeshTool->setObjectName(QString::fromUtf8("actionAbout_MeshTool"));
    centralWidget = new QWidget(MTMainWindow);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    MTMainWindow->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(MTMainWindow);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 600, 21));
    menu_Help = new QMenu(menuBar);
    menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
    menu_Tools = new QMenu(menuBar);
    menu_Tools->setObjectName(QString::fromUtf8("menu_Tools"));
    menuFile = new QMenu(menuBar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menu_View = new QMenu(menuBar);
    menu_View->setObjectName(QString::fromUtf8("menu_View"));
    MTMainWindow->setMenuBar(menuBar);
    mainToolBar = new QToolBar(MTMainWindow);
    mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
    mainToolBar->setOrientation(Qt::Horizontal);
    MTMainWindow->addToolBar(static_cast<Qt::ToolBarArea>(4), mainToolBar);
    statusBar = new QStatusBar(MTMainWindow);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    MTMainWindow->setStatusBar(statusBar);

    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menu_View->menuAction());
    menuBar->addAction(menu_Tools->menuAction());
    menuBar->addAction(menu_Help->menuAction());
    menu_Help->addAction(actionAbout_MeshTool);
    menu_Tools->addAction(actionVertex_Normal_Compute);
    menu_Tools->addAction(actionMesh_Analysis);
    menuFile->addAction(action_New);
    menuFile->addAction(actionLoad_Mesh);
    menuFile->addSeparator();
    menuFile->addAction(actionSave_BkgGS);
    menuFile->addAction(actionSave_BkgGS_as);
    menuFile->addAction(actionSave_Mesh);
    menuFile->addAction(actionSave_Mesh_As);
    menuFile->addSeparator();
    menuFile->addAction(actionRecent_Files);
    menuFile->addSeparator();
    menuFile->addAction(action_Close_All);
    menuFile->addAction(action_Exit);
    menu_View->addSeparator();
    menu_View->addAction(actionTool_Bar);
    menu_View->addAction(actionStatus_Bar);
    menu_View->addSeparator();
    menu_View->addAction(action_Font_2);
    menu_View->addAction(action_Backgroud_Color);

    retranslateUi(MTMainWindow);

    QSize size(600, 400);
    size = size.expandedTo(MTMainWindow->minimumSizeHint());
    MTMainWindow->resize(size);


    QMetaObject::connectSlotsByName(MTMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MTMainWindow)
    {
    MTMainWindow->setWindowTitle(QApplication::translate("MTMainWindow", "MeshTool", 0, QApplication::UnicodeUTF8));
    action_New->setText(QApplication::translate("MTMainWindow", "Load &BkgGS...", 0, QApplication::UnicodeUTF8));
    actionLoad_Mesh->setText(QApplication::translate("MTMainWindow", "Load &Mesh...", 0, QApplication::UnicodeUTF8));
    actionClose_All->setText(QApplication::translate("MTMainWindow", "&Close All", 0, QApplication::UnicodeUTF8));
    actionSave_BkgGS->setText(QApplication::translate("MTMainWindow", "Save BkgGS", 0, QApplication::UnicodeUTF8));
    actionSave_BkgGS_as->setText(QApplication::translate("MTMainWindow", "Save BkgGS as...", 0, QApplication::UnicodeUTF8));
    actionSave_Mesh->setText(QApplication::translate("MTMainWindow", "Save Mesh", 0, QApplication::UnicodeUTF8));
    actionSave_Mesh_As->setText(QApplication::translate("MTMainWindow", "Save Mesh As...", 0, QApplication::UnicodeUTF8));
    actionRecent_Files->setText(QApplication::translate("MTMainWindow", "Recent Files", 0, QApplication::UnicodeUTF8));
    action_Close_All->setText(QApplication::translate("MTMainWindow", "&Close All", 0, QApplication::UnicodeUTF8));
    action_Exit->setText(QApplication::translate("MTMainWindow", "&Exit", 0, QApplication::UnicodeUTF8));
    actionControl_Panel->setText(QApplication::translate("MTMainWindow", "Control Panel", 0, QApplication::UnicodeUTF8));
    actionOutput_Panel->setText(QApplication::translate("MTMainWindow", "Output Panel", 0, QApplication::UnicodeUTF8));
    actionTool_Bar->setText(QApplication::translate("MTMainWindow", "Tool Bar", 0, QApplication::UnicodeUTF8));
    actionStatus_Bar->setText(QApplication::translate("MTMainWindow", "Status Bar", 0, QApplication::UnicodeUTF8));
    actionVertex_Normal_Compute->setText(QApplication::translate("MTMainWindow", "Vertex Normal Compute...", 0, QApplication::UnicodeUTF8));
    actionMesh_Analysis->setText(QApplication::translate("MTMainWindow", "Mesh Analysis...", 0, QApplication::UnicodeUTF8));
    action_Font->setText(QApplication::translate("MTMainWindow", "&Font...", 0, QApplication::UnicodeUTF8));
    action_Backgroud_Color->setText(QApplication::translate("MTMainWindow", "&Background Color...", 0, QApplication::UnicodeUTF8));
    action_Font_2->setText(QApplication::translate("MTMainWindow", "Background &Font...", 0, QApplication::UnicodeUTF8));
    actionAbout_MeshTool->setText(QApplication::translate("MTMainWindow", "About MeshTool", 0, QApplication::UnicodeUTF8));
    menu_Help->setTitle(QApplication::translate("MTMainWindow", "&Help", 0, QApplication::UnicodeUTF8));
    menu_Tools->setTitle(QApplication::translate("MTMainWindow", "&Tools", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("MTMainWindow", "&File", 0, QApplication::UnicodeUTF8));
    menu_View->setTitle(QApplication::translate("MTMainWindow", "&View", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MTMainWindow: public Ui_MTMainWindow {};
} // namespace Ui

#endif // UI_MESHTOOL_H
