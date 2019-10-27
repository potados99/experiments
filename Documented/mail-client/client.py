from socket import *
from sys import *
from time import *


def tell(sock, what):
    sock.send((what + "\r\n").encode())


def hear(sock):
    return sock.recv(1024).decode()


def not_good():
    print("Not a good situation.")
    exit(1)


def is_okay(message, ok_condition):
    return (message != "" and message[:3] == str(ok_condition))


def check(sock, ok_condition):
    if not is_okay(hear(sock), ok_condition):
        not_good()


def tell_and_expect(sock, what, expectation):
    tell(sock, what)
    check(sock, expectation)


server = input("Server address: ")
port = int(input("Server port: "))

# Only for SMTP, without auth.

client_socket = socket(AF_INET, SOCK_STREAM)
client_socket.connect((server, port))
check(client_socket, 220)

tell_and_expect(client_socket, "HELO", 250)

mail_from = input("From: ")
tell_and_expect(client_socket, "MAIL FROM: <" + mail_from + ">", 250)

mail_to = input("To: ")
tell_and_expect(client_socket, "RCPT TO: <" + mail_to + ">", 250)

tell_and_expect(client_socket, "DATA", 354)

subject = input("Subject: ")
tell(client_socket, "Subject: " + subject)
tell(client_socket, "From: " + mail_from)
tell(client_socket, "To: " + mail_to)

body = input("Body: ")
tell_and_expect(client_socket, "\r\n" + body + "\r\n.\r\n", 250)

print("\nMail successfully sent.\n")

client_socket.close()
