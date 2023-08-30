
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    int or = 0;
    int ov = 0;
    char *dir_name = NULL;
    if (argc <= 1)
    {
        fprintf(stderr, "Too few arguments\n");
        exit(EXIT_FAILURE);
    }
    if (argv[1][0] == '-')
    {
        if (argc <= 2)
        {
            fprintf(stderr, "Too few arguments\n");
            exit(EXIT_FAILURE);
        }
        dir_name = strdup(argv[2]);
        if (strcmp(argv[1], "-r") == 0)
        {
            or = 1;
        }
        else if (strcmp(argv[1], "-v") == 0)
        {
            ov = 1;
            printf("Forking new process\n");
            printf("Executing dir\n");
        }
        else
        {
            fprintf(stderr, "wrong option\n"); //, argv[1]);
            exit(1);
        }
    }
    else
    {
        dir_name = strdup(argv[1]);
    }

    int de = 0;
    DIR *dir = opendir(dir_name);
    if (dir)
    {
        de = 1;
        closedir(dir);
    }

    if (de && (! or))
    {
        fprintf(stderr, "Directory already exist\n");
        printf("type cd.. to go back shell directory\n");
        exit(EXIT_FAILURE);
    }

    if (de && or)
    {
        printf("Waring: Removing existing directory\n");
        if (rmdir(dir_name) == 0)
        {
            // printf("Directory deleted successfully.\n");
        }
        else
        {
            perror("Error deleting directory");
            exit(EXIT_FAILURE);
        }
    }
    if (ov)
        printf("Creating directory\n");
    if (mkdir(dir_name, 0777) == 0)
    {
        if (ov)
        {
            printf("Directory created successfully\n");
            printf("Changing working directory\n");
        }
        char s[100];
        // printf("%s\n", getcwd(s, 100));
        if (chdir(dir_name) == 0)
        {
            if (ov)
                printf("Changed working directory to %s\n", dir_name);
            printf("type cd.. to go back shell directory\n");
        }
        else
        {
            perror("Error changing working directory");
            exit(EXIT_FAILURE);
        }
        // printf("%s\n", getcwd(s, 100));
    }
    else
    {
        perror("Error creating directory");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
    return 0;
}
