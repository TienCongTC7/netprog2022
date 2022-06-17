import socket
import sys
import socketserver
import time
import fcntl
from threading import Thread, Lock
import threading

BUFFSIZE = 1024
count = 0
class MyTCPSocketHandler(socketserver.BaseRequestHandler):
    def handle(self):
        global count
        lock = threading.Lock()
        #x = open("ticket_available.txt", "r")
        #count = x.read()
        #count = int(count)
        #x.close()
        lock.acquire()
        lock_counter = count
        delay = 1
        print(f"{self.client_address[0]} watting for:{delay} seconds to process the ticket")
        time.sleep(delay)
        print(f"{self.client_address[0]} has requested a ticket")
        msg = f"Your ticket number is {count}".encode()
        self.request.sendall(msg)
        lock_counter += 1
        count = lock_counter
        lock.release()
        #f = open("ticket_available.txt", "w+")
        #fcntl.flock(f, fcntl.LOCK_EX)
        #f.write(str(count))
        #fcntl.flock(f, fcntl.LOCK_UN)

if __name__ == "__main__":
    port = int(sys.argv[1])
    #server = socketserver.ForkingTCPServer( ("",port), MyTCPSocketHandler)
    server = socketserver.ThreadingTCPServer( ("",port), MyTCPSocketHandler)
    server.serve_forever()
