#include <OpenMesh/Core/IO/MeshIO.hh>

#include <QtGui>
#include <QString>
#include <QDockWidget>

#include "meshtool.h"
#include "statistic.h"
#include "remesher.h"

#include <fstream>
#include <iostream>
#include <iomanip>

MeshTool::MeshTool(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
	//ui.setupUi(this);
	setupUi(this);

	//glwidgetcenter = new GLWidgetCenter(this);
	//setCentralWidget(glwidgetcenter);
	meshviewerwidget = new MeshViewerWidget(this, 0, &mesh);
    setCentralWidget(meshviewerwidget);


	//deal with ControlPanel and InformationBox as dock widget
	QDockWidget * dock = new QDockWidget(tr("Contrl Panel"), this);
    dock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable 
			| QDockWidget::DockWidgetFloatable);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	//dw->adjustSize();
	//dw->setMinimumSize(50, 50);
	//dw->setMaximumSize(300, 300);
	controlpanel = new ControlPanel(dock);	
	dock->setWidget(controlpanel);
    addDockWidget(LeftDockWidgetArea,dock);

	menu_View->insertAction(actionTool_Bar, dock->toggleViewAction());
	//menu_View->addSeparator();
    //menu_View->addAction(dock->toggleViewAction());

	dock = new QDockWidget(tr("Information Box"), this);
    dock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable
			| QDockWidget::DockWidgetFloatable);
    dock->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    informationbox = new InformationBox(dock);
	dock->setWidget(informationbox);
	addDockWidget(Qt::BottomDockWidgetArea, dock);

	menu_View->insertAction(actionTool_Bar, dock->toggleViewAction());
	menu_View->insertSeparator(actionTool_Bar);


	//openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    actionLoad_Mesh->setShortcut(tr("Ctrl+M"));
    actionLoad_Mesh->setStatusTip(tr("Load an existing mesh"));
    connect(actionLoad_Mesh, SIGNAL(triggered()), this, SLOT(load_mesh()));

	actionSave_Mesh_As->setStatusTip(tr("Save the current mesh to another file"));
	connect(actionSave_Mesh_As, SIGNAL(triggered()), this, SLOT(save_mesh_as()));

	// attention: this signal can not be accepted by the object with a template class
	// type without the Q_OBJECT. the Q_OBJECT doesn't support template class.
	// it's big problem, but it has to be resolved in a proper way.
	// Qt's signal <-> Qt's interface, template class <-> data. How to combine them?!

	init();
}

MeshTool::~MeshTool()
{

}

void MeshTool::init()
{
	//need to be enhanced

	setConnection();
}

void MeshTool::setConnection()
{
	connect(this, SIGNAL(mesh_loaded()), meshviewerwidget, SLOT(on_mesh_loaded()));

	connect(controlpanel, SIGNAL(viewportSetted(QString)), meshviewerwidget, SLOT(setViewport(QString)));
	connect(controlpanel, SIGNAL(objectShowButtonClicked(bitset<OSI_NumObjectShowItems>)),
			meshviewerwidget, SLOT(setObjectShowItems(bitset<OSI_NumObjectShowItems>)));
	connect(controlpanel, SIGNAL(viewChanged()), meshviewerwidget, SLOT(updateView()));
	connect(controlpanel, SIGNAL(featureViewButtonClicked(bitset<FV_NumFeatureViewItems>)),
			meshviewerwidget, SLOT(setFeatureViewItems(bitset<FV_NumFeatureViewItems>)));

	connect(controlpanel, SIGNAL(outputMessage(QString)), informationbox, SLOT(appendMessage(QString)));
	connect(meshviewerwidget, SIGNAL(outputMessage(QString)), informationbox, SLOT(appendMessage(QString)));
	
}

