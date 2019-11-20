#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 7000
#define IP_ADDR_SERVER "127.0.0.1"

int main(){

	int clientSocket;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	// socket creation and verification 
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("connection error\n");
		exit(1);
	}

	//zero-valued bytes in area pointed by severAddr
	bzero(&serverAddr, sizeof(serverAddr)); 
	//Assigning IP and port number
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr(IP_ADDR_SERVER);

	//binding IP and port and verifying it
	if( (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) < 0){
		printf("connection error\n");
		exit(1);
	}
	printf("Connected to Server.\n");

	//loop to perform multiple operations one by one
	while(1){
		printf("Enter an arithmetic expression: ");
		//taking input from user
		fgets(buffer, 1024, stdin);
		//sending the data to server
		send(clientSocket, buffer, strlen(buffer), 0);
		//if users enters exit close the socket and terminate the program
		if(strcmp(buffer, "exit\n") == 0){
			close(clientSocket);
			printf("Disconnected from server.\n");
			exit(1);
		}
		//zero-valued bytes in area pointed by buffer
		bzero(buffer, sizeof(buffer));
		//receiving the result from server and putting it in buffer
		if(recv(clientSocket, buffer, 1024, 0) < 0){
			printf("Error in receiving\n");
		}else{
			printf("Solution: %s\n", buffer);
		}
	}
	return 0;
}