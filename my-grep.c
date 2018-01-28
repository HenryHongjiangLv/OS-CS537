//
// Created by Henry on 1/26/18.
//
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>



void computeLPSArray(char *pat, int M, int *lps);

// Prints occurrences of txt[] in pat[]
bool KMPSearch(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0;  // index for txt[]
    int j  = 0;  // index for pat[]
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

            // mismatch after j matches
        else if (i < N && pat[j] != txt[i])
        {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j-1];
            else
                i = i+1;
        }
    }

    return false;
}

// Fills lps[] for given patttern pat[0..M-1]
void computeLPSArray(char *pat, int M, int *lps)
{
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0)
            {
                len = lps[len-1];

                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
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