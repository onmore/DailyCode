﻿import socket
import os
ss=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
ss.connect(('127.0.0.1',12345))
#f=open('aa','wb')
ss.sendall(b'helloserverddddddddddddddddddddddddddddddddddd')
ss.send(b'EOF')
data=ss.recv(1024)
print("server dafu %s"%data)
ss.close()
  