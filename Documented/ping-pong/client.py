from socket import *
from time import *


def no_response():
    print("No response from server.")


def after_response(elapsed):
    print("Response in " + str(elapsed) + "ms.")


def millis():
    return int(round(time() * 1000))


server = input("Server address: ")
port = int(input("Server port: "))

client_socket = socket(AF_INET, SOCK_DGRAM)
client_socket.settimeout(1.0)

while True:
    client_socket.sendto("ping".encode(), (server, port))
    time_sent = millis()

    try:
        data, addr = client_socket.recvfrom(10)
        elapsed = millis() - time_sent
        after_response(elapsed)

    except timeout:
        no_response()

    sleep(1)
