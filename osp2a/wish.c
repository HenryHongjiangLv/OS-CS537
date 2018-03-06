#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>



void exeOutCmd(char* cmd, int numOfPara);

char **path;
int pathLength;

void errorHandler()
{
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
}

char *trim(char *str)
{
  char *end;

  // Trim leading space
  while(*str == ' ') str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && *end == ' ') end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}

int exeCmd(char* cmd)
{
    char *sep = "\n\t ", *brkt;
    char *token;
    int cmdLen = 1;
    char *cmdIterator = cmd;
    while(*cmdIterator++ != '\0')
        cmdLen++;
    //cmdIterator--;
    //cmdIterator--;
    //if(*cmdIterator == '\n')
    //  *cmdIterator = '\0';
    char *cmdBackUp = malloc(cmdLen + 1);
    strcpy(cmdBackUp, cmd);
    token = strtok_r(cmd, sep, &brkt);
    char cmdBegin[10];
    int matched = 0;

    if(token == NULL)
      return 0;
    strcpy(cmdBegin, "cd");
    if(strcmp(token, cmdBegin) == 0)
    {
        matched = 1;
        token = strtok_r(NULL, sep, &brkt);
	if(token == NULL)
	{
	    errorHandler();
	    return 0;
	}
	char *directory = token;
        chdir(directory);
        if(strtok_r(NULL, sep, &brkt) != NULL)
            errorHandler();
    }

    strcpy(cmdBegin, "exit");
    if(strcmp(token, cmdBegin) == 0)
    {
        token = strtok_r(NULL, sep, &brkt);
        if(token != NULL)
	{
	  errorHandler();
	  return 0;
	}
        exit(0);
    }

    strcpy(cmdBegin, "path");
    if(strcmp(token, cmdBegin) == 0)
    {
        matched = 1;
        int count = 0;
        for (token = strtok_r(NULL, sep, &brkt);
             token;
             token = strtok_r(NULL, sep, &brkt))
        {
            count++;
        }

        path = malloc(count);
        pathLength = count;
        char *brkt2;
        strtok_r(cmdBackUp, sep, &brkt2);

        int i = 0;
        for (token = strtok_r(NULL, sep, &brkt2);
             token;
             token = strtok_r(NULL, sep, &brkt2))
        {
            int pathLen = 1;
            char *tokenIter = token;
            while(*tokenIter++ != '\0')
                pathLen++;
            path[i] = malloc(pathLen + 1);
            strcpy(path[i++], token);
        }

    }


    if(matched == 0)
    {
        int rc = fork();
        if(rc == 0)
        {
            int count = 1;
            for (token = strtok_r(NULL, sep, &brkt);
                 token;
                 token = strtok_r(NULL, sep, &brkt))
            {
                count++;
            }
            exeOutCmd(cmdBackUp, count);
	    exit(0);
	}
        return 1;
    }

    return 0;
}

void exeOutCmd(char* cmdOri, int numOfPara)
{
    char *sepRedirection = ">\n";
    char *containsR;
    containsR = strstr(cmdOri, ">");
    
      
    char *brktR;
    char *sep = "\n\t ", *brkt;
    char *cmd = strtok_r(cmdOri, sepRedirection, &brktR);
    char *file = strtok_r(NULL, sepRedirection, &brktR);
    
    if(containsR != NULL && file == NULL)
    {
      errorHandler();
      return;
    }
    if (file != NULL) {
        char *firstFile = strdup(strtok_r(file, sep, &brkt));
        //int fd = open(firstFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if(strtok_r(NULL, sep, &brkt) != NULL)
	{
	  errorHandler();
	  return;
	}
	if(strtok_r(NULL,sepRedirection,&brktR) != NULL)
	  {
	    errorHandler();
	    return;
	  }
	int fd = open(firstFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if(fd < 0)
	{
	  errorHandler();
	  return;
	}
        dup2(fd, 1);
        dup2(fd, 2);

        close(fd);
    }

    brkt = NULL;

    char *token;
    int canAccess = -1;
    token = strtok_r(cmd, sep, &brkt);
    for(int i = 0; i < pathLength; i++)
    {
        char cmdToAccess[sizeof(path[i]) + sizeof(token)];
        cmdToAccess[0] = '\0';
        strcat(cmdToAccess, path[i]);
        strcat(cmdToAccess, "/");
        strcat(cmdToAccess, token);
        canAccess = access(cmdToAccess, X_OK);
	//printf(cmdToAccess);fflush(stdout);
	if(canAccess == 0)
        {
            //exec
            char *argv[numOfPara];
            argv[0] = strdup(token);
            int index = 1;
            for (token = strtok_r(NULL, sep, &brkt);
                 token;
                 token = strtok_r(NULL, sep, &brkt))
            {
                argv[index++] = strdup(token);
            }
            argv[index] = NULL;
            execv(cmdToAccess, argv);

            break;
        }
    }

    if(canAccess == -1)
        errorHandler();
}

int main(int argc, const char* argv[]) {
    char *line = NULL, *brktP, *word;
    char *sepParallel = "&";

    size_t len = 0;
    ssize_t nread;


    path = malloc(1);
    path[0] = malloc(sizeof("/bin"));
    strcpy(path[0], "/bin");
    pathLength = 1;

    if(argc == 1)
        while(1)
        {
            printf("wish> ");
	    fflush(stdout);
	    //nread = 3;
            //line = malloc(3);
            //strcpy(line, "ls\n");
            //strcpy(line, "path /bin /usr/bin\n");
            nread = getline(&line, &len, stdin);
            //printf("%d", (int)nread);
	    if(nread == -1)
	    {
	      exit(0);
	    }
            if(nread <= 1) //user input nothing
            {
                continue;
            }
            else
            {
                int sum = 0;
                for (word = strtok_r(line, sepParallel, &brktP);
                     word;
                     word = strtok_r(NULL, sepParallel, &brktP))
                {
                    sum += exeCmd(word);
                }
                for(int i = 0; i < sum; i++)
                    wait(NULL);
            }

        }
    else if(argc == 2)
    {
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL) {
            errorHandler();
	    exit(1);
	}
        char *line = NULL;
        size_t linecap = 0;
	int nread;
        while ((nread = getline(&line, &linecap, fp)) && nread > 0)
        {
	  
	  /*if (*(line+nread - 1) == '\n')
	    {
	      *(line + nread - 1) = '\0';
	      }*/
            int sum = 0;
            for (word = strtok_r(line, sepParallel, &brktP);
                 word;
                 word = strtok_r(NULL, sepParallel, &brktP))
            {
                sum += exeCmd(word);
            }
            for(int i = 0; i < sum; i++)
                wait(NULL);
        }

        fclose(fp);
    }
    else
    {
        errorHandler();
	exit(1);
    }
    exit(0);
}
