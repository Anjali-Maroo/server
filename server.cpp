#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        cerr << "Failed to create socket" << endl;
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        cerr << "Failed to set socket options" << endl;
        return 1;
    }

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "Failed to bind socket" << endl;
        return 1;
    }

    if (listen(server_fd, 5) < 0) {
        cerr << "Failed to listen on socket" << endl;
        return 1;
    }

    cout << "Server is listening on http://localhost:8080" << endl;
    cout << "Press Ctrl+C to stop the server" << endl;

    while (true) {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
        
        if (client_fd < 0) {
            cerr << "Failed to accept connection" << endl;
            continue;
        }

        char buffer[1024] = {0};
        int bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
        
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            cout << "Received request:\n" << buffer << endl;
        }

        string response_body = "<html><body><h1>Hello from my C++ Server!</h1>"
                               "<p>Server is working correctly!</p></body></html>";
        
        string response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: " + to_string(response_body.length()) + "\r\n"
            "Connection: close\r\n"
            "\r\n" + 
            response_body;

        int bytes_sent = write(client_fd, response.c_str(), response.length());
        
        if (bytes_sent < 0) {
            cerr << "Failed to send response" << endl;
        } else {
            cout << "Sent " << bytes_sent << " bytes to client" << endl;
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}
