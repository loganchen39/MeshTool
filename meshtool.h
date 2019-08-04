#ifndef MESHTOOL_H
#define MESHTOOL_H

//using namespace std;
#include <string>

#include <QtGui/QMainWindow>

#include "ui_meshtool.h"
#include "global.h"
#include "meshviewerwidget.h"
#include "controlpanel.h"
#include "informationbox.h"

//typedef MeshViewerWidgetT<MyMesh> MeshViewerWidget;

class MeshTool : public QMainWindow, public Ui::MTMainWindow
{
    Q_OBJECT

public:
    MeshTool(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~MeshTool();

public:
	void init();
	void setConnection();

private:
    //Ui::MeshToolClass ui;
	//GLWidgetCenter* glwidgetcenter;
	MeshViewerWidget* meshviewerwidget;
	ControlPanel* controlpanel;
	InformationBox* informationbox;
	//QDockWidget* dw_controlpanel;

	//QColor backgroud_color_;
	//QFont  backgroud_font_;

signals:
    void mesh_loaded(void);

private slots:
	bool load_mesh();
	bool save_mesh_as();

private:
	bool read_mesh(std::string& ifname);
	bool write_mesh(std::string& ofname);
};

#endif // MESHTOOL_H
