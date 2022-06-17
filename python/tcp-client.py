import sys
import socket

def main():
    s = socket.socket()
    s.connect( ('',PORT))
    while True:
        msg = input("Enter a message: ")
        s.send(msg.encode())
        if(msg == "exit"):
            print("Exiting Client....")
            break
        msg_server = s.recv(1024).decode()
        print("Server response: ",msg_server)
    s.close()

if __name__ == "__main__":
    PORT = int(sys.argv[1])
    main()