#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_LEN 5

/* ---- Task 2 functions reused ---- */

char* map(char *array, int array_length, char (*f) (char)) {
    if (array_length <= 0 || f == NULL) {
        return NULL;
    }

    char *mapped_array = malloc(array_length * sizeof(char));
    if (mapped_array == NULL) {
        perror("malloc failed");
        exit(1);
    }

    for (int i = 0; i < array_length; i++) {
        mapped_array[i] = f(array[i]);
    }

    return mapped_array;
}

char my_get(char c) {
    (void)c; /* ignore input */
    int ch = fgetc(stdin);
    if (ch == EOF) {
        return 0;
    }
    return (char)ch;
}

char dprt(char c) {
    printf("%d\n", (unsigned char)c);
    return c;
}

char cxprt(char c) {
    unsigned char uc = (unsigned char)c;

    if (uc >= 0x20 && uc <= 0x7E) {
        printf("%c ", c);
    } else {
        printf(". ");
    }
    printf("%02X\n", uc);

    return c;
}

char encrypt(char c) {
    unsigned char uc = (unsigned char)c;

    if (uc >= 0x1F && uc <= 0x7E) {
        uc = uc + 1;
    }
    return (char)uc;
}

char decrypt(char c) {
    unsigned char uc = (unsigned char)c;

    if (uc >= 0x21 && uc <= 0x7F) {
        uc = uc - 1;
    }
    return (char)uc;
}

/* ---- Task 3: menu ---- */

struct fun_desc {
    char *name;
    char (*fun)(char);
};

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    /* carray: pointer to char array of length 5, "empty string" */
    char *carray = malloc(BASE_LEN * sizeof(char));
    if (carray == NULL) {
        perror("malloc failed");
        exit(1);
    }
    memset(carray, 0, BASE_LEN);

    struct fun_desc menu[] = {
        { "Get string",      my_get   },
        { "Print dec",       dprt     },
        { "Print string+hex",cxprt    },
        { "Encrypt",         encrypt  },
        { "Decrypt",         decrypt  },
        { NULL,              NULL     }
    };

    int menu_len = 0;
    while (menu[menu_len].name != NULL) {
        menu_len++;
    }

    char input[128];

    while (1) {
        printf("Select operation from the following menu:\n");
        for (int i = 0; i < menu_len; i++) {
            printf("%d) %s\n", i, menu[i].name);
        }
        printf("Option: ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            /* EOF */
            free(carray);
            return 0;
        }

        int choice;
        if (sscanf(input, "%d", &choice) != 1) {
            /* not a number → treat as invalid and exit */
            printf("Not within bounds\n");
            free(carray);
            return 0;
        }

        if (choice < 0 || choice >= menu_len) {
            printf("Not within bounds\n");
            free(carray);
            return 0;
        }

        printf("Within bounds\n");

        /* apply selected function over carray via map */
        char *new_carray = map(carray, BASE_LEN, menu[choice].fun);
        free(carray);
        carray = new_carray;

        printf("DONE.\n\n");
    }
}

