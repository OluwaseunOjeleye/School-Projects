#include <stdio.h>
#include <stdlib.h>

struct team{
    char name[12];
    char alias;
    int points;
    int total_matches;
    int wins;
    int draws;
    int losses;
    int GoalsScored;
    int GoalsAllowed;
    int GoalDifference;
};
typedef struct team Team;

Team *Teams;
int **playedMatch;
int n, win, draw, lose;

void PrintTournamentInfo(){
    printf("************************************TOURNAMENT************************************\n");
    printf("   Team\t\tAlias\tPoints\tTM\tWins\tDraws\tLosses\tGS\tGA\tGD\n");
    for(int i=0; i<n; i++){
        printf("%d. %s\t%c\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i+1,Teams[i].name, Teams[i].alias, Teams[i].points, Teams[i].total_matches, Teams[i].wins, Teams[i].draws, Teams[i].losses, Teams[i].GoalsScored, Teams[i].GoalsAllowed, Teams[i].GoalDifference );
    }
}

void PrintTournamentInfoFile(char filename[]){
    FILE *fp;
    fp = fopen(filename, "w");
    fprintf(fp,"************************************TOURNAMENT************************************\n");
    fprintf(fp,"   Team\tAlias\tPoints\tTM\tWins\tDraws\tLosses\tGS\tGA\tGD\n");
    for(int i=0; i<n; i++){
        fprintf(fp, "%d. %s\t%c\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i+1,Teams[i].name, Teams[i].alias, Teams[i].points, Teams[i].total_matches, Teams[i].wins, Teams[i].draws, Teams[i].losses, Teams[i].GoalsScored, Teams[i].GoalsAllowed, Teams[i].GoalDifference);
    }
    fclose(fp);
}

void getInfo(char filename[],int *n, int *w,int *d,int *l){
    //File opening and adding
    FILE *fp;
    fp = fopen(filename, "r");    //file name is Info
    if (fp == NULL){
        printf("Error: Info file doesnot exist");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d",&*n);
    fscanf(fp, "%d",&*w);
    fscanf(fp, "%d",&*d);
    fscanf(fp, "%d",&*l);
    printf("Operation: Info copied\n");
}

void getTeamsName(char filename[]){
    //File opening and adding
    FILE *fp;
    fp = fopen(filename, "r");    //file name is spor
    if (fp == NULL){
        printf("Error: Team Name file doesnot exist");
        exit(EXIT_FAILURE);
    }

    char names[n][12], buffer[100]; int i=0;
    memset(names, 0, n*12*sizeof(char));

    while (fgets(buffer, 50, fp) != NULL )
    {
        buffer[strlen(buffer)-1] = '\0';
        strncpy (names[i], buffer,11);
        //printf("%s\n", names[i]);
        i++;
        if(i>=n){
            break;
        }
    }
    fclose(fp);
    // End of file operation

    //initializing the structures
    Teams=malloc(sizeof(Team) * n);;
    for(int i=0; i<n; i++){
        Teams[i]=(Team){ .name="No Name", .alias = 'z', .points = 0, .total_matches=0, .wins=0, .draws=0, .losses=0, .GoalsScored=0, .GoalsAllowed=0, .GoalDifference=0 };
    }

    char alias='A';
    for(int i=0; i<n; i++){
        strcpy(Teams[i].name,names[i]);
        Teams[i].alias=alias++;
    }
    printf("Operation: Team Names copied\n");
}


void updateInfo(int index1, int index2, int s1, int s2){
    if((playedMatch[index1][index2])==1){
        printf("->%c vs %c Match has been played\n", Teams[index1].alias, Teams[index2].alias);
        return;
    }
    if(s1>s2){
        Teams[index1].points+=win;
        Teams[index1].wins+=1;
        Teams[index1].total_matches+=1;
        Teams[index1].GoalsScored+=s1;
        Teams[index1].GoalsAllowed+=s2;
        Teams[index1].GoalDifference=Teams[index1].GoalsScored-Teams[index1].GoalsAllowed;


        Teams[index2].points+=lose;
        Teams[index2].losses+=1;
        Teams[index2].total_matches+=1;
        Teams[index2].GoalsScored+=s2;
        Teams[index2].GoalsAllowed+=s1;
        Teams[index2].GoalDifference=Teams[index2].GoalsScored-Teams[index2].GoalsAllowed;
    }
    else if(s1<s2){
        Teams[index2].points+=win;
        Teams[index2].wins+=1;
        Teams[index2].total_matches+=1;
        Teams[index2].GoalsScored+=s2;
        Teams[index2].GoalsAllowed+=s1;
        Teams[index2].GoalDifference=Teams[index2].GoalsScored-Teams[index2].GoalsAllowed;


        Teams[index1].points+=lose;
        Teams[index1].losses+=1;
        Teams[index1].total_matches+=1;
        Teams[index1].GoalsScored+=s1;
        Teams[index1].GoalsAllowed+=s2;
        Teams[index1].GoalDifference=Teams[index1].GoalsScored-Teams[index1].GoalsAllowed;
    }
    else{
        Teams[index1].points+=draw;
        Teams[index1].draws+=1;
        Teams[index1].total_matches+=1;
        Teams[index1].GoalsScored+=s1;
        Teams[index1].GoalsAllowed+=s2;
        Teams[index1].GoalDifference=Teams[index1].GoalsScored-Teams[index1].GoalsAllowed;


        Teams[index2].points+=draw;
        Teams[index2].draws+=1;
        Teams[index2].total_matches+=1;
        Teams[index2].GoalsScored+=s2;
        Teams[index2].GoalsAllowed+=s1;
        Teams[index2].GoalDifference=Teams[index2].GoalsScored-Teams[index2].GoalsAllowed;
    }
    playedMatch[index1][index2]=1;
    playedMatch[index2][index1]=1;

    printf("->%c %d vs %c %d added\n", Teams[index1].alias, s1 , Teams[index2].alias, s2);
}


void getScoresFile(char filename[]){
    //File opening and adding
    FILE *fp;
    fp = fopen(filename, "r");    //file name is score
    if (fp == NULL){
        printf("Error: Scores file doesnot exist");
        exit(EXIT_FAILURE);
    }

    char ch; int lines=0;
    while(!feof(fp)){
        ch = fgetc(fp);
        if(ch == '\n'){
            lines++;
        }
    }

    fp = fopen("score", "r");    //file name is score

    char a1, a2; int s1, s2;
    for(int i=0; i<lines-1; i++){
        fscanf(fp, "%c %d %c %d\n", &a1, &s1, &a2, &s2);
        int index1=a1-'A', index2=a2-'A';
        updateInfo(index1, index2, s1, s2);
    }
    fclose(fp);
    printf("Operation: Scores copied\n");
}

void getScoresKeyboard(){
    char a1, a2, input;
    int s1, s2;
    while(1){
        printf("Input Score info in A 2 B 3 format: ");

        char line[20];
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%c %d %c %d", &a1, &s1, &a2, &s2);

        int index1=a1-'A', index2=a2-'A';
        updateInfo(index1, index2, s1, s2);

        printf("Do you want to input another score? Y/N:");
        char line2[20];
        fgets(line2, sizeof(line2), stdin);
        sscanf(line2, "%c", &input);
        if(input=='y'){
            continue;
        }
        else if(input=='Y'){
            continue;
        }
        else{
            break;
        }

    }
}

void clearTournamentTable(){
    //clearing adjacency matrix
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            playedMatch[i][j]=0;
        }
    }

    for(int i=0; i<n; i++){
        Teams[i]=(Team){ .name="No Name", .alias = 'z', .points = 0, .total_matches=0, .wins=0, .draws=0, .losses=0, .GoalsScored=0, .GoalsAllowed=0, .GoalDifference=0 };
    }
    printf("Operation: League Table Cleared\n");
}

void GUI(){
    printf("*********Football Tournament************\n");
    printf("->1. Print League Table on Screen\n");
    printf("->2. Print League Table into file\n");
    printf("->3. Add Match results from file\n");
    printf("->4. Add Match results Through Keyboard\n");
    printf("->5. Clear League Table\n");
    printf("->99. Exit\n");
    printf("*******************************************\n");
    int choice;
    printf("-> ");
    char line[20];
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &choice);

    if(choice==1){
        PrintTournamentInfo();
    }
    else if(choice==2){
        PrintTournamentInfoFile("output");
    }
    else if(choice==3){
        getScoresFile("score");
    }
    else if(choice==4){
        getScoresKeyboard();
    }
    else if(choice==5){
        clearTournamentTable();
        getInfo("info",&n, &win, &draw, &lose);
        getTeamsName("spor");
    }
    else if(choice==99){
        exit(0);
    }
    else{
        GUI();
    }
    
    GUI();

}

int main(){
    getInfo("info",&n, &win, &draw, &lose);

    playedMatch=malloc(n*sizeof(int*));
    int *temp=malloc(n*n*sizeof(int));
    for(int i=0; i<n; i++){
        playedMatch[i]=temp+(i*n);
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            playedMatch[i][j]=0;
        }
    }

    getTeamsName("spor");
    GUI();
    
    /*
    getScoresFile("score");
    getScoresKeyboard();

    //PrintTournamentInfoFile("output");
    PrintTournamentInfo();
    //clearTournamentTable();
    //PrintTournamentInfo();
    */


   for (int i=0; i<n; i++){
        int* c= playedMatch[i];
        free(c);
    }
    free(Teams);
}
