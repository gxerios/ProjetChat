#include "CServer.h"

#define mBitsSet(f,m) ((f)|=(m))
#define mBitsClr(f,m) ((f)&=(~(m)))
#define mBitsTgl(f,m) ((f)^=(m))
#define mBitsMsk(f,m) ((f)& (m))
#define mIsBitsSet(f,m) (((f)&(m))==(m))
#define mIsBitsClr(f,m) (((~(f))&(m))==(m))

#ifdef QT_DEBUG
#define putLogs(log)    m_pLW->addItem(log)
#define putThLogs(log)  pServer->m_pLW->addItem(log)
#else
#define putLogs(log)
#define putThLogs(log)
#endif


CServer::CServer(QListWidget*pLW, QListWidget*pLWChat) :
    m_uStatus{ST_ALL_CLEARED}
  , m_sock{INVALID_SOCKET}
  , m_sin{}
  , m_pAcceptThread{nullptr}
  , m_pLW{pLW}
  , m_pLWChat{pLWChat}
{
#if defined (WIN32)
    WSADATA WSAData;
    if(WSAStartup(MAKEWORD(2,2), &WSAData)){
        mBitsSet(m_uStatus, ST_FAILED);
    }
#endif
}

CServer::~CServer(){
    Stop();
#if defined (WIN32)
    WSACleanup();
#endif
}


int CServer::Start(const QString &serverPort){

    if(mIsBitsSet(m_uStatus, ST_STARTED)){
        putLogs("!!!! Server already started !!!!");
        return (int)INVALID_SOCKET;
    }

    /* Server Socket creation */
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(m_sock == INVALID_SOCKET){
        mBitsSet(m_uStatus, ST_FAILED);
        putLogs("CServer::Start() Failed to create socket!");
        return (int)INVALID_SOCKET;
    }

    putLogs("The socket " + QString::number(m_sock) + " is opened in TCP/IP mode.");

    /* Socket option for immediate releasing when closing it: canceling the delay after close */
    /* Releasing bound ports on socket closing */
    int iSetOption=1;
    setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&iSetOption, sizeof iSetOption);
    /* Configuration */
    m_sin.sin_addr.s_addr = htonl(INADDR_ANY);
    /* Auto IP address */
    m_sin.sin_family = AF_INET;	/* IP protocol family */
    m_sin.sin_port = htons(serverPort.toShort());

    socklen_t recsize = sizeof m_sin;
    int sockError = bind(m_sock, (SOCKADDR*)&m_sin, recsize);
    /*If the socket does'nt work...*/
    if(sockError == SOCKET_ERROR){
        mBitsSet(m_uStatus, ST_FAILED);
        putLogs("CServer::Start() Failed to bind socket!");
        closesocket(m_sock);
        return m_sock=INVALID_SOCKET;
    }

    /* Start listening (server mode) */
    sockError = listen(m_sock, SERVER_PENDING_CONNEXIONS_MAX);

    /* If the socket does'nt work... */
    if(sockError == SOCKET_ERROR){
        mBitsSet(m_uStatus, ST_FAILED);
        putLogs("CServer::Start() Failed to listen on socket!");
        closesocket(m_sock);
        return m_sock=INVALID_SOCKET;
    }
    putLogs("Listening port " + serverPort + "...");

    mBitsSet(m_uStatus, ST_STARTED);
    m_pAcceptThread = new std::thread(AcceptThreadProc, this);
    return 0;
}

int CServer::Stop(){
    if(mIsBitsClr(m_uStatus, ST_STARTED)){
        putLogs("!!!! Server not started yet !!!!");
        return (int)INVALID_SOCKET;
    }

    for(std::list<CClient*>::iterator it = m_clients.begin(); it != m_clients.end(); ++it){
        (*it)->Disconnect();
        delete *it;
    }

    m_clients.clear();

    mBitsClr(m_uStatus, ST_STARTED);    /* Tells the accept thread that we've stopped the server... */
    m_pAcceptThread->join();        /* ... and we wait for the accept thread terminating. */
    delete m_pAcceptThread; m_pAcceptThread=nullptr;
    closesocket(m_sock);
    m_sock=INVALID_SOCKET;

    return 0;
}

int CServer::IsStarted() const { return mIsBitsSet(m_uStatus, ST_STARTED); }



int CServer::PushMessage(const QString&msg, const CClient*pClient) const{

    for(std::list<CClient*>::const_iterator it = m_clients.begin(); it != m_clients.end(); ++it){
        if(*it!=pClient){
            (*it)->Send(msg);
        }
    }
    return 0;
}

#include <fcntl.h>


/* static */ void CServer::AcceptThreadProc(CServer *pServer){

    putThLogs("********* Entering CServer::AcceptThreadProc() **********");

    SOCKET csock = INVALID_SOCKET;
    SOCKADDR_IN csin;
    socklen_t crecsize = sizeof csin;

#ifdef USE_SELECT
    fd_set  acceptSet;
    struct timeval timeout;

    FD_ZERO(&acceptSet);
    FD_SET(pServer->m_sock, &acceptSet);
    timeout.tv_sec  = 0;
    timeout.tv_usec = 200000;

    /* Waiting for an incoming client	*/
    putThLogs("Please wait while an incoming client on port " + QString::number(pServer->m_sin.sin_port));


    while(mIsBitsSet(pServer->m_uStatus, ST_STARTED)){
        select(FD_SETSIZE, &acceptSet, NULL, NULL, &timeout);

        if(FD_ISSET(pServer->m_sock, &acceptSet)){
            csock = accept(pServer->m_sock, (SOCKADDR*)&csin, &crecsize);
            putThLogs("An incoming client with socket " + QString::number(csock) + " of " +
                      inet_ntoa(csin.sin_addr) + ":" + QString::number(htons(csin.sin_port)));

            pServer->m_clients.push_back(new CClient(pServer, pServer->m_pLW, pServer->m_pLWChat, csock, csin));
            putThLogs("Please wait while an incoming another client on port " + QString::number(pServer->m_sin.sin_port));
        }
    }
#else
    /* Waiting for an incoming client	*/
    putThLogs("Please wait while an incoming client on port " + QString::number(pServer->m_sin.sin_port));

    /* Setting non blocking socket */
#if defined (linux)
    int flags = fcntl(pServer->m_sock, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(pServer->m_sock, F_SETFL, flags);
#endif
    while(mIsBitsSet(pServer->m_uStatus, ST_STARTED)){

        switch(csock = accept(pServer->m_sock, (SOCKADDR*)&csin, &crecsize)){
        case INVALID_SOCKET:
        case 0:
            std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(1));       /* Sleeping the thread for 1000µs... */
            break;
        default:
            putThLogs("An incoming client with socket " + QString::number(csock) + " of " +
                      inet_ntoa(csin.sin_addr) + ":" + QString::number(htons(csin.sin_port)));
            pServer->m_clients.push_back(new CClient(pServer, pServer->m_pLW, pServer->m_pLWChat, csock, csin));
            putThLogs("Please wait while an incoming another client on port " + QString::number(pServer->m_sin.sin_port));
            break;
        }
    }
#endif

    putThLogs("********* Exiting  CServer::AcceptThreadProc() **********");
}
