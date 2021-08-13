from socket import *

serverName = "localhost"
serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind((serverName, serverPort))
serverSocket.listen(1)
connectionSocket, addr = serverSocket.accept()
print("The server is ready to receive")
while True:
	sentence = connectionSocket.recv(1024)
	sentence = sentence.decode()
	print("Client: " + sentence)
	modifiedmessage = sentence.upper()
	connectionSocket.send(modifiedmessage.encode(encoding='ASCII'))
