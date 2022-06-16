import socket
import sys
import socketserver
import time

BUFFSIZE = 1024
class MyTCPSocketHandler(socketserver.BaseRequestHandler):
    def handle(self):
        self.data = self.request.recv(BUFFSIZE).strip()
        delay = len(self.data)
        print(f"{self.client_address[0]} watting for:{delay} seconds")
        time.sleep(delay)
        print(f"{self.client_address[0]} wrote:\n{self.data}")
        self.request.sendall(self.data.upper())

if __name__ == "__main__":
    port = int(sys.argv[1])
    server = socketserver.ForkingTCPServer( ("",port), MyTCPSocketHandler)
    server.serve_forever()
