#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) { perror(msg); exit(1); } // Error function used for reporting issues

int main(int argc, char *argv[])
{

//this is the example code provided
	int listenSocketFD, establishedConnectionFD, portNumber, charsRead;
	socklen_t sizeOfClientInfo;
	char buffer[70000];
	struct sockaddr_in serverAddress, clientAddress;

	// Set up the address struct for this process (the server)
	memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process

	// Set up the socket
	listenSocketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (listenSocketFD < 0) error("ERROR opening socket");

	// Enable the socket to begin listening
	if (bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to port
		error("ERROR on binding");
	listen(listenSocketFD, 5); // Flip the socket on - it can now receive up to 5 connections
	// Accept a connection, blocking if one is not available until one connects
	sizeOfClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect
//this is the example code provided

while(1)
{
	establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept
	if (establishedConnectionFD < 0) exit(1);
	pid_t pid = fork();
	if(pid == -1) //if pid is negative then its a a bad fork
	{
		exit(1);
		break;
	}
	else if(pid == 0)
	{
	recv(establishedConnectionFD, buffer, 70000, 0); // Read the client's message from the socket


//parse info when recciving from clients verfication and two files
		char connect_to[70000];
		char* token = strtok(buffer, "-");
		char* strings[10];

		char stringstore1[70000];
		char stringstore2[70000];
		int a = 0;


		//we parse the information here to separate things pased from the client
		while (token != NULL) {
				strings[a] = token;
				token = strtok(NULL, "-");
				a++;
		}

	strcat(stringstore1,strings[1]);
	strcat(stringstore2,strings[2]);

//check if the client_enc is true else do not do anything
		if(strcmp("client_dec",strings[0]) == 0) { //check if the client is related to the server
			strcat(connect_to, "true-");
		}
		else {
			strcat(connect_to, "false-"); //if it's not related we want to send a message to ignore the request from the user
			send(establishedConnectionFD, connect_to, sizeof(connect_to), 0);
			exit(1);
			exit(EXIT_FAILURE);
		}


		char stored[70000]; //stored will eventually contain the decrpyted message

		//variables below are used to changing character to ascii and back to characters
	  char c4;
	  char c5;
	  int char_int_F1;
	  int char_int_F2;

		//we get the string length of the encrypted message
		int string_length = strlen(stringstore1);


		int encrpyted;
		int y = 0;
		while (string_length != y) //will loop until the stringlength is not equal to it's length amount
		{

			c4 = stringstore1[y]; //will loop through each character until the end and stores it in a character variable
			c5 = stringstore2[y]; //will loop through each character until the end and stores it in a character variable

			char_int_F1 = c4; //converting encrpyted file to int
			char_int_F2 = c5; //converting key file to int


			if(char_int_F1 == 32) //we convert from the encryption file all " " (spaces) back into "[" (open bracket) to prevent conversion issues with %27
	    {
	      char_int_F1 = 91;
	    }

	    if(char_int_F2 == 32) //we convert from the key file all " " (spaces) back into "[" (open bracket) to prevent conversion issues with %27
	    {
	      char_int_F2 = 91;
	    }

	    if(char_int_F1 == 10 || char_int_F1 == -1) //if this is a new line \0 then we do nothing
			{
				//do nothing
	    }
	    else {
	      if(char_int_F1 < char_int_F2) //this case is needed when doing negative modulous of 27
	      {
	        encrpyted = (((char_int_F1) - (char_int_F2)) + 27) % 27; //we want to add 27 since negative numbers will give problems and will not substract -65
	        encrpyted += 65; //we add 65 to get to the correct ascii letters
	      }
	      else
	      {
	      encrpyted = ((char_int_F1 - 65) - (char_int_F2 - 65)) % 27; //we do this math in order to get the right ascii value
	      encrpyted += 65; //we add 65 to get to the right position
	      }


	      if(encrpyted == 91) //we convert 91 open bracket back to a 32 which is a space because we are using spaces on this assignment
	      {
	        encrpyted = 32;
	      }

				char int_char = encrpyted;
				stored[y] = int_char;
				y++;
			}
		}
		//we concatinate stored which is the decrpyted information to connect_to and add a - to the end
		strcat(connect_to, stored);
		strcat(connect_to, "-");


		send(establishedConnectionFD, connect_to, 70000, 0); //send the verifcation and decrypted information back all in one send

		close(establishedConnectionFD); // Close the existing socket which is connected to the client
		close(listenSocketFD); // Close the listening socket
	}
}
	return 0;
}
