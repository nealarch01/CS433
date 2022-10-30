
/**
 * Assignment 2: Simple UNIX Shell
 * @file pcbtable.h
 * @author Neal Archival and Ahmed Ali
 * @brief This is the main function of a simple UNIX Shell. You may add
 * additional functions in this file for your implementation
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are
// done. Remember to add sufficient and clear comments to your code

#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

#define MAX_LINE 80     // The maximum length command
#define MAX_HISTORY 500 // The maximum number of commands to be stored in history

class ShellHistory {
    private:
        char *log[MAX_HISTORY] = {}; // History log
        int count; // The current number of elements in the log

        // When the history overflows, replace the old ones
        void shiftLog() {
            // Shift the log to erase older commands
            for (int i = 0; i < MAX_HISTORY - 1; i++) {
                log[i] = log[i + 1];
            }
        }

    public:

        ShellHistory() { // Default constructor
            count = 0;
        }

        // Adds to the history
        void add(char *args[], int numberOfArgs) {
            if (count == MAX_HISTORY) { // If the number of elements is greater than history, we will need to shift the array
                // Also, do not increment count
                shiftLog();
                count--; // Decrement the count so that it can be added to the last index
            }
            char command[MAX_LINE] = {};
            strcat(command, args[0]); // Append the command (no space)
            for (int i = 1; i <= numberOfArgs; i++) { // <= since numberOfArgs excludes the command
                strcat(command, " "); // Add a space
                strcat(command, args[i]); // Append the arguments 
            }
            // Combine the args
            log[count] = strdup(command); // Set the log
            count++;   // Increment the count
        }

        // Function clears the history
        void clear() {
            for (unsigned int i = 0; i < MAX_HISTORY; i++) {
                log[i] = NULL;
            }
            count = 0;
        }

        // Returns the previous command
        char *previous() {
            if (count == 0) {
                cout << "Shell history empty" << endl;
                return NULL; // History is empty
            }
            return log[count - 1];
        }

        // Displays the commands (oldest at the top to most recent at the bottom)
        void display() {
            // Iterate through log
            if (count == 0) {
                cout << "History is empty." << endl;
                return;
            }
            for (unsigned int i = 0; i < count; i++) {
                cout << i + 1 << ": " << log[i] << endl;
            }
        }
};

/**
 * @brief parse out the command and arguments from the input command separated
 * by spaces
 *
 * @param command
 * @param args
 * @return int
 */
int parse_command(char command[], char *args[]) {
    // TODO: implement this function
    // Command such as "ls -l" will be parsed into ["ls", "-l"]
    int numberOfArgs = 0;
    // Using strtok, separate by new lines
    char *token = strtok(command, " "); // Get the first token (the command)
    // Get the arguments and put it into args array
    while (token != NULL) { // This loop walks through the rest of the input string
        args[numberOfArgs++] = token; // Put the command first
        token = strtok(NULL, " ");    // Read through the rest of the inputs
    }
    args[numberOfArgs] = NULL; // Add a termination to the end of the array
    args[numberOfArgs - 1] = strtok(args[numberOfArgs - 1], "\n"); // Remove the trailing new line in the last argument
    return numberOfArgs - 1; // Subtract one to exclude the command was included in index 0
}

// Function that checks if an ampersand exists in any of the arguments
bool commandContainsAmpersand(char *args[], int numberOfArgs) {
    // Start at index 1 because index 0 is the command
    for (int i = 1; i <= numberOfArgs; i++) {
        if (strcmp(args[i], "&") == 0) {
            return true;
        }
    }
    return false;
}


bool commandContainsIO(char *args[], int numberOfArgs, char &type) {
    for (int i = 1; i <= numberOfArgs; i++) {
        if (strcmp(args[i], ">") == 0) {
            type = 'o'; // o signifies output, write to file
            return true;
        }
        else if (strcmp(args[i], "<") == 0) {
            type = 'i'; // I signifies input, read from file
            return true;
        }
    }
    return false;
}

// Function that checks for output / input flags

/**
 * @brief The main function of a simple UNIX Shell. You may add additional
 * functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */

