#include "shell.h"

void show_environment(void) {
    char **env = environ;
    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }
}

int commandExists(const char *path, const char *file) {
    char full_path[MAX_PATH_LENGTH];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, file);
    return (access(full_path, F_OK) != -1);
}

int runCmd(const char *cmd) {
    pid_t pid;
    char *path = getenv("PATH");
    char path_copy[MAX_PATH_LENGTH];
    char full_cmd[MAX_PATH_LENGTH];
    char *args[MAX_COMMAND_LENGTH];
    char *saveptr1, *saveptr2;
    char *token;
    char *token_cmd;
    int i = 0;

    strncpy(path_copy, path, MAX_PATH_LENGTH);
    token_cmd = strtok_r((char *)cmd, " ", &saveptr1);

    while (token_cmd != NULL) {
        args[i++] = token_cmd;
        token_cmd = strtok_r(NULL, " ", &saveptr1);
    }
    args[i] = NULL;
    token = strtok_r(path_copy, ":", &saveptr2);

    do {
        snprintf(full_cmd, sizeof(full_cmd), "%s/%s", token, args[0]);
        if (commandExists(token, args[0])) {
            pid = fork();
            if (pid == -1) {
                perror("fork");
                return (1);
            }
            if (pid == 0) {
                if (execve(full_cmd, args, NULL) == -1) {
                    perror(full_cmd);
                    exit(EXIT_FAILURE);
                }
            } else {
                int status;
                waitpid(pid, &status, 0);
                if (WIFEXITED(status)) {
                    if (WEXITSTATUS(status) == 0) {
                        return (0);
                    } else {
                        return (1);
                    }
                } else {
                    perror("Child process did not exit successfully");
                    return (1);
                }
            }
        }
    } while ((token = strtok_r(NULL, ":", &saveptr2)) != NULL);

    printf("'%s' not found\n", args[0]);
    return (0);
}

int main(void) {
    char *command = (char *)malloc(MAX_COMMAND_LENGTH * sizeof(char));
    char *space_ptr;

    do {
        printf("#cisfun$ ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);

        if (strcmp(command, "exit\n") == 0) {
            printf("Exiting the shell. Goodbye!\n");
            free(command);
            return (0); 
	}else if (strcmp(command, "env\n") == 0) 
	{
            show_environment();
        } else {
            if (strchr(command, ';') || strchr(command, '|') || strchr(command, '<') || strchr(command, '>')) {
                printf("Error: Command contains special characters or advanced features.\n");
                continue;
            }

            space_ptr = strchr(command, ' ');
            if (space_ptr && *(space_ptr + 1) != '-') {
                printf("Error: Command should contain only one word.\n");
                continue;
            }
            command[strcspn(command, "\n")] = '\0';
            if (runCmd(command) == 0) {
                continue;
            }
        }
    } while (1);

    free(command);
    return (0);
}

