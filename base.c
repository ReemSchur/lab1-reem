#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
char* map(char *array, int array_length, char (*f) (char)){
  char* mapped_array = (char*)(malloc(array_length*sizeof(char)));
  /* TODO: Complete during task 2.a */

  for (int i = 0; i < array_length; i++) {
    mapped_array[i] = f(array[i]);
  }
  return mapped_array;
}


char my_get(char c) {
    (void)c; // ignore input
    int ch = fgetc(stdin);
    return (ch == EOF) ? 0 : (char)ch;
}

char encrypt(char c) {
    unsigned char uc = (unsigned char)c;
    if (uc >= 0x1F && uc <= 0x7E) uc++;
    return (char)uc;
}

char decrypt(char c) {
    unsigned char uc = (unsigned char)c;
    if (uc >= 0x21 && uc <= 0x7F) uc--;
    return (char)uc;
}

char dprt(char c) {
    printf("%d\n", (unsigned char)c);
    return c;
}

char cxprt(char c) {
    unsigned char uc = (unsigned char)c;
    if (uc >= 0x20 && uc <= 0x7E)
        printf("%c ", c);
    else
        printf(". ");
    printf("%02X\n", uc);
    return c;
}


int main(int argc, char **argv) {
    (void)argc; (void)argv;

    int base_len = 5;
    char arr1[base_len];

    printf("Enter %d characters:\n", base_len);

    char* arr2 = map(arr1, base_len, my_get);   // get input
    char* arr3 = map(arr2, base_len, dprt);     // print decimals
    char* arr4 = map(arr3, base_len, cxprt);    // print chars+hex

    free(arr2);
    free(arr3);
    free(arr4);

    return 0;
}

