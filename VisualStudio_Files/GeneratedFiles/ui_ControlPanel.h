/********************************************************************************
** Form generated from reading ui file 'ControlPanel.ui'
**
** Created: Wed Jul 16 20:22:58 2008
**      by: Qt User Interface Compiler version 4.2.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CONTROLPANEL_H
#define UI_CONTROLPANEL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_ControlPanel
{
public:
    QHBoxLayout *hboxLayout;
    QTabWidget *tabWidget;
    QWidget *MeshViewer;
    QVBoxLayout *vboxLayout;
    QGroupBox *quickSetViewportGroupBox;
    QHBoxLayout *hboxLayout1;
    QLabel *viewportTextLabel;
    QComboBox *viewportCombo;
    QGroupBox *objectsShowGroupBox;
    QVBoxLayout *vboxLayout1;
    QGridLayout *gridLayout;
    QCheckBox *hiddenLineCheckBox;
    QCheckBox *vertexCheckBox;
    QCheckBox *faceCheckBox;
    QCheckBox *edgeCheckBox;
    QCheckBox *fIdxCheckBox;
    QCheckBox *eIdxCheckBox;
    QCheckBox *vIdxCheckBox;
    QCheckBox *lightCheckBox;
    QCheckBox *vNormCheckBox;
    QCheckBox *coordsCheckBox;
    QCheckBox *fNormCheckBox;
    QCheckBox *bBoxCheckBox;
    QCheckBox *lightDirCheckBox;
    QCheckBox *editLitDirCheckBox;
    QCheckBox *shadeSmoothCheckBox;
    QCheckBox *colorMaterialCheckBox;
    QCheckBox *inertiaCheckBox;
    QCheckBox *perspectiveCheckBox;
    QFrame *line_2;
    QHBoxLayout *hboxLayout2;
    QLabel *elemTypeTextLabel;
    QComboBox *elemTypeComboBox;
    QLabel *indexTextLabel;
    QLineEdit *indexLineEdit;
    QPushButton *locatePushButton;
    QFrame *line_3;
    QHBoxLayout *hboxLayout3;
    QPushButton *propertiesPushButton;
    QSpacerItem *spacerItem;
    QSpacerItem *spacerItem1;
    QWidget *FeatureDetection;
    QVBoxLayout *vboxLayout2;
    QGroupBox *algoAndParamGroupBox;
    QVBoxLayout *vboxLayout3;
    QToolBox *algoAndParamToolBox;
    QWidget *page;
    QGridLayout *gridLayout1;
    QLabel *cNdAngleThreshLabel;
    QLabel *rEgAngleThreshLabel;
    QLineEdit *cNdPromAngleThreshLineEdit;
    QLineEdit *rEdAngleThreshLineEdit;
    QLineEdit *cNdAngleThreshLineEdit;
    QLabel *cNdPromAngleThreshLabel;
    QWidget *page_2;
    QWidget *page_3;
    QHBoxLayout *hboxLayout4;
    QPushButton *applyPushButton;
    QSpacerItem *spacerItem2;
    QFrame *line;
    QToolBox *featureViewAndEditToolBox;
    QWidget *page_4;
    QVBoxLayout *vboxLayout4;
    QSplitter *splitter_2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout2;
    QCheckBox *flatNdCheckBox;
    QCheckBox *cNdIdxCheckBox;
    QCheckBox *bNdNormCheckBox;
    QCheckBox *fNdIdxCheckBox;
    QCheckBox *ridgeEgCheckBox;
    QCheckBox *bouNdCheckBox;
    QCheckBox *cNdNormCheckBox;
    QCheckBox *cornerNdCheckBox;
    QCheckBox *bEdIdxCheckBox;
    QCheckBox *fNdNormCheckBox;
    QCheckBox *flatEdCheckBox;
    QCheckBox *ridgeNdCheckBox;
    QCheckBox *rNdIdxCheckBox;
    QCheckBox *rEdIdxCheckBox;
    QCheckBox *rNdNormCheckBox;
    QCheckBox *bNdIdxCheckBox;
    QCheckBox *fEdIdxCheckBox;
    QCheckBox *bouEdCheckBox;
    QWidget *layoutWidget1;
    QHBoxLayout *hboxLayout5;
    QPushButton *featureViewPropertiesPushButton;
    QSpacerItem *spacerItem3;
    QWidget *page_5;
    QVBoxLayout *vboxLayout5;
    QGroupBox *featureEdgeEditGroupBox;
    QHBoxLayout *hboxLayout6;
    QVBoxLayout *vboxLayout6;
    QHBoxLayout *hboxLayout7;
    QLabel *featureEdgeEditFromlabel;
    QLineEdit *featureEdgeEditFromLineEdit;
    QLabel *featureEdgeEditToLabel;
    QLineEdit *featureEdgeEditTolineEdit;
    QHBoxLayout *hboxLayout8;
    QLabel *featureEdgeEditEdIdxLabel;
    QLineEdit *featureEdgeEditEdIdxLineEdit;
    QLabel *featureEdgeEditAsLabel;
    QComboBox *featureEdgeEditAsComboBox;
    QGroupBox *featureNodeEditGroupBox;
    QHBoxLayout *hboxLayout9;
    QVBoxLayout *vboxLayout7;
    QHBoxLayout *hboxLayout10;
    QLabel *featureNodeEditFromLabel;
    QLineEdit *featureNodeEditFromLineEdit;
    QLabel *featureNodeEditToLabel;
    QLineEdit *featureNodeEditToLineEdit;
    QHBoxLayout *hboxLayout11;
    QLabel *featureNodeEditNdIdxLabel;
    QLineEdit *featureNodeEditNdIdxLineEdit;
    QLabel *featureNodeEditAsLabel;
    QComboBox *featureNodeEditAsComboBox;
    QSpacerItem *spacerItem4;
    QWidget *Dense__TopoTrans;
    QVBoxLayout *vboxLayout8;
    QToolBox *denseAndTopoTransToolBox;
    QWidget *page_6;
    QVBoxLayout *vboxLayout9;
    QGroupBox *uniformDensityGroupBox;
    QHBoxLayout *hboxLayout12;
    QLabel *globalSpacingLabel;
    QLineEdit *globalSpacingLineEdit;
    QGroupBox *bkgAndSorGroupBox;
    QHBoxLayout *hboxLayout13;
    QPushButton *ba3FilePushButton;
    QLineEdit *ba3FileLineEdit;
    QGroupBox *geometricDensityGroupBox;
    QHBoxLayout *hboxLayout14;
    QLabel *proportionalityCoefficientLabel;
    QLineEdit *proportionalityCoefficientLineEdit;
    QSpacerItem *spacerItem5;
    QWidget *page_7;
    QVBoxLayout *vboxLayout10;
    QGroupBox *mshGradContGroupBox;
    QVBoxLayout *vboxLayout11;
    QRadioButton *contHVarRadioButton;
    QHBoxLayout *hboxLayout15;
    QLabel *alphaLabel;
    QLineEdit *alphaLineEdit;
    QRadioButton *reduceHShockRadioButton;
    QHBoxLayout *hboxLayout16;
    QLabel *betaLabel;
    QLineEdit *betaLineEdit;
    QGroupBox *densitySmoothingGroupBox;
    QHBoxLayout *hboxLayout17;
    QLabel *parameterLabel;
    QLineEdit *parameterLineEdit;
    QSpacerItem *spacerItem6;
    QWidget *page_8;
    QVBoxLayout *vboxLayout12;
    QGroupBox *topoTransGroupBox;
    QVBoxLayout *vboxLayout13;
    QRadioButton *edgeSplitRadioButton;
    QRadioButton *vertexSplitRadioButton;
    QCheckBox *edgeCollapseCheckBox;
    QCheckBox *edgeSwapCheckBox;
    QSpacerItem *spacerItem7;
    QPushButton *denseAndTopoTransExecutePushButton;
    QWidget *Smoothing;
    QVBoxLayout *vboxLayout14;
    QToolBox *smoothingToolBox;
    QWidget *page_9;
    QVBoxLayout *vboxLayout15;
    QHBoxLayout *hboxLayout18;
    QLabel *smmethodLabel;
    QLineEdit *smmethodLineEdit;
    QHBoxLayout *hboxLayout19;
    QLabel *nsmoothsurfLabel;
    QLineEdit *nsmoothsurfLineEdit;
    QHBoxLayout *hboxLayout20;
    QLabel *relaxsurfLabel;
    QLineEdit *relaxsurfLineEdit;
    QWidget *page_10;
    QWidget *page_11;
    QPushButton *smoothingExecutePushButton;
    QSpacerItem *spacerItem8;

    void setupUi(QWidget *ControlPanel)
    {
    ControlPanel->setObjectName(QString::fromUtf8("ControlPanel"));
    hboxLayout = new QHBoxLayout(ControlPanel);
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(9);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    tabWidget = new QTabWidget(ControlPanel);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tabWidget->setWindowModality(Qt::NonModal);
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(13), static_cast<QSizePolicy::Policy>(13));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
    tabWidget->setSizePolicy(sizePolicy);
    tabWidget->setMinimumSize(QSize(150, 400));
    tabWidget->setTabShape(QTabWidget::Rounded);
    MeshViewer = new QWidget();
    MeshViewer->setObjectName(QString::fromUtf8("MeshViewer"));
    vboxLayout = new QVBoxLayout(MeshViewer);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(9);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    quickSetViewportGroupBox = new QGroupBox(MeshViewer);
    quickSetViewportGroupBox->setObjectName(QString::fromUtf8("quickSetViewportGroupBox"));
    quickSetViewportGroupBox->setWindowModality(Qt::NonModal);
    hboxLayout1 = new QHBoxLayout(quickSetViewportGroupBox);
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(9);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    viewportTextLabel = new QLabel(quickSetViewportGroupBox);
    viewportTextLabel->setObjectName(QString::fromUtf8("viewportTextLabel"));
    QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(5));
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(viewportTextLabel->sizePolicy().hasHeightForWidth());
    viewportTextLabel->setSizePolicy(sizePolicy1);
    viewportTextLabel->setAlignment(Qt::AlignCenter);

    hboxLayout1->addWidget(viewportTextLabel);

    viewportCombo = new QComboBox(quickSetViewportGroupBox);
    viewportCombo->setObjectName(QString::fromUtf8("viewportCombo"));

    hboxLayout1->addWidget(viewportCombo);


    vboxLayout->addWidget(quickSetViewportGroupBox);

    objectsShowGroupBox = new QGroupBox(MeshViewer);
    objectsShowGroupBox->setObjectName(QString::fromUtf8("objectsShowGroupBox"));
    objectsShowGroupBox->setAutoFillBackground(false);
    objectsShowGroupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    vboxLayout1 = new QVBoxLayout(objectsShowGroupBox);
    vboxLayout1->setSpacing(6);
    vboxLayout1->setMargin(9);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    gridLayout = new QGridLayout();
    gridLayout->setSpacing(6);
    gridLayout->setMargin(0);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    hiddenLineCheckBox = new QCheckBox(objectsShowGroupBox);
    hiddenLineCheckBox->setObjectName(QString::fromUtf8("hiddenLineCheckBox"));
    hiddenLineCheckBox->setEnabled(true);

    gridLayout->addWidget(hiddenLineCheckBox, 1, 1, 1, 1);

    vertexCheckBox = new QCheckBox(objectsShowGroupBox);
    vertexCheckBox->setObjectName(QString::fromUtf8("vertexCheckBox"));

    gridLayout->addWidget(vertexCheckBox, 0, 0, 1, 1);

    faceCheckBox = new QCheckBox(objectsShowGroupBox);
    faceCheckBox->setObjectName(QString::fromUtf8("faceCheckBox"));

    gridLayout->addWidget(faceCheckBox, 2, 0, 1, 1);

    edgeCheckBox = new QCheckBox(objectsShowGroupBox);
    edgeCheckBox->setObjectName(QString::fromUtf8("edgeCheckBox"));
    edgeCheckBox->setChecked(true);

    gridLayout->addWidget(edgeCheckBox, 1, 0, 1, 1);

    fIdxCheckBox = new QCheckBox(objectsShowGroupBox);
    fIdxCheckBox->setObjectName(QString::fromUtf8("fIdxCheckBox"));

    gridLayout->addWidget(fIdxCheckBox, 2, 2, 1, 1);

    eIdxCheckBox = new QCheckBox(objectsShowGroupBox);
    eIdxCheckBox->setObjectName(QString::fromUtf8("eIdxCheckBox"));

    gridLayout->addWidget(eIdxCheckBox, 1, 2, 1, 1);

    vIdxCheckBox = new QCheckBox(objectsShowGroupBox);
    vIdxCheckBox->setObjectName(QString::fromUtf8("vIdxCheckBox"));

    gridLayout->addWidget(vIdxCheckBox, 0, 2, 1, 1);

    lightCheckBox = new QCheckBox(objectsShowGroupBox);
    lightCheckBox->setObjectName(QString::fromUtf8("lightCheckBox"));
    lightCheckBox->setChecked(true);

    gridLayout->addWidget(lightCheckBox, 3, 0, 1, 1);

    vNormCheckBox = new QCheckBox(objectsShowGroupBox);
    vNormCheckBox->setObjectName(QString::fromUtf8("vNormCheckBox"));

    gridLayout->addWidget(vNormCheckBox, 0, 1, 1, 1);

    coordsCheckBox = new QCheckBox(objectsShowGroupBox);
    coordsCheckBox->setObjectName(QString::fromUtf8("coordsCheckBox"));

    gridLayout->addWidget(coordsCheckBox, 5, 1, 1, 1);

    fNormCheckBox = new QCheckBox(objectsShowGroupBox);
    fNormCheckBox->setObjectName(QString::fromUtf8("fNormCheckBox"));

    gridLayout->addWidget(fNormCheckBox, 2, 1, 1, 1);

    bBoxCheckBox = new QCheckBox(objectsShowGroupBox);
    bBoxCheckBox->setObjectName(QString::fromUtf8("bBoxCheckBox"));

    gridLayout->addWidget(bBoxCheckBox, 5, 2, 1, 1);

    lightDirCheckBox = new QCheckBox(objectsShowGroupBox);
    lightDirCheckBox->setObjectName(QString::fromUtf8("lightDirCheckBox"));

    gridLayout->addWidget(lightDirCheckBox, 3, 1, 1, 1);

    editLitDirCheckBox = new QCheckBox(objectsShowGroupBox);
    editLitDirCheckBox->setObjectName(QString::fromUtf8("editLitDirCheckBox"));
    editLitDirCheckBox->setEnabled(false);

    gridLayout->addWidget(editLitDirCheckBox, 3, 2, 1, 1);

    shadeSmoothCheckBox = new QCheckBox(objectsShowGroupBox);
    shadeSmoothCheckBox->setObjectName(QString::fromUtf8("shadeSmoothCheckBox"));
    shadeSmoothCheckBox->setChecked(true);

    gridLayout->addWidget(shadeSmoothCheckBox, 4, 0, 1, 1);

    colorMaterialCheckBox = new QCheckBox(objectsShowGroupBox);
    colorMaterialCheckBox->setObjectName(QString::fromUtf8("colorMaterialCheckBox"));

    gridLayout->addWidget(colorMaterialCheckBox, 4, 1, 1, 1);

    inertiaCheckBox = new QCheckBox(objectsShowGroupBox);
    inertiaCheckBox->setObjectName(QString::fromUtf8("inertiaCheckBox"));
    inertiaCheckBox->setEnabled(false);

    gridLayout->addWidget(inertiaCheckBox, 5, 0, 1, 1);

    perspectiveCheckBox = new QCheckBox(objectsShowGroupBox);
    perspectiveCheckBox->setObjectName(QString::fromUtf8("perspectiveCheckBox"));

    gridLayout->addWidget(perspectiveCheckBox, 4, 2, 1, 1);


    vboxLayout1->addLayout(gridLayout);

    line_2 = new QFrame(objectsShowGroupBox);
    line_2->setObjectName(QString::fromUtf8("line_2"));
    line_2->setFrameShape(QFrame::HLine);
    line_2->setFrameShadow(QFrame::Sunken);

    vboxLayout1->addWidget(line_2);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    elemTypeTextLabel = new QLabel(objectsShowGroupBox);
    elemTypeTextLabel->setObjectName(QString::fromUtf8("elemTypeTextLabel"));

    hboxLayout2->addWidget(elemTypeTextLabel);

    elemTypeComboBox = new QComboBox(objectsShowGroupBox);
    elemTypeComboBox->setObjectName(QString::fromUtf8("elemTypeComboBox"));

    hboxLayout2->addWidget(elemTypeComboBox);

    indexTextLabel = new QLabel(objectsShowGroupBox);
    indexTextLabel->setObjectName(QString::fromUtf8("indexTextLabel"));

    hboxLayout2->addWidget(indexTextLabel);

    indexLineEdit = new QLineEdit(objectsShowGroupBox);
    indexLineEdit->setObjectName(QString::fromUtf8("indexLineEdit"));

    hboxLayout2->addWidget(indexLineEdit);


    vboxLayout1->addLayout(hboxLayout2);

    locatePushButton = new QPushButton(objectsShowGroupBox);
    locatePushButton->setObjectName(QString::fromUtf8("locatePushButton"));

    vboxLayout1->addWidget(locatePushButton);

    line_3 = new QFrame(objectsShowGroupBox);
    line_3->setObjectName(QString::fromUtf8("line_3"));
    line_3->setFrameShape(QFrame::HLine);
    line_3->setFrameShadow(QFrame::Sunken);

    vboxLayout1->addWidget(line_3);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    propertiesPushButton = new QPushButton(objectsShowGroupBox);
    propertiesPushButton->setObjectName(QString::fromUtf8("propertiesPushButton"));

    hboxLayout3->addWidget(propertiesPushButton);

    spacerItem = new QSpacerItem(80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout3->addItem(spacerItem);


    vboxLayout1->addLayout(hboxLayout3);


    vboxLayout->addWidget(objectsShowGroupBox);

    spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout->addItem(spacerItem1);

    tabWidget->addTab(MeshViewer, QApplication::translate("ControlPanel", "MeshViewer", 0, QApplication::UnicodeUTF8));
    FeatureDetection = new QWidget();
    FeatureDetection->setObjectName(QString::fromUtf8("FeatureDetection"));
    vboxLayout2 = new QVBoxLayout(FeatureDetection);
    vboxLayout2->setSpacing(6);
    vboxLayout2->setMargin(9);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    algoAndParamGroupBox = new QGroupBox(FeatureDetection);
    algoAndParamGroupBox->setObjectName(QString::fromUtf8("algoAndParamGroupBox"));
    vboxLayout3 = new QVBoxLayout(algoAndParamGroupBox);
    vboxLayout3->setSpacing(6);
    vboxLayout3->setMargin(9);
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    algoAndParamToolBox = new QToolBox(algoAndParamGroupBox);
    algoAndParamToolBox->setObjectName(QString::fromUtf8("algoAndParamToolBox"));
    page = new QWidget();
    page->setObjectName(QString::fromUtf8("page"));
    page->setGeometry(QRect(0, 0, 212, 87));
    gridLayout1 = new QGridLayout(page);
    gridLayout1->setSpacing(6);
    gridLayout1->setMargin(9);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    cNdAngleThreshLabel = new QLabel(page);
    cNdAngleThreshLabel->setObjectName(QString::fromUtf8("cNdAngleThreshLabel"));

    gridLayout1->addWidget(cNdAngleThreshLabel, 1, 0, 1, 1);

    rEgAngleThreshLabel = new QLabel(page);
    rEgAngleThreshLabel->setObjectName(QString::fromUtf8("rEgAngleThreshLabel"));

    gridLayout1->addWidget(rEgAngleThreshLabel, 0, 0, 1, 1);

    cNdPromAngleThreshLineEdit = new QLineEdit(page);
    cNdPromAngleThreshLineEdit->setObjectName(QString::fromUtf8("cNdPromAngleThreshLineEdit"));

    gridLayout1->addWidget(cNdPromAngleThreshLineEdit, 2, 1, 1, 1);

    rEdAngleThreshLineEdit = new QLineEdit(page);
    rEdAngleThreshLineEdit->setObjectName(QString::fromUtf8("rEdAngleThreshLineEdit"));

    gridLayout1->addWidget(rEdAngleThreshLineEdit, 0, 1, 1, 1);

    cNdAngleThreshLineEdit = new QLineEdit(page);
    cNdAngleThreshLineEdit->setObjectName(QString::fromUtf8("cNdAngleThreshLineEdit"));
    cNdAngleThreshLineEdit->setEnabled(false);

    gridLayout1->addWidget(cNdAngleThreshLineEdit, 1, 1, 1, 1);

    cNdPromAngleThreshLabel = new QLabel(page);
    cNdPromAngleThreshLabel->setObjectName(QString::fromUtf8("cNdPromAngleThreshLabel"));

    gridLayout1->addWidget(cNdPromAngleThreshLabel, 2, 0, 1, 1);

    algoAndParamToolBox->addItem(page, QApplication::translate("ControlPanel", "Basic Algorithm", 0, QApplication::UnicodeUTF8));
    page_2 = new QWidget();
    page_2->setObjectName(QString::fromUtf8("page_2"));
    page_2->setGeometry(QRect(0, 0, 98, 28));
    algoAndParamToolBox->addItem(page_2, QApplication::translate("ControlPanel", "mtoolsurf's Algorithm", 0, QApplication::UnicodeUTF8));
    page_3 = new QWidget();
    page_3->setObjectName(QString::fromUtf8("page_3"));
    page_3->setGeometry(QRect(0, 0, 98, 28));
    algoAndParamToolBox->addItem(page_3, QApplication::translate("ControlPanel", "Jiang's Algorithm", 0, QApplication::UnicodeUTF8));

    vboxLayout3->addWidget(algoAndParamToolBox);

    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setSpacing(6);
    hboxLayout4->setMargin(0);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    applyPushButton = new QPushButton(algoAndParamGroupBox);
    applyPushButton->setObjectName(QString::fromUtf8("applyPushButton"));

    hboxLayout4->addWidget(applyPushButton);

    spacerItem2 = new QSpacerItem(211, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout4->addItem(spacerItem2);


    vboxLayout3->addLayout(hboxLayout4);


    vboxLayout2->addWidget(algoAndParamGroupBox);

    line = new QFrame(FeatureDetection);
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    vboxLayout2->addWidget(line);

    featureViewAndEditToolBox = new QToolBox(FeatureDetection);
    featureViewAndEditToolBox->setObjectName(QString::fromUtf8("featureViewAndEditToolBox"));
    featureViewAndEditToolBox->setEnabled(true);
    page_4 = new QWidget();
    page_4->setObjectName(QString::fromUtf8("page_4"));
    page_4->setGeometry(QRect(0, 0, 98, 34));
    vboxLayout4 = new QVBoxLayout(page_4);
    vboxLayout4->setSpacing(6);
    vboxLayout4->setMargin(9);
    vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
    splitter_2 = new QSplitter(page_4);
    splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
    splitter_2->setOrientation(Qt::Vertical);
    layoutWidget = new QWidget(splitter_2);
    layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    gridLayout2 = new QGridLayout(layoutWidget);
    gridLayout2->setSpacing(6);
    gridLayout2->setMargin(0);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    flatNdCheckBox = new QCheckBox(layoutWidget);
    flatNdCheckBox->setObjectName(QString::fromUtf8("flatNdCheckBox"));

    gridLayout2->addWidget(flatNdCheckBox, 3, 0, 1, 1);

    cNdIdxCheckBox = new QCheckBox(layoutWidget);
    cNdIdxCheckBox->setObjectName(QString::fromUtf8("cNdIdxCheckBox"));

    gridLayout2->addWidget(cNdIdxCheckBox, 1, 1, 1, 1);

    bNdNormCheckBox = new QCheckBox(layoutWidget);
    bNdNormCheckBox->setObjectName(QString::fromUtf8("bNdNormCheckBox"));

    gridLayout2->addWidget(bNdNormCheckBox, 0, 2, 1, 1);

    fNdIdxCheckBox = new QCheckBox(layoutWidget);
    fNdIdxCheckBox->setObjectName(QString::fromUtf8("fNdIdxCheckBox"));

    gridLayout2->addWidget(fNdIdxCheckBox, 3, 1, 1, 1);

    ridgeEgCheckBox = new QCheckBox(layoutWidget);
    ridgeEgCheckBox->setObjectName(QString::fromUtf8("ridgeEgCheckBox"));

    gridLayout2->addWidget(ridgeEgCheckBox, 4, 1, 1, 1);

    bouNdCheckBox = new QCheckBox(layoutWidget);
    bouNdCheckBox->setObjectName(QString::fromUtf8("bouNdCheckBox"));

    gridLayout2->addWidget(bouNdCheckBox, 0, 0, 1, 1);

    cNdNormCheckBox = new QCheckBox(layoutWidget);
    cNdNormCheckBox->setObjectName(QString::fromUtf8("cNdNormCheckBox"));

    gridLayout2->addWidget(cNdNormCheckBox, 1, 2, 1, 1);

    cornerNdCheckBox = new QCheckBox(layoutWidget);
    cornerNdCheckBox->setObjectName(QString::fromUtf8("cornerNdCheckBox"));

    gridLayout2->addWidget(cornerNdCheckBox, 1, 0, 1, 1);

    bEdIdxCheckBox = new QCheckBox(layoutWidget);
    bEdIdxCheckBox->setObjectName(QString::fromUtf8("bEdIdxCheckBox"));

    gridLayout2->addWidget(bEdIdxCheckBox, 5, 0, 1, 1);

    fNdNormCheckBox = new QCheckBox(layoutWidget);
    fNdNormCheckBox->setObjectName(QString::fromUtf8("fNdNormCheckBox"));

    gridLayout2->addWidget(fNdNormCheckBox, 3, 2, 1, 1);

    flatEdCheckBox = new QCheckBox(layoutWidget);
    flatEdCheckBox->setObjectName(QString::fromUtf8("flatEdCheckBox"));

    gridLayout2->addWidget(flatEdCheckBox, 4, 2, 1, 1);

    ridgeNdCheckBox = new QCheckBox(layoutWidget);
    ridgeNdCheckBox->setObjectName(QString::fromUtf8("ridgeNdCheckBox"));

    gridLayout2->addWidget(ridgeNdCheckBox, 2, 0, 1, 1);

    rNdIdxCheckBox = new QCheckBox(layoutWidget);
    rNdIdxCheckBox->setObjectName(QString::fromUtf8("rNdIdxCheckBox"));

    gridLayout2->addWidget(rNdIdxCheckBox, 2, 1, 1, 1);

    rEdIdxCheckBox = new QCheckBox(layoutWidget);
    rEdIdxCheckBox->setObjectName(QString::fromUtf8("rEdIdxCheckBox"));

    gridLayout2->addWidget(rEdIdxCheckBox, 5, 1, 1, 1);

    rNdNormCheckBox = new QCheckBox(layoutWidget);
    rNdNormCheckBox->setObjectName(QString::fromUtf8("rNdNormCheckBox"));

    gridLayout2->addWidget(rNdNormCheckBox, 2, 2, 1, 1);

    bNdIdxCheckBox = new QCheckBox(layoutWidget);
    bNdIdxCheckBox->setObjectName(QString::fromUtf8("bNdIdxCheckBox"));

    gridLayout2->addWidget(bNdIdxCheckBox, 0, 1, 1, 1);

    fEdIdxCheckBox = new QCheckBox(layoutWidget);
    fEdIdxCheckBox->setObjectName(QString::fromUtf8("fEdIdxCheckBox"));

    gridLayout2->addWidget(fEdIdxCheckBox, 5, 2, 1, 1);

    bouEdCheckBox = new QCheckBox(layoutWidget);
    bouEdCheckBox->setObjectName(QString::fromUtf8("bouEdCheckBox"));

    gridLayout2->addWidget(bouEdCheckBox, 4, 0, 1, 1);

    splitter_2->addWidget(layoutWidget);
    layoutWidget1 = new QWidget(splitter_2);
    layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
    hboxLayout5 = new QHBoxLayout(layoutWidget1);
    hboxLayout5->setSpacing(6);
    hboxLayout5->setMargin(0);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    featureViewPropertiesPushButton = new QPushButton(layoutWidget1);
    featureViewPropertiesPushButton->setObjectName(QString::fromUtf8("featureViewPropertiesPushButton"));

    hboxLayout5->addWidget(featureViewPropertiesPushButton);

    spacerItem3 = new QSpacerItem(231, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout5->addItem(spacerItem3);

    splitter_2->addWidget(layoutWidget1);

    vboxLayout4->addWidget(splitter_2);

    featureViewAndEditToolBox->addItem(page_4, QApplication::translate("ControlPanel", "Feature View", 0, QApplication::UnicodeUTF8));
    page_5 = new QWidget();
    page_5->setObjectName(QString::fromUtf8("page_5"));
    page_5->setGeometry(QRect(0, 0, 237, 190));
    vboxLayout5 = new QVBoxLayout(page_5);
    vboxLayout5->setSpacing(6);
    vboxLayout5->setMargin(9);
    vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
    featureEdgeEditGroupBox = new QGroupBox(page_5);
    featureEdgeEditGroupBox->setObjectName(QString::fromUtf8("featureEdgeEditGroupBox"));
    featureEdgeEditGroupBox->setCheckable(true);
    featureEdgeEditGroupBox->setChecked(false);
    hboxLayout6 = new QHBoxLayout(featureEdgeEditGroupBox);
    hboxLayout6->setSpacing(6);
    hboxLayout6->setMargin(9);
    hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
    vboxLayout6 = new QVBoxLayout();
    vboxLayout6->setSpacing(6);
    vboxLayout6->setMargin(0);
    vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
    hboxLayout7 = new QHBoxLayout();
    hboxLayout7->setSpacing(6);
    hboxLayout7->setMargin(0);
    hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
    featureEdgeEditFromlabel = new QLabel(featureEdgeEditGroupBox);
    featureEdgeEditFromlabel->setObjectName(QString::fromUtf8("featureEdgeEditFromlabel"));

    hboxLayout7->addWidget(featureEdgeEditFromlabel);

    featureEdgeEditFromLineEdit = new QLineEdit(featureEdgeEditGroupBox);
    featureEdgeEditFromLineEdit->setObjectName(QString::fromUtf8("featureEdgeEditFromLineEdit"));

    hboxLayout7->addWidget(featureEdgeEditFromLineEdit);

    featureEdgeEditToLabel = new QLabel(featureEdgeEditGroupBox);
    featureEdgeEditToLabel->setObjectName(QString::fromUtf8("featureEdgeEditToLabel"));

    hboxLayout7->addWidget(featureEdgeEditToLabel);

    featureEdgeEditTolineEdit = new QLineEdit(featureEdgeEditGroupBox);
    featureEdgeEditTolineEdit->setObjectName(QString::fromUtf8("featureEdgeEditTolineEdit"));

    hboxLayout7->addWidget(featureEdgeEditTolineEdit);


    vboxLayout6->addLayout(hboxLayout7);

    hboxLayout8 = new QHBoxLayout();
    hboxLayout8->setSpacing(6);
    hboxLayout8->setMargin(0);
    hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
    featureEdgeEditEdIdxLabel = new QLabel(featureEdgeEditGroupBox);
    featureEdgeEditEdIdxLabel->setObjectName(QString::fromUtf8("featureEdgeEditEdIdxLabel"));

    hboxLayout8->addWidget(featureEdgeEditEdIdxLabel);

    featureEdgeEditEdIdxLineEdit = new QLineEdit(featureEdgeEditGroupBox);
    featureEdgeEditEdIdxLineEdit->setObjectName(QString::fromUtf8("featureEdgeEditEdIdxLineEdit"));

    hboxLayout8->addWidget(featureEdgeEditEdIdxLineEdit);


    vboxLayout6->addLayout(hboxLayout8);


    hboxLayout6->addLayout(vboxLayout6);

    featureEdgeEditAsLabel = new QLabel(featureEdgeEditGroupBox);
    featureEdgeEditAsLabel->setObjectName(QString::fromUtf8("featureEdgeEditAsLabel"));

    hboxLayout6->addWidget(featureEdgeEditAsLabel);

    featureEdgeEditAsComboBox = new QComboBox(featureEdgeEditGroupBox);
    featureEdgeEditAsComboBox->setObjectName(QString::fromUtf8("featureEdgeEditAsComboBox"));

    hboxLayout6->addWidget(featureEdgeEditAsComboBox);


    vboxLayout5->addWidget(featureEdgeEditGroupBox);

    featureNodeEditGroupBox = new QGroupBox(page_5);
    featureNodeEditGroupBox->setObjectName(QString::fromUtf8("featureNodeEditGroupBox"));
    featureNodeEditGroupBox->setCheckable(true);
    featureNodeEditGroupBox->setChecked(false);
    hboxLayout9 = new QHBoxLayout(featureNodeEditGroupBox);
    hboxLayout9->setSpacing(6);
    hboxLayout9->setMargin(9);
    hboxLayout9->setObjectName(QString::fromUtf8("hboxLayout9"));
    vboxLayout7 = new QVBoxLayout();
    vboxLayout7->setSpacing(6);
    vboxLayout7->setMargin(0);
    vboxLayout7->setObjectName(QString::fromUtf8("vboxLayout7"));
    hboxLayout10 = new QHBoxLayout();
    hboxLayout10->setSpacing(6);
    hboxLayout10->setMargin(0);
    hboxLayout10->setObjectName(QString::fromUtf8("hboxLayout10"));
    featureNodeEditFromLabel = new QLabel(featureNodeEditGroupBox);
    featureNodeEditFromLabel->setObjectName(QString::fromUtf8("featureNodeEditFromLabel"));

    hboxLayout10->addWidget(featureNodeEditFromLabel);

    featureNodeEditFromLineEdit = new QLineEdit(featureNodeEditGroupBox);
    featureNodeEditFromLineEdit->setObjectName(QString::fromUtf8("featureNodeEditFromLineEdit"));

    hboxLayout10->addWidget(featureNodeEditFromLineEdit);

    featureNodeEditToLabel = new QLabel(featureNodeEditGroupBox);
    featureNodeEditToLabel->setObjectName(QString::fromUtf8("featureNodeEditToLabel"));

    hboxLayout10->addWidget(featureNodeEditToLabel);

    featureNodeEditToLineEdit = new QLineEdit(featureNodeEditGroupBox);
    featureNodeEditToLineEdit->setObjectName(QString::fromUtf8("featureNodeEditToLineEdit"));

    hboxLayout10->addWidget(featureNodeEditToLineEdit);


    vboxLayout7->addLayout(hboxLayout10);

    hboxLayout11 = new QHBoxLayout();
    hboxLayout11->setSpacing(6);
    hboxLayout11->setMargin(0);
    hboxLayout11->setObjectName(QString::fromUtf8("hboxLayout11"));
    featureNodeEditNdIdxLabel = new QLabel(featureNodeEditGroupBox);
    featureNodeEditNdIdxLabel->setObjectName(QString::fromUtf8("featureNodeEditNdIdxLabel"));

    hboxLayout11->addWidget(featureNodeEditNdIdxLabel);

    featureNodeEditNdIdxLineEdit = new QLineEdit(featureNodeEditGroupBox);
    featureNodeEditNdIdxLineEdit->setObjectName(QString::fromUtf8("featureNodeEditNdIdxLineEdit"));

    hboxLayout11->addWidget(featureNodeEditNdIdxLineEdit);


    vboxLayout7->addLayout(hboxLayout11);


    hboxLayout9->addLayout(vboxLayout7);

    featureNodeEditAsLabel = new QLabel(featureNodeEditGroupBox);
    featureNodeEditAsLabel->setObjectName(QString::fromUtf8("featureNodeEditAsLabel"));

    hboxLayout9->addWidget(featureNodeEditAsLabel);

    featureNodeEditAsComboBox = new QComboBox(featureNodeEditGroupBox);
    featureNodeEditAsComboBox->setObjectName(QString::fromUtf8("featureNodeEditAsComboBox"));

    hboxLayout9->addWidget(featureNodeEditAsComboBox);


    vboxLayout5->addWidget(featureNodeEditGroupBox);

    featureViewAndEditToolBox->addItem(page_5, QApplication::translate("ControlPanel", "Feature Edit", 0, QApplication::UnicodeUTF8));

    vboxLayout2->addWidget(featureViewAndEditToolBox);

    spacerItem4 = new QSpacerItem(20, 31, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout2->addItem(spacerItem4);

    tabWidget->addTab(FeatureDetection, QApplication::translate("ControlPanel", "FeatureDetection", 0, QApplication::UnicodeUTF8));
    Dense__TopoTrans = new QWidget();
    Dense__TopoTrans->setObjectName(QString::fromUtf8("Dense__TopoTrans"));
    vboxLayout8 = new QVBoxLayout(Dense__TopoTrans);
    vboxLayout8->setSpacing(6);
    vboxLayout8->setMargin(9);
    vboxLayout8->setObjectName(QString::fromUtf8("vboxLayout8"));
    denseAndTopoTransToolBox = new QToolBox(Dense__TopoTrans);
    denseAndTopoTransToolBox->setObjectName(QString::fromUtf8("denseAndTopoTransToolBox"));
    page_6 = new QWidget();
    page_6->setObjectName(QString::fromUtf8("page_6"));
    page_6->setGeometry(QRect(0, 0, 249, 419));
    vboxLayout9 = new QVBoxLayout(page_6);
    vboxLayout9->setSpacing(6);
    vboxLayout9->setMargin(9);
    vboxLayout9->setObjectName(QString::fromUtf8("vboxLayout9"));
    uniformDensityGroupBox = new QGroupBox(page_6);
    uniformDensityGroupBox->setObjectName(QString::fromUtf8("uniformDensityGroupBox"));
    uniformDensityGroupBox->setCheckable(true);
    uniformDensityGroupBox->setChecked(false);
    hboxLayout12 = new QHBoxLayout(uniformDensityGroupBox);
    hboxLayout12->setSpacing(6);
    hboxLayout12->setMargin(9);
    hboxLayout12->setObjectName(QString::fromUtf8("hboxLayout12"));
    globalSpacingLabel = new QLabel(uniformDensityGroupBox);
    globalSpacingLabel->setObjectName(QString::fromUtf8("globalSpacingLabel"));

    hboxLayout12->addWidget(globalSpacingLabel);

    globalSpacingLineEdit = new QLineEdit(uniformDensityGroupBox);
    globalSpacingLineEdit->setObjectName(QString::fromUtf8("globalSpacingLineEdit"));

    hboxLayout12->addWidget(globalSpacingLineEdit);


    vboxLayout9->addWidget(uniformDensityGroupBox);

    bkgAndSorGroupBox = new QGroupBox(page_6);
    bkgAndSorGroupBox->setObjectName(QString::fromUtf8("bkgAndSorGroupBox"));
    bkgAndSorGroupBox->setCheckable(true);
    bkgAndSorGroupBox->setChecked(true);
    hboxLayout13 = new QHBoxLayout(bkgAndSorGroupBox);
    hboxLayout13->setSpacing(6);
    hboxLayout13->setMargin(9);
    hboxLayout13->setObjectName(QString::fromUtf8("hboxLayout13"));
    ba3FilePushButton = new QPushButton(bkgAndSorGroupBox);
    ba3FilePushButton->setObjectName(QString::fromUtf8("ba3FilePushButton"));

    hboxLayout13->addWidget(ba3FilePushButton);

    ba3FileLineEdit = new QLineEdit(bkgAndSorGroupBox);
    ba3FileLineEdit->setObjectName(QString::fromUtf8("ba3FileLineEdit"));

    hboxLayout13->addWidget(ba3FileLineEdit);


    vboxLayout9->addWidget(bkgAndSorGroupBox);

    geometricDensityGroupBox = new QGroupBox(page_6);
    geometricDensityGroupBox->setObjectName(QString::fromUtf8("geometricDensityGroupBox"));
    geometricDensityGroupBox->setCheckable(true);
    geometricDensityGroupBox->setChecked(false);
    hboxLayout14 = new QHBoxLayout(geometricDensityGroupBox);
    hboxLayout14->setSpacing(6);
    hboxLayout14->setMargin(9);
    hboxLayout14->setObjectName(QString::fromUtf8("hboxLayout14"));
    proportionalityCoefficientLabel = new QLabel(geometricDensityGroupBox);
    proportionalityCoefficientLabel->setObjectName(QString::fromUtf8("proportionalityCoefficientLabel"));

    hboxLayout14->addWidget(proportionalityCoefficientLabel);

    proportionalityCoefficientLineEdit = new QLineEdit(geometricDensityGroupBox);
    proportionalityCoefficientLineEdit->setObjectName(QString::fromUtf8("proportionalityCoefficientLineEdit"));

    hboxLayout14->addWidget(proportionalityCoefficientLineEdit);


    vboxLayout9->addWidget(geometricDensityGroupBox);

    spacerItem5 = new QSpacerItem(20, 261, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout9->addItem(spacerItem5);

    denseAndTopoTransToolBox->addItem(page_6, QApplication::translate("ControlPanel", "Density Specification", 0, QApplication::UnicodeUTF8));
    page_7 = new QWidget();
    page_7->setObjectName(QString::fromUtf8("page_7"));
    page_7->setGeometry(QRect(0, 0, 193, 209));
    vboxLayout10 = new QVBoxLayout(page_7);
    vboxLayout10->setSpacing(6);
    vboxLayout10->setMargin(9);
    vboxLayout10->setObjectName(QString::fromUtf8("vboxLayout10"));
    mshGradContGroupBox = new QGroupBox(page_7);
    mshGradContGroupBox->setObjectName(QString::fromUtf8("mshGradContGroupBox"));
    mshGradContGroupBox->setCheckable(true);
    mshGradContGroupBox->setChecked(false);
    vboxLayout11 = new QVBoxLayout(mshGradContGroupBox);
    vboxLayout11->setSpacing(6);
    vboxLayout11->setMargin(9);
    vboxLayout11->setObjectName(QString::fromUtf8("vboxLayout11"));
    contHVarRadioButton = new QRadioButton(mshGradContGroupBox);
    contHVarRadioButton->setObjectName(QString::fromUtf8("contHVarRadioButton"));

    vboxLayout11->addWidget(contHVarRadioButton);

    hboxLayout15 = new QHBoxLayout();
    hboxLayout15->setSpacing(6);
    hboxLayout15->setMargin(0);
    hboxLayout15->setObjectName(QString::fromUtf8("hboxLayout15"));
    alphaLabel = new QLabel(mshGradContGroupBox);
    alphaLabel->setObjectName(QString::fromUtf8("alphaLabel"));

    hboxLayout15->addWidget(alphaLabel);

    alphaLineEdit = new QLineEdit(mshGradContGroupBox);
    alphaLineEdit->setObjectName(QString::fromUtf8("alphaLineEdit"));

    hboxLayout15->addWidget(alphaLineEdit);


    vboxLayout11->addLayout(hboxLayout15);

    reduceHShockRadioButton = new QRadioButton(mshGradContGroupBox);
    reduceHShockRadioButton->setObjectName(QString::fromUtf8("reduceHShockRadioButton"));

    vboxLayout11->addWidget(reduceHShockRadioButton);

    hboxLayout16 = new QHBoxLayout();
    hboxLayout16->setSpacing(6);
    hboxLayout16->setMargin(0);
    hboxLayout16->setObjectName(QString::fromUtf8("hboxLayout16"));
    betaLabel = new QLabel(mshGradContGroupBox);
    betaLabel->setObjectName(QString::fromUtf8("betaLabel"));

    hboxLayout16->addWidget(betaLabel);

    betaLineEdit = new QLineEdit(mshGradContGroupBox);
    betaLineEdit->setObjectName(QString::fromUtf8("betaLineEdit"));

    hboxLayout16->addWidget(betaLineEdit);


    vboxLayout11->addLayout(hboxLayout16);


    vboxLayout10->addWidget(mshGradContGroupBox);

    densitySmoothingGroupBox = new QGroupBox(page_7);
    densitySmoothingGroupBox->setObjectName(QString::fromUtf8("densitySmoothingGroupBox"));
    densitySmoothingGroupBox->setCheckable(true);
    densitySmoothingGroupBox->setChecked(false);
    hboxLayout17 = new QHBoxLayout(densitySmoothingGroupBox);
    hboxLayout17->setSpacing(6);
    hboxLayout17->setMargin(9);
    hboxLayout17->setObjectName(QString::fromUtf8("hboxLayout17"));
    parameterLabel = new QLabel(densitySmoothingGroupBox);
    parameterLabel->setObjectName(QString::fromUtf8("parameterLabel"));

    hboxLayout17->addWidget(parameterLabel);

    parameterLineEdit = new QLineEdit(densitySmoothingGroupBox);
    parameterLineEdit->setObjectName(QString::fromUtf8("parameterLineEdit"));

    hboxLayout17->addWidget(parameterLineEdit);


    vboxLayout10->addWidget(densitySmoothingGroupBox);

    spacerItem6 = new QSpacerItem(20, 251, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout10->addItem(spacerItem6);

    denseAndTopoTransToolBox->addItem(page_7, QApplication::translate("ControlPanel", "Density Correction", 0, QApplication::UnicodeUTF8));
    page_8 = new QWidget();
    page_8->setObjectName(QString::fromUtf8("page_8"));
    page_8->setGeometry(QRect(0, 0, 184, 143));
    vboxLayout12 = new QVBoxLayout(page_8);
    vboxLayout12->setSpacing(6);
    vboxLayout12->setMargin(9);
    vboxLayout12->setObjectName(QString::fromUtf8("vboxLayout12"));
    topoTransGroupBox = new QGroupBox(page_8);
    topoTransGroupBox->setObjectName(QString::fromUtf8("topoTransGroupBox"));
    vboxLayout13 = new QVBoxLayout(topoTransGroupBox);
    vboxLayout13->setSpacing(6);
    vboxLayout13->setMargin(9);
    vboxLayout13->setObjectName(QString::fromUtf8("vboxLayout13"));
    edgeSplitRadioButton = new QRadioButton(topoTransGroupBox);
    edgeSplitRadioButton->setObjectName(QString::fromUtf8("edgeSplitRadioButton"));
    edgeSplitRadioButton->setChecked(true);

    vboxLayout13->addWidget(edgeSplitRadioButton);

    vertexSplitRadioButton = new QRadioButton(topoTransGroupBox);
    vertexSplitRadioButton->setObjectName(QString::fromUtf8("vertexSplitRadioButton"));
    vertexSplitRadioButton->setChecked(false);

    vboxLayout13->addWidget(vertexSplitRadioButton);

    edgeCollapseCheckBox = new QCheckBox(topoTransGroupBox);
    edgeCollapseCheckBox->setObjectName(QString::fromUtf8("edgeCollapseCheckBox"));
    edgeCollapseCheckBox->setEnabled(false);
    edgeCollapseCheckBox->setChecked(true);

    vboxLayout13->addWidget(edgeCollapseCheckBox);

    edgeSwapCheckBox = new QCheckBox(topoTransGroupBox);
    edgeSwapCheckBox->setObjectName(QString::fromUtf8("edgeSwapCheckBox"));
    edgeSwapCheckBox->setEnabled(false);
    edgeSwapCheckBox->setChecked(true);

    vboxLayout13->addWidget(edgeSwapCheckBox);


    vboxLayout12->addWidget(topoTransGroupBox);

    spacerItem7 = new QSpacerItem(20, 271, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout12->addItem(spacerItem7);

    denseAndTopoTransToolBox->addItem(page_8, QApplication::translate("ControlPanel", "Topology Transformation", 0, QApplication::UnicodeUTF8));

    vboxLayout8->addWidget(denseAndTopoTransToolBox);

    denseAndTopoTransExecutePushButton = new QPushButton(Dense__TopoTrans);
    denseAndTopoTransExecutePushButton->setObjectName(QString::fromUtf8("denseAndTopoTransExecutePushButton"));

    vboxLayout8->addWidget(denseAndTopoTransExecutePushButton);

    tabWidget->addTab(Dense__TopoTrans, QApplication::translate("ControlPanel", "Dense&&TopoTrans", 0, QApplication::UnicodeUTF8));
    Smoothing = new QWidget();
    Smoothing->setObjectName(QString::fromUtf8("Smoothing"));
    vboxLayout14 = new QVBoxLayout(Smoothing);
    vboxLayout14->setSpacing(6);
    vboxLayout14->setMargin(9);
    vboxLayout14->setObjectName(QString::fromUtf8("vboxLayout14"));
    smoothingToolBox = new QToolBox(Smoothing);
    smoothingToolBox->setObjectName(QString::fromUtf8("smoothingToolBox"));
    page_9 = new QWidget();
    page_9->setObjectName(QString::fromUtf8("page_9"));
    page_9->setGeometry(QRect(0, 0, 249, 166));
    vboxLayout15 = new QVBoxLayout(page_9);
    vboxLayout15->setSpacing(6);
    vboxLayout15->setMargin(9);
    vboxLayout15->setObjectName(QString::fromUtf8("vboxLayout15"));
    hboxLayout18 = new QHBoxLayout();
    hboxLayout18->setSpacing(6);
    hboxLayout18->setMargin(0);
    hboxLayout18->setObjectName(QString::fromUtf8("hboxLayout18"));
    smmethodLabel = new QLabel(page_9);
    smmethodLabel->setObjectName(QString::fromUtf8("smmethodLabel"));

    hboxLayout18->addWidget(smmethodLabel);

    smmethodLineEdit = new QLineEdit(page_9);
    smmethodLineEdit->setObjectName(QString::fromUtf8("smmethodLineEdit"));

    hboxLayout18->addWidget(smmethodLineEdit);


    vboxLayout15->addLayout(hboxLayout18);

    hboxLayout19 = new QHBoxLayout();
    hboxLayout19->setSpacing(6);
    hboxLayout19->setMargin(0);
    hboxLayout19->setObjectName(QString::fromUtf8("hboxLayout19"));
    nsmoothsurfLabel = new QLabel(page_9);
    nsmoothsurfLabel->setObjectName(QString::fromUtf8("nsmoothsurfLabel"));

    hboxLayout19->addWidget(nsmoothsurfLabel);

    nsmoothsurfLineEdit = new QLineEdit(page_9);
    nsmoothsurfLineEdit->setObjectName(QString::fromUtf8("nsmoothsurfLineEdit"));

    hboxLayout19->addWidget(nsmoothsurfLineEdit);


    vboxLayout15->addLayout(hboxLayout19);

    hboxLayout20 = new QHBoxLayout();
    hboxLayout20->setSpacing(6);
    hboxLayout20->setMargin(0);
    hboxLayout20->setObjectName(QString::fromUtf8("hboxLayout20"));
    relaxsurfLabel = new QLabel(page_9);
    relaxsurfLabel->setObjectName(QString::fromUtf8("relaxsurfLabel"));

    hboxLayout20->addWidget(relaxsurfLabel);

    relaxsurfLineEdit = new QLineEdit(page_9);
    relaxsurfLineEdit->setObjectName(QString::fromUtf8("relaxsurfLineEdit"));

    hboxLayout20->addWidget(relaxsurfLineEdit);


    vboxLayout15->addLayout(hboxLayout20);

    smoothingToolBox->addItem(page_9, QApplication::translate("ControlPanel", "mtoolsurf's Algorithm", 0, QApplication::UnicodeUTF8));
    page_10 = new QWidget();
    page_10->setObjectName(QString::fromUtf8("page_10"));
    page_10->setGeometry(QRect(0, 0, 249, 166));
    smoothingToolBox->addItem(page_10, QApplication::translate("ControlPanel", "Other's Algorithm", 0, QApplication::UnicodeUTF8));
    page_11 = new QWidget();
    page_11->setObjectName(QString::fromUtf8("page_11"));
    page_11->setGeometry(QRect(0, 0, 249, 166));
    smoothingToolBox->addItem(page_11, QApplication::translate("ControlPanel", "Reserved", 0, QApplication::UnicodeUTF8));

    vboxLayout14->addWidget(smoothingToolBox);

    smoothingExecutePushButton = new QPushButton(Smoothing);
    smoothingExecutePushButton->setObjectName(QString::fromUtf8("smoothingExecutePushButton"));

    vboxLayout14->addWidget(smoothingExecutePushButton);

    spacerItem8 = new QSpacerItem(20, 161, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout14->addItem(spacerItem8);

    tabWidget->addTab(Smoothing, QApplication::translate("ControlPanel", "Smoothing", 0, QApplication::UnicodeUTF8));

    hboxLayout->addWidget(tabWidget);

    viewportTextLabel->setBuddy(viewportCombo);
    elemTypeTextLabel->setBuddy(elemTypeComboBox);
    indexTextLabel->setBuddy(indexLineEdit);
    cNdAngleThreshLabel->setBuddy(cNdAngleThreshLineEdit);
    rEgAngleThreshLabel->setBuddy(rEdAngleThreshLineEdit);
    cNdPromAngleThreshLabel->setBuddy(cNdPromAngleThreshLineEdit);
    featureEdgeEditFromlabel->setBuddy(featureEdgeEditFromLineEdit);
    featureEdgeEditToLabel->setBuddy(featureEdgeEditTolineEdit);
    featureEdgeEditEdIdxLabel->setBuddy(featureEdgeEditEdIdxLineEdit);
    featureEdgeEditAsLabel->setBuddy(featureEdgeEditAsComboBox);
    featureNodeEditFromLabel->setBuddy(featureNodeEditFromLineEdit);
    featureNodeEditToLabel->setBuddy(featureNodeEditToLineEdit);
    featureNodeEditNdIdxLabel->setBuddy(featureNodeEditNdIdxLineEdit);
    featureNodeEditAsLabel->setBuddy(featureNodeEditAsComboBox);
    globalSpacingLabel->setBuddy(globalSpacingLineEdit);
    proportionalityCoefficientLabel->setBuddy(proportionalityCoefficientLineEdit);
    alphaLabel->setBuddy(alphaLineEdit);
    betaLabel->setBuddy(betaLineEdit);
    parameterLabel->setBuddy(parameterLineEdit);
    smmethodLabel->setBuddy(smmethodLineEdit);
    nsmoothsurfLabel->setBuddy(nsmoothsurfLineEdit);
    relaxsurfLabel->setBuddy(relaxsurfLineEdit);

    retranslateUi(ControlPanel);

    QSize size(291, 591);
    size = size.expandedTo(ControlPanel->minimumSizeHint());
    ControlPanel->resize(size);

    QObject::connect(contHVarRadioButton, SIGNAL(toggled(bool)), alphaLabel, SLOT(setEnabled(bool)));
    QObject::connect(contHVarRadioButton, SIGNAL(toggled(bool)), alphaLineEdit, SLOT(setEnabled(bool)));
    QObject::connect(reduceHShockRadioButton, SIGNAL(toggled(bool)), betaLabel, SLOT(setEnabled(bool)));
    QObject::connect(reduceHShockRadioButton, SIGNAL(toggled(bool)), betaLineEdit, SLOT(setEnabled(bool)));

    tabWidget->setCurrentIndex(0);
    algoAndParamToolBox->setCurrentIndex(0);
    featureViewAndEditToolBox->setCurrentIndex(1);
    denseAndTopoTransToolBox->setCurrentIndex(0);
    smoothingToolBox->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(ControlPanel);
    } // setupUi

    void retranslateUi(QWidget *ControlPanel)
    {
    ControlPanel->setWindowTitle(QApplication::translate("ControlPanel", "Form", 0, QApplication::UnicodeUTF8));
    quickSetViewportGroupBox->setTitle(QApplication::translate("ControlPanel", "Quick Set Viewport", 0, QApplication::UnicodeUTF8));
    viewportTextLabel->setText(QApplication::translate("ControlPanel", "Viewport:", 0, QApplication::UnicodeUTF8));
    viewportCombo->clear();
    viewportCombo->addItem(QApplication::translate("ControlPanel", "------", 0, QApplication::UnicodeUTF8));
    viewportCombo->addItem(QApplication::translate("ControlPanel", "Reset", 0, QApplication::UnicodeUTF8));
    viewportCombo->addItem(QApplication::translate("ControlPanel", "Center", 0, QApplication::UnicodeUTF8));
    viewportCombo->addItem(QApplication::translate("ControlPanel", "Isomet", 0, QApplication::UnicodeUTF8));
    viewportCombo->addItem(QApplication::translate("ControlPanel", "X-Y Plane", 0, QApplication::UnicodeUTF8));
    viewportCombo->addItem(QApplication::translate("ControlPanel", "Y-X Plane", 0, QApplication::UnicodeUTF8));
    viewportCombo->addItem(QApplication::translate("ControlPanel", "Y-Z Plane", 0, QApplication::UnicodeUTF8));
    viewportCombo->addItem(QApplication::translate("ControlPanel", "Z-Y Plane", 0, QApplication::UnicodeUTF8));
    viewportCombo->addItem(QApplication::translate("ControlPanel", "X-Z Plane", 0, QApplication::UnicodeUTF8));
    viewportCombo->addItem(QApplication::translate("ControlPanel", "Z-X Plane", 0, QApplication::UnicodeUTF8));
    objectsShowGroupBox->setTitle(QApplication::translate("ControlPanel", "Objects Show", 0, QApplication::UnicodeUTF8));
    hiddenLineCheckBox->setText(QApplication::translate("ControlPanel", "HiddenLine", 0, QApplication::UnicodeUTF8));
    vertexCheckBox->setText(QApplication::translate("ControlPanel", "Vertex", 0, QApplication::UnicodeUTF8));
    faceCheckBox->setText(QApplication::translate("ControlPanel", "Face", 0, QApplication::UnicodeUTF8));
    edgeCheckBox->setText(QApplication::translate("ControlPanel", "Edge", 0, QApplication::UnicodeUTF8));
    fIdxCheckBox->setText(QApplication::translate("ControlPanel", "FIdx", 0, QApplication::UnicodeUTF8));
    eIdxCheckBox->setText(QApplication::translate("ControlPanel", "EIdx", 0, QApplication::UnicodeUTF8));
    vIdxCheckBox->setText(QApplication::translate("ControlPanel", "VIdx", 0, QApplication::UnicodeUTF8));
    lightCheckBox->setText(QApplication::translate("ControlPanel", "Light", 0, QApplication::UnicodeUTF8));
    vNormCheckBox->setText(QApplication::translate("ControlPanel", "VNorm", 0, QApplication::UnicodeUTF8));
    coordsCheckBox->setText(QApplication::translate("ControlPanel", "Coords", 0, QApplication::UnicodeUTF8));
    fNormCheckBox->setText(QApplication::translate("ControlPanel", "FNorm", 0, QApplication::UnicodeUTF8));
    bBoxCheckBox->setText(QApplication::translate("ControlPanel", "BBox", 0, QApplication::UnicodeUTF8));
    lightDirCheckBox->setText(QApplication::translate("ControlPanel", "LightDir", 0, QApplication::UnicodeUTF8));
    editLitDirCheckBox->setText(QApplication::translate("ControlPanel", "EditLitDir", 0, QApplication::UnicodeUTF8));
    shadeSmoothCheckBox->setText(QApplication::translate("ControlPanel", "ShadeSmooth", 0, QApplication::UnicodeUTF8));
    colorMaterialCheckBox->setText(QApplication::translate("ControlPanel", "ColorMaterial", 0, QApplication::UnicodeUTF8));
    inertiaCheckBox->setText(QApplication::translate("ControlPanel", "Inertia", 0, QApplication::UnicodeUTF8));
    perspectiveCheckBox->setText(QApplication::translate("ControlPanel", "Perspective", 0, QApplication::UnicodeUTF8));
    elemTypeTextLabel->setText(QApplication::translate("ControlPanel", "Elem Type:", 0, QApplication::UnicodeUTF8));
    elemTypeComboBox->clear();
    elemTypeComboBox->addItem(QApplication::translate("ControlPanel", "---", 0, QApplication::UnicodeUTF8));
    elemTypeComboBox->addItem(QApplication::translate("ControlPanel", "Vertex", 0, QApplication::UnicodeUTF8));
    elemTypeComboBox->addItem(QApplication::translate("ControlPanel", "Edge", 0, QApplication::UnicodeUTF8));
    elemTypeComboBox->addItem(QApplication::translate("ControlPanel", "Face", 0, QApplication::UnicodeUTF8));
    indexTextLabel->setText(QApplication::translate("ControlPanel", "Index:", 0, QApplication::UnicodeUTF8));
    locatePushButton->setText(QApplication::translate("ControlPanel", "Locate", 0, QApplication::UnicodeUTF8));
    propertiesPushButton->setText(QApplication::translate("ControlPanel", "Properties", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(MeshViewer), QApplication::translate("ControlPanel", "MeshViewer", 0, QApplication::UnicodeUTF8));
    algoAndParamGroupBox->setTitle(QApplication::translate("ControlPanel", "Algorithms&&Parameters", 0, QApplication::UnicodeUTF8));
    cNdAngleThreshLabel->setText(QApplication::translate("ControlPanel", "Corner-Node Angle Thresh:", 0, QApplication::UnicodeUTF8));
    rEgAngleThreshLabel->setText(QApplication::translate("ControlPanel", "Ridge-Edge Angle Thresh:", 0, QApplication::UnicodeUTF8));
    cNdPromAngleThreshLabel->setText(QApplication::translate("ControlPanel", "Corner-Node Prom Anle Thresh:", 0, QApplication::UnicodeUTF8));
    algoAndParamToolBox->setItemText(algoAndParamToolBox->indexOf(page), QApplication::translate("ControlPanel", "Basic Algorithm", 0, QApplication::UnicodeUTF8));
    algoAndParamToolBox->setItemText(algoAndParamToolBox->indexOf(page_2), QApplication::translate("ControlPanel", "mtoolsurf's Algorithm", 0, QApplication::UnicodeUTF8));
    algoAndParamToolBox->setItemText(algoAndParamToolBox->indexOf(page_3), QApplication::translate("ControlPanel", "Jiang's Algorithm", 0, QApplication::UnicodeUTF8));
    applyPushButton->setText(QApplication::translate("ControlPanel", "Apply", 0, QApplication::UnicodeUTF8));
    flatNdCheckBox->setText(QApplication::translate("ControlPanel", "FlatNd", 0, QApplication::UnicodeUTF8));
    cNdIdxCheckBox->setText(QApplication::translate("ControlPanel", "CNdIdx", 0, QApplication::UnicodeUTF8));
    bNdNormCheckBox->setText(QApplication::translate("ControlPanel", "BNdNorm", 0, QApplication::UnicodeUTF8));
    fNdIdxCheckBox->setText(QApplication::translate("ControlPanel", "FNdIdx", 0, QApplication::UnicodeUTF8));
    ridgeEgCheckBox->setText(QApplication::translate("ControlPanel", "RidgeEd", 0, QApplication::UnicodeUTF8));
    bouNdCheckBox->setText(QApplication::translate("ControlPanel", "BouNd", 0, QApplication::UnicodeUTF8));
    cNdNormCheckBox->setText(QApplication::translate("ControlPanel", "CNdNorm", 0, QApplication::UnicodeUTF8));
    cornerNdCheckBox->setText(QApplication::translate("ControlPanel", "CornerNd", 0, QApplication::UnicodeUTF8));
    bEdIdxCheckBox->setText(QApplication::translate("ControlPanel", "BEdIdx", 0, QApplication::UnicodeUTF8));
    fNdNormCheckBox->setText(QApplication::translate("ControlPanel", "FNdNorm", 0, QApplication::UnicodeUTF8));
    flatEdCheckBox->setText(QApplication::translate("ControlPanel", "FlatEd", 0, QApplication::UnicodeUTF8));
    ridgeNdCheckBox->setText(QApplication::translate("ControlPanel", "RidgeNd", 0, QApplication::UnicodeUTF8));
    rNdIdxCheckBox->setText(QApplication::translate("ControlPanel", "RNdIdx", 0, QApplication::UnicodeUTF8));
    rEdIdxCheckBox->setText(QApplication::translate("ControlPanel", "REdIdx", 0, QApplication::UnicodeUTF8));
    rNdNormCheckBox->setText(QApplication::translate("ControlPanel", "RNdNorm", 0, QApplication::UnicodeUTF8));
    bNdIdxCheckBox->setText(QApplication::translate("ControlPanel", "BNdIdx", 0, QApplication::UnicodeUTF8));
    fEdIdxCheckBox->setText(QApplication::translate("ControlPanel", "FEdIdx", 0, QApplication::UnicodeUTF8));
    bouEdCheckBox->setText(QApplication::translate("ControlPanel", "BouEd", 0, QApplication::UnicodeUTF8));
    featureViewPropertiesPushButton->setText(QApplication::translate("ControlPanel", "Properties", 0, QApplication::UnicodeUTF8));
    featureViewAndEditToolBox->setItemText(featureViewAndEditToolBox->indexOf(page_4), QApplication::translate("ControlPanel", "Feature View", 0, QApplication::UnicodeUTF8));
    featureEdgeEditGroupBox->setTitle(QApplication::translate("ControlPanel", "Edge", 0, QApplication::UnicodeUTF8));
    featureEdgeEditFromlabel->setText(QApplication::translate("ControlPanel", "From", 0, QApplication::UnicodeUTF8));
    featureEdgeEditToLabel->setText(QApplication::translate("ControlPanel", "To", 0, QApplication::UnicodeUTF8));
    featureEdgeEditEdIdxLabel->setText(QApplication::translate("ControlPanel", "EdIdx", 0, QApplication::UnicodeUTF8));
    featureEdgeEditAsLabel->setText(QApplication::translate("ControlPanel", "As", 0, QApplication::UnicodeUTF8));
    featureEdgeEditAsComboBox->clear();
    featureEdgeEditAsComboBox->addItem(QApplication::translate("ControlPanel", "RidgeEd", 0, QApplication::UnicodeUTF8));
    featureEdgeEditAsComboBox->addItem(QApplication::translate("ControlPanel", "FlatEd", 0, QApplication::UnicodeUTF8));
    featureNodeEditGroupBox->setTitle(QApplication::translate("ControlPanel", "Node", 0, QApplication::UnicodeUTF8));
    featureNodeEditFromLabel->setText(QApplication::translate("ControlPanel", "From", 0, QApplication::UnicodeUTF8));
    featureNodeEditToLabel->setText(QApplication::translate("ControlPanel", "To", 0, QApplication::UnicodeUTF8));
    featureNodeEditNdIdxLabel->setText(QApplication::translate("ControlPanel", "NdIdx", 0, QApplication::UnicodeUTF8));
    featureNodeEditAsLabel->setText(QApplication::translate("ControlPanel", "As", 0, QApplication::UnicodeUTF8));
    featureNodeEditAsComboBox->clear();
    featureNodeEditAsComboBox->addItem(QApplication::translate("ControlPanel", "RidgeNd", 0, QApplication::UnicodeUTF8));
    featureNodeEditAsComboBox->addItem(QApplication::translate("ControlPanel", "CornerNd", 0, QApplication::UnicodeUTF8));
    featureNodeEditAsComboBox->addItem(QApplication::translate("ControlPanel", "FlatNd", 0, QApplication::UnicodeUTF8));
    featureViewAndEditToolBox->setItemText(featureViewAndEditToolBox->indexOf(page_5), QApplication::translate("ControlPanel", "Feature Edit", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(FeatureDetection), QApplication::translate("ControlPanel", "FeatureDetection", 0, QApplication::UnicodeUTF8));
    uniformDensityGroupBox->setTitle(QApplication::translate("ControlPanel", "Uniform Density", 0, QApplication::UnicodeUTF8));
    globalSpacingLabel->setText(QApplication::translate("ControlPanel", "Global Spacing:", 0, QApplication::UnicodeUTF8));
    bkgAndSorGroupBox->setTitle(QApplication::translate("ControlPanel", "Background && Source", 0, QApplication::UnicodeUTF8));
    ba3FilePushButton->setText(QApplication::translate("ControlPanel", "Ba3 File", 0, QApplication::UnicodeUTF8));
    geometricDensityGroupBox->setTitle(QApplication::translate("ControlPanel", "Gometric Density", 0, QApplication::UnicodeUTF8));
    proportionalityCoefficientLabel->setText(QApplication::translate("ControlPanel", "Proportionality Coefficient:", 0, QApplication::UnicodeUTF8));
    denseAndTopoTransToolBox->setItemText(denseAndTopoTransToolBox->indexOf(page_6), QApplication::translate("ControlPanel", "Density Specification", 0, QApplication::UnicodeUTF8));
    mshGradContGroupBox->setTitle(QApplication::translate("ControlPanel", "Mesh Gradation Control", 0, QApplication::UnicodeUTF8));
    contHVarRadioButton->setText(QApplication::translate("ControlPanel", "Control H-Variation", 0, QApplication::UnicodeUTF8));
    alphaLabel->setText(QApplication::translate("ControlPanel", "Alpha:", 0, QApplication::UnicodeUTF8));
    reduceHShockRadioButton->setText(QApplication::translate("ControlPanel", "Reduce H-Shock", 0, QApplication::UnicodeUTF8));
    betaLabel->setText(QApplication::translate("ControlPanel", "Beta:", 0, QApplication::UnicodeUTF8));
    densitySmoothingGroupBox->setTitle(QApplication::translate("ControlPanel", "Density Smoothing", 0, QApplication::UnicodeUTF8));
    parameterLabel->setText(QApplication::translate("ControlPanel", "Parameter:", 0, QApplication::UnicodeUTF8));
    denseAndTopoTransToolBox->setItemText(denseAndTopoTransToolBox->indexOf(page_7), QApplication::translate("ControlPanel", "Density Correction", 0, QApplication::UnicodeUTF8));
    topoTransGroupBox->setTitle(QApplication::translate("ControlPanel", "Topology Transformations", 0, QApplication::UnicodeUTF8));
    edgeSplitRadioButton->setText(QApplication::translate("ControlPanel", "Edge Split", 0, QApplication::UnicodeUTF8));
    vertexSplitRadioButton->setText(QApplication::translate("ControlPanel", "Vertex Split", 0, QApplication::UnicodeUTF8));
    edgeCollapseCheckBox->setText(QApplication::translate("ControlPanel", "Edge Collapse", 0, QApplication::UnicodeUTF8));
    edgeSwapCheckBox->setText(QApplication::translate("ControlPanel", "Edge Swap", 0, QApplication::UnicodeUTF8));
    denseAndTopoTransToolBox->setItemText(denseAndTopoTransToolBox->indexOf(page_8), QApplication::translate("ControlPanel", "Topology Transformation", 0, QApplication::UnicodeUTF8));
    denseAndTopoTransExecutePushButton->setText(QApplication::translate("ControlPanel", "Execute", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(Dense__TopoTrans), QApplication::translate("ControlPanel", "Dense&&TopoTrans", 0, QApplication::UnicodeUTF8));
    smmethodLabel->setText(QApplication::translate("ControlPanel", "smmethod:", 0, QApplication::UnicodeUTF8));
    nsmoothsurfLabel->setText(QApplication::translate("ControlPanel", "nsmoothsurf:", 0, QApplication::UnicodeUTF8));
    relaxsurfLabel->setText(QApplication::translate("ControlPanel", "relaxsurf:", 0, QApplication::UnicodeUTF8));
    smoothingToolBox->setItemText(smoothingToolBox->indexOf(page_9), QApplication::translate("ControlPanel", "mtoolsurf's Algorithm", 0, QApplication::UnicodeUTF8));
    smoothingToolBox->setItemText(smoothingToolBox->indexOf(page_10), QApplication::translate("ControlPanel", "Other's Algorithm", 0, QApplication::UnicodeUTF8));
    smoothingToolBox->setItemText(smoothingToolBox->indexOf(page_11), QApplication::translate("ControlPanel", "Reserved", 0, QApplication::UnicodeUTF8));
    smoothingExecutePushButton->setText(QApplication::translate("ControlPanel", "Execute", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(Smoothing), QApplication::translate("ControlPanel", "Smoothing", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ControlPanel);
    } // retranslateUi

};

namespace Ui {
    class ControlPanel: public Ui_ControlPanel {};
} // namespace Ui

#endif // UI_CONTROLPANEL_H
