#ifndef CCLIENT_H
#define CCLIENT_H

#include <QString>
#include <QListWidget>
#include <QDateTime>
#include <thread>



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

class CServer;

class CClient{
private:
    enum e_statusMask:uint32_t{
        ST_ALL_CLEARED      = 0x00000000,
        ST_CONNECTED        = 0x00000001,
    };
private:
    CServer*        m_pServer;
    QListWidget*    m_pLW;
    QListWidget*    m_pLWChat;
    uint32_t        m_uStatus;
    SOCKET          m_sock;
    SOCKADDR_IN     m_sin;
    std::thread*    m_pReceiveThread;
public:
    CClient() = delete;
    CClient(CServer*pServer, QListWidget*pLW, QListWidget*pLWChat, SOCKET csock, SOCKADDR_IN csin);
    ~CClient();
    int Disconnect();
    int Send(const QString& msg) const;

private:
    static void ReceiveThreadProc(CClient*pClient);
};

#endif // CCLIENT_H
