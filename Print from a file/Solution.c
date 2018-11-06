#include <stdio.h>
#include <stdlib.h>


int main()
{
    static const char filename[] = "kampresultater.txt";
    FILE *file = fopen(filename, "r");

    if (file != NULL){
        char line[128]; /*Needs to be atleast the size of a line*/

        /*Read line*/
        while (fgets(line, sizeof line, file) != NULL){
            fputs(line, stdout);
        }
        fclose(file);
    }
    else {
        perror(filename);
    }

    return 0;
}
