#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


void error(const char *msg) { perror(msg); exit(0); } // Error function used for reporting issues

int main(int argc, char *argv[])
{
	FILE *check_len1 = fopen(argv[1],"r"); //original text
	FILE *check_len2 = fopen(argv[2],"r"); //key

	FILE *check_inside = fopen(argv[1],"r"); //check content

	FILE *origin_file = fopen(argv[1],"r"); //origin_file content
	FILE *key_file  = fopen(argv[2],"r"); // key_file content

	if (check_len1 == NULL || check_len2 == NULL) //check if the file can be opened
	{
		fprintf(stderr, "%s\n", "could not open a file");
		exit(EXIT_FAILURE);
	}


	//all these variables are used for checking files and storing
	char c1;
	char c2;
	char c3;
	char c4;
	char c5;
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	int count4 = 0;
	int char_int;
	int char_int_F1;
	int char_int_F2;

	while (c1 != EOF) //check the length of the normal file
	{
		c1 = fgetc(check_len1);
		count1++;
	}
	count1 -= 2;

	while (c2 != EOF) //check the length of the keyfile
	{
		c2 = fgetc(check_len2);
		count2++;
	}
	count2 -= 2;

	if(count1 > count2) //check if the size if alright
	{
		fprintf(stderr, "%s\n", "the key is too small");
		exit(EXIT_FAILURE);
	}
///////////////////////

	while (c3 != EOF) //loops through the testkey file
	{
		c3 = fgetc(check_inside);
		count3++;
		char_int = c3;

//32 is space
//10 is 0
//-1 is \
//65-90 is A-Z

		if(65 <= char_int && char_int <= 90 || char_int == -1 || char_int == 10 || char_int == 32)
		{
			//file is valid
		}
		else
		{
			fprintf(stderr, "%s\n", "invalid characters in file"); //if its not a valid file from the
			exit(EXIT_FAILURE);
		}
	}


	//file1 and file2 is going to eventually store the content of both files sent
	char file1[70000];
	char file2[70000];

	int y = 0;
	while (c4 != EOF)
	{
		c4 = fgetc(origin_file); //add a - at first file
		c5 = fgetc(key_file); //add a - at second file

		if(c4 == '\n' || c5 == '\n') //prevent from getting garbage
		{
			file1[y] = '-';
			file2[y] = '-';
			break;
		}

		file1[y] = c4; //storing char in array
		file2[y] = c5; //storing char in array
		y++;
	}

	//example code from assignment 4
	char server_connect [70000];
	strcat(server_connect,"client_enc-"); //will be used to check if connection is valid
	char result[70000];
	int socketFD, portNumber, charsWritten, charsRead;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;

	// Set up the server address struct
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[3]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverHostInfo = gethostbyname("localhost"); // Convert the machine name into a special form of address
	if (serverHostInfo == NULL) {
		fprintf(stderr, "CLIENT: ERROR, no such host\n"); exit(0);
	}
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address
	// Set up the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (socketFD < 0) {
		error("CLIENT: ERROR opening socket");
	}
	// Connect to server
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) { // Connect socket to address
		error("CLIENT: ERROR connecting");
	}


	//open files here and send to server once verification is done on the files themselves
	strcat(server_connect,file1);
	strcat(server_connect,file2);

	send(socketFD, server_connect, strlen(server_connect), 0); // Write to the server
	recv(socketFD, result, 70000, 0); // Read data from the socket



	char connect_to[70000];
	char* token = strtok(result, "-");
	char* strings[10]; //will be used to store the strings
	int a = 0;

	while (token != NULL) { //loops through and parses information given from the server
			strings[a] = token;
			token = strtok(NULL, "-");
			a++;
	}

	if(strcmp(strings[0],"false") == 0) //if it's false we want to stderr that they shouldnt connect to that server
	{
		close(socketFD);
		fprintf(stderr, "%s\n", "ERROR: unable to connect to server");
		exit(EXIT_FAILURE);
	}

	printf("%s\n", strings[1]); //result

	close(socketFD); // Close the socket
	fclose(origin_file); //close file
	fclose(key_file); //close file
	return 0;
}
