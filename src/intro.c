#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "functions.h"
#include "varsandincs.h"




void white_snow(){
    char intro[4000];
    int colors[2]= {0,255};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int random,counter = 0;
    int c,i;
    for(i=0;i<4000;i++){
        if(i%100 == 0 && i == 0){
            intro[i] = '\n';
            continue;
        }
        intro[i] = ' ';
    }
    srand(time(NULL));
    while(1){
        if(kbhit()){
            break;
        }
        random = rand() % 2;
        SetConsoleTextAttribute(hConsole,colors[random]);
        printf("%c",intro[counter]);
        if(counter == 3999){
            counter = 0;
        }
        counter++;

    }
}

void print_logo(){

  int i,temp;
  int color = 1;
  char c;


    Mix_Music *noise = Mix_LoadMUS("Music/TV-static-sound-effects.mp3");
    Mix_Music *background = Mix_LoadMUS(music_address);
    Mix_Chunk *effect = Mix_LoadWAV(effect_address);
  hidecursor();
    Mix_PlayMusic(noise, -1 );
  white_snow();
  c = getchar();
    Mix_FadeOutMusic(200);
    Mix_FadeInMusic(background, -1 , 100);


    clear();
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
  char logo[] = " OO\n                     O  O\n                    O    O\n                   O      O\n                  O        O\n     O           O          O           O\n     OO         O            O         OO\n     O O       OOOOOOOOOOOOOOOO       O O\n     O  O     O                O     O  O\n     O   O   O                  O   O   O\n     O    O O                    O O    O\n     O     O                      O     O\n     O    O O                    O O    O\n     O   O   O                  O   O   O\n     O  O     O                O     O  O\n     O O       OOOOOOOOOOOOOOOO       O O\n     OO         O            O         OO\n     O           O          O           O\n                  O        O\n                   O      O\n                    O    O\n                     O  O\n                      OO";

  for(i=0;i<15;i++){
    SetPosition(21,2);
    if(i==14){
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
      printf("%s",logo);
      Sleep(200);
    }
    else{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),i);
    printf("%s",logo);
    Sleep(200);}
  }

  int x = 12;
  SetPosition(x,13);
  char teatro[] = "   T  E  A  T  R  O";
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
  color = 8;
  for(i=0;i<19;i++,x++){
    if('A'<= teatro[i] && teatro[i] <= 'Z'){
      color++;
      //if(i==18){
        //color+=5;
      //}
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    SetPosition(x,13);
    printf("%c",teatro[i]);
    Sleep(250);
  }
  Sleep(750);

  SetPosition(14,15);
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
  printf(" Theater of Games");
  Sleep(3500);
  //int c = getchar();

  clear();
  SetPosition(4,2);
  setconsoleThemeDefault();
  printf("<< T E A T R O >>\n\n    'Theater of GAMES'\n\n Mini Game-Console which is coded in 'C-Programming-language', compiled by 'GCC'.\n All the licenses go to 'A & A'.\n Created By 'A & A' Entertainment-Gaming Team\n Background music : Lines of Code By Trevor Lentz \n Produced & Manufactured in 'IR-SHIRAZ-SHIRAZ UNIVERSITY'");
  Sleep(10000);
}
