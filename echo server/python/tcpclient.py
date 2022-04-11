from socket import *
serverName = "localhost"
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))
i = 0
while True:
	i += 1
	message = str(i)
	# message = raw_input('input lowercase sentence: ')
	if i == 100011:
		break
	clientSocket.send(message.encode(encoding='ASCII'))
	modifiedMessage = clientSocket.recv(2048)
	print("From Server: " + modifiedMessage.decode())
clientSocket.close()