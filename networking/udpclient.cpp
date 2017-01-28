#include <cstring> 
#include <iostream> 
#include <netdb.h> 
#include <netinet/in.h>
#include <string>
#include <sys/socket.h> 

namespace { 
    constexpr int BUFFSIZE = 256; 
    constexpr int PORTNO = 5001; 
    const char *HOSTNAME = "localhost"; 
} 

int main() 
{ 
    auto sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { 
        std::cerr << "unable to open socket\n"; 
    } 

    auto server = gethostbyname(HOSTNAME);
    if (!server) { 
        std::cerr << "unable to resolve hostname\n"; 
    }

    struct sockaddr_in serv_addr; 
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(static_cast<void*>(&serv_addr.sin_addr.s_addr), 
           static_cast<void*>(server->h_addr), server->h_length);   

    serv_addr.sin_port = htons(PORTNO);
   
    std::string buffer("hello world");
    int ret = sendto(sock, buffer.c_str(), buffer.length(), 0, 
              reinterpret_cast<struct sockaddr*>(&serv_addr), 
              sizeof(struct sockaddr_in));

    if (ret < 0) { 
        std::cerr << "unable to send message\n"; 
    }

    return 0; 
} 
