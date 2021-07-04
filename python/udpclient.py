from socket import *

serverName = 'localhost'; serverPort = 12000
clientSocket  = socket(AF_INET, SOCK_DGRAM)

while True:
	i = 0
	while True:
		i += 1
		message = str(i)
		# message = raw_input('input lowercase sentence: ')
		if len(message) == 0:
			break
		message = message.encode(encoding='ASCII')
		clientSocket.sendto(message, (serverName, serverPort))
		modifiedMessage, serverAddress = clientSocket.recvfrom(2048)
		print(modifiedMessage.encode(encoding='ASCII'))
	break
clientSocket.close()