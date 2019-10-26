# _*_ coding utf-8 _*_

# Import socket module
from socket import *
import sys # In order to terminate the program


def dump(title, body):
    padding = max(map(lambda line: len(line), body.split("\n"))) // 2

    print("\n" + "=" * padding + " " + title + " 시작 " + "=" * padding)
    print(body)
    print("=" * padding + " " + title + " 종료 " + "=" * padding + "\n")


serverSocket = socket(AF_INET, SOCK_STREAM)

serverPort = 6789

serverSocket.bind(("", serverPort))

serverSocket.listen(1)

while True:
    connectionSocket, addr = serverSocket.accept()

    try:
        message = connectionSocket.recv(1024).decode()
        dump("HTTP 요청 내용", message)

        filename = message.split()[1][1:]
        dump("요청받은 파일 이름", filename)

        f = open(filename)

        payload = f.read()

        response_string = "HTTP/1.1 200 OK\r\n\r\n"
        response_string += payload
        response_string += "\r\n"

        dump("HTTP 응답 내용", response_string)

        connectionSocket.send(response_string.encode())
        connectionSocket.close()

    except IOError:
        print("요청된 파일을 찾지 못했습니다...")
        print("에러 페이지를 내보냅니다.")

        error_string = "HTTP/1.1 404 Not Found\r\n\r\n"
        error_string += "<html><head></head><body><h1>404 Not Found</h1></body></html>\r\n"

        dump("HTTP 응답 내용", error_string)

        connectionSocket.send(error_string.encode())
        connectionSocket.close()
