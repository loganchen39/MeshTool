#include "controlpanel.h"  // including global.h

#include "featuredetector.h"
#include "userdensity.h"
#include "remesher.h"
#include "smoother.h"
#include "statistic.h"

#include <QMessageBox>
#include <QFileDialog>

ControlPanel::ControlPanel(QWidget *parent)
        : QWidget(parent)
{
	ui.setupUi(this);
	init();
}

ControlPanel::~ControlPanel()
{
}

void ControlPanel::init()
{
	meshViewerButtonGroup = new QButtonGroup(ui.MeshViewer); // what if ui.objectsShowGroupBox ?
	meshViewerButtonGroup->setExclusive(false);  // without this even the checkboxes are mutually exclusive
	meshViewerButtonGroup->addButton(ui.vertexCheckBox);	
	meshViewerButtonGroup->addButton(ui.vNormCheckBox);
	meshViewerButtonGroup->addButton(ui.vIdxCheckBox);	
	meshViewerButtonGroup->addButton(ui.edgeCheckBox);
	meshViewerButtonGroup->addButton(ui.hiddenLineCheckBox);	
	meshViewerButtonGroup->addButton(ui.eIdxCheckBox);	
	meshViewerButtonGroup->addButton(ui.faceCheckBox);	
	meshViewerButtonGroup->addButton(ui.fNormCheckBox);
	meshViewerButtonGroup->addButton(ui.fIdxCheckBox);
	meshViewerButtonGroup->addButton(ui.lightCheckBox);
	meshViewerButtonGroup->addButton(ui.lightDirCheckBox);
	meshViewerButtonGroup->addButton(ui.editLitDirCheckBox);
	meshViewerButtonGroup->addButton(ui.shadeSmoothCheckBox);
	meshViewerButtonGroup->addButton(ui.colorMaterialCheckBox);
	meshViewerButtonGroup->addButton(ui.perspectiveCheckBox);
	meshViewerButtonGroup->addButton(ui.inertiaCheckBox);
	meshViewerButtonGroup->addButton(ui.coordsCheckBox);
	meshViewerButtonGroup->addButton(ui.bBoxCheckBox);

	objectShowFlags.reset();
	objectShowFlags.set(OSI_Edge);
	objectShowFlags.set(OSI_Light);
	objectShowFlags.set(OSI_ShadeSmooth);

	// Feature detection, Parameters for basic algorithm 
	ui.rEdAngleThreshLineEdit->setText("45.0");
	ui.cNdPromAngleThreshLineEdit->setText("120.0");

	// not "FeatureDetection", what if "page_4", the page it belongs to ?
	featureViewButtonGroup = new QButtonGroup(ui.featureViewAndEditToolBox); 
	featureViewButtonGroup->setExclusive(false); // default it's exclusive
	featureViewButtonGroup->addButton(ui.bouNdCheckBox);
	featureViewButtonGroup->addButton(ui.bNdIdxCheckBox);
	featureViewButtonGroup->addButton(ui.bNdNormCheckBox);
	featureViewButtonGroup->addButton(ui.cornerNdCheckBox);
	featureViewButtonGroup->addButton(ui.cNdIdxCheckBox);
	featureViewButtonGroup->addButton(ui.cNdNormCheckBox);
	featureViewButtonGroup->addButton(ui.ridgeNdCheckBox);
	featureViewButtonGroup->addButton(ui.rNdIdxCheckBox);
	featureViewButtonGroup->addButton(ui.rNdNormCheckBox);
	featureViewButtonGroup->addButton(ui.flatNdCheckBox);
	featureViewButtonGroup->addButton(ui.fNdIdxCheckBox);
	featureViewButtonGroup->addButton(ui.fNdNormCheckBox);
	featureViewButtonGroup->addButton(ui.bouEdCheckBox);
	featureViewButtonGroup->addButton(ui.ridgeEgCheckBox);
	featureViewButtonGroup->addButton(ui.flatEdCheckBox);
	featureViewButtonGroup->addButton(ui.bEdIdxCheckBox);
	featureViewButtonGroup->addButton(ui.rEdIdxCheckBox);
	featureViewButtonGroup->addButton(ui.fEdIdxCheckBox);
	featureViewButtonGroup->addButton(ui.featureViewPropertiesPushButton); // ok ?

	featureViewFlags.reset();

	ui.smmethodLineEdit->setText("1");
	ui.nsmoothsurfLineEdit->setText("10");
	ui.relaxsurfLineEdit->setText("0.1");


	connect(meshViewerButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, // this can not be omitted
		    SLOT(on_meshViewerButtonGroup_buttonClicked(QAbstractButton*)));
	connect(featureViewButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, 
		    SLOT(on_featureViewButtonGroup_buttonClicked(QAbstractButton*)));
}

