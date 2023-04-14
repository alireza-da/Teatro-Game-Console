#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "functions.h"
#include "varsandincs.h"
#define INSIDE 1
#define OUTSIDE 0
#define YEAR 1
#define MONTH 2
#define DAY 3
#define HOUR 4
#define MINUTE 5
#define SECOND 6

struct Profile{
  char *username;
  char *password;
  char *loginstate;
  char *max_score;
};

void show_profile(struct Profile* profile){
    FILE *fp;
    int year = 0,month = 0 ,day = 0 ,hour = 0 ,min = 0 ,sec = 0 , i, state;
    char c;
    char temp[30];
    char dir[60];
    // struct tm temp;

    strcpy(dir,"Profiles/");
    hidecursor();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);
    SetPosition(4, 2);
    printf("Username :");
    if( profile -> username == NULL ){
      setconsoleThemeDefault();
      printf("   Not Found");
    }
    else{
      setconsoleThemeDefault();
      printf("  %s",profile -> username);
    }

    SetPosition(4, 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);
    printf("Highest Score :");
    if( profile -> max_score == NULL ){
      setconsoleThemeDefault();
      printf("   Not Found");
      return ;
    }
    setconsoleThemeDefault();
    printf("  %s",profile ->max_score);
    strcat(dir,profile->username);
    strcat(dir,".txt");
    fp = fopen(dir,"r");
    if(fp == NULL){
      return;
    }
    if(fp != NULL){
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);
      SetPosition(4,6);
       // fscanf(fp,"Last Online:%d-%d-%d %d:%d:%d",&year,&month,&day,&hour,&min,&sec);
       // printf("%d",fscanf(fp,"Last Online:%d-%d-%d %d:%d:%d",&year,&month,&day,&hour,&min,&sec));
       // Sleep(1000);
      i = 0;
      while((c=fgetc(fp))!=EOF){
        temp[i] = c;
        if ( temp[i] == ':'){
          ++i;
          temp[i] = '\0';
          if ( strcmp(temp,"Last Online:") == 0){
            state = YEAR;
            while((c=fgetc(fp))!='\n'){
              if ( state == YEAR && c >='0' && c<='9' ){
                year = year * 10 + ( c - '0' );
              }
              else if ( c == '-' && state == YEAR){
                state = MONTH;
              }
              else if ( state == MONTH && c >='0' && c<='9'){
                month = month * 10 + ( c - '0' );
              }
              else if ( c == '-' && state == MONTH){
                state = DAY;
              }
              else if ( state == DAY && c >='0' && c<='9'){
                day = day * 10 + ( c - '0' );
              }
              else if ( c == ' ' && state == DAY ){
                state = HOUR;
              }
              else if ( state == HOUR && c >='0' && c<='9'){
                hour = hour * 10 + ( c - '0' );
              }
              else if ( c== ':' && state == HOUR ){
                state = MINUTE;
              }
              else if ( state == MINUTE && c >='0' && c<='9'){
                min = min * 10 + ( c - '0' );
              }
              else if ( c== ':' && state == MINUTE ){
                state = SECOND;
              }
              else if ( state == SECOND && c >='0' && c<='9'){
                sec = sec * 10 + ( c - '0' );
              }

            }

            }

            else{
              i = 0;
              while((c=fgetc(fp))!='\n'){
                ;
              }
            }
          }
          else{
            ++i;
          }
        }
      }
      printf("Last Online :");
      setconsoleThemeDefault();
      printf("  %d-%d-%d %d:%d:%d",year,month,day,hour,min,sec);
      fclose(fp);


}

struct Profile* search_public(char *username){

  FILE *profile;
  char dir[60] = "Profiles/";
  char usrname[30];
  struct Profile *temp_profile = (struct Profile*)malloc(sizeof(struct Profile));
  temp_profile->username = NULL;
  temp_profile->max_score = NULL;
  temp_profile->loginstate = NULL;
  temp_profile->password = NULL;
  char *temp_user = ( char * ) malloc(sizeof(char) * 30);
  char *temp_maxscr = ( char * )malloc(sizeof(char) * 30);
  char *temp_login = (char *)malloc(sizeof(char) * 30);
  int c, state, i;

  strcpy(usrname,username);
  strcat(dir,usrname);
  strcat(dir,".txt");

