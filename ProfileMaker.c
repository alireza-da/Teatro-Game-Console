#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "functions.h"
#include "varsandincs.h"


struct Profile{
  char *username;
  char *password;
  char *loginstate;
  char *max_score;
};

struct Profile* registering(char *username,char *password){
  struct Profile* newprofile = (struct Profile*)malloc(sizeof(struct Profile));
  newprofile->username = username;
  newprofile->password = encode(password);
  newprofile->max_score = "0";
  newprofile->loginstate = "0";
  return newprofile;
}

char *encode(char *text){// a function to encode a text 'used for encoding password
  char *temp,*rev_temp;
  int len;
  //printf("%d\n",len);
  int i;
  rev_temp = strrev(text);
  len = strlen(rev_temp);

  for(i=0;i<len;i++){
    temp[i] = rev_temp[i] + 5;
  }
  temp[i] = '\0';

  return temp;
}

char *decode(char *text){// a function to decode a text 'used for decoding password
  char *temp,*rev_temp;
  int len = strlen(text);
  int i;
  for(i=0;i<len;i++){
    temp[i] = text[i] - 5;
  }
  rev_temp = strrev(temp);
  return rev_temp;
}
////////////////////////////////////////////////////////////////////////////////
//writing info part
void writeProfiles(struct Profile* profile){
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  FILE *newprofile;

  char dir[60] = "Profiles/";
  char username[30];
  strcpy(username,profile->username);
  strcat(dir,username);
  strcat(dir,".txt");

  //printf("dir name : %s",dir);

  newprofile = fopen(dir,"w");

  fputs("Username:",newprofile);
  fputs(profile->username,newprofile);fputc('\n',newprofile);

  fputs("Password:",newprofile);
  fputs(profile->password,newprofile);fputc('\n',newprofile);

  fputs("Highest Score:",newprofile);
  fputs(profile->max_score,newprofile);fputc('\n',newprofile);

  //fputs("Last Online:",newprofile);
  fprintf(newprofile,"Last Online:%d-%d-%d %d:%d:%d\n",tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  fputs("Login State:",newprofile);
  fputs(profile->loginstate,newprofile);fputc('\n',newprofile);

  //fclose(newprofile);

  //newprofile = fopen(dir,"w");


  fclose(newprofile);
}
////////////////////////////////////////////////////////////////////////////////
//making a profile
void profile_maker(){
  char *username;
  char *password;

  printf("Username:");
  scanf("%s",username);
  printf("Password:");
  scanf("%s",password);

  struct Profile* newprofile = registering(username,password);
  writeProfiles(newprofile);
}
////////////////////////////////////////////////////////////////////////////////
