#include "main.h"
/**
 * commandExists - Cheks if a file exists at a specified path.
 * @path: The directory path where the file is expected.
 * @file: The name of the file to check for existence.
 * Return: 1 if the file exists, 0 if don't exists
*/
int commandExists(const char *path, const char *file)
{
char full_path[MAX_PATH_LENGTH];
snprintf(full_path, sizeof(full_path), "%s%s", path, file);
return (access(full_path, F_OK) != -1);
}
