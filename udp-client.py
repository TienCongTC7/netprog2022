import socket
import sys

host = (sys.argv[1])
PORT = int(sys.argv[2])
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
while True:
    msg = input("Enter your message: ")
    s.sendto(msg.encode(),(host,PORT))
    if(msg == "exit"):
        break

print("Exit Client...")
s.close()