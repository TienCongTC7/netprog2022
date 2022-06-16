import socket
import sys

host = "127.0.0.1"
host = sys.argv[1]
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
while True:
    msg = input("Enter your message: ")
    s.sendto(msg.encode(),("127.0.0.1",8765))
    if(msg == "exit"):
        break

print("Exit Client...")
s.close()