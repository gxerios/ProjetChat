#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>

#include "CServer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CMainWindow; }
QT_END_NAMESPACE

class CMainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::CMainWindow *ui;

    CServer *       m_pServer;

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

private slots:
    void on_pb_startStop_clicked();

    void on_pb_clearLogs_clicked();

    void on_pb_clearChats_clicked();

    void on_cb_clients_textActivated(const QString &arg1);
};
#endif // CMAINWINDOW_H
