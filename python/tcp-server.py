import sys
import socket
from unicodedata import name
PORT = 1234

def main():
    s = socket.socket()
    s.bind( ('',PORT))
    print(f"Listening on port {PORT}")
    s.listen(0)
    #waiting for a connection
    cnx, addr = s.accept()
    print("Connected")
    #reading data from this connection
    while True:
        msg = cnx.recv(1024).decode()
        #while msg[len(msg)-1] == '\n':
            #msg = cnx.recv(5).decode()
        cnx.send("OK i received it.".encode())
        print("Client sent: ",msg)
        if(msg == "exit"):
            print("close server!")
            break
    s.close()

if __name__ == "__main__":
    main()
