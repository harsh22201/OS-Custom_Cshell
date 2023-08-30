// #define _XOPEN_SOURCE /* See feature_test_macros(7) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

// int date_d(char *date_string)
// {

//     struct tm time_struct;
//     if (strptime(date_string, "%Y-%m-%d %H:%M:%S", &time_struct) == NULL)
//     {
//         fprintf(stderr, "Invalid date format\n");
//         exit(EXIT_FAILURE);
//     }

//     time_t time_value = mktime(&time_struct);
//     if (time_value == -1)
//     {
//         fprintf(stderr, "Invalid date and time\n");
//         exit(EXIT_FAILURE);
//     }

//     char formatted_time[80];
//     strftime(formatted_time, sizeof(formatted_time), " %m-%d, %H:%M:%S IST %Y", &time_struct);
//     printf("Parsed date and time: %s\n", formatted_time);

//     return 0;
// }
int main(int argc, char *argv[])
{

    int or = 0;
    char *file_name = NULL;
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
        file_name = strdup(argv[2]);
        if (strcmp(argv[1], "-d") == 0)
        {
            ;
        }
        else if (strcmp(argv[1], "-R") == 0)
        {
            or = 1;
        }
        else
        {
            fprintf(stderr, "wrong option\n"); //, argv[1]);
            exit(1);
        }
    }
    else
    {
        file_name = strdup(argv[1]);
    }

    // FILE *file = fopen(file_name, "r");
    // if (file == NULL)
    // {
    //     perror("Error");
    //     exit(EXIT_FAILURE);
    // }
    struct stat file_stat;
    struct tm *tm_info;

    if (stat(file_name, &file_stat) == 0)
    {
        time_t modified_time = file_stat.st_mtime;
        tm_info = localtime(&modified_time);
    }
    else
    {
        perror("Error");
    }

    char time_buffer[80];

    if (or)
    {
        strftime(time_buffer, sizeof(time_buffer), "%a, %d %b %Y %H:%M:%S %z", tm_info);
        printf("Last modified time: %s\n", time_buffer);
    }

    else
    {
        strftime(time_buffer, sizeof(time_buffer), "%a %b %d %H:%M:%S IST %Y", tm_info);
        printf("Last modified time: %s\n", time_buffer);
    }

    return 0;
}
