//
// Created by Henry on 1/26/18.
//

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    char *line = NULL;
    size_t linecap = 0;

    if(argc < 2)
    {
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }
    else
    {
	char current_char;
        int count = -1;
        for(int i = 1; i < argc; i++)
        {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("my-zip: cannot open file\n");
                exit(1);
            }
	    

            while (getline(&line, &linecap, fp) > 0)
            {
                for(int i = 0; line[i] != 0; i++)
                {
		    if(count == -1)
		    {
                        count = 1;
                        current_char = line[i];
		    }
		    else
                    if(line[i] == current_char)
                        count++;
                    else
                    {
			
                        fwrite(&count, sizeof(count), 1, stdout);
                        fwrite(&current_char, sizeof(current_char), 1, stdout);
                        count = 1;
                        current_char = line[i];
                    }
                }
            }
	    
            fclose(fp);
        }
        fwrite(&count, sizeof(count), 1, stdout);
        fwrite(&current_char, sizeof(current_char), 1, stdout);
    }

    return 0;
}
