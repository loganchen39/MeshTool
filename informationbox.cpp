#include "informationbox.h"

InformationBox::InformationBox(QWidget* parent) 
        : QWidget(parent)
{
	ui.setupUi(this);
}

InformationBox::~InformationBox()
{
}

void InformationBox::appendMessage(QString message)
{
	ui.outputTextEdit->append(message);
}