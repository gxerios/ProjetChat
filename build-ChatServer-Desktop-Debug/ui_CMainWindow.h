/********************************************************************************
** Form generated from reading UI file 'CMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMAINWINDOW_H
#define UI_CMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *lb_serverPort;
    QLineEdit *le_serverPort;
    QPushButton *pb_startStop;
    QSpacerItem *horizontalSpacer;
    QLabel *lb_clients;
    QComboBox *cb_clients;
    QVBoxLayout *verticalLayout;
    QListWidget *lw_logs;
    QPushButton *pb_clearLogs;
    QListWidget *lw_chats;
    QPushButton *pb_clearChats;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CMainWindow)
    {
        if (CMainWindow->objectName().isEmpty())
            CMainWindow->setObjectName("CMainWindow");
        CMainWindow->resize(800, 600);
        centralwidget = new QWidget(CMainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        lb_serverPort = new QLabel(centralwidget);
        lb_serverPort->setObjectName("lb_serverPort");
        lb_serverPort->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(lb_serverPort);

        le_serverPort = new QLineEdit(centralwidget);
        le_serverPort->setObjectName("le_serverPort");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(le_serverPort->sizePolicy().hasHeightForWidth());
        le_serverPort->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(le_serverPort);

        pb_startStop = new QPushButton(centralwidget);
        pb_startStop->setObjectName("pb_startStop");

        horizontalLayout->addWidget(pb_startStop);

        horizontalSpacer = new QSpacerItem(458, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        lb_clients = new QLabel(centralwidget);
        lb_clients->setObjectName("lb_clients");

        horizontalLayout->addWidget(lb_clients);

        cb_clients = new QComboBox(centralwidget);
        cb_clients->setObjectName("cb_clients");
        sizePolicy.setHeightForWidth(cb_clients->sizePolicy().hasHeightForWidth());
        cb_clients->setSizePolicy(sizePolicy);
        cb_clients->setMinimumSize(QSize(200, 0));

        horizontalLayout->addWidget(cb_clients);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        lw_logs = new QListWidget(centralwidget);
        lw_logs->setObjectName("lw_logs");

        verticalLayout->addWidget(lw_logs);

        pb_clearLogs = new QPushButton(centralwidget);
        pb_clearLogs->setObjectName("pb_clearLogs");

        verticalLayout->addWidget(pb_clearLogs);

        lw_chats = new QListWidget(centralwidget);
        lw_chats->setObjectName("lw_chats");

        verticalLayout->addWidget(lw_chats);

        pb_clearChats = new QPushButton(centralwidget);
        pb_clearChats->setObjectName("pb_clearChats");

        verticalLayout->addWidget(pb_clearChats);


        verticalLayout_2->addLayout(verticalLayout);

        CMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CMainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        CMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(CMainWindow);
        statusbar->setObjectName("statusbar");
        CMainWindow->setStatusBar(statusbar);

        retranslateUi(CMainWindow);

        QMetaObject::connectSlotsByName(CMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CMainWindow)
    {
        CMainWindow->setWindowTitle(QCoreApplication::translate("CMainWindow", "Chat Server", nullptr));
        lb_serverPort->setText(QCoreApplication::translate("CMainWindow", "ServerPort:", nullptr));
        le_serverPort->setPlaceholderText(QCoreApplication::translate("CMainWindow", "#port", nullptr));
        pb_startStop->setText(QCoreApplication::translate("CMainWindow", "Start", nullptr));
        lb_clients->setText(QCoreApplication::translate("CMainWindow", "Clients:", nullptr));
        pb_clearLogs->setText(QCoreApplication::translate("CMainWindow", "CLEAR", nullptr));
        pb_clearChats->setText(QCoreApplication::translate("CMainWindow", "CLEAR", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CMainWindow: public Ui_CMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAINWINDOW_H