void ControlPanel::on_viewportCombo_activated(const QString& viewport)
{
	if ("------" == viewport)
		return;

	emit viewportSetted(viewport);
}

void ControlPanel::on_meshViewerButtonGroup_buttonClicked(QAbstractButton *button)
{
	QString buttonText = button->text();

	if ("Vertex" == buttonText)
		objectShowFlags.flip(OSI_Vertex);
	else if ("VNorm" == buttonText)
		objectShowFlags.flip(OSI_VNorm);
	else if ("VIdx" == buttonText)
		objectShowFlags.flip(OSI_VIdx);
	else if ("Edge" == buttonText)
		objectShowFlags.flip(OSI_Edge);
	else if ("HiddenLine" == buttonText)
		objectShowFlags.flip(OSI_HiddenLine);
	else if ("EIdx" == buttonText)
		objectShowFlags.flip(OSI_EIdx);
	else if ("Face" == buttonText)
		objectShowFlags.flip(OSI_Face);
	else if ("FNorm" == buttonText)
		objectShowFlags.flip(OSI_FNorm);
	else if ("FIdx" == buttonText)
		objectShowFlags.flip(OSI_FIdx);
	else if ("Light" == buttonText) 
		objectShowFlags.flip(OSI_Light);
	else if ("LightDir" == buttonText)
		objectShowFlags.flip(OSI_LightDir);
	else if ("EditLightDir" == buttonText)
		objectShowFlags.flip(OSI_EditLitDir);
	if ("ShadeSmooth" == buttonText)
		objectShowFlags.flip(OSI_ShadeSmooth);
	else if ("ColorMaterial" == buttonText)
		objectShowFlags.flip(OSI_ColorMaterial);
	else if ("Perspective" == buttonText)
		objectShowFlags.flip(OSI_Perspective);
	else if ("Inertia" == buttonText)
		objectShowFlags.flip(OSI_Inertia);
	else if ("Coords" == buttonText)
		objectShowFlags.flip(OSI_Coords);
	else if ("BBox" == buttonText)
		objectShowFlags.flip(OSI_BBox);

	emit objectShowButtonClicked(objectShowFlags);
}

