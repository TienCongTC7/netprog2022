from http.server import BaseHTTPRequestHandler, HTTPServer
import imp
import time
import os
from datetime import datetime
from xmlrpc.client import Server
from pytz import timezone
import datetime
from requests import request
import json


#author: Nguyen Tien Cong



hostName = "localhost"
serverPort = 8080

class MyServer(BaseHTTPRequestHandler):
    def do_GET(self):
        today = datetime.datetime.now()
        Paris_timezone = timezone('Europe/Paris')
        paris_time = datetime.datetime.now(Paris_timezone)

        self.Paris = paris_time.strftime("Paris current date: %a, %b %d at %H:%M")
        self.VietNam = today.strftime("Viet Nam current date: %a, %b %d at %H:%M")

        print(self.VietNam)
        print(self.Paris)
        data = [self.VietNam, self.Paris]
        print(data)
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write(bytes("<p>{0} </p>".format(self.VietNam), "utf-8"))
        self.wfile.write(bytes("<p>{0} </p>".format(self.Paris), "utf-8"))
        self.wfile.write(bytes(json.dumps(data),"utf-8"))
        self.wfile.write(bytes("<body>", "utf-8"))
        self.wfile.write(bytes("</body></html>", "utf-8"))
       
    #def json_example(self):
        #self.send_response(status_code)
        #self.send_header("Content-type", "application/json")
        #self.end_headers()
        #self.wfile.write(bytes(json.dumps(data), "utf-8"))
        


if __name__ == "__main__":        
    webServer = HTTPServer((hostName, serverPort), MyServer)
    print("Server started http://%s:%s" % (hostName, serverPort))

    try:
        webServer.serve_forever()
    except KeyboardInterrupt:
        pass

    webServer.server_close()
    print("Server stopped.")


