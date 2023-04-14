#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "functions.h"
#include "varsandincs.h"
#define MAX 100000





int * put_raindb(int number){
  int random,i,position;
  int *positions = (int *)malloc(sizeof(int)*MAX);
  for(i=0;i<number;i++){
    // srand(time(NULL));
    random = rand() % (map_width*3);
    if(map[random] == ' '){
      map[random] = deathblock;
      positions[i] = random;
    }
    else{
      i--;
    }
  }
  return positions;
}

void put_rpoints(char shape,int number){
  int i,random;


  if ( number == 0 ){
    return ;

  }
  
  for(i=0;i<number;i++){
    // srand(time(NULL));
    random = rand() % ((map_width+1)*map_height);
    // printf("random : %d",random);
    if(map[random] != ' '){
      // printf("\nmap random: %c",map[random]);
      i--;
      continue;
    }
    else if(map[random] == ' '){

      map[random] = shape;
    }
  }
}

void print_mapp(){
  clear();
  int width,height,i,x,y;
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  width = map_width;
  height = map_height;
  //SetConsoleTextAttribute(hConsole,background_color);

  x=4;
  y=2;

  for(i=0;i<height*(width+1);i++){
    //SetPosition(x,y);
    if(map[i] == ' '){
        SetConsoleTextAttribute(hConsole,background_color);
        //printf("%c",map[i]);
        fputc(map[i],stdout);

    }
    else if(map[i] == wall){
        SetConsoleTextAttribute(hConsole,wall_color);
        //printf("%c",map[i]);
        fputc(map[i],stdout);

    }
    else if(map[i] == solidblock){

        SetConsoleTextAttribute(hConsole,solidblock_color);
        //printf("%c",map[i]);//
        fputc(map[i],stdout);


    }
    else if(map[i] == moveblock){

        SetConsoleTextAttribute(hConsole,moveblock_color);
        //printf("%c",map[i]);
        fputc(map[i],stdout);

    }
    else if(map[i] == deathblock){

        SetConsoleTextAttribute(hConsole,death_blk_color);
        //printf("%c",map[i]);
        fputc(map[i],stdout);

    }
    else if(map[i] == character){
        SetConsoleTextAttribute(hConsole,character_color);
        //printf("%c",map[i]);
        fputc(map[i],stdout);

    }
    else if(map[i] == rpoint){
        SetConsoleTextAttribute(hConsole,rpoint_color);
        //printf("%c",map[i]);
        fputc(map[i],stdout);

    }
    else if(map[i] == target){
        SetConsoleTextAttribute(hConsole,target_color);
        //printf("%c",map[i]);
        fputc(map[i],stdout);

    }
    else if(map[i] == object){
        SetConsoleTextAttribute(hConsole,object_color);
        //printf("%c",map[i]);
        fputc(map[i],stdout);

    }
    else if(map[i] == opp){
        SetConsoleTextAttribute(hConsole,opp_color);
        //printf("%c",map[i]);
        fputc(map[i],stdout);

    }

    else if(map[i] == bullet){
        SetConsoleTextAttribute(hConsole,bullet_color);
        //printf("%c",map[i]);
        fputc(map[i],stdout);

    }
    else if(map[i] == '\n'){
        SetConsoleTextAttribute(hConsole,background_color);
        //printf("%c",map[i]);
        fputc(map[i],stdout);
        x = 3;
        y++;

    }
    else if(map[i] == '\0'){
      break;
    }
    else{
      SetConsoleTextAttribute(hConsole,wall_color);
      //printf("%c",map[i]);
      fputc(map[i],stdout);

    }

    x++;
  }

}


void replay ( char ** frames, int speed){

    int j = 0;

    clear();

    for(j = 0 ; j < 6 ; ++j){

    clear();
    int width,height,i,x,y;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    width = map_width;
    height = map_height;
    //SetConsoleTextAttribute(hConsole,background_color);

    x=4;
    y=2;

    for(i=0;i<height*(width+1);i++){
        //SetPosition(x,y);
        if(frames[j][i] == ' '){
            SetConsoleTextAttribute(hConsole,background_color);
            //printf("%c",map[i]);
            fputc(frames[j][i],stdout);

        }
        else if(frames[j][i] == wall){
            SetConsoleTextAttribute(hConsole,wall_color);
            //printf("%c",map[i]);
            fputc(frames[j][i],stdout);

        }
        else if(frames[j][i] == solidblock){

            SetConsoleTextAttribute(hConsole,solidblock_color);
            //printf("%c",map[i]);//
            fputc(frames[j][i],stdout);


        }
        else if(frames[j][i] == moveblock){

            SetConsoleTextAttribute(hConsole,moveblock_color);
            //printf("%c",map[i]);
            fputc(frames[j][i],stdout);

        }
        else if(frames[j][i] == deathblock){

            SetConsoleTextAttribute(hConsole,death_blk_color);
            //printf("%c",map[i]);
            fputc(frames[j][i],stdout);

        }
        else if(frames[j][i] == character){
            SetConsoleTextAttribute(hConsole,character_color);
            //printf("%c",map[i]);
            fputc(frames[j][i],stdout);

        }
        else if(frames[j][i] == rpoint){
            SetConsoleTextAttribute(hConsole,rpoint_color);
            //printf("%c",map[i]);
            fputc(frames[j][i],stdout);

        }
        else if(frames[j][i] == target){
            SetConsoleTextAttribute(hConsole,target_color);
            //printf("%c",map[i]);
            fputc(frames[j][i],stdout);

        }
        else if(map[i] == object){
            SetConsoleTextAttribute(hConsole,object_color);
            //printf("%c",map[i]);
            fputc(map[i],stdout);

        }
        else if(frames[j][i] == opp){
            SetConsoleTextAttribute(hConsole,opp_color);
            //printf("%c",map[i]);
            fputc(frames[j][i],stdout);

        }

        else if(frames[j][i] == bullet){
            SetConsoleTextAttribute(hConsole,bullet_color);
            //printf("%c",map[i]);
            fputc(frames[j][i],stdout);

        }
        else if(frames[j][i] == '\n'){
            SetConsoleTextAttribute(hConsole,background_color);
            //printf("%c",map[i]);
            fputc(frames[j][i],stdout);
            x = 3;
            y++;

        }
        else if(frames[j][i] == '\0'){
            break;
        }
        else{
            SetConsoleTextAttribute(hConsole,wall_color);
            //printf("%c",map[i]);
            fputc(frames[j][i],stdout);

        }

        x++;
    }


    Sleep(1000/speed);
    }

}