void ControlPanel::on_applyPushButton_clicked()
{
	QString currentItemText = ui.algoAndParamToolBox->itemText(ui.algoAndParamToolBox->currentIndex());

	if ("Basic Algorithm" == currentItemText)
	{
		BasicFeatureDetectorT<MyMesh> feature_detector(mesh);

		bool ok = false;
		float angle = 0.0;
		if (!ui.rEdAngleThreshLineEdit->text().isEmpty()) // if empty, use default
		{
			angle = ui.rEdAngleThreshLineEdit->text().toFloat(&ok);
			if (!ok || angle < 0.0 || angle > 180.0)
			{
				QMessageBox::critical(this, tr("Critical Error"),"The angle thresh for ridge edge is invalid!",
					QMessageBox::Ok);

				return;
			}
			else
				feature_detector.set_ridge_edge_angle_thresh(OpenMesh::deg_to_rad((MyMesh::Scalar)angle));
		}
		else
		{
			QMessageBox::critical(this, tr("Critical Error"),"Please input an angle thresh for ridge edge!",
					QMessageBox::Ok);

			return;
		}

		if (!ui.cNdPromAngleThreshLineEdit->text().isEmpty())
		{
			angle = ui.cNdPromAngleThreshLineEdit->text().toFloat(&ok);
			if (!ok || angle < 0.0 || angle > 180.0)
			{
				QMessageBox::critical(this, tr("Critical Error"),"The angle thresh for corner node promotion is invalid!",
					QMessageBox::Ok);

				return;
			}
			else
				feature_detector.set_corner_node_promotion_angle_thresh(OpenMesh::deg_to_rad((MyMesh::Scalar)angle));
		}
		else
		{
			QMessageBox::critical(this, tr("Critical Error"),"Please input an angle thresh for corner node promotion!",
					QMessageBox::Ok);

			return;
		}
		
		feature_detector.detect_feature();
	}
	else if ("mtoolsurf's Algorithm" == currentItemText)
	{
	}
	else
	{
	}

	// only to inform the MeshViewerWidget of updating 
	//emit featureViewButtonClicked(featureViewFlags); 
	emit viewChanged();
}

void ControlPanel::on_featureViewButtonGroup_buttonClicked(QAbstractButton* button)
{
	QString buttonText = button->text();

	if ("Properties" == buttonText)
	{
		// todo

		return;
	}

	if ("BouNd" == buttonText)
		featureViewFlags.flip(FV_BouNd);
	if ("BNdIdx" == buttonText)
		featureViewFlags.flip(FV_BNdIdx);
	if ("BNdNorm" == buttonText)
		featureViewFlags.flip(FV_BNdNorm);
	if ("CornerNd" == buttonText)
		featureViewFlags.flip(FV_CornerNd);
	if ("CNdIdx" == buttonText)
		featureViewFlags.flip(FV_CNdIdx);
	if ("CNdNorm" == buttonText)
		featureViewFlags.flip(FV_CNdNorm);
	if ("RidgeNd" == buttonText)
		featureViewFlags.flip(FV_RidgeNd);
	if ("RNdIdx" == buttonText)
		featureViewFlags.flip(FV_RNdIdx);
	if ("RNdNorm" == buttonText)
		featureViewFlags.flip(FV_RNdNorm);
	if ("FlatNd" == buttonText)
		featureViewFlags.flip(FV_FlatNd);
	if ("FNdIdx" == buttonText)
		featureViewFlags.flip(FV_FNdIdx);
	if ("FNdNorm" == buttonText)
		featureViewFlags.flip(FV_FNdNorm);
	if ("BouEd" == buttonText)
		featureViewFlags.flip(FV_BouEd);
	if ("RidgeEd" == buttonText)
		featureViewFlags.flip(FV_RidgeEd);
	if ("FlatEd" == buttonText)
		featureViewFlags.flip(FV_FlatEd);
	if ("BEdIdx" == buttonText)
		featureViewFlags.flip(FV_BEdIdx);
	if ("REdIdx" == buttonText)
		featureViewFlags.flip(FV_REdIdx);
	if ("FEdIdx" == buttonText)
		featureViewFlags.flip(FV_FEdIdx);

	emit featureViewButtonClicked(featureViewFlags);
}

void ControlPanel::on_ba3FilePushButton_clicked()
{
	QString dir;
	QString qfn = QFileDialog::getOpenFileName(this, tr("Open ba3 file"), dir,
		tr("Bkg mesh files(*.ba3)")); // filter to ba3 files
	if (!qfn.isEmpty()) 
	{
		ui.ba3FileLineEdit->setText(qfn);
		ui.ba3FileLineEdit->displayText();
	}
}

