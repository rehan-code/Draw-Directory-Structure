#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <grp.h>
#include <unistd.h>

/**
 * Student Name: Rehan Nagoor Mohideen
 * Student ID: 110592
 */

/**
 * Recursively prints the relationships for the inner files
 */
void printDir(char path[4096], char prevStr[1000]) {
    DIR *directory = opendir(path);
    if (directory == NULL) {
        printf("Could not open PATH directory\n" );
        return;
    }

    struct dirent *dirEntry;
    struct stat fileStat;
    int currInt = 0;

    while ((dirEntry = readdir(directory)) != NULL){//for each file in the directory
        char nPath[4096];
        strcpy(nPath, path);
        strcat(nPath, "/");
        strcat(nPath, dirEntry->d_name);
        char currStr[1000];

        if (stat(nPath, &fileStat) == 0  && strcmp(dirEntry->d_name, ".")!=0 && strcmp(dirEntry->d_name, "..")!=0) {//if successfully obtaines the stats
            if (S_ISDIR(fileStat.st_mode)){//for directories
                currInt++;
                char curIntStr[1000];
                sprintf(curIntStr, "%d", currInt);
                strcpy(currStr, prevStr);
                strcat(currStr, "_");
                strcat(currStr, curIntStr);

                printf("%s[%s]\n", currStr, dirEntry->d_name);
                printf("%s --- %s\n", prevStr, currStr);
                printDir(nPath, currStr);//recursively for inner files

            } else if (S_ISREG(fileStat.st_mode)) {//for files
                currInt++;
                char curIntStr[1000];
                sprintf(curIntStr, "%d", currInt);
                strcpy(currStr, prevStr);
                strcat(currStr, "_");
                strcat(currStr, curIntStr);

                printf("%s(%s)\n", currStr, dirEntry->d_name);
                printf("%s --- %s\n", prevStr, currStr);
            }
        }
    }

    closedir(directory);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./drawDir Directory-name\n");
        return 1;
    }
    char path[4096];
    getcwd(path, sizeof(path));
    strcat(path, "/");
    strcat(path, argv[1]);

    DIR *directory = opendir(path);
    if (directory == NULL) {
        printf("Could not open PATH directory\n" );
        return 0;
    }

    printf("<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"utf-8\">\n</head>\n<body>\n<center>\n<div class=\"mermaid\">\n");
    printf("graph TD\n");
    char currChar = 'A';
    char prevChar = 'A';
    printf("%c[%s]\n", currChar, argv[1]);

    struct dirent *dirEntry;
    struct stat fileStat;
    while ((dirEntry = readdir(directory)) != NULL){//for each file in the directory
        char nPath[4096];
        strcpy(nPath, path);
        strcat(nPath, "/");
        strcat(nPath, dirEntry->d_name);


        if (stat(nPath, &fileStat) == 0  && strcmp(dirEntry->d_name, ".")!=0 && strcmp(dirEntry->d_name, "..")!=0) {//if successfully obtaines the stats
            if (S_ISDIR(fileStat.st_mode)){//for directories
                currChar++;
                printf("%c[%s]\n", currChar, dirEntry->d_name);
                printf("%c --- %c\n", prevChar, currChar);
                char curStr[1000];
                sprintf(curStr, "%c", currChar);
                printDir(nPath, curStr);//recursively do for inner files

            } else if (S_ISREG(fileStat.st_mode)) {//for files
                currChar++;
                printf("%c(%s)\n", currChar, dirEntry->d_name);
                printf("%c --- %c\n", prevChar, currChar);
            }
        }
    }

    printf("</div>\n</center>\n<script src=\"mermaid8.9.1.min.js\"></script>\n<script>mermaid.initialize({startOnLoad:true});</script>\n</body>\n</html>\n");
    closedir(directory);

    return 0;
}
