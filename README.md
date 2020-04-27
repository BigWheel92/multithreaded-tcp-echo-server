# multithreaded-tcp-echo-server
A multithreaded tcp-based echo server implemented in C++

# How To run:
# First you need to compile and run server.cpp:
  1. Open a terminal in a Linux-based OS. 
  2. compile server.cpp file using the command: g++ server.cpp -lpthread -o s.out
  3. now run the server using the command:  ./s.out 8000

# Now you need to compile and run client.cpp
  4. Open another terminal in linux OS.
  5. compile client.cpp file using the command: g++ client.cpp -o c.out
  6. Now run the client using the command: ./c.out 127.0.0.1 8000

# Some Clarifications:
1. In step 2, the argument 8000 is the port number on which the server will listen. You can pass any valid port number on which you want the server to listen. The server binds to all available ip address of host machine (INADDR_ANY).

2. The command in step 6 has two command line arguments. The first argument (127.0.0.1) is the ip address of the server. If the server is on another machine, then you can pass the ip address of that machine. The second argument is the port number on which the server is listening.

3. The client will take input from the user and send it to the server. The server will send the input back to the client.

4. The server is multithreaded, so it can handle multiple clients at the same time. The server creates a separate thread for each connected client. 

5. When a client sends "exit" to the server, the server terminates the corresponding thread. The client also terminates.
