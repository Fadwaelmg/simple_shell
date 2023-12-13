#include "main.h"
/**
 * show_environment -Displays the environment variables to the standard output.
 * External Variable: 'environ' is declared as an external variable
 * meaning it is defined in another source file
 * this function assumes its existence for accessing the environment variables
*/
extern char **environ;
void show_environment(void)
{
char **env = environ;
while (*env != NULL)
{
printf("%s\n", *env);
env++;
}
}
