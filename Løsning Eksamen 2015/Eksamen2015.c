#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_TEAMS 11
#define NAME_LENGTH 4
#define WIN 3
#define PLAY 1
#define MAX_MATCHES 197

/*Defining team struct*/
typedef struct team_x{
    char name[NAME_LENGTH];        
    int games_played;            
    int goals_scored;           
    int goals_conceded;            
    int total_points;           
    int goal_diff;
    double spectators;
    int homewin;
    int awaywin;
    int draws;
    int awayloss;
    int homeloss;
}team_x;

/*Defining match struct*/
typedef struct{
    char weekday[NAME_LENGTH], hometeam[NAME_LENGTH], awayteam[NAME_LENGTH];
    double time, num_spec;
    int home_goals, away_goals, num_round, month, day;
}match_t;


void solve_all_tasks();                               /*Solve all the tasks*/
void get_match_data(match_t *output); 
void opgave_1(match_t *input);                        /*Find matches with/more 7 goals*/
void opgave_2(match_t *input);                        /*Find the round with highest score*/
void get_team_names(match_t *input, team_x *output);  /*Get the team names from the txt file, and putting them in the team struct*/
int team_id(char *name, team_x *all_teams);           /*Team identifier*/
void opgave_3(match_t *input, team_x *all_teams);     /*Finding the teams with more awaywins than homewins*/
void opgave_4(match_t *input, team_x *all_teams);     /*Finding the teams with fewest spectators throughtout season*/
void opgave_5(match_t *input);                        /*Friday matches sorted*/
int match_comp(const void *A, const void *B);         /*sorting function for "opgave_5"*/
void opgave_6(match_t *input, team_x *all_teams);     /*Sorting the teams by points*/
int comp(const void *A, const void *B);               /*Sorting function for "opgave_6"*/


int main(void){
    solve_all_tasks();
    return 0;
}