  profile = fopen(dir,"r");
  if(profile == NULL){
    return temp_profile;
  }
  if(profile != NULL){

      // getting the username
      state = OUTSIDE;
      i = 0;
      while((c=fgetc(profile))!='\n'){

          if ( c == ':' ){
              if ( state == OUTSIDE ){
                  state = INSIDE;
              }
              else {
                  temp_user[i] = c;
                  ++i;
              }
          }

          else if ( state == INSIDE ) {

              temp_user[i] = c;
              ++i;

          }

          else{
              continue;
          }
      }

      temp_user[i] = '\0';

      // skip a line
      while((c=fgetc(profile))!='\n'){
          ;
      }

      //getting the highscore
      state = OUTSIDE;
      i = 0;
      while((c=fgetc(profile))!='\n'){

          if ( c == ':' ){
              if ( state == OUTSIDE ){
                  state = INSIDE;
              }
              else {
                  temp_maxscr[i] = c;
                  ++i;
              }
          }

          else if ( state == INSIDE ) {

              temp_maxscr[i] = c;
              ++i;

          }

          else{
              continue;
          }
      }

      temp_maxscr[i] = '\0';

      // getting the login state
      state = OUTSIDE;
      i = 0;
      while((c=fgetc(profile))!='\n'){

          if ( c == ':' ){
              if ( state == OUTSIDE ){
                  state = INSIDE;
              }
              else {
                  temp_login[i] = c;
                  ++i;
              }
          }

          else if ( state == INSIDE ) {

              temp_login[i] = c;
              ++i;

          }

          else{
              continue;
          }
      }

      temp_login[i] = '\0';


    temp_profile->username = temp_user;
    temp_profile->loginstate = temp_login;
    temp_profile->max_score = temp_maxscr;


    fclose(profile);

    return temp_profile;
  }
}

void update_highscore(char *username,int score){
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  char dir[60] = "Profiles/";
  char usrname[30],password[30],loginstate[2],highest_score[7];
  int high_scr;

  strcpy(usrname,username);
  strcat(dir,usrname);
  strcat(dir,".txt");

  FILE *read_datas;
  read_datas = fopen(dir,"r");

  fscanf(read_datas,"Username:%s\n",&usrname);
  fscanf(read_datas,"Password:%s\n",&password);
  fscanf(read_datas,"Highest Score:%d\n",&high_scr);
  fscanf(read_datas,"Login State:%s\n",&loginstate);

  fclose(read_datas);

  if(score > high_scr){
    FILE *edit;
    edit = fopen(dir,"w");
    fprintf(edit,"Username:%s\n",usrname);
    fprintf(edit,"Password:%s\n",password);
    fprintf(edit,"Highest Score:%d\n",score);
    fprintf(edit,"Last Online:%d-%d-%d %d:%d:%d\n",tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fprintf(edit,"Login State:%s\n",loginstate);
    fclose(edit);

  }
}

void update_loginstate(char *username,int login_state){
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  char dir[60] = "Profiles/";
  char usrname[30],password[30],loginstate[2];
  char high_scr[7];

  strcpy(usrname,username);
  strcat(dir,usrname);
  strcat(dir,".txt");

  FILE *read_datas;
  read_datas = fopen(dir,"r");

  fscanf(read_datas,"Username:%s\n",&usrname);
  fscanf(read_datas,"Password:%s\n",&password);
  fscanf(read_datas,"Highest Score:%s\n",&high_scr);
  fscanf(read_datas,"Login State:%s\n",&loginstate);

  fclose(read_datas);

  FILE *edit;

  edit = fopen(dir,"w");

  fputs("Username:",edit);
  fputs(usrname,edit);fputc('\n',edit);
  fputs("Password:",edit);
  fputs(password,edit);fputc('\n',edit);
  fputs("Highest Score:",edit);
  fputs(high_scr,edit);fputc('\n',edit);
  fprintf(edit,"Last Online:%d-%d-%d %d:%d:%d\n",tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  switch (login_state) {

    case 1:
      strcpy(loginstate,"1");
      fputs("Login State:",edit);
      fputs(loginstate,edit);fputc('\n',edit);
      break;

    case 0:
      strcpy(loginstate,"0");
      fputs("Login State:",edit);
      fputs(loginstate,edit);fputc('\n',edit);
      break;
  }


  fclose(edit);
}


// PRINT FUNCTION FOR PRINTING PROFILE IN MENU
void printf_curr_prf1 ( void ) {

    int i;
    i = 0;

    // If someone is logged in
    if ( global_loginstate == 1 ){

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
        SetPosition(43, 4);
        printf("H e l l o , \n");
        SetPosition(43,6);
        while ( User[i] != '\0' ){
            putchar(User[i]);
            putchar(' ');
            ++i;
        }
        SetPosition(43,8);
        printf(";)");

        setconsoleThemeDefault();

    }

    // If no one is logged in
    else{
        return ;
    }
}

// FUNCTION USED FOR PRINTING PROFILE IN LOGIN_UI
void printf_curr_prf2 ( void ) {

    int i;
    i = 0;

    // If someone is logged in
    if ( global_loginstate == 1 ){

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
        SetPosition(28, 4);
        printf("You are currently\n");
        SetPosition(28, 6);
        printf("Signed in as \n");
        SetPosition(28, 8);
        printf("%s",User);
        setconsoleThemeDefault();

    }

        // If no one is logged in
    else{
        return ;
    }
}


// FUNCTION USED FOR PRINTING PROFILE IN "PROFILES"
void printf_curr_prf3 ( void ){

    int i;
    i = 0;

    // If someone is logged in
    if ( global_loginstate == 1 ){

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
        SetPosition(50 , 3);
        printf("You are currently\n");
        SetPosition(50 , 5);
        printf("Signed in as \n");
        SetPosition(50 , 7);
        printf("%s",User);
        setconsoleThemeDefault();

    }

        // If no one is logged in
    else{
        return ;
    }


}
