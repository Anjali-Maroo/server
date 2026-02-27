As part of my course work syllabus of Data Communication and Computer Network, I have built a basic server that has following features: 
- Listens for HTTP requests on port 8080
- Serves HTML responses to GET requests
- Cross-platform compatibility (Linux, macOS, WSL)
  
## Set-up requirements
- C++ Compiler (g++ or clang++)
- Terminal

## Installation
1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/cpp-basic-server.git
   cd cpp-basic-server
   ```
2. **Compile the server**
   ```bash
   g++ basic_server.cpp -o server
   ```

## Usage

1. **Start the server**
   ```bash
   ./server
   ```
   You should see:
   ```
   Server is listening on http://localhost:8080
   Press Ctrl+C to stop the server
   ```

2. **Test the server**
   
   Open your web browser and navigate to:
   ```
   http://localhost:8080
   ```

3. **run the server and visit `http://localhost:8080`, you'll see:**

**Browser displays:**
> # Hello from my C++ Server!
> Server is working correctly!

**Server console shows:**
```
Server is listening on http://localhost:8080
Received request:
GET / HTTP/1.1
Host: localhost:8080
User-Agent: Mozilla/5.0 ...
...

Sent 156 bytes to client
```

   
4. **Stop the server** : Press `Ctrl+C` in the terminal where the server is running.

## How It Works
The server follows these steps for each connection:
1. **Socket Creation**: Creates a TCP socket using `socket()`
2. **Binding**: Binds the socket to port 8080 using `bind()`
3. **Listening**: Waits for incoming connections with `listen()`
4. **Accepting**: Accepts client connections via `accept()`
5. **Reading**: Reads the HTTP request from the client
6. **Responding**: Sends back an HTML response
7. **Closing**: Closes the connection and repeats

### Request-Response Flow
```
Browser → [HTTP GET Request] → C++ Server
                                  ↓
Browser ← [HTML Response]    ←  C++ Server
```