void solve_all_tasks(){
    match_t match_arr[200];
    team_x team_arr[12];    
    
    get_match_data(match_arr);
    opgave_1(match_arr);
    opgave_2(match_arr);
    get_team_names(match_arr, team_arr);
    opgave_3(match_arr, team_arr);
    opgave_4(match_arr, team_arr);
    opgave_5(match_arr);
    opgave_6(match_arr, team_arr);
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

void opgave_1(match_t *input){
    int score = 0;
    int i;

    printf("Opgave 1:\n");
    for(i=0; i<=MAX_MATCHES; i++ ){                       
        score = input[i].home_goals+input[i].away_goals;
        if(score > 6){
            printf("In round %d in match between %s and %s %d goals were scored.\n", input[i].num_round, input[i].hometeam, input[i].awayteam, score);
        }
    }
}

void opgave_2(match_t *input){
    int round_score=0;
    int i;
    int high_score=0;                                            /*Used for saving highest score in round*/
    int high_round=0;                                            /*Used for saving number of round*/
  
    printf("Opgave 2:\n");
    for(i=0; i<=MAX_MATCHES; i++){
        round_score += (input[i].home_goals+input[i].away_goals); /*Adding the amount of goals to round score*/
        if(i%6==5){                                               /*Checking if round is over*/
            if(high_score<round_score){
                high_score=round_score;
                high_round=input[i].num_round;
            }
            round_score = 0;
        }
    }  
    printf("Highest score was %d in round %d\n", high_score, high_round); 
}

void get_team_names(match_t *input, team_x *output){    
    int i=0,j=0;
  
    for(i=0; i<=5; i++){                                    /*Running loop for 1 round to get all names*/
        strcpy(output[j].name, input[i].hometeam);          /*Copying hometeams name into team array #1*/
        strcpy(output[j+1].name, input[i].awayteam);        /*Copying awayteams name into team array #2*/
        j+=2;                                               /*Moving the placer for team array up 2 so it becomes #3 and so on*/
    }
}

int team_id(char *name, team_x *all_teams){
    int i=0;

    for(i=0; i<=NUMBER_OF_TEAMS; i++){                    
        if(strcmp(name, all_teams[i].name)==0){                 /*Checking if the name input is the same as any of the names in team array*/
            return i;                                           /*Returning team number*/
        }
    }
  return 0;
}

void opgave_3(match_t *input, team_x *all_teams){
    int i=0;
    int home=0;
    int away=0;
  
    for(i=0; i<=MAX_MATCHES; i++){                        /*Running the loop through all matches*/
        home = team_id(input[i].hometeam, all_teams);       /*Finding hometeam*/
        away = team_id(input[i].awayteam, all_teams);       
        
        if(input[i].home_goals>input[i].away_goals){        /*If hometeam wins*/
            all_teams[home].homewin++;
            all_teams[away].awayloss++;                      
        }
        else if(input[i].home_goals==input[i].away_goals){  /*If draw*/
            all_teams[home].draws++;
            all_teams[away].draws++;
        }
        else if(input[i].home_goals<input[i].away_goals){   /*If awayteam wins*/
            all_teams[away].awaywin++;
            all_teams[home].homeloss++;
        }
    }    
    printf("Opgave 3:\n");    
    for(i=0; i<=NUMBER_OF_TEAMS; i++){
        if(all_teams[i].homewin<all_teams[i].awaywin){
            printf("%s only won %d at home but won %d away\n", all_teams[i].name, all_teams[i].homewin, all_teams[i].awaywin); 
        }
    }
}

void opgave_4(match_t *input, team_x *all_teams){
    int i;
    int home;
    int spectators_season;
    int boring_team = 0;
    for(i=0; i<=MAX_MATCHES; i++){                        /*Counting all the spectators for all matches*/
        home = team_id(input[i].hometeam, all_teams);
        all_teams[home].spectators = input[i].num_spec+all_teams[home].spectators;  /*Adding the amount of spectators to hometeam current amount*/
    }
    printf("Opgave 4:\n");
    spectators_season = all_teams[10].spectators;         /*all_teams[10] equals to FCK - the biggest team in Denmark.
                                                         To make sure, spectators_season was lower than [i]spectators*/
    for(i=0; i<=NUMBER_OF_TEAMS; i++){
      if(all_teams[i].spectators<spectators_season){
        spectators_season=all_teams[i].spectators;       
        boring_team=i;                                  /*used to save the teams number*/
      }
    }  
    printf("%s was the team who had fewest spectators throughout the season\nwith only %d spectators going to there matches.\n", all_teams[boring_team].name, spectators_season);
  
}

void opgave_5(match_t *input){                        
    int i;
    char time_buffer[10];                                 /*Used to making time to char*/
    char *k1 = "19.05";
    char *k2 = "18.05";

    printf("Opgave 5:\n");
    qsort(input, MAX_MATCHES, sizeof(input[0]), match_comp);  /*Sorting all matches by total score*/
  
    for(i=0; i<=MAX_MATCHES; i++){
        sprintf(time_buffer, "%f", input[i].time);                /*Making input[i].time to char*/
        if(strcmp(input[i].weekday, "Fre")==0){                 /*Finding matches only on fridays*/
            if(strcmp(time_buffer, k1) <= 0&&strcmp(time_buffer, k2)>=0){ /*Finding matches in the timespace*/
                printf("%s %d/%d \t %.2lf \t %s-%s \t %d goals\n",  input[i].weekday, input[i].day, input[i].month, 
                                                                                          input[i].time, input[i].hometeam, input[i].awayteam, 
                                                                                          (input[i].home_goals+input[i].away_goals));
           
            }
        }
    }
}
 
int match_comp(const void *A, const void *B){
    match_t *a = (match_t *)A;                                /*Casting input to a match array pointer*/
    match_t *b = (match_t *)B;
    
    return((b -> away_goals + b -> home_goals) - (a -> home_goals + a -> away_goals));
}

void opgave_6(match_t *input, team_x *all_teams){
    int i;
    int home=0;
    int away=0;
    
    for(i=0; i<=MAX_MATCHES; i++){
        home = team_id(input[i].hometeam, all_teams);
        away = team_id(input[i].awayteam, all_teams);
        
        all_teams[home].games_played++;                 
        all_teams[away].games_played++;                          /*Match +1 everytime a game is played*/
        
        all_teams[home].goals_scored  += input[i].home_goals;    /*Adding goals to the table - for and against*/
        all_teams[home].goals_conceded+= input[i].away_goals;
        all_teams[away].goals_scored  += input[i].away_goals;
        all_teams[away].goals_conceded+= input[i].home_goals;
    }
    
    for(i=0; i<=NUMBER_OF_TEAMS; i++){
        all_teams[i].total_points = ((all_teams[i].homewin+all_teams[i].awaywin)*WIN)+(all_teams[i].draws); /*Counting total points for team*/
        all_teams[i].goal_diff = all_teams[i].goals_scored - all_teams[i].goals_conceded;                   /*Counting goal difference for team*/
    }
    qsort(all_teams, 12 , sizeof all_teams[0], comp);                                                  /*Sorting teams by points*/
    
    printf("Opgave 6:\n");
    printf("Hold\tK\tV\tU\tT\t+/-\tMf\tMi\tP\n");
    
    for(i=0; i<=NUMBER_OF_TEAMS; i++){
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", all_teams[i].name, all_teams[i].games_played, (all_teams[i].homewin+all_teams[i].awaywin), all_teams[i].draws, 
                                                        (all_teams[i].homeloss+all_teams[i].awayloss), all_teams[i].goal_diff, all_teams[i].goals_scored, all_teams[i].goals_conceded, all_teams[i].total_points);
    }
}

int comp(const void *A, const void *B){
    team_x *a = (team_x *)A;
    team_x *b = (team_x *)B;
    
    return(b->total_points - a->total_points);
}