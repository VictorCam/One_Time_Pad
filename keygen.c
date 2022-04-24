#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

int gen_random(int argc, char *argv[])
{
  int count = atoi(argv[1]); //gets the number asks from the user
  int i;
  char key[count]; //we will use this to print out the
	for(i = 0; i < count; i++)
	{
    int rand_key = rand() % 27 + 65; //we want to get the range from 65 to 91 which is "A-Z [" (according to ascii table)

    if(rand_key == 91) //if the key is "[" then we convert it to " " ascii table
    {
      rand_key = 32;
    }

    char c = rand_key; //we are converting it here back into a space
    key[i] = c;
	}

  int j;
  for (j = 0; j < count; j++)
  {
    printf("%c", key[j]); //we print each character on the screen and if it's on a file it won't get printed but instead be stored in the file
  }
  printf("\n");
}


int main(int argc, char *argv[])
{
  //these two lines below are for randomizing
  time_t t;
  srand((unsigned) time(&t));
 	gen_random(argc, argv); //we call the function which will randomize the information we provide from the command line
  return 0;
}
