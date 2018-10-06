import socket

clientsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientsocket.connect(('localhost', 10000))

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serversocket.bind(('localhost', 9999))
serversocket.listen(5)

while True:
    try:
        connection, address = serversocket.accept()
    except:
        print("Searching...")
    while True:

        buf = connection.recv(64)
        if len(buf) > 0:
            print(buf.decode())
            
        message = raw_input("Message: ")
        clientsocket.send(message)

    
