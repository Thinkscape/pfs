#ifndef SOCKETS_H_INCLUDED
#define SOCKETS_H_INCLUDED

#if !defined(MINGW) && !defined(_WIN32)

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netdb.h>

#else

#define _WIN32_WINNT 0x0501

#include <winsock2.h>
#include <Ws2tcpip.h>

#ifndef AI_ADDRCONFIG
#define AI_ADDRCONFIG	0x0001
#endif

#ifndef AI_ALL
#define AI_ALL      	0x0002
#endif

#ifndef AI_CANONNAME
#define AI_CANONNAME	0x0004
#endif

#ifndef AI_NUMERICHOST
#define AI_NUMERICHOST	0x0008
#endif

#ifndef AI_NUMERICSERV
#define AI_NUMERICSERV	0x0010
#endif

#ifndef AI_PASSIVE
#define AI_PASSIVE  	0x0020
#endif

#ifndef AI_V4MAPPED
#define AI_V4MAPPED	    0x0040
#endif


static int inet_pton(int af, const char *src, void *dst)
{
    struct addrinfo *result = NULL;
    int res = getaddrinfo(src, NULL, NULL, &result);
    if (res != 0){
        if (res == WSANOTINITIALISED){
            WSADATA wsaData;
            res = WSAStartup(MAKEWORD(2, 2), &wsaData);
            if (res != 0) {
                return -1;
            }
            return inet_pton(af, src, dst);
        }
        return -1;
    }
    if (result->ai_family == af){
        res = 1;
    }
    freeaddrinfo(result);
    return res;
}

#endif

#endif // SOCKETS_H_INCLUDED
