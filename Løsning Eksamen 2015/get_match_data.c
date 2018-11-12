#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_TEAMS 11
#define NAME_LENGTH 4
#define WIN 3
#define PLAY 1
#define MAX_MATCHES 197


/*Defining match struct*/
typedef struct{
    char weekday[NAME_LENGTH], hometeam[NAME_LENGTH], awayteam[NAME_LENGTH];
    double time, num_spec;
    int home_goals, away_goals, num_round, month, day;
}match_t;

void get_match_data(match_t *output); 

int main(void){
    match_t match_arr[200];
    
    get_match_data(match_arr);

    return 0;
}

void get_match_data(match_t *output){      
    static const char filename[] = "kampresultater.txt";
    FILE *file = fopen(filename, "r");
    char temp[60];                                        /*Used for saving info from fgets temporaily*/
    int i=0,j=1;                                          /*Loop variables*/
  
  
    while((fgets(temp, 5000, file)) != NULL){
        if(strlen(temp)>5){                                 /*If the length of temp is lower than 5, its a blank line, and it wont get saved*/
            sscanf(temp,"%s %d/%d %lf %s - %s %d - %d %lf", output[i].weekday, &output[i].day, 
                                                        &output[i].month, &output[i].time, output[i].hometeam, output[i].awayteam, 
                                                        &output[i].home_goals, &output[i].away_goals, &output[i].num_spec);
            output[i].num_round = j;
            i++;                                              /*Otherwise save data in match array*/  
        }
        else{
            j++;                                              /*If its lower than 5 it will count up the round number*/
        }
    }
    fclose(file);
}   