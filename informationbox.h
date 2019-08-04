#ifndef INFORMATIONBOX_H  //if CONTROLPANEL_H, compile error would happen
#define INFORMATIONBOX_H

#include <QtGui/QWidget>

#include "ui_InformationBox.h"

class InformationBox : public QWidget
{
    Q_OBJECT

public:
    InformationBox(QWidget *parent = 0);
    ~InformationBox();

public slots:
	void appendMessage(QString);

private:
    Ui::InformationBox ui;
};

#endif 