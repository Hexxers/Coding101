#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 4

/*Structure of the matches*/
typedef struct{
    char weekday[NAME_LENGTH], hometeam[NAME_LENGTH], awayteam[NAME_LENGTH];
    double time;
    int home_goals, away_goals, month, day, num_spec;
}match_t;

/*Remember to declare prototypes*/
void get_match_data(match_t *output); 
void print_tester(match_t *match_array);

int main()
{
    match_t match_array[200];
    get_match_data(match_array);
    print_tester(match_array);
    return 0;
}

void get_match_data(match_t *output){
    static const char filename[] = "kampresultater.txt";
    FILE *file = fopen(filename, "r");
    int i = 0;

    if (file != NULL){
        char line[128]; /*Needs to be atleast the size of a line*/

        /*Read line*/
        while (fgets(line, 5000, file) != NULL){
            if (strlen(line)>5){
                int thousand_separator = 0;
                int hundred_separator = 0;
                sscanf(line,"%s %d/%d %lf %s - %s %d - %d %d.%d", output[i].weekday, &output[i].day, 
                                                        &output[i].month, &output[i].time, output[i].hometeam, output[i].awayteam, 
                                                        &output[i].home_goals, &output[i].away_goals, &thousand_separator, &hundred_separator);
                output[i].num_spec = thousand_separator * 1000 + hundred_separator;
                
                i++;
            }
        }
        fclose(file);
    }
    else {
        perror(filename);
    }
}

void print_tester(match_t *match_array){
    int i = 0;

    for (i; i < 198; i++)
    {
        printf("%s %d/%d %.2lf %s - %s %d - %d %d\n", match_array[i].weekday, match_array[i].day, 
                                                      match_array[i].month, match_array[i].time, match_array[i].hometeam, match_array[i].awayteam, 
                                                      match_array[i].home_goals, match_array[i].away_goals, match_array[i].num_spec);
    }
    
    
}