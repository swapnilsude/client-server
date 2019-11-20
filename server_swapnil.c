#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>

#define PORT 7000
#define IP_ADDR_SERVER "127.0.0.1"

void calculator(char *string, char *result)
{
    char *string2 = malloc(20);
    char *string3 = malloc(20);
    char operator;

    int  j,k=0;
    for(j=0;string[j];j++){
        string[j]=string[j+k];           
        if(string[j]==' '|| string[j]=='\t'){
            k++;
            j--;
        }
    }

    size_t length = strlen(string);
    size_t i = 0; 
    for (; i < length; i++) {
        if ( string[i] == '+' || string[i] == '*' || string[i] == '-' || string[i] == '/' ){
            operator=string[i];
            strncpy(string2, string, i);
            strncpy(string3, string+i+1, strlen(string));
        }
    }

    if ( isdigit(*string2) ==0 || isdigit(*string3) ==0){
        strcpy(result,"Error! Invalid number/operator entry");
    }
    else{
        int num1 = atoi(string2);
        int num2 = atoi(string3);

        switch(operator)
        {
            case '+':
                sprintf(result, "%d", num1+num2);  
                break;
            case '-':
                sprintf(result, "%d", num1-num2);
                break;
            case '*':
                sprintf(result, "%d", num1*num2);
                break;
            case '/':
                if (num2==0){
                    strcpy(result,"Error! Divide by zero");
                    break;
                }
                sprintf(result, "%d", num1/num2);
                break;
            // operator doesn't match any case constant (+, -, *, /)
            default:
                strcpy(result,"Error! operator not correct");
        }
    }
}

int main(){

	int sockfd;
	struct sockaddr_in serverAddr;
	int newSocket, len;
	struct sockaddr_in newAddr;

	char buffer[1024],result[1024];
	pid_t childpid;

	// socket creation and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
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
	if( (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) < 0){
		printf("binding error\n");
		exit(1);
	}
	printf("Bind to port %d\n", PORT);

	//start listening and verifiying if it was executed correctly
	if(listen(sockfd, 5) == 0){
		printf("Listening\n");
	}else{
		printf("binding error\n");
	}

	//loop for server to listen to incoming client connections
	while(1){
		len=sizeof(newAddr);
		//accept data from client and verifying it
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &len);
		if(newSocket < 0){
			exit(1);
		}
		//creating a child process for this client so that other client can connect
		if((childpid = fork()) == 0){
			close(sockfd);
			//loop for the client to perform multiple operations one by one
			while(1){
				//receiving the data from client and putiing it in buffer
				recv(newSocket, buffer, 1024, 0);
				//when client send exit break the loop
				if(strcmp(buffer, "exit\n") == 0){
					break;
				}else{
					//calcutaing the received operation
    				calculator(buffer,result);
					//sending the results
					send(newSocket, result, strlen(result), 0);
					//zero-valued bytes in area pointed by buffer and result
					bzero(buffer, sizeof(buffer));
					bzero(result, sizeof(result));
				}
			}
		}
	}
	//closing the socket
	close(newSocket);
	return 0;
}