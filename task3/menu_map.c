/*
 * This code was written and refactored with assistance from Gemini.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The fixed size for our data array
#define DATA_SIZE 5

/* ================================================================================
===== TASK 2 FUNCTIONS =========================================================
================================================================================
*/

/**
 * @brief Applies a function 'f' to each element of 'array'.
 * @return A pointer to a *newly allocated* array with the results.
 * The caller is responsible for freeing this new array.
 */
char* map(char *array, int array_length, char (*f) (char)) {
    if (array_length <= 0 || f == NULL) {
        return NULL;
    }

    // 1. Allocate memory for the new result array
    char *result_array = malloc(array_length * sizeof(char));

    // 2. CRITICAL: Always check if malloc succeeded.
    if (result_array == NULL) {
        perror("malloc failed");
        exit(1);
    }

    // 3. Apply the function 'f' to each element
    for (int i = 0; i < array_length; i++) {
        result_array[i] = f(array[i]);
    }

    // 4. Return the new array
    return result_array;
}

/**
 * @brief (Task 2b) Reads a single char from stdin.
 */
char my_get(char c) {
    (void)c; // Ignore the unused parameter
    int ch = fgetc(stdin);
    if (ch == EOF) {
        return 0;
    }
    return (char)ch;
}

/**
 * @brief (Task 2b) Prints the decimal (int) value of 'c'.
 */
char dprt(char c) {
    printf("%d\n", (unsigned char)c);
    return c;
}

/**
 * @brief (Task 2b) Prints the char (if printable) and its hex value.
 */
char cxprt(char c) {
    unsigned char uc = (unsigned char)c;
    if (uc >= 0x20 && uc <= 0x7E) { // Is it a printable ASCII char?
        printf("%c ", c);
    } else {
        printf(". "); // Otherwise, print a dot
    }
    printf("%02X\n", uc); // Print 2-digit hex
    return c;
}

/**
 * @brief (Task 2b) Encrypts 'c' by adding 1.
 */
char encrypt(char c) {
    unsigned char uc = (unsigned char)c;
    if (uc >= 0x1F && uc <= 0x7E) {
        uc = uc + 1;
    }
    return (char)uc;
}

/**
 * @brief (Task 2b) Decrypts 'c' by subtracting 1.
 */
char decrypt(char c) {
    unsigned char uc = (unsigned char)c;
    if (uc >= 0x21 && uc <= 0x7F) {
        uc = uc - 1;
    }
    return (char)uc;
}

/* ================================================================================
===== TASK 3: THE MENU =========================================================
================================================================================
*/

/**
 * @brief A struct to link a menu item's name to its function.
 */
struct MenuOption {
    char *name;         // The string to show in the menu
    char (*fun)(char);  // The pointer to the function to call
};

/**
 * @brief Main function: The program's control loop.
 */
int main(int argc, char **argv) {
    (void)argc; // Silence warnings
    (void)argv;

    // --- 1. Initialization ---
    
    // This 'data_array' is the program's "memory" or "state"
    char *data_array = malloc(DATA_SIZE * sizeof(char));
    if (data_array == NULL) {
        perror("malloc failed");
        exit(1);
    }
    memset(data_array, 0, DATA_SIZE); // Start with a clean, empty array

    // --- 2. Menu Setup ---

    // This array links user-friendly names to our functions
    struct MenuOption menu_options[] = {
        { "Get string",       my_get   },
        { "Print dec",        dprt     },
        { "Print string+hex", cxprt    },
        { "Encrypt",          encrypt  },
        { "Decrypt",          decrypt  },
        { NULL,               NULL     }  // A "sentinel" to mark the end
    };

    // Calculate the menu size *once*
    int menu_size = 0;
    while (menu_options[menu_size].name != NULL) {
        menu_size++;
    }

    char user_input_line[128]; // Buffer for the user's raw input line

    // --- 3. Main Event Loop ---
    
    while (1) {
        // 3a. Print the menu
        printf("Select operation from the following menu:\n");
        for (int i = 0; i < menu_size; i++) {
            printf("%d) %s\n", i, menu_options[i].name);
        }
        printf("Option: ");

        // 3b. Get User Input (checking for EOF)
        if (fgets(user_input_line, sizeof(user_input_line), stdin) == NULL) {
            printf("\nExiting...\n");
            break; // Exit loop on Ctrl+D (EOF)
        }

        // 3c. Parse and Validate Input
        int menu_choice;
        if (sscanf(user_input_line, "%d", &menu_choice) != 1) {
            printf("Invalid input, exiting.\n");
            break; // Exit loop if input wasn't a number
        }

        if (menu_choice < 0 || menu_choice >= menu_size) {
            printf("Not within bounds, exiting.\n");
            break; // Exit loop if number is out of range
        }

        printf("Within bounds\n");

        // 3d. Execute the Function
        // This is the core logic: call 'map' and pass it the function
        // pointer from the 'menu_options' array.
        char *new_data_array = map(data_array, DATA_SIZE, menu_options[menu_choice].fun);

        // 3e. Memory Management
        // We must free the *old* array to prevent a memory leak
        free(data_array);
        // And update our main pointer to point to the *new* data
        data_array = new_data_array;
        // --- 3f: Input Buffer clear (Fix) ---
        // If we just ran "Get string", we must clear the leftover '\n'
        if (menu_choice == 0) {
            int c;
            while ((c = fgetc(stdin)) != '\n' && c != EOF);
        }

        printf("DONE.\n\n");

    } // End of while(1) loop

    // --- 4. Cleanup ---
    free(data_array); // Free the last allocated array
    return 0;
}