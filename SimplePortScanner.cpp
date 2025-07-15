#include <iostream>
#include <cstring>
#include <cerrno>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <vector>
#include <string>


#pragma comment(lib, "ws2_32.lib")

bool isOpen(const std::string& ip, int port, int timeout = 500) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        return false;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }

    DWORD timeoutValue = timeout;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeoutValue, sizeof(timeoutValue));

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);

    bool isPortOpen = (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) == 0);

    closesocket(sock);
    WSACleanup();

    return isPortOpen;
}

void scanPort(const std::string& target, const std::vector<int>& ports, int timeout = 500){

    std::cout << "Scanning target: " << target << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    for (int port : ports)
    {
        if (isOpen(target, port, timeout)) {
            std::cout << "Port " << port << ": \033[32mOpen\033[0m" << std::endl;
        }
        Sleep(1000);
        
    }
    
}

std::vector<int> analayzePort(const std::string& range){

    std::vector<int> ports;
    size_t dash = range.find('-');

    if(dash == std::string::npos){
        ports.push_back(std::stoi(range));
    } else {
        int start = std::stoi(range.substr(0, dash));
        int end = std::stoi(range.substr(dash + 1));

        for (int port = start; port <= end; ++port) {
            ports.push_back(port);
        }

    }
    
    return ports;

}



int main(int argc, char* argv[]) {

    if(argc <3){
        std::cerr << "Usage: " << argv[0] << " <target IP> <port range>" << std::endl;
        std::cerr << "Example: " << std::endl;
        std::cerr << argv[0] << "127.0.0.1 80" << std::endl;
        std::cerr << argv[0] << "192.168.1.1 20-100" << std::endl;
        std::cerr << argv[0] << "10.0.0.1 433 1000" << std::endl;

        return 1;
    }

    std::string target = argv[1];
    std::string portRange = argv[2];
    int timeout = (argc > 3) ? std::stoi(argv[3]) : 500;

    std::vector<int> ports = analayzePort(portRange);

    scanPort(target, ports, timeout);

    return 0;
}