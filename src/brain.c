#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAM_SIZE 65536
#define MAX_SRC_SIZE 65536

int
main(int argc, char* argv[])
{
    // Allocate memory.
    char* ram = calloc(RAM_SIZE, sizeof(char));
    char* program = calloc(MAX_SRC_SIZE, sizeof(char));

    // Check CLI args.
    if (argc != 2) {
        printf("USAGE: %s [SOURCE]\n", argv[0]);
        goto clean;
    }

    // Set up array of bytes.
    char* pc = ram;

    // Load src file.
    FILE* src = fopen(argv[1], "r");

    if (src == NULL) {
        fprintf(stderr, "Failed to open '%s' because: %s.\n", argv[1], strerror(errno));
        goto clean;
    }

    char c = fgetc(src);
    while(!feof(src)) {
        if (
            c == '>' || c == '<' || c == '+' || c == '-' || 
            c == '[' || c == ']' || c == '.' || c == ','
        ) {
            putchar(c);
        }
        c = fgetc(src);
    }

clean:
    // Clean memory.
    free(program);
    free(ram);

    return 0;
}
