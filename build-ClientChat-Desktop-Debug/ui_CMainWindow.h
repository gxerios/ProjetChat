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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *lb_serverIp;
    QLineEdit *le_serverIp;
    QLabel *lb_serverPort;
    QLineEdit *le_serverPort;
    QLabel *lb_pseudo;
    QLineEdit *le_pseudo;
    QPushButton *pb_connectDisconnect;
    QListWidget *lw_recvChat;
    QPushButton *pb_clearRecvLw;
    QListWidget *lw_trmtChat;
    QPushButton *pb_clearSentLw;
    QLineEdit *le_msgChat;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CMainWindow)
    {
        if (CMainWindow->objectName().isEmpty())
            CMainWindow->setObjectName("CMainWindow");
        CMainWindow->resize(515, 643);
        centralwidget = new QWidget(CMainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        lb_serverIp = new QLabel(centralwidget);
        lb_serverIp->setObjectName("lb_serverIp");

        horizontalLayout->addWidget(lb_serverIp);

        le_serverIp = new QLineEdit(centralwidget);
        le_serverIp->setObjectName("le_serverIp");

        horizontalLayout->addWidget(le_serverIp);

        lb_serverPort = new QLabel(centralwidget);
        lb_serverPort->setObjectName("lb_serverPort");

        horizontalLayout->addWidget(lb_serverPort);

        le_serverPort = new QLineEdit(centralwidget);
        le_serverPort->setObjectName("le_serverPort");

        horizontalLayout->addWidget(le_serverPort);

        lb_pseudo = new QLabel(centralwidget);
        lb_pseudo->setObjectName("lb_pseudo");

        horizontalLayout->addWidget(lb_pseudo);

        le_pseudo = new QLineEdit(centralwidget);
        le_pseudo->setObjectName("le_pseudo");

        horizontalLayout->addWidget(le_pseudo);

        pb_connectDisconnect = new QPushButton(centralwidget);
        pb_connectDisconnect->setObjectName("pb_connectDisconnect");

        horizontalLayout->addWidget(pb_connectDisconnect);


        verticalLayout->addLayout(horizontalLayout);

        lw_recvChat = new QListWidget(centralwidget);
        lw_recvChat->setObjectName("lw_recvChat");

        verticalLayout->addWidget(lw_recvChat);

        pb_clearRecvLw = new QPushButton(centralwidget);
        pb_clearRecvLw->setObjectName("pb_clearRecvLw");

        verticalLayout->addWidget(pb_clearRecvLw);

        lw_trmtChat = new QListWidget(centralwidget);
        lw_trmtChat->setObjectName("lw_trmtChat");

        verticalLayout->addWidget(lw_trmtChat);

        pb_clearSentLw = new QPushButton(centralwidget);
        pb_clearSentLw->setObjectName("pb_clearSentLw");

        verticalLayout->addWidget(pb_clearSentLw);

        le_msgChat = new QLineEdit(centralwidget);
        le_msgChat->setObjectName("le_msgChat");

        verticalLayout->addWidget(le_msgChat);


        verticalLayout_2->addLayout(verticalLayout);

        CMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CMainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 515, 22));
        CMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(CMainWindow);
        statusbar->setObjectName("statusbar");
        CMainWindow->setStatusBar(statusbar);

        retranslateUi(CMainWindow);

        QMetaObject::connectSlotsByName(CMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CMainWindow)
    {
        CMainWindow->setWindowTitle(QCoreApplication::translate("CMainWindow", "CMainWindow", nullptr));
        lb_serverIp->setText(QCoreApplication::translate("CMainWindow", "Server ip:", nullptr));
        le_serverIp->setPlaceholderText(QCoreApplication::translate("CMainWindow", "<server IP>", nullptr));
        lb_serverPort->setText(QCoreApplication::translate("CMainWindow", "Server port:", nullptr));
        le_serverPort->setPlaceholderText(QCoreApplication::translate("CMainWindow", "<server Port>", nullptr));
        lb_pseudo->setText(QCoreApplication::translate("CMainWindow", "Pseudo:", nullptr));
        le_pseudo->setPlaceholderText(QCoreApplication::translate("CMainWindow", "<your pseudo>", nullptr));
        pb_connectDisconnect->setText(QCoreApplication::translate("CMainWindow", "Connect", nullptr));
        pb_clearRecvLw->setText(QCoreApplication::translate("CMainWindow", "Clear", nullptr));
        pb_clearSentLw->setText(QCoreApplication::translate("CMainWindow", "Clear", nullptr));
        le_msgChat->setPlaceholderText(QCoreApplication::translate("CMainWindow", "<your message>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CMainWindow: public Ui_CMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAINWINDOW_H
