/*simple shell code
 -This code creidited to 
                         kareem hassaan mohamed
                         ID : 204

 - code functionality is create a childprocess via fork()
 - It excute a command with or without arguments (ls , ls -l ,firefox ,firefox & , ... )
 - The program terminated when you write command "exit"    */

/*---------------------------------***************************----------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#define line_size 100
#define char_Nb 100
#define Null 0

/*Read_command function prototype take the command over all from the user in a array of char and return void*/
void Read_command(char char_arr[]);
/*Swaping_EndLine function prototype that swap the end of the command in the memory (from "\n" to "\0") taking the array of command and return void*/
void Swaping_EndLine(char char_arr[]);
/*Parsing_command function prototype that take the array of command parsing it and store in array of pointers to send it to the function execvp()*/
int Parsing_command(char * parsed_command[],char char_arr[]);

/*Global variable as a flag when the user needs to the background by entering "&" at the end*/
int B_G = 0;

int main (void)
{
	char * parsed_command[line_size];           /*array of pointers to store the parsed command */

	char   char_arr[char_Nb];                   /*array of char to store the scaned command from user directly */

	while(1)
	{
		printf("Enter_command ->> ");

		Read_command(char_arr);                     /*Read_command function call*/
		Parsing_command(parsed_command,char_arr);   /*Parsing_command function call*/

		int pid = fork();

		if (pid == 0)
		{

			execvp(parsed_command[0],parsed_command);

		}
		else
		{
			if( B_G != 1)
			{
				wait(NULL);
			}
		}
	}
}


void Read_command(char char_arr[])   		/*Read_command function implementation*/
{
	int c ;
	
	fgets(char_arr,char_Nb,stdin);       	/*fgets to scan command as a string from user*/
	Swaping_EndLine(char_arr);           	/*Swaping_EndLine function call*/

	while( char_arr[c] != 0 )          		/*while loop to scan if the user enterd "&" to background mode*/
	{
		c++;
		if(char_arr[c] == '&')
	    {
			B_G = 1;
	    }
	}

	if(strcmp(char_arr,"exit") == 0)
	{
	   /*exit condition by using function exit ()*/
	   exit(0);
	}
}

void Swaping_EndLine(char char_arr[])      /*Swaping_EndLine function implementation*/
{
	int c = 0;

	while(char_arr[c] != '\n')
	c++;

	char_arr[c] = '\0';
}

int Parsing_command(char * parsed_command[],char char_arr[])     /*Parsing_command function implementation*/
{
	int c = 0 ;
	parsed_command[c] = strtok(char_arr," ");

	if(parsed_command[c] == NULL)
	{
		return 1;
	}


	while( parsed_command[c] != NULL)
	{
		c++;
		parsed_command[c] = strtok(NULL," ");
	}
	 
	return 1;
}
