# Lab 3
## TCP/IP and UDP Socket Programming - Chat/Transfer

![](https://img.shields.io/badge/language-C-brightgreen.svg)

### Contents
* [Two-way Client Server Chat Program](#cscp)
* [Client Server File Transfer Program (Using DGRAM Socket)](#csftp)

___

<a name="cscp"></a>
## Two-way Client Server Chat Program
Write a client-server program that provides chat facility. Your application allows a user on one machine to type in and send text to a user on another machine. Your application should provide non blocking chat facility to the users.

* For Server:
```
 gcc server.c -o ser
 ./ser
```

* For Client:
```
 gcc client.c -o cli
 ./cli
```

___

<a name="csftp"></a>
## Client Server File Transfer Program (Using DGRAM Socket)
Write a server program, which can provide facility of file transfer to the clients. Server should be able to support any number of clients simultaneously. Implement using DGRAM Socket.

* For Server:
```
 gcc server.c -o ser
 ./ser
```

* For Client:
```
 gcc client.c -o cli
 ./cli
```

___


