import socket

clientsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientsocket.connect(('localhost', 10000))

while True:
    message = raw_input("Message: ")
    clientsocket.send(message)
