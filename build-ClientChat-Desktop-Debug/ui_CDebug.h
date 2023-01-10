/********************************************************************************
** Form generated from reading UI file 'CDebug.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDEBUG_H
#define UI_CDEBUG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CDebug
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *lw_debug;
    QPushButton *pb_clearLwDebug;

    void setupUi(QDialog *CDebug)
    {
        if (CDebug->objectName().isEmpty())
            CDebug->setObjectName("CDebug");
        CDebug->resize(345, 230);
        verticalLayout = new QVBoxLayout(CDebug);
        verticalLayout->setObjectName("verticalLayout");
        lw_debug = new QListWidget(CDebug);
        lw_debug->setObjectName("lw_debug");

        verticalLayout->addWidget(lw_debug);

        pb_clearLwDebug = new QPushButton(CDebug);
        pb_clearLwDebug->setObjectName("pb_clearLwDebug");

        verticalLayout->addWidget(pb_clearLwDebug);


        retranslateUi(CDebug);

        QMetaObject::connectSlotsByName(CDebug);
    } // setupUi

    void retranslateUi(QDialog *CDebug)
    {
        CDebug->setWindowTitle(QCoreApplication::translate("CDebug", "Debug window", nullptr));
        pb_clearLwDebug->setText(QCoreApplication::translate("CDebug", "CLEAR", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDebug: public Ui_CDebug {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDEBUG_H
