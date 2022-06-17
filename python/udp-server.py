import socket
import sys
from datetime import datetime
now = datetime.now()
PORT = 8765
BUFFSIZE = 1024

PORT = int(sys.argv[1])
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("",PORT))

while True:
    data, addr = s.recvfrom(BUFFSIZE)
    result = now.strftime(f"[%Y-%m-%d %H:%M:%S] client {addr} sent' {data.decode()}' ")
    print(result)
    if data.decode() == "exit":
        print(f"Client {addr} exited!!!")





