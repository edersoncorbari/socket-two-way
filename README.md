## Synopsis

Simple bidirectional socket using [Qt](https://www.qt.io/) and [C++11](https://isocpp.org/wiki/faq/cpp11). This project is 
a structure of a bidirectional socket server developed with Qt, it is the client asks a question (command) the server 
responds by doing some action. It can be used by others who have this need, simply by adapting to their current need.

It was created based on the [Fortune](http://doc.qt.io/qt-5/qtnetwork-fortuneserver-example.html) example that comes 
in the Qt sample package, is thread-based and has been tested on Windows, Linux and FreeBSD systems.

It is not using SSL because it did not need this security for my client, but you can easily adapt it 
using the [QSslSocket](http://doc.qt.io/qt-5/qsslsocket.html) class.


#### Provided Mechanisms ####

 * Receive a command and return the response;
 * Manage multiple concurrent connections using thread.
 
 ### Build ###
 
To compile the project, you must have the following tools installed:

* [Qt-5.7](https://www.qt.io/download/) or greater;
* [CMake-2.8](https://cmake.org/) or greater;
* [CLang-3](https://clang.llvm.org/) or greater, you can also use [GCC](https://gcc.gnu.org/).

Now run the commands below to compile the project:

```shell
$ git clone https://github.com/edersoncorbari/socket-two-way.git
$ cd socket-two-way
$ ./configure
```

Ready! You may need to export Qt's PATH's. You can use QtCreator too, but I have not tested it.

 ### Testing ###
 
 To test it is very simple you have to run the server on an IP and a port where the client can connect, 
 for testing purposes you can use the locahost port 127.0.0.1 and port 5100. Run the commands below:
 
```shell
$ ./build/tools/run-socket/run-socket -ip 127.0.0.1 -port 5100
```

Now in another terminal window run the test:

```shell
$  python2 test/info.py
```

Do you test something like the screen below:

![Screen](https://raw.github.com/edersoncorbari/socket-two-way/master/doc/server-test.png)

I created a post about this project, you can see it here:[https://edersoncorbari.github.io/tutorials/qt-socket-server/](https://edersoncorbari.github.io/tutorials/qt-socket-server/)

It's the end :-)
