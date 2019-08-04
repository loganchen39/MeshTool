/**
*class MyMesh header file
*@author LigangChen
*@version 0.1 2007/02/04
*/

#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QtGui/QWidget>

//#include <bitset>

#include "global.h"

#include "ui_ControlPanel.h"

//using namespace std;
using namespace Qt;

class ControlPanel : public QWidget
{
    Q_OBJECT

public:
    ControlPanel(QWidget *parent = 0);
    ~ControlPanel();
	
public:
	void init();

private slots:
	// mesh viewer
    void on_viewportCombo_activated(const QString&);
	void on_meshViewerButtonGroup_buttonClicked(QAbstractButton*);

	// detect features
	void on_applyPushButton_clicked();
	void on_featureViewButtonGroup_buttonClicked(QAbstractButton*);

	// remesh
	void on_ba3FilePushButton_clicked();
	void on_denseAndTopoTransExecutePushButton_clicked();

	// smoothing
	void on_smoothingExecutePushButton_clicked();

signals:
	void viewportSetted(QString);
	void objectShowButtonClicked(bitset<OSI_NumObjectShowItems>);

	void featureViewButtonClicked(bitset<FV_NumFeatureViewItems>);

	void viewChanged();

	void outputMessage(QString);

private:
    Ui::ControlPanel ui;

	QButtonGroup* meshViewerButtonGroup;
	bitset<OSI_NumObjectShowItems> objectShowFlags;

	QButtonGroup* featureViewButtonGroup;  // include "Properties"
	bitset<FV_NumFeatureViewItems> featureViewFlags; // does not include "Properties"

	// static int smooth_time_;
};

#endif 