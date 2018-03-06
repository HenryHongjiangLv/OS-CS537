//
// Created by Henry on 1/26/18.
//
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>



void computeLPSArray(char *pat, int M, int *lps);

bool KMPSearch(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int lps[M];

    computeLPSArray(pat, M, lps);

    int i = 0;  
    int j  = 0; 
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            return true;
        }

        else if (i < N && pat[j] != txt[i])
        {
            if (j != 0)
                j = lps[j-1];
            else
                i = i+1;
        }
    }

    return false;
}

void computeLPSArray(char *pat, int M, int *lps)
{
    int len = 0;

    lps[0] = 0; 
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else 
        {
            if (len != 0)
            {
                len = lps[len-1];
	    }
            else 
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    char *line = NULL;
    size_t linecap = 0;

    if(argc == 1)
    {
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }
    else if (argc == 2)
    {
        while (getline(&line, &linecap, stdin) > 0)
            if(KMPSearch(argv[1], line))
                printf("%s", line);
    }
    else
    {
        if(argv[1][0] == 0)
            return 0;
        for(int i = 2; i < argc; i++)
        {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("my-grep: cannot open file\n");
                exit(1);
            }

            while (getline(&line, &linecap, fp) > 0)
                if(KMPSearch(argv[1], line))
                    printf("%s", line);

            fclose(fp);
        }
    }

    return 0;
}
