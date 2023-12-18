#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_BUF_SIZE 4096

int main() {
    char buffer[MAX_BUF_SIZE];
    char *eof_string = "EOF\n";
    ssize_t bytesRead;

    // Create a temporary file to store the input
    int tmpFileDescriptor = open("temp_input_file", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    if (tmpFileDescriptor == -1) {
        perror("Error creating temporary file");
        exit(EXIT_FAILURE);
    }

    // Read input until "EOF" is encountered
    while (1) {
        bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer));
        printf("->%d\n",bytesRead);
	if (bytesRead == -1) {
            perror("Error reading from stdin");
            exit(EXIT_FAILURE);
        }

        // Check for EOF
        if (strstr(buffer, eof_string) != NULL) {
            break;
        }

        // Write to the temporary file
        if (write(tmpFileDescriptor, buffer, bytesRead) == -1) {
            perror("Error writing to temporary file");
            exit(EXIT_FAILURE);
        }
    }

    // Close the temporary file
    if (close(tmpFileDescriptor) == -1) {
        perror("Error closing temporary file");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid_t childPid = fork();

    if (childPid == -1) {
        perror("Error forking");
        exit(EXIT_FAILURE);
    }

    if (childPid == 0) {
        // Child process

        // Redirect standard input to the temporary file
        int inputFileDescriptor = open("temp_input_file", O_RDONLY);
        if (inputFileDescriptor == -1) {
            perror("Error opening temporary file for reading");
            exit(EXIT_FAILURE);
        }
        dup2(inputFileDescriptor, STDIN_FILENO);
        close(inputFileDescriptor);

        // Execute the command using execve
        char *cmd[] = {"/bin/cat", NULL};
        execve("/bin/cat", cmd, NULL);

        // If execve fails
        perror("Error executing command");
        exit(EXIT_FAILURE);
    } else {
        // Parent process

        // Wait for the child to finish
        waitpid(childPid, NULL, 0);

        // Clean up: remove the temporary file
        if (unlink("temp_input_file") == -1) {
            perror("Error removing temporary file");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

