#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

#ifdef QT_DEBUG
#include <CDebug.h>
#endif

#include <CClient.h>


QT_BEGIN_NAMESPACE
namespace Ui { class CMainWindow; }
QT_END_NAMESPACE

class CMainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::CMainWindow *ui;

#ifdef QT_DEBUG
    CDebug*     m_pDebug;
#endif

    CClient *   m_pClient;

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

    void AddRecvMessage(const QString&& msg);
    void AddSentMessage(const QString& msg);

    void ServerHasDisconnected();

    void PutLog(const QString& log);


private slots:
    void on_pb_connectDisconnect_clicked();

    void on_le_msgChat_returnPressed();

    void on_pb_clearRecvLw_clicked();

    void on_pb_clearSentLw_clicked();

    void on_receivePostMessage(const QString&);

private:
    void keyPressEvent(QKeyEvent *event) override;

};
#endif // CMAINWINDOW_H