bool MeshTool::load_mesh()
{
	bool res = false;
	QString QFileName = QFileDialog::getOpenFileName(this);
	if (!QFileName.isEmpty()) 
	{
		std::string ifname = QFileName.toStdString();
		res = read_mesh(ifname);
		if (res) 
		{
			mesh.add_property(edge_type); // what if put in main() function ?
			mesh.add_property(node_type);
			//mesh.add_property(statistic);
			//mesh.property(statistic).set_mesh(mesh);

			mesh.update_face_normals();
			mesh.update_vertex_normals();

			StatisticT<MyMesh> statistic(mesh);
			statistic.calc_statistic();
			std::string fn = "original_statistic.txt";
			statistic.output_statistic(fn);

			// RemesherT<MyMesh> remesher(mesh, user_density);
			// remesher.eliminate_sliver();

			// statistic.calc_statistic();
			// fn = "original_sliver_eliminated_statistic.txt";
			// statistic.output_statistic(fn);

			emit mesh_loaded();

			informationbox->appendMessage("Load mesh " + QFileName + " succeed!");
			char c_n[1024];
			sprintf(c_n, "%d  %d  %d", mesh.n_vertices(), mesh.n_edges(), mesh.n_faces());
			informationbox->appendMessage("#V #E #F: " + (QString)c_n);

			//mesh.property(statistic).calc_edge_length_info();
			sprintf(c_n, "Edge length information\nminimum edge length: %f, its index: %d\nmaximum edge length: %f, its index: %d\naverage edge length: %f\n", 
				statistic.min_edge_length(), statistic.min_length_edge_handle().idx(), \
				statistic.max_edge_length(), statistic.max_length_edge_handle().idx(), \
				statistic.ave_edge_length());
			informationbox->appendMessage(c_n);
		}
		else 
			informationbox->appendMessage("Load mesh " + QFileName + " failed!\n");

		return res;
	}
	else 
	{
		informationbox->appendMessage("Please select a valid mesh!\n");
		return false;
	}	    
}

bool MeshTool::read_mesh(std::string& ifname)
{
    OpenMesh::IO::Options opt;
	bool rc = false;
	rc = OpenMesh::IO::read_mesh(mesh, ifname, opt);
	if (rc) 		
        return true;
    else
        return false;
}

bool MeshTool::save_mesh_as()
{
	bool res = false;
	QString QFileName = QFileDialog::getSaveFileName(this);
	if (!QFileName.isEmpty()) 
	{
		std::string ofname = QFileName.toStdString();
		res = write_mesh(ofname);
		if (!res)
		{
			informationbox->appendMessage("Save mesh failed, the file name might be invalid!\n");
			return false;
		}
	}
	else 
	{
		informationbox->appendMessage("Please input a file name!\n");
		return false;
	}

	return true;
}

bool MeshTool::write_mesh(std::string &ofname)
{
	ofstream off_file(ofname.c_str());
	if (!off_file)
	{
		cerr << "error: unable to open off file: " << ofname << endl;
		return false;
	}

	MyMesh::ConstVertexIter      v_it(mesh.vertices_begin()),
		                         v_end(mesh.vertices_end());
	MyMesh::ConstFaceIter        f_it(mesh.faces_begin()),
		                         f_end(mesh.faces_end());
	MyMesh::ConstFaceVertexIter  cfv_it;

	int np = mesh.n_vertices(), ne = mesh.n_faces();
	MyMesh::Point pt;

	off_file << "OFF" << endl;
	off_file << left << setw(10) << np << " "<< setw(10) << ne << " " << 0 << endl;

	off_file.precision(8);
	off_file << fixed;
	for (; v_it != v_end; ++v_it)
	{
		pt = mesh.point(v_it.handle());
		off_file << setw(15) << pt[0] << setw(15) << pt[1] << setw(15) << pt[2] << endl;
	}

	off_file << right;
	for (; f_it != f_end; ++f_it)
	{
		off_file << 3;
		cfv_it = mesh.cfv_iter(f_it.handle());
		off_file << setw(10) << cfv_it.handle().idx();
		++cfv_it;
		off_file << setw(10) << cfv_it.handle().idx();
		++cfv_it;
		off_file << setw(10) << cfv_it.handle().idx();
		
		off_file << endl;
	}

	off_file.close();

	return true;


	/** original code, will be used again
	OpenMesh::IO::Options opt;
	bool rc = false;
	rc = OpenMesh::IO::write_mesh(mesh, ofname, opt);
	if (rc) 		
        return true;
    else
        return false;
	*/
}
