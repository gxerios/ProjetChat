#ifndef CSERVER_H
#define CSERVER_H

#include <QString>
#include <QListWidget>

#include <thread>
#include <list>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined (WIN32)
#include <winsock2.h>
#define Cleanup()		WSACleanup()
typedef int socklen_t;
#elif defined (linux)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define INVALID_SOCKET		-1
#define SOCKET_ERROR		-1
#define closesocket(s)		close(s)
typedef int SOCKET;
typedef struct sockaddr_in	SOCKADDR_IN;
typedef struct sockaddr		SOCKADDR;
#else
#error "OS not supported!"
#endif


#include "CClient.h"


#define SERVER_PENDING_CONNEXIONS_MAX   5



class CServer{
private:
    enum e_statusMasks:uint32_t{
        ST_ALL_CLEARED      = 0x00000000,
        ST_FAILED           = 0x80000000,
        ST_STARTED          = 0x00000001,
    };

private:
    uint32_t        m_uStatus;

    /* Server Socket and address context */
    SOCKET          m_sock;
    SOCKADDR_IN     m_sin;

    /* Accept thread */
    std::thread     *m_pAcceptThread;

    /* For logs purpose */
    QListWidget     *m_pLW;
    QListWidget     *m_pLWChat;

    /* Remote connected client's collection */
    std::list<CClient*>  m_clients;
public:
    CServer(QListWidget*pLW, QListWidget*pLWChat);
    ~CServer();

    int Start(const QString& serverPort);
    int Stop();
    int IsStarted() const;

    int PushMessage(const QString&msg, const CClient*pClient) const;

private:
    static void AcceptThreadProc(CServer*pServer);
};

#endif // CSERVER_H