// https://learn.zybooks.com/zybook/CSUSMCS433ZhangFall2022/chapter/3/section/14
int main(int argc, char *argv[]) {
    char command[MAX_LINE];            // the command that was entered
    char history[MAX_HISTORY];         // the history of the commands entered
    char *args[MAX_LINE / 2 + 1]; // parsed out command line arguments
    bool should_run = true; /* flag to determine when to exit program */
    bool awaitCommand = true;

    ShellHistory shellHistory = ShellHistory(); // Instantiate a shell history object

    while (should_run) {
        printf("osh> ");
        fflush(stdout); // Clears the output buffer and prints everything
        // Read the input command
        char *input = fgets(command, MAX_LINE, stdin); // Read the input from the user
        if (strcmp(input, "\n") == 0) { // If nothing is entered, don't process.
            continue; 
        }
        // Parse the input command
        int numOfArgs = parse_command(input, args); // Returns the number of arguments
        if (strcmp(args[0], "exit") == 0) {
            cout << "Goodbye!" << endl;
            should_run = false;
            return 0;
        } else if (strcmp(args[0], "history") == 0) {
            // If history is entered, display the history
            shellHistory.display();
            continue;
        } else if (strcmp(args[0], "!!") == 0) {
            char *previousCommand = shellHistory.previous(); // Function implicitly prints if history is empty
            if (previousCommand == NULL) { // If there is no previous founnd
                continue;
            }
            // We now need to run the previous command
            // To do this, replace input with the previous command
            strcpy(input, previousCommand);
            strcat(input, "\n"); // Add a new line character for the parse command function
            // Re-parse the command
            numOfArgs = parse_command(command, args);
        }

        // Add the user input into history
        shellHistory.add(args, numOfArgs);

        if (commandContainsAmpersand(args, numOfArgs)) {
            // If an ampersand exists, then drop the last index
            args[numOfArgs] = NULL; // Terminate the array and replace the ampersand
            numOfArgs--; // Decrement the number of arguments to not include ampersand if IO character exists
            awaitCommand = false; // Set the awaitCommand flag to false to make shell not wait for child process to complete
        } else {
            awaitCommand = true; // Set the awaitCommand flag to true to make shell wait for child process to complete before being ready to serve additional questions
        }

        pid_t pid = fork(); // Fork a process; creates a copy of the main process

        if (pid == 0) { // If the process is a child process. Execute commands
            char ioType = '0'; // Initialize as an empty character
            // ioType can be either 'o' for output or 'i' for input
            if (commandContainsIO(args, numOfArgs, ioType)) { // Check if a ">" or "<" exists in arguments array
                // Check if a file was provided
                if (numOfArgs == 1) { // ie: "ls >"
                    cout << "Missing file argument." << endl; 
                    exit(1);
                }
                int fileDescriptor;
                if (ioType == 'o') {
                    // CHMOD 0777 => if file doesn't exist create a file with specified permissions
                    fileDescriptor = open(args[numOfArgs], O_WRONLY|O_CREAT, 0777); // O_CREAT will create a new file to redirect output
                    // We need to remove the arguments to run the command in execvp
                } else { // ioType == 'i'
                    fileDescriptor = open(args[numOfArgs], O_RDONLY); // Read only mode for protection. Will not create a new file if it does not exist
                }
                // STDIN_FILENO = 0, input stream
                // STDOUT_FILENO = 1, output stream

                // dup2 opens the file of the specified file descriptor
                args[numOfArgs - 1] = NULL; // Remove the IO character
                args[numOfArgs] = NULL; // Remove output file since it has already been opened.
                dup2(fileDescriptor, ioType == 'o' ? STDOUT_FILENO : STDIN_FILENO); 
            }
            int processStatus = execvp(args[0], args);
            // Process status will return 0 if successful.
            if (processStatus == -1) {
                cout << "Command not found" << endl;
            }
            exit(0);
        }

        else if (pid > 0) {
            // Parent will invoke wait() unless command included "&"
            if (awaitCommand) { // If no ampersand was found, wait for completion
                wait(NULL);
            }
            // Otherwise, continue to the next iteration (do nothing)
        }

        else { // If not parent or child (pid < 0), then error
            cout << "There was an error attempting to fork process" << endl;
            return 1; // Return early and exit status 1 (failed)
        }

        // TODO: Add your code for the implementation
        /**
         * After reading user input, the steps are:
         * (1) fork a child process using fork()
         * (2) the child process will invoke execvp()
         * (3) parent will invoke wait() unless command included &
         */
    }

    return 0;
}
