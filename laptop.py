import socket

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serversocket.bind(('localhost', 10000))
serversocket.listen(5)


while True:
    try:
        clientsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        clientsocket.connect(('localhost', 9999))
        message = raw_input("Message: ")
        clientsocket.send(message)

        while True:
            connection, address = serversocket.accept()
        
            buf = connection.recv(64)
            if len(buf) > 0:
                print(buf.decode())

    except:
        print("Searching for server...")

