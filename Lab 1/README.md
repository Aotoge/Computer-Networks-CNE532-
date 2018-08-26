# Lab 1
## Basics

<img src="https://img.shields.io/badge/language-C-brightgreen.svg"/>

### Contents
* [Implementing Linked List](#ll)
* [Basic Client-Server Chat Program using TCP/IP Socket Programming](#socks)

___

<a name="ll"></a>
## Implementing Linked List
Code for Implementing a Linked List with following operations:
* Inserting node at beginning
* Inserting node at end
* Inserting node at position
* Sorting Linked List in Ascending Order
* Deleting Node from any Position
* Update Node Value
* Searching for element in the Linked List
* Displaying list contents from beginning to end iteratively
* Display list contente from end to beginning using recursion
___

<a name="socks"></a>
## Basic Client-Server Chat Program using TCP/IP Socket Programming
Create a Basic Client-Server Chat program that allows a user on one machine to type in and send text to a user on another
machine.
* For client side:
```
 gcc client.c -o cli
```
```
 ./cli <host_name> <port_no>
```

* For server side:
```
 gcc server.c -o ser
```
```
 ./ser <port_no>
```
