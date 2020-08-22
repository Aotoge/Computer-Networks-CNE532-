# Lab 4
## Self Specified Protocol Based Programming

![](https://img.shields.io/badge/language-C-brightgreen.svg)

### Contents
* [Protocol Based Client Server Communication Program](#cscp)

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

___
