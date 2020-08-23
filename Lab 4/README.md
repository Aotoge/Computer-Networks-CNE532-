# Lab 4
## Protocol Based & Concurrent Socket Programming

![](https://img.shields.io/badge/language-C-brightgreen.svg)

### Contents
* [Protocol Based Client Server Communication Program](#cscp)
* [Protocol Based Client Server File Transfer Program](#csftp)
* [Concurrent File Transfer Program](#concftp)
___

<a name="cscp"></a>
## Protocol Based Client Server Communication Program
In this lab you will convert your previous program. The only logical change you need to make is to implement your exchange of messages as a protocol. The protocol will be structured as follows (note, a string of digits followed by a b (means a binary number)):

+ Requests:

byte | content |
-----|---------|
0 |request code, 0000001(b) = name, <br> 00001001(b) = number|
1-n| request data|
n+1 |end-of-request, 00000011(b) (ETX)|

+ Replies:

byte | content|
---- | -------|
0-n | reply data|
n+1 | end-of-reply, 00000011(b) (ETX)|

Note that the requests allow for both name and number matching, so you need to also be able to match a name. Also, note that the character string can contain any type of byte-oriented data, including binary representations of numbers.

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
## Protocol Based Client Server File Transfer Program

Write a client server application in which client request a file to server and server send requested file to client. Design a suitable protocol for message exchange as above, so that client and server can communicate efficiently and server can ask different option to the client.

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

<a name="concftp"></a>
## Concurrent Client Server File Transfer Program

Write a concurrent server program, which can provide facility of file transfer to the clients. Server should be able to support many number of clients simultaneously. (Hint: Use fork() system call).

* For Server:
```
 gcc server.c -o ser
 ./ser
```

* For Clients:
```
 gcc client.c -o cli
 ./cli
```
___


