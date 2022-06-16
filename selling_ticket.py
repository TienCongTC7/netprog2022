import socket
import sys
import socketserver
import time

BUFFSIZE = 1024
class MyTCPSocketHandler(socketserver.BaseRequestHandler):
    def handle(self):
        count = 0
        while True:                  
            self.data = self.request.recv(BUFFSIZE).strip()
            delay = 1
            print(f"{self.client_address[0]} watting for:{delay} seconds to process the ticket")
            time.sleep(delay)
            print(f"{self.client_address[0]} wrote:\n{self.data}")
            msg = f"Your ticket number is {count}".encode()
            self.request.sendall(msg)
            count += 1

if __name__ == "__main__":
    port = int(sys.argv[1])
    server = socketserver.ForkingTCPServer( ("",port), MyTCPSocketHandler)
    server.serve_forever()
