#include "CClient.h"

#include "CServer.h"


#define mBitsSet(f,m) ((f)|=(m))
#define mBitsClr(f,m) ((f)&=(~(m)))
#define mBitsTgl(f,m) ((f)^=(m))
#define mBitsMsk(f,m) ((f)& (m))
#define mIsBitsSet(f,m) (((f)&(m))==(m))
#define mIsBitsClr(f,m) (((~(f))&(m))==(m))

#ifdef QT_DEBUG
#define putLogs(log)    m_pLW->addItem(log)
#define putThLogs(log)  pClient->m_pLW->addItem(log)
#else
#define putLogs(log)
#define putThLogs(log)
#endif

CClient::CClient(CServer*pServer, QListWidget*pLW, QListWidget*pLWChat,SOCKET csock, SOCKADDR_IN csin) :
    m_pServer{pServer}
  , m_pLW{pLW}
  , m_pLWChat{pLWChat}
  , m_uStatus{ST_CONNECTED}
  , m_sock{csock}
  , m_sin{csin}
  , m_pReceiveThread{nullptr}
{
    m_pReceiveThread = new std::thread(ReceiveThreadProc, this);
}

CClient::~CClient(){
    Disconnect();
}

int CClient::Disconnect(){
    if(mIsBitsClr(m_uStatus, ST_CONNECTED)){
        return (int)INVALID_SOCKET;
    }
    mBitsClr(m_uStatus, ST_CONNECTED);
    m_pReceiveThread->join();
    delete m_pReceiveThread; m_pReceiveThread=nullptr;
    send(m_sock, "", 1, 0); /* Tells the remote client that we've closed the connexion */
    closesocket(m_sock);
    m_sock=INVALID_SOCKET;
    return 0;
}

int CClient::Send(const QString &msg) const{
    if(mIsBitsClr(m_uStatus, ST_CONNECTED)){
        return (int)INVALID_SOCKET;
    }

    if(SOCKET_ERROR==send(m_sock, msg.toStdString().c_str(), msg.length()+1, 0)){
        putLogs("CClient::Send() Failed to send message!");
        return SOCKET_ERROR;
    }

    return 0;
}

#include <fcntl.h>

/* static */ void CClient::ReceiveThreadProc(CClient *pClient){

    putThLogs("****** Entering CClient::ReceiveThreadProc() ******");

    int res=-1;
    char buf[BUFSIZ];

#if defined (linux)
    /*For linux*/
    int flags = fcntl(pClient->m_sock, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(pClient->m_sock, F_SETFL, flags);
#elif defined (WIN32)
    /*For Windows*/
    u_long ulMode =1;
    int iResult = ioctlsocket(pClient->m_sock,FIONBIO,&ulMode);
    if(iResult != NO_ERROR){
        putThLogs("AcceptThreadProc() : ioctlsocket failed with an error");
    }
#endif

    while(res && mIsBitsSet(pClient->m_uStatus, ST_CONNECTED)) {

        switch(res=recv(pClient->m_sock, buf, BUFSIZ, 0)) {
        case 0:
        case 1:
            putThLogs("Remote client has closed the connexion");
            send(pClient->m_sock, "", 1, 0);
            break;
        case SOCKET_ERROR:
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            break;
        default:
            pClient->m_pLWChat->addItem("Received: \"" + QString(buf) + "\"");
            pClient->m_pServer->PushMessage(buf, pClient);
            break;
        }
    }

    while(mIsBitsSet(pClient->m_uStatus, ST_CONNECTED));


    putThLogs("****** Exiting  CClient::ReceiveThreadProc() ******");
}
