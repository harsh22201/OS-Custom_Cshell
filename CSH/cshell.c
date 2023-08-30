#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"
#define BLUE "\x1B[34m"
#define YELLOW "\x1B[33m"
#define MAX_WORDS 25
#define MAX_WORD_LENGTH 25

int word_count(const char *filename, int ign)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error");
        return -1;
    }
    int word = 0;
    char pch, ch;
    pch = ' ';
    while ((ch = fgetc(file)) != EOF)
    {
        // if (ign && ch == '\n')
        //     ch = ' ';
        if (ign && (isspace(ch) == 0) && (isspace(pch)))
        {
            word++;
        }
        else if (!ign && (ch != ' ') && (pch == ' '))
        {
            word++;
        }
        pch = ch;
    }
    fclose(file);
    return word;
}

void stringToWords(char *input_string, char *words[], int *word_count)
{
    *word_count = 0;
    char *token = strtok(input_string, " ");
    while (token != NULL && *word_count < MAX_WORDS)
    {
        words[*word_count] = token;
        (*word_count)++;
        token = strtok(NULL, " ");
    }
}

int main()
{
    printf(YELLOW "\n======================\n        SHELL       \n======================\n" RESET);
    char path[128];
    char shellpath[128];
    getcwd(shellpath, 128);

    while (1)
    {

        printf(GREEN "user@DEVICE:" RESET);
        printf(BLUE "%s" RESET, getcwd(path, 128));
        printf("$ ");
        char command[256];
        int argc;
        char *argv[25];
        fgets(command, 256, stdin);
        int len = strlen(command);
        command[len - 1] = ' ';
        stringToWords(command, argv, &argc);
        // for (int i = 0; i < argc; i++)
        // {
        //     printf("Word %d: %s\n", i + 1, argv[i]);
        // }

        if (!argc)
            continue;

        if (strcmp(argv[0], "word") == 0)
        {
            if (argc == 1)
            {
                fprintf(stderr, "Too few arguments\n");
                continue;
            }
            if (argv[1][0] == '-')
            {
                if (strcmp(argv[1], "-n") == 0)
                {
                    if (argc == 2)
                    {
                        fprintf(stderr, "Too few arguments\n");
                        continue;
                    }
                    char *filename = argv[2];
                    int wc = word_count(filename, 1);
                    if (wc >= 0)
                        printf("word count %d\n", wc);
                }
                else if (strcmp(argv[1], "-d") == 0)
                {
                    if (argc == 3)
                    {
                        fprintf(stderr, "Too few arguments\n");
                        continue;
                    }
                    char *filename1 = argv[2];
                    int wc1 = word_count(filename1, 0);
                    char *filename2 = argv[3];
                    int wc2 = word_count(filename2, 0);
                    if (wc1 >= 0 && wc2 >= 0)
                        printf("word difference %d\n", abs(wc1 - wc2));
                }
                else
                {
                    fprintf(stderr, "wrong option\n"); //, argv[1]);
                    continue;
                }
            }
            else
            {
                char *filename = argv[1];
                int wc = word_count(filename, 0);
                if (wc >= 0)
                    printf("word count %d\n", wc);
            }
        }

        else if (strcmp(argv[0], "dir") == 0)
        {
            int rc = fork();
            if (rc < 0)
            {
                fprintf(stderr, "dir Fork failed.\n");
                continue;
            }
            else if (rc == 0)
            {
                char *myargs[argc + 1];
                myargs[0] = strdup("./dir");
                char dirpath[128];
                strcpy(dirpath, shellpath);
                char dirf[5] = "/dir";
                strcat(dirpath, dirf);
                for (int i = 1; i < argc; i++)
                {
                    myargs[i] = strdup(argv[i]);
                    // printf("%s", myargs[i]);
                }
                myargs[argc] = NULL;
                execv(dirpath, myargs);
            }
            else
            {
                int dirstatus;
                wait(&dirstatus);
                if (WIFEXITED(dirstatus))
                {
                    if (argc == 2)
                        chdir(argv[1]);
                    else
                        chdir(argv[2]);
                }
            }
        }

        else if (strcmp(argv[0], "date") == 0)
        {
            int rc = fork();
            if (rc < 0)
            {
                fprintf(stderr, "date Fork failed.\n");
            }
            else if (rc == 0)
            {
                char *myargs[argc];
                myargs[0] = strdup("./date");
                char datepath[128];
                strcpy(datepath, shellpath);
                char datef[6] = "/date";
                strcat(datepath, datef);
                for (int i = 1; i < argc; i++)
                {
                    myargs[i] = strdup(argv[i]);
                }
                myargs[argc] = NULL;
                execv(datepath, myargs);
            }
            else
            {
                wait(NULL);
            }
        }

        else if (strcmp(argv[0], "cd..") == 0)
        {
            if (chdir("..") != 0)
            {
                perror("Error");
            }
        }

        else if (strcmp(argv[0], "exit") == 0)
        {
            exit(EXIT_SUCCESS);
        }

        else
        {
            fprintf(stderr, "command not found\n"); //, argv[1]);
        }
    }
    return 0;
}