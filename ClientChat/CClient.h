#ifndef CCLIENT_H
#define CCLIENT_H


#include <QObject>
#include <QString>
#include <QTimer>
#include <thread>

#include <cstdio>
#include <cstdlib>

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

#ifdef QT_DEBUG
#include <CDebug.h>
#endif

#define mBitsSet(f,m)       ((f)|=(m))
#define mBitsClr(f,m)       ((f)&=(~(m)))
#define mBitsTgl(f,m)       ((f)^=(m))
#define mBitsMsk(f,m)       ((f)& (m))
#define mIsBitsSet(f,m)     (((f)&(m))==(m))
#define mIsBitsClr(f,m)     (((~(f))&(m))==(m))

class CMainWindow;

class CClient : public QObject {
    Q_OBJECT

private:
    enum e_statusMasks:uint32_t{
        ST_ALL_CLEARED          = 0x00000000,
        ST_CONNECTED            = 0x00000001,
#if defined (WIN32)
        ST_WSADATA_ERROR        = 0x80000000,
        ST_WSADATA_INITIATED    = 0x40000000,
#endif
    };

private:
    uint32_t        m_uStatus;
    SOCKET          m_sock;
    SOCKADDR_IN     m_sin;
    std::thread     *m_pReceiveThread;
    CMainWindow     *m_pMainWindow;
    QString         m_pseudo;
    QTimer         *m_pTokenTimer;
public:
    CClient() = delete;
    CClient(CMainWindow*pMainWindow);
    ~CClient();

    int Connect(const QString&serverIp, const QString&serverPort, const QString&pseudo);
    int Disconnect();
    int IsConnected() const;
    int Send(const QString&msg) const;

private:
    static void ReceiveThreadProc(CClient*pClient);

signals:
    void ServerHasDisconnected();
    void PostChatMessage(const QString&);

private slots:
    void SendPresenceToken();
};

#endif // CCLIENT_H
