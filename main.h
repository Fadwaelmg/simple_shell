#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#define MAX_PATH_LENGTH 1024
#define MAX_COMMAND_LENGTH 1024

extern char **environ;

void show_environment(void);
int commandExists(const char *path, const char *file);
int runCmd(const char *cmd);
int main(void);
#endif
