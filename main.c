#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

int save();
int checkifexists();
int checkdir();
char title[32];
char note[1024];

int main() {
    DIR* dir = opendir("notes");
    if (dir) {
        closedir(dir); //exists
    } else if (ENOENT == errno) {
        system("mkdir notes");
    }

    int welcome; 
    printf("Type 0 to inspect your notes, 1 to create a new note.\n");
    scanf("%d", &welcome);
    
    if (welcome == 0) {
        system("start notes");
    } else if (welcome == 1) {
        printf("Type the title of note (max: 32 chars):\n > ");
        scanf(" %[^\t\n]s", title);
        
        if (checkifexists() == 1) {
            printf("A note with %s title already exists.", title);
        } else if (checkifexists() == 0) {
            printf("Write your note (max: 1024 chars):\n > ");
            scanf(" %[^\t\n]s", note);
            save();
        }

    }
    

    return 0;
}

int save() {
    char filename[42] = "notes/";
    strcat(filename, title);
    strcat(filename, ".txt");
    FILE * fp;
    fp = fopen(filename, "w");
    fprintf(fp, "%s", note);
    fclose(fp);
    return 0;
}

int checkifexists() {
    char filename[42] = "notes/";
    strcat(filename, title);
    strcat(filename, ".txt");

    if (fopen(filename, "r")) {
        return 1; //exists
    } else {
        return 0;
    }
}