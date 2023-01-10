#include "CMainWindow.h"
#include "ui_CMainWindow.h"

CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CMainWindow)
    , m_pServer{nullptr}
{
    ui->setupUi(this);

    m_pServer = new CServer(ui->lw_logs, ui->lw_chats);
    ui->le_serverPort->setText("16000");

    connect(ui->lw_chats->model(), SIGNAL(rowsInserted(QModelIndex,int,int)), ui->lw_chats, SLOT(scrollToBottom()));
    connect(ui->lw_logs->model(), SIGNAL(rowsInserted(QModelIndex,int,int)), ui->lw_logs, SLOT(scrollToBottom()));


}

CMainWindow::~CMainWindow(){

    delete  m_pServer;

    delete ui;
}


void CMainWindow::on_pb_startStop_clicked(){

    if(m_pServer->IsStarted()){
        if(m_pServer->Stop()==0){
            ui->pb_startStop->setText("Start");
        }
    }
    else{
        if(ui->le_serverPort->text().isEmpty()){
            ui->lw_logs->addItem("Server port must be set!");
            return;
        }
        if(m_pServer->Start(ui->le_serverPort->text())==0){
            ui->pb_startStop->setText("Stop");
        }
    }
}

void CMainWindow::on_pb_clearLogs_clicked(){
    ui->lw_logs->clear();
}

void CMainWindow::on_pb_clearChats_clicked(){
    ui->lw_chats->clear();
}

void CMainWindow::on_cb_clients_textActivated(const QString &arg1)
{
    ui->lw_logs->addItem(arg1);
}


