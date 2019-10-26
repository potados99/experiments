from socket import *

host = ""
port = 2525

server_socket = socket(AF_INET, SOCK_DGRAM)
server_socket.bind((host, port))

while True:
    data, addr = server_socket.recvfrom(10)
    if data.decode() == "ping":
        print("Ping from " + str(addr))
        server_socket.sendto("pong".encode(), addr)
