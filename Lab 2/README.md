# Lab 2
## TCP/IP and UDP Socket Programming

![](https://img.shields.io/badge/language-C-brightgreen.svg)

### Contents
* [Multi client communication program (single character)](#mcc)
* [Multi client communication program (structure)](#mcs)
* [Basic client server directory service](#dir)

___

<a name="mcc"></a>
## Multi client communication program (single character)
Create three programs, two of which are clients to a single server using datagram socket. Client1 will send a character to the Server process. The Server will decrement the character's ASCII and send the result to Client2. Client2 prints the letter it receives and then all the processes terminate.
* For Server:
```
 gcc server.c -o ser
```
```
 ./ser <port_1> <host_name> <port_2>
```

* For Clients:
```
 gcc client1.c -o cli1
 gcc client2.c -o cli2
```
```
 ./cli1 <host_name> <port_1>
 ./cli2 <port_2>
```

___

<a name="mcs"></a>
## Multi client communication program (structure)
Send a C structure that includes data of type integer, character and float from Client1 to the Server. The Server should change the values so that Client2 receives a structure with the data alterted by basic mathematic operations. It is not permitted that the data should be converted to any other data type before transmission.
* For Server:
```
 gcc server.c -o ser
```
```
 ./ser <port_1> <host_name> <port_2>
```

* For Clients:
```
 gcc client1.c -o cli1
 gcc client2.c -o cli2
```
```
 ./cli1 <host_name> <port_1>
 ./cli2 <port_2>
```
___

<a name="dir"></a>
## Basic client server directory service
Build a very simple client-server operation using Stream capabilities. Build a client and server pair to implement your own little directory service.

Suppose that the server has the following database:
- 0 Bob
- 3 Anne
- 5 Barb
- 7 Ray
- 9 Denbigh
- 10 Terri
- 104 John

This can be in a file that is read. The Client is to read a request, which is a numeric address to be sent to the Server. The Server looks up the matching name and sends it back to the Client to be printed out. If the address isn't found, the Server should send back an error message. For example, "Address not found".

* To Create Directory File (Optional):
```
 gcc make_dir_file.c
 ./a.out
```

* For Server:
```
 gcc server.c -o ser
 ./ser <port_number>
```

* For Client:
```
 gcc client.c -o cli
 ./cli <host_name> <port_number>
```
___
