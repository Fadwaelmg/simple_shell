#include "main.h"
/**
 * runCmd - Executes a command specified by the user.
 * @cmd: The command string to be executed.
 * Return: 0 if the command is executed successfully , 1 if not
*/
int runCmd(const char *cmd)
{
pid_t pid;
char *path = getenv("PATH");
char path_copy[MAX_PATH_LENGTH], full_cmd[MAX_PATH_LENGTH], *args[MAX_COMMAND_LENGTH];
char *saveptr1, *saveptr2;
char *token, *token_cmd;
int i = 0;
strncpy(path_copy, path, MAX_PATH_LENGTH);
token_cmd = strtok_r((char *)cmd, " ", &saveptr1);
while (token_cmd != NULL)
{
args[i++] = token_cmd;
token_cmd = strtok_r(NULL, " ", &saveptr1);
}
args[i] = NULL;
token = strtok_r(path_copy, ":", &saveptr2);
do {
snprintf(full_cmd, sizeof(full_cmd), "%s%s", token, args[0]);
if (commandExists(token, args[0]))
{
pid = fork();
if (pid == -1)
{
perror("fork");
return (1);
}
if (pid == 0)
{
if (execvp(full_cmd, args) == -1)
{
perror(full_cmd);
exit(EXIT_FAILURE);
}
}
else
{
int status;
waitpid(pid, &status, 0);
if (WIFEXITED(status))
{
if (WEXITSTATUS(status) == 0)
{
return (0);
}
else
{
return (1);
}
}
else
{
perror("Child process didn't exit successfully");
return (1);
}
}
}
} while ((token = strtok_r(NULL, ":", &saveptr2)) != NULL);
printf("'%s' not found\n", args[0]);
return (0);
}
