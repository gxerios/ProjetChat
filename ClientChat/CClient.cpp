#include "CClient.h"
#include <CMainWindow.h>

using namespace std;

#ifdef QT_DEBUG
#define mPutLog(log)    m_pMainWindow->PutLog(log)
#define mThPutLog(log)  pClient->m_pMainWindow->PutLog(log)
#else
#define mPutLog(log)
#define mThPutLog(log)
#endif


CClient::CClient(CMainWindow*pMainWindow) :
    m_uStatus{ST_ALL_CLEARED}
  , m_sock{INVALID_SOCKET}
  , m_sin{}
  , m_pReceiveThread{}
  , m_pMainWindow{pMainWindow}
{
#if defined (WIN32)
    WSADATA WSAData;
    int error = WSAStartup(MAKEWORD(2,2), &WSAData);
    if(error){
        mBitsSet(m_uStatus, ST_WSADATA_ERROR);
    }
    else{
        mBitsSet(m_uStatus, ST_WSADATA_INITIATED);
    }
#endif
    mPutLog("CClient::CClient()");
}

CClient::~CClient(){
#if defined (WIN32)
    if(mIsBitsSet(m_uStatus, ST_WSADATA_INITIATED)){
        WSACleanup();
        mBitsClr(m_uStatus, ST_WSADATA_INITIATED);
    }
#endif
    mPutLog("CClient::~CClient()");
}

#define DO_IT

int CClient::Connect(const QString &serverIp, const QString &serverPort, const QString &pseudo){
    if(mIsBitsSet(m_uStatus, ST_CCONNECTED)) return (int)INVALID_SOCKET;

    m_pseudo = pseudo;

#ifdef DO_IT
    /* Create the socket */
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(m_sock==INVALID_SOCKET){
        mPutLog("Failed to create socket!");
        return (int)INVALID_SOCKET;
    }

    /* Connection configuration */
    m_sin.sin_addr.s_addr = inet_addr(serverIp.toStdString().c_str());
    m_sin.sin_family = AF_INET;
    m_sin.sin_port = htons(serverPort.toShort());

    /* If client got connection */
      if(::connect(m_sock, (SOCKADDR*)&m_sin, sizeof m_sin)==SOCKET_ERROR){
        mPutLog("Failed to connect to server!");
        closesocket(m_sock);
        return (m_sock = INVALID_SOCKET);
    }

    mPutLog(QString("Connected to ")    +
            inet_ntoa(m_sin.sin_addr)   +
            " on port " +
            QString::number(htons(m_sin.sin_port)));
#endif
    mBitsSet(m_uStatus, ST_CCONNECTED);

    m_pReceiveThread = new std::thread(ReceiveThreadProc, this);

    mPutLog("CClient::Connect()");
    return 0;
}

int CClient::Disconnect(){
    if(mIsBitsClr(m_uStatus, ST_CCONNECTED)) return (int)INVALID_SOCKET;

    send(m_sock, "", 1, 0);
    mBitsClr(m_uStatus, ST_CCONNECTED);
    m_pReceiveThread->join();

    delete m_pReceiveThread; m_pReceiveThread=nullptr;

    closesocket(m_sock);
    m_sock = INVALID_SOCKET;

    mPutLog("CClient::Disconnect()");
    return 0;
}

int CClient::IsConnected() const { return mIsBitsSet(m_uStatus, ST_CCONNECTED); }


int CClient::Send(const QString& msg) const{
    /**
     * ToDo: Send message to server
     */
    if(mIsBitsClr(m_uStatus, ST_CCONNECTED)) return -1;

    send(m_sock, msg.toStdString().c_str(), msg.length()+1, 0);

    m_pMainWindow->AddSentMessage(msg);
    return 0;
}

#include <fcntl.h>

/*static*/ void CClient::ReceiveThreadProc(CClient*pClient){

    mThPutLog("-------CClient::ReceiveThreadProc()::Entering--------");
    uint32_t cpt=0;

    char buf[BUFSIZ];
    ssize_t res=-1;

    /* Setting non blocking socket */

#if defined (linux)
    int flags = fcntl(pClient->m_sock, F_GETFL, 0);
    mBitsSet(flags, O_NONBLOCK);
    fcntl(pClient->m_sock, F_SETFL, flags);
#endif

    while(res && mIsBitsSet(pClient->m_uStatus, ST_CCONNECTED)){
        mThPutLog(QString("CClient::ReceiveThreadProc()::Running #")+QString::number(cpt++));

        /* If we received data, print them on terminal */
        switch(res=recv(pClient->m_sock, buf, sizeof buf, 0)){ /* recv is non longer blocking! */
        case SOCKET_ERROR:
            this_thread::sleep_for(chrono::duration<int, milli>(500));
            break;
        case 0:
        case 1:
            if(buf[0]=='\0'){
                mThPutLog("Received 0 length string! : Remote server has disconnected!");
                res=0;
                //pClient->m_pMainWindow->ServerHasDisconnected();
                emit pClient->ServerHasDisconnected();
            }
            break;
        default:
            //mThPutLog(QString("Received #")+QString::number(res)+" \""+buf+"\"");
            //pClient->m_pMainWindow->AddRecvMessage(QString("Received #")+QString::number(res)+" \""+buf+"\"");
            emit pClient->PostChatMessage(QString("Received #")+QString::number(res)+" \""+buf+"\"");
            break;
        }
    }

    if(res==0) mThPutLog("-------CClient::ReceiveThreadProc()::ACK REMOTE DISCONNEXION ---------");

    while(mIsBitsSet(pClient->m_uStatus, ST_CCONNECTED)); /* Waiting for local deconnection from the IHM thread */

    mThPutLog("-------CClient::ReceiveThreadProc()::Exiting---------");
}
