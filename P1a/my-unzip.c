//
// Created by Henry on 1/26/18.
//

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);
    }
    else
    {
        for(int i = 1; i < argc; i++)
        {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("my-unzip: cannot open file\n");
                exit(1);
            }

            int count;
            char current_char;
            while (fread(&count, sizeof(count), 1, fp) > 0)
            {
                fread(&current_char, sizeof(current_char), 1, fp);
                for(int i = 0; i < count; i++)
                    printf("%c", current_char);
            }
            fclose(fp);
        }
    }

    return 0;
}