void ControlPanel::on_denseAndTopoTransExecutePushButton_clicked()
{
	//UserDensity user_density;
	float uniform_spacing = 0.0;
	bool ok = false;

	if (ui.uniformDensityGroupBox->isChecked())
	{
		user_density.set_use_uniform_density(true);

		if (!ui.globalSpacingLineEdit->text().isEmpty()) // deal with empty later
		{
			uniform_spacing = ui.globalSpacingLineEdit->text().toFloat(&ok);
			if (!ok || uniform_spacing < 0.0)
			{
				QMessageBox::critical(this, tr("Critical Error"),"The uniform spacing is invalid!",
					QMessageBox::Ok);
				return;
			}
			else
				user_density.set_uniform_spacing(uniform_spacing);
		}
		else
		{
			QMessageBox::warning(this, tr("Warning"),"The uniform spacing has not been specified, or not to use uniform density!",
					QMessageBox::Ok);
			return;
			//user_density.set_uniform_spacing(0.0);
		}
	}
	else
		user_density.set_use_uniform_density(false);


	if (ui.bkgAndSorGroupBox->isChecked()) 
	{
		user_density.set_use_user_density(true);

		string fn = ui.ba3FileLineEdit->text().toStdString();
		if (!fn.empty())
		{
			if (!user_density.read_ba3(fn))
			{
				QMessageBox::critical(this, tr("Critical error"),"Fail to read the backgroud grid file!",
					QMessageBox::Ok);
				return;
			}
		}
		else
		{
			QMessageBox::warning(this, tr("Warning"),"The backgroud grid file has not been specified, or not to use it!",
					QMessageBox::Ok);
			return;
		}
	}
	else
		user_density.set_use_user_density(false);

	if (ui.geometricDensityGroupBox->isChecked()) // handle it later
	{

	}

	RemesherT<MyMesh> remesher(mesh, user_density);
	remesher.set_flip_type(FT_TopoTrans);

	remesher.remesh();

	emit viewChanged();
}

void ControlPanel::on_smoothingExecutePushButton_clicked()
{
	QString currentItemText = ui.smoothingToolBox->itemText(ui.smoothingToolBox->currentIndex());

	if ("mtoolsurf's Algorithm" == currentItemText)
	{
		SmootherT<MyMesh> smoother(mesh);

		int smmethod, nsmoothsurf;
		float relaxsurf;
		bool ok = false;

		smmethod = ui.smmethodLineEdit->text().toInt(&ok);
		if (!ok || (1 != smmethod && 2 != smmethod))
		{
			QMessageBox::critical(this, tr("Critical Error"),"The smmethod is invalid!",
					QMessageBox::Ok);
			return;
		}
		else
			smoother.set_smmethod(smmethod);

		nsmoothsurf = ui.nsmoothsurfLineEdit->text().toInt(&ok);
		if (!ok || nsmoothsurf < 0)
		{
			QMessageBox::critical(this, tr("Critical Error"),"The nsmoothsurf is invalid!",
					QMessageBox::Ok);
			return;
		}
		else
			smoother.set_nsmoothsurf(nsmoothsurf);

		relaxsurf = ui.relaxsurfLineEdit->text().toFloat(&ok);
		if (!ok) // || relaxsurf < 0.0
		{
			QMessageBox::critical(this, tr("Critical Error"),"The relaxsurf is invalid!",
					QMessageBox::Ok);
			return;
		}
		else
			smoother.set_relaxsurf(relaxsurf);

		smoother.smooth();	
		++smooth_time;


		if (smooth_time > 1)
		{
			RemesherT<MyMesh> remesher(mesh, user_density);
			remesher.set_flip_type(FT_Smoothing);
			remesher.optimize(); // edge flip

			if (smooth_time > 4)
				remesher.eliminate_sliver();
		}

		StatisticT<MyMesh> statistic(mesh);
		statistic.calc_statistic();
		statistic.output_statistic("statistic.txt");
	}
	else if ("Other's Algorithm" == currentItemText)
	{

	}
	else // Reserved
	{

	}

	emit viewChanged();
}
