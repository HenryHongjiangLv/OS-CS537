#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE (1024)

int main(int argc, char* argv[])
{
    if(argc > 1)
    {
        for(int i = 1; i < argc; i++)
        {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("my-cat: cannot open file\n");
                exit(1);
            }

            char buffer[BUFFER_SIZE];
            while (fgets(buffer, BUFFER_SIZE, fp) != NULL)
                printf("%s", buffer);

            fclose(fp);
        }
    }

    return 0;
}
