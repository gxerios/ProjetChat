#include "CMainWindow.h"
#include "ui_CMainWindow.h"

#ifdef QT_DEBUG
#define mPuts(log)      m_pDebug->PutLog(log)
#else
#define mPuts(log)
#endif

CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CMainWindow)
#ifdef QT_DEBUG
    , m_pDebug(new CDebug(this))
#endif
    , m_pClient{}
{
    ui->setupUi(this);
#ifdef QT_DEBUG
    m_pDebug->show();
#endif
    m_pClient = new CClient(this);
    ui->le_pseudo->setText("<!@bob>");
    ui->le_serverIp->setText("127.0.0.1");
    ui->le_serverPort->setText("16000");

    connect(ui->lw_recvChat->model(), SIGNAL(rowsInserted(QModelIndex,int,int)), ui->lw_recvChat, SLOT(scrollToBottom()));
    connect(ui->lw_trmtChat->model(), SIGNAL(rowsInserted(QModelIndex,int,int)), ui->lw_trmtChat, SLOT(scrollToBottom()));

    connect(m_pClient, SIGNAL(ServerHasDisconnected()), this, SLOT(on_pb_connectDisconnect_clicked()));

    connect(m_pClient, &CClient::PostChatMessage, this, &CMainWindow::on_receivePostMessage );
}

CMainWindow::~CMainWindow(){
    delete m_pClient;
#ifdef QT_DEBUG
    delete m_pDebug; m_pDebug=nullptr;
#endif
    delete ui;
}

void CMainWindow::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Escape:
        event->accept();
        QApplication::quit();
        break;
    default:
        event->ignore();
        break;
    }
}

void CMainWindow::on_pb_connectDisconnect_clicked(){
    if(m_pClient->IsConnected()){
        if(m_pClient->Disconnect()==0){
            ui->pb_connectDisconnect->setText("Connect");
        }
    }
    else{
        if(m_pClient->Connect(
                    ui->le_serverIp->text(),
                    ui->le_serverPort->text(),
                    ui->le_pseudo->text())==0){
            ui->pb_connectDisconnect->setText("Disconnect");
        }
    }
}

void CMainWindow::on_le_msgChat_returnPressed(){
    mPuts("on_le_msgChat_returnPressed()");
    m_pClient->Send(ui->le_msgChat->text());
    ui->le_msgChat->clear();
}

void CMainWindow::AddRecvMessage(const QString&& msg){
    ui->lw_recvChat->addItem(msg);
}

void CMainWindow::AddSentMessage(const QString& msg){
    ui->lw_trmtChat->addItem(msg);
}

void CMainWindow::on_pb_clearRecvLw_clicked(){
    ui->lw_recvChat->clear();
}


void CMainWindow::on_pb_clearSentLw_clicked(){
    ui->lw_trmtChat->clear();
}

void CMainWindow::on_receivePostMessage(const QString&msg){
    ui->lw_recvChat->addItem(msg);
}

void CMainWindow::ServerHasDisconnected(){
//    if(m_pClient->Disconnect()==0){
//        ui->pb_connectDisconnect->setText("Connect");
//    }
}

void CMainWindow::PutLog(const QString& log){
    mPuts(log);
}


