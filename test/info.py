#!/usr/bin/env python
import socket, string 

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('127.0.0.1', 5100)
sock.connect(server_address)

printable = set(string.printable)

try:
    sock.sendall(b'INFO_SERVER')
    fragments = []
    s = ' '

    while True:
        chunck = sock.recv(10000)
        if not chunck:
            break
        fragments.append(chunck)

    print(s.join(fragments))

finally:
    sock.close()

