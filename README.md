# SimplePortScanner

A basic command-line tool for scanning open ports on a target IP address.

---

### Educational Purpose Only

This tool is developed solely for educational purposes to demonstrate basic socket programming and port scanning concepts. It is not intended for any malicious activities. Please use it responsibly and only on networks or systems you have explicit permission to test.

---

## Features

* Scan a single port.
* Scan a range of ports.
* Customizable timeout for connection attempts.

---

## How to Use

### 1. Save the Code

Save the provided C++ code into a file named `port_scanner.cpp`.

### 2. Compile the Program

You can compile the program using Visual Studio or MinGW. use the following command in your bash terminal:

```bash
g++ port_scanner.cpp -o port_scanner.exe -lws2_32
```
This command compiles the source code and links against the Winsock2 library (ws2_32) required for network operations on Windows.

3. Run the Program
Once compiled, you can run the port_scanner.exe executable from your command prompt.

Scanning a Single Port:
To scan a specific port on a target IP address, use the following syntax:

DOS
```cmd
port_scanner.exe 127.0.0.1 80
```
This command will check if port 80 is open on 127.0.0.1 (localhost).

Scanning a Port Range:
To scan a range of ports, specify the start and end ports separated by a hyphen:

DOS
````
port_scanner.exe 192.168.1.1 20-100
````
This command will scan all ports from 20 to 100 on 192.168.1.1.

Specifying a Custom Timeout (in milliseconds):
You can set a custom timeout for connection attempts. The default timeout is 500 milliseconds.

DOS
```
port_scanner.exe 10.0.0.1 443 1000
```
This command will check port 443 on 10.0.0.1 with a timeout of 1000 milliseconds (1 second).

<h2>Requirements</h2>
-Windows Operating System (due to Winsock2 library usage)

-C++ Compiler (e.g., MinGW, Visual Studio)
