





int strCompare(char* command, char* shellCommand);

main ()
{
	char buffer[13312];	//this is the maximum size of a file
	int sectorsRead;
	char command[4];
	char fileName[6];
	int isCommandSame;
	int isFileNameSame;
	int i;
	int j;
	int decider = 0;

	//initial shell should run an infinite loop.
	while(1)
	{
		char line[80];
		
		//on each iteration it should pront a prompt.
		syscall(0,"A:>");	//printString

		//it should then read in a line and match that line to a command.
		syscall(1, line);	//readString

		for(i = 0; i < 4; i++)
		{
			command[i] = line[i]; //store the command portion of line into a char array.
		}
		//syscall(0, command);	//print string for the command portion
		for(j = 0; j < 6; j++)
		{
			fileName[j] = line[j + 5];	//store the filename portion of line into a char array.
		}

		//test various inputs for the command.
		isCommandSame = strCompare(command, "type");
		if(isCommandSame == 1)
		{
			decider = 1;
		}
		isCommandSame = strCompare(command, "exec");
		if(isCommandSame == 1)
		{
			decider = 2;
		}
		//compare the shell command to the string "type"
		if(decider == 1)
		{
			syscall(3, fileName, buffer, &sectorsRead);
			if(sectorsRead > 0)
			{
				syscall(0, buffer);	//fileName was found and put into buffer.
			}
			else
			{
				syscall(0, "messag not found\r\n");	//fileName was not found.
			}
		}

		//compare shell command to the string "exec"
		if(decider == 2)
		{
			syscall(4, fileName);	//executes program if it is found
			syscall(0, "<PROGRAM NOT FOUND>\r\n");//it will ony get here if program is not found.
		}

		if(decider == 0)
		{
		syscall(0, "Bad Command!\r\n");	//printString
		}
	}
}


// Fake boolean. 1 if same. 0 if different.
int strCompare(char* command, char* shellCommand)
{
	int index;
	for(index = 0; index < 4; index++)
	{
		if(command[index] != shellCommand[index])
		{
			return 0;
		}
		if(command[0 + index] == '\0')
		{
			return 1;
		}
	}
	return 1;
}