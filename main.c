#include "main.h"
/**
 * main - Simple shell program that reads and executes user commands.
 * Return: 0 an successful execution, or an appropriate error code.
 */
int main(void)
{
char *command = (char *)malloc(MAX_COMMAND_LENGTH * sizeof(char));
char *space_ptr;
do {
printf("#cisfun$ ");
fgets(command, MAX_COMMAND_LENGTH, stdin);
if (strcmp(command, "exit\n") == 0)
{
printf("Exiting cisfun . Goodbye! \n");
break;
}
else if (strcmp(command, "env\n") == 0)
{
show_environment();
}
else
{
if (strchr(command, ';') || strchr(command, '|') || strchr(command, '<')
|| strchr(command, '>'))
{
printf("Error: Command contains special characters or advanced features.\n");
continue;
}
space_ptr = strchr(command, ' ');
if (space_ptr && *(space_ptr + 1) != '-')
{
printf("Error: Command should contain only one word.\n");
continue;
}
command[strcspn(command, "\n")] = '\0';
if (runCmd(command) == 0)
continue;
}
} while (1);
free(command);
return (0);
}
