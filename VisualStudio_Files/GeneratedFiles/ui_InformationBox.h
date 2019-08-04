/********************************************************************************
** Form generated from reading ui file 'InformationBox.ui'
**
** Created: Wed Jul 16 20:22:58 2008
**      by: Qt User Interface Compiler version 4.2.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INFORMATIONBOX_H
#define UI_INFORMATIONBOX_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_InformationBox
{
public:
    QVBoxLayout *vboxLayout;
    QTextEdit *outputTextEdit;
    QHBoxLayout *hboxLayout;
    QLabel *inputCommandLabel;
    QLineEdit *commandLineEdit;

    void setupUi(QWidget *InformationBox)
    {
    InformationBox->setObjectName(QString::fromUtf8("InformationBox"));
    vboxLayout = new QVBoxLayout(InformationBox);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(9);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    outputTextEdit = new QTextEdit(InformationBox);
    outputTextEdit->setObjectName(QString::fromUtf8("outputTextEdit"));
    outputTextEdit->setFocusPolicy(Qt::NoFocus);
    outputTextEdit->setReadOnly(true);
    outputTextEdit->setTextInteractionFlags(Qt::TextBrowserInteraction);

    vboxLayout->addWidget(outputTextEdit);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    inputCommandLabel = new QLabel(InformationBox);
    inputCommandLabel->setObjectName(QString::fromUtf8("inputCommandLabel"));

    hboxLayout->addWidget(inputCommandLabel);

    commandLineEdit = new QLineEdit(InformationBox);
    commandLineEdit->setObjectName(QString::fromUtf8("commandLineEdit"));

    hboxLayout->addWidget(commandLineEdit);


    vboxLayout->addLayout(hboxLayout);


    retranslateUi(InformationBox);

    QSize size(549, 85);
    size = size.expandedTo(InformationBox->minimumSizeHint());
    InformationBox->resize(size);


    QMetaObject::connectSlotsByName(InformationBox);
    } // setupUi

    void retranslateUi(QWidget *InformationBox)
    {
    InformationBox->setWindowTitle(QApplication::translate("InformationBox", "Form", 0, QApplication::UnicodeUTF8));
    inputCommandLabel->setText(QApplication::translate("InformationBox", "Input Command:", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(InformationBox);
    } // retranslateUi

};

namespace Ui {
    class InformationBox: public Ui_InformationBox {};
} // namespace Ui

#endif // UI_INFORMATIONBOX_H
