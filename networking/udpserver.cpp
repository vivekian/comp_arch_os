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
    char buff[BUFFSIZE];
} 

int main() 
{ 
    auto sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { 
        std::cerr << "unable to open socket\n"; 
    } 

    struct sockaddr_in serv_addr, from; 
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORTNO);
 
    if (bind(sock, (struct sockaddr*)(&serv_addr), sizeof(struct sockaddr_in)) < 0) { 
        std::cerr << "unable to bind socket\n"; 
        return 1; 
    }

    socklen_t fromlen = sizeof(struct sockaddr_in);
    int ret = recvfrom(sock, buff, BUFFSIZE, 0, 
              reinterpret_cast<struct sockaddr *>(&from), &fromlen);

    if (ret < 0) { 
        std::cerr << "unable to receive message\n"; 
    }

    std::cout << buff << std::endl;

    return 0; 
} 
