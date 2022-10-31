import socket
import sys
import threading


def recv():
    while 1:
        data = conn.recv(1024)
        if not data:
            break
        sys.stdout.write(data.decode('gbk'))
        sys.stdout.flush()


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
addr = ('0.0.0.0', 9999)
s.bind(addr)
s.listen(5)
print('Listening on {}'.format(addr))
conn, addr = s.accept()
print('Connection from {}'.format(addr))
threading.Thread(target=recv).start()
while 1:
    cmd = input()
    conn.send(bytes(cmd + '\r\n', encoding='gbk'))
