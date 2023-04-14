#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "functions.h"
#include "varsandincs.h"

#define MAX 10000

int character_position;
char move = 0;
char *bot_moves;
int opp_position;
int win1_state;
int win2_state;
int score1;
int score2;
int bullet_position;
int *gravity_object_posS;
int bullet_counter = 0;
//int bullet_state = 0;
int hp1 = 100;


// An array of bullets existing in the map
struct Bullet *Ammo[100];



void input_update( char c1, int *raindbs_positions){
  int c2 = 0,put = 0,put_ai = 0,move_ai = 0,i,random;


    if ( c1 == '\0' ){
      put = 0;
      for ( i = 0 ; i < bullet_counter ; i++){
          update_bullet(Ammo[i]);
      }
      update_raindb(raindbs_positions,raindb);
      gravity(gravity_state,gravity_side,gravity_object_posS);
      return;
    }

//    print_mapp();
    //printf("%s\n",map);

      if(c1 == move_keys[0]){
          move = c1;
      }
      else if(c1 == move_keys[1]){
          move = c1;
      }
      else if(c1 == move_keys[2]){
          move = c1;
      }
      else if(c1 == move_keys[3]){
          move = c1;
      }
      else if(c1 == put_key){
        // printf("put here");
        // Sleep(1000);
          put = 1;
      }

      else if(c1 == attack_key){
        // printf("POS:%dMOVE:%c\n",character_position,move );
          struct Bullet *tmp = (struct Bullet *)malloc(sizeof(struct Bullet));
          tmp = put_bullet(character_position,move);
          // there was something in the way of the bullet
          if ( tmp == NULL ){
            update_character(move,put);
            update_raindb(raindbs_positions,raindb);
            return;
          }
          Ammo[bullet_counter] = tmp;
          // printf("bullet position : %d char pos : %d ",tmp->previous_pos, character_position);
          // Sleep(2000);
          bullet_counter++;
          //bullet_state = 1;
      }

    //c2 = ai();
    update_character(move,put);
    put = 0;
    for ( i = 0 ; i < bullet_counter ; i++){
        update_bullet(Ammo[i]);
    }
    update_raindb(raindbs_positions,raindb);
    gravity(gravity_state,gravity_side,gravity_object_posS);
    //update_ai()
}




void update_character(char move,int put){
    Mix_Chunk *effect = Mix_LoadWAV("Music/Explosion.wav");
    Mix_Chunk *hit_effect = Mix_LoadWAV("Music/hitmarker_2.wav");

  int height = map_width+1, width = map_height,i,random;
  if(move == move_keys[0]){//up
      if(map[character_position - height] == ' ') {
          map[character_position - height] = character;
          map[character_position] = ' ';
          character_position = character_position - height;
      }
      else if(map[character_position - height] == rpoint){
        map[character_position - height] = character;
        map[character_position] = ' ';
        character_position = character_position - height;
        score1+=rpointScore;

        random = rand() % (height*width) ;
        while (map[random] != ' ') {

          random = rand() % (height*width) ;
        }
        map[random] = rpoint;
      }
      else if(map[character_position - height] == wall){
          map[character_position] = character;
      }
      else if(map[character_position - height] == solidblock){
          map[character_position] = character;
      }
      else if(map[character_position - height] == moveblock){
          if(map[character_position - height - height] == ' '){
            map[character_position - height] = character;
            map[character_position - height - height] = moveblock;

            map[character_position] = ' ';
            character_position = character_position - height;
          }
      }
      else if(map[character_position - height] == deathblock){
          Mix_PlayChannel(-1, effect , 0);
          hp1 = 0;;
      }
      else if(map[character_position - height] == object){
          if(map[character_position - height - height] == ' '){
            map[character_position - height] = character;
            map[character_position - height - height] = object;

            map[character_position] = ' ';
            character_position = character_position - height;
          }
          else if(map[character_position - height - height] == target){
            map[character_position - height] = character;
            map[character_position - height - height] = object;


            map[character_position] = ' ';
            character_position = character_position - height;
            win1_state = 3;
          }
      }
      else if(map[character_position - height] == opp){
          if(opp_target == character){
            win2_state = 7;
            // win2_state = 1;
          }
      }
      else if(map[character_position - height] == bullet){
          Mix_PlayChannel(-1, hit_effect , 0);
          map[character_position - height] = character;
          map[character_position] = ' ';
          character_position = character_position - height;
          hp1 = hp1 - 50;
          if(hp1 <= 0){
            hp1 = hp1 - 50;;
          }
      }
    }
    else if(move == move_keys[1]){//down
        if(map[character_position + height] == ' '){
            map[character_position + height] = character;
            map[character_position] = ' ';
            character_position += height;
        }
        else if(map[character_position + height] == rpoint){
          map[character_position + height] = character;
          map[character_position] = ' ';
          character_position = character_position + height;
          score1+=rpointScore;

          random = rand() % (height*width) ;
          while (map[random] != ' ') {

            random = rand() % (height*width) ;
          }
          map[random] = rpoint;
        }
        else if(map[character_position + height] == wall){
            map[character_position] = character;
        }
        else if(map[character_position + height] == solidblock){
            map[character_position] = character;
        }
        else if(map[character_position + height] == moveblock){
            if(map[character_position + height + height] == ' '){
              map[character_position + height] = character;
              map[character_position + height + height] = moveblock;

              map[character_position] = ' ';
              character_position += height;
            }
        }
        else if(map[character_position + height] == deathblock){
            Mix_PlayChannel(-1, effect , 0);
            hp1 = 0;;
        }
        else if(map[character_position + height] == object){
            if(map[character_position + height + height] == ' '){
              map[character_position + height] = character;
              map[character_position + height + height] = object;

              map[character_position] = ' ';
              character_position += height;
            }
            else if(map[character_position + height + height] == target){
              map[character_position + height] = character;
              map[character_position + height + height] = object;

              map[character_position] = ' ';
              character_position += height;
              win1_state = 3;
            }
        }
        else if(map[character_position + height] == opp){
            if(opp_target == character){
              win2_state = 7;
              // win2_state = 1;
            }
        }
        else if(map[character_position + height] == bullet){
            Mix_PlayChannel(-1, hit_effect , 0);
            map[character_position + height] = character;
            map[character_position] = ' ';
            character_position += height;
            hp1 = hp1 - 20;
            if(hp1 <= 0){
              hp1 = hp1 - 20;;
            }
        }
      }
      else if( move == move_keys[2]){//left
          if (map[character_position - 1] == ' '){
              map[character_position - 1] = character;
              map[character_position] = ' ';
              character_position = character_position - 1;
          }
          else if(map[character_position - 1] == rpoint){
            map[character_position - 1] = character;
            map[character_position] = ' ';
            character_position = character_position - 1;
            score1+=rpointScore;

            random = rand() % (height*width) ;
            while (map[random] != ' ') {

              random = rand() % (height*width) ;
            }
            map[random] = rpoint;
          }
          else if(map[character_position - 1] == target){
              map[character_position] = character;
          }
          else if(map[character_position - 1] == wall){
              map[character_position] = character;
          }
          else if(map[character_position - 1] == solidblock){
              map[character_position] = character;
          }
          else if(map[character_position - 1] == moveblock){
              if(map[character_position - 1 - 1] == ' '){
                map[character_position - 1] = character;
                map[character_position - 1 - 1] = moveblock;

                map[character_position] = ' ';
                character_position = character_position - 1;
              }
          }
          else if(map[character_position - 1] == deathblock){
              Mix_PlayChannel(-1, effect , 0);
              hp1 = 0;
          }
          else if(map[character_position - 1] == object){
              if(map[character_position - 1 - 1] == ' '){
                map[character_position - 1] = character;
                map[character_position - 1 - 1] = object;

                map[character_position] = ' ';
                character_position = character_position - 1;
              }
              else if(map[character_position - 1 - 1] == target){
                map[character_position - 1] = character;
                map[character_position - 1 - 1] = object;

                map[character_position] = ' ';
                character_position = character_position - 1;
                win1_state = 3;
              }
          }
          else if(map[character_position - 1] == opp){
              if(opp_target == character){
                win2_state = 7;
                // win2_state = 1;
              }
            }
          else if(map[character_position - 1] == bullet){
              Mix_PlayChannel(-1, hit_effect , 0);
              map[character_position - 1] = character;
              map[character_position] = ' ';
              character_position = character_position - 1;
              hp1 = hp1 - 20;
              if(hp1 <= 0){
                hp1 = hp1 - 20;;
              }
            }
        }
        else if(move == move_keys[3]){//right
              if(map[character_position + 1] == ' '){
                  map[character_position + 1] = character;
                  map[character_position] = ' ';
                  character_position += 1;
              }
              else if(map[character_position + 1] == rpoint){
                map[character_position + 1] = character;
                map[character_position] = ' ';
                character_position = character_position + 1;
                score1+=rpointScore;
                random = rand() % (height*width) ;
                while (map[random] != ' ') {
                  random = rand() % (height*width) ;
                }
                map[random] = rpoint;
              }
              else if(map[character_position + 1] == wall){
                map[character_position] = character;
              }
              else if(map[character_position + 1] == solidblock){
                  map[character_position] = character;
              }
              else if(map[character_position + 1] == moveblock){
                  if(map[character_position + 1 + 1] == ' '){
                    map[character_position + 1 + 1] = moveblock;
                    map[character_position + 1] = character;
                    map[character_position] = ' ';
                    character_position += 1;
                  }
              }
              else if(map[character_position + 1] == deathblock){
                  Mix_PlayChannel(-1, effect , 0);
                  hp1 = 0;
              }
              else if(map[character_position + 1] == object){
                  if(map[character_position + 1 + 1] == ' '){
                    map[character_position + 1 + 1] = object;
                    map[character_position + 1] = character;
                    map[character_position] = ' ';
                    character_position += 1;
                  }
                  else if(map[character_position + height + height] == target){
                    map[character_position + 1 + 1] = object;
                    map[character_position + 1] = character;
                    map[character_position] = ' ';
                    character_position += 1;
                    win1_state = 3;
                  }
              }
              else if(map[character_position + 1] == opp){
                  if(opp_target == character){
                    win2_state = 7;
                    // win2_state = 1;
                  }
              }
              else if(map[character_position + 1] == bullet){
                  Mix_PlayChannel(-1, hit_effect , 0);
                  map[character_position + 1] = character;
                  map[character_position] = ' ';
                  character_position += 1;
                  hp1 = hp1 - 20;
                  if(hp1 <= 0){
                    hp1 = hp1 - 20;;
                  }
              }
            }

  if(put == 1){
    // printf("limit of put : %d",put_limit);
    // Sleep(1500);
    if(put_limit <= 0){
      // printf("got here");
      // Sleep(1000);
      return;
    }
    if(move == move_keys[0]){
      if(map[character_position - height] == ' '){
        // printf("got up");
        // Sleep(1000);
        map[character_position - height] = put_obj;
      }
    }
    else if(move == move_keys[1]){
      if(map[character_position + height] == ' '){
        map[character_position+ height] = put_obj;
      }
    }
    else if(move == move_keys[2]){
      if(map[character_position - 1] == ' '){
        map[character_position - 1] = put_obj;
      }
    }
    else if(move == move_keys[3]){
      if(map[character_position + 1] == ' '){
        map[character_position + 1] = put_obj;
      }
    }
    put_limit--;
  }

}


void update_ai(char *moves){

    Mix_Chunk *effect = Mix_LoadWAV("Music/Explosion.wav");
    Mix_Chunk * hit_effect = Mix_LoadWAV("Music/hitmarker_2.wav");

  int height = map_width + 1, width = map_height,random, i;
  i = 0;
  while( i < original_opp_num ){

    // if the bot has been deleted

    if ( opps_positionS[i] == -2 ){
      ++i;
      continue;
    }

    else{


      if(moves[i] == move_keys[0]){//up
          if(map[opps_positionS[i] - height] == ' ') {
              map[opps_positionS[i] - height] = opp;
              map[opps_positionS[i]] = ' ';
              opps_positionS[i] = opps_positionS[i] - height;
          }
          else if(map[opps_positionS[i] - height] == rpoint){
            map[opps_positionS[i] - height] = opp;
            map[opps_positionS[i]] = ' ';
            opps_positionS[i] = opps_positionS[i] - height;
            score2 += rpointScore;

            random = rand() % (height*width) ;
            while (map[random] != ' ') {

              random = rand() % (height*width) ;
            }
            map[random] = rpoint;
          }
          else if(map[opps_positionS[i] - height] == wall){
              map[opps_positionS[i]] = opp;
          }
          else if(map[opps_positionS[i] - height] == solidblock){
              map[opps_positionS[i]] = opp;
          }
          else if(map[opps_positionS[i] - height] == moveblock){
              if(map[opps_positionS[i] - height - height] == ' '){
                map[opps_positionS[i] - height] = opp;
                map[opps_positionS[i] - height - height] = moveblock;

                map[opps_positionS[i]] = ' ';
                opps_positionS[i] = opps_positionS[i] - height;
              }
          }
          else if(map[opps_positionS[i] - height] == deathblock){
              Mix_PlayChannel(-1, effect , 0);
              map[opps_positionS[i]] = ' ';
              opps_positionS[i] = -2;
              num_opps--;
          }
          else if(map[opps_positionS[i] - height] == object){
              if(map[opps_positionS[i] - height - height] == ' '){
                map[opps_positionS[i] - height] = opp;
                map[opps_positionS[i] - height - height] = object;

                map[opps_positionS[i]] = ' ';
                opps_positionS[i] = opps_positionS[i] - height;
              }
              else if(map[opps_positionS[i] - height - height] == target){
                map[opps_positionS[i] - height] = opp;
                map[opps_positionS[i] - height - height] = object;

                map[opps_positionS[i]] = ' ';
                opps_positionS[i] = opps_positionS[i] - height;
                win2_state = 7;
              }
          }
          else if(map[opps_positionS[i] - height] == character){
              if(opp_target == character){
                // win2_state = ;
                win2_state = 7;
              }
          }
          else if(map[opps_positionS[i] - height] == bullet){
              Mix_PlayChannel(-1, hit_effect , 0);
              map[opps_positionS[i] - height] = opp;
              map[opps_positionS[i]] = ' ';
              opps_positionS[i] = -2;
              num_opps = num_opps - 1;
              score1++;
          }
          else if(map[opps_positionS[i] - height] == opp_target){
            map[opps_positionS[i] - height] = opp;
            map[opps_positionS[i]] = ' ';
            win2_state = 7;
            opps_positionS[i] = opps_positionS[i] - height;
          }
        }
        else if(moves[i] == move_keys[1]){
            if(map[opps_positionS[i] + height ] == ' '){
                map[opps_positionS[i] + height] = opp;
                map[opps_positionS[i]] = ' ';
                opps_positionS[i] += height;
            }
            else if(map[opps_positionS[i] + height] == rpoint){
              map[opps_positionS[i] + height] = opp;
              map[opps_positionS[i]] = ' ';
              opps_positionS[i] = opps_positionS[i] + height;
              score2 += rpointScore;

              random = rand() % (height*width) ;
              while (map[random] != ' ') {

                random = rand() % (height*width) ;
              }
              map[random] = rpoint;
            }
            else if(map[opps_positionS[i] + height] == wall){
                map[opps_positionS[i]] = opp;
            }
            else if(map[opps_positionS[i] + height] == solidblock){
                map[opps_positionS[i]] = opp;
            }
            else if(map[opps_positionS[i] + height] == moveblock){
                if(map[opps_positionS[i] + height + height] == ' '){
                  map[opps_positionS[i] + height] = opp;
                  map[opps_positionS[i] + height + height] = moveblock;

                  map[opps_positionS[i]] = ' ';
                  opps_positionS[i] += height;
                }
            }
            else if(map[opps_positionS[i] + height] == deathblock){
                Mix_PlayChannel(-1, effect , 0);
                map[opps_positionS[i]] = ' ';
                opps_positionS[i] = -2;
                num_opps--;
            }
            else if(map[opps_positionS[i] + height] == object){
                if(map[opps_positionS[i] + height + height] == ' '){
                  map[opps_positionS[i] + height] = opp;
                  map[opps_positionS[i] + height + height] = object;

                  map[opps_positionS[i]] = ' ';
                  opps_positionS[i] += height;
                }
                else if(map[opps_positionS[i] + height + height] == target){
                  map[opps_positionS[i] + height] = opp;
                  map[opps_positionS[i] + height + height] = object;

                  map[opps_positionS[i]] = ' ';
                  opps_positionS[i] += height;
                  win2_state = 7;
                }
            }
            else if(map[opps_positionS[i] + height] == character){
                if(opp_target == character){
                  // win2_state = 0;
                  win2_state = 7;
                }
            }
            else if(map[opps_positionS[i] + height] == bullet){
                Mix_PlayChannel(-1, hit_effect , 0);
                map[opps_positionS[i] + height] = opp;
                map[opps_positionS[i]] = ' ';
                opps_positionS[i] = -2;
                num_opps = num_opps - 1;
                score1++;
            }
            else if(map[opps_positionS[i] + height] == opp_target){
              map[opps_positionS[i] + height] = opp;
              map[opps_positionS[i]] = ' ';
              win2_state = 7;
              opps_positionS[i] = opps_positionS[i] + height;
            }
          }
          else if( moves[i] == move_keys[2]){
              if (map[opps_positionS[i] - 1] == ' '){
                  map[opps_positionS[i] - 1] = opp;
                  map[opps_positionS[i]] = ' ';
                  opps_positionS[i] = opps_positionS[i] - 1;
              }
              else if(map[opps_positionS[i] - 1] == rpoint){
                map[opps_positionS[i] - 1] = opp;
                map[opps_positionS[i]] = ' ';
                opps_positionS[i] = opps_positionS[i] - 1;
                score2 += rpointScore;

                random = rand() % (height*width) ;
                while (map[random] != ' ') {

                  random = rand() % (height*width) ;
                }
                map[random] = rpoint;
              }
              else if(map[opps_positionS[i] - 1] == wall){
                  map[opps_positionS[i]] = opp;
              }
              else if(map[opps_positionS[i] - 1] == solidblock){
                  map[opps_positionS[i]] = opp;
              }
              else if(map[opps_positionS[i] - 1] == moveblock){
                  if(map[opps_positionS[i] - 1 - 1] == ' '){
                    map[opps_positionS[i] - 1] = opp;
                    map[opps_positionS[i] - 1 - 1] = moveblock;

                    map[opps_positionS[i]] = ' ';
                    opps_positionS[i] = opps_positionS[i] - 1;
                  }
              }
              else if(map[opps_positionS[i] - 1] == deathblock){
                  Mix_PlayChannel(-1, effect , 0);
                  map[opps_positionS[i]] = ' ';
                  opps_positionS[i] = -2;
                  num_opps--;
              }
              else if(map[opps_positionS[i] - 1] == object){
                  if(map[opps_positionS[i] - 1 - 1] == ' '){
                    map[opps_positionS[i] - 1] = opp;
                    map[opps_positionS[i] - 1 - 1] = object;

                    map[opps_positionS[i]] = ' ';
                    opps_positionS[i] = opps_positionS[i] - 1;
                  }
                  else if(map[opps_positionS[i] - 1 - 1] == target){
                    map[opps_positionS[i] - 1] = opp;
                    map[opps_positionS[i] - 1 - 1] = object;

                    map[opps_positionS[i]] = ' ';
                    opps_positionS[i] = opps_positionS[i] - 1;
                    win2_state = 7;
                  }
              }
              else if(map[opps_positionS[i] - 1] == character){
                  if(opp_target == character){
                    // win2_state = 0;
                    win2_state = 7;
                  }
                }
                else if(map[opps_positionS[i] - 1] == bullet){
                  Mix_PlayChannel(-1, hit_effect , 0);
                  map[opps_positionS[i] - 1] = opp;
                  map[opps_positionS[i]] = ' ';
                  opps_positionS[i] = -2;
                  num_opps = num_opps - 1;
                  score1++;

                }
                else if(map[opps_positionS[i] - 1] == opp_target){
                  map[opps_positionS[i] - 1] = opp;
                  map[opps_positionS[i]] = ' ';
                  win2_state = 7;
                  opps_positionS[i] = opps_positionS[i] - 1;
                }
            }
            else if(moves[i] == move_keys[3]){
                  if(map[opps_positionS[i] + 1] == ' '){
                      map[opps_positionS[i] + 1] = opp;
                      map[opps_positionS[i]] = ' ';
                      opps_positionS[i] += 1;
                  }
                  else if(map[opps_positionS[i] + 1] == rpoint){
                    map[opps_positionS[i] + 1] = opp;
                    map[opps_positionS[i]] = ' ';
                    opps_positionS[i] = opps_positionS[i] + 1;
                    score2 += rpointScore;

                    random = rand() % (height*width) ;

                    while (map[random] != ' ') {
                      random = rand() % (height*width) ;
                    }
                    map[random] = rpoint;
                  }
                  else if(map[opps_positionS[i] + 1] == wall){
                      map[opps_positionS[i]] = opp;
                  }
                  else if(map[opps_positionS[i] + 1] == solidblock){
                      map[opps_positionS[i]] = opp;
                  }
                  else if(map[opps_positionS[i] + 1] == moveblock){
                      if(map[opps_positionS[i] + 1 + 1] == ' '){
                        map[opps_positionS[i] + 1] = opp;
                        map[opps_positionS[i] + 1 + 1] = moveblock;

                        map[opps_positionS[i]] = ' ';
                        opps_positionS[i] += 1;
                      }
                  }
                  else if(map[opps_positionS[i] + 1] == deathblock){
                      Mix_PlayChannel(-1, effect , 0);
                      map[opps_positionS[i]] = ' ';
                      opps_positionS[i] = -2;
                      num_opps--;
                  }
                  else if(map[opps_positionS[i] + 1] == object){
                      if(map[opps_positionS[i] + 1 + 1] == ' '){
                        map[opps_positionS[i] + 1] = opp;
                        map[opps_positionS[i] + 1 + 1] = object;

                        map[opps_positionS[i]] = ' ';
                        opps_positionS[i] += 1;
                      }
                      else if(map[opps_positionS[i] + height + height] == target){
                        map[opps_positionS[i] + 1] = opp;
                        map[opps_positionS[i] + 1 + 1] = object;

                        map[opps_positionS[i]] = ' ';
                        opps_positionS[i] += 1;
                        win2_state = 7;
                      }
                  }
                  else if(map[opps_positionS[i] + 1] == character){
                      if(opp_target == character){
                        // win2_state = 0;
                        win2_state = 7;
                      }
                  }
                  else if(map[opps_positionS[i] + 1] == bullet){
                      Mix_PlayChannel(-1, hit_effect , 0);
                      map[opps_positionS[i] + 1] = opp;
                      map[opps_positionS[i]] = ' ';
                      opps_positionS[i] = -2;
                      num_opps = num_opps - 1;
                      score1++;
                  }
                  else if(map[opps_positionS[i] + 1] == opp_target){
                    map[opps_positionS[i] + 1] = opp;
                    map[opps_positionS[i]] = ' ';
                    win2_state = 7;
                    opps_positionS[i] = opps_positionS[i] + 1;
                  }
                }

    }
    // if(put == 1){
    //
    //   if(put_limit <= 0){
    //     return;
    //   }
    //   if(moves[i] == move_keys[0]){
    //     if(map[opp_position - height] == ' '){
    //       map[opp_position - height] = put_obj;
    //     }
    //   }
    //   else if(moves[i] == move_keys[1]){
    //     if(map[opp_position + height] == ' '){
    //       map[opp_position+ height] = put_obj;
    //     }
    //   }
    //   else if(moves[i] == move_keys[2]){
    //     if(map[opp_position - 1] == ' '){
    //       map[opp_position - 1] = put_obj;
    //     }
    //   }
    //   else if(moves[i] == move_keys[3]){
    //     if(map[opp_position + 1] == ' '){
    //       map[opp_position + 1] = put_obj;
    //     }
    //   }
    //   put_limit--;
    //
    // }

    ++i;

  }

}



struct Bullet * put_bullet(int character_position,char side){// side of player // pos is current character position
  int i;
  struct Bullet* new_bullet = (struct Bullet*)malloc(sizeof(struct Bullet));
    Mix_Chunk *effect = Mix_LoadWAV("Music/Laser_Shoot.wav");
  new_bullet ->position = -1;
  new_bullet->side = side;
  if(side == move_keys[0]){
    if ( map[character_position - map_width - 1] == opp || map[character_position - map_width - 1 - map_width - 1] == opp || map[character_position - map_width - 1 - map_width - 1 - map_width - 1] == opp){
        Mix_PlayChannel(-1, effect, 0);
        if ( map[character_position - map_width - 1] == opp){
        map[character_position - map_width - 1] = ' ';
        for ( i = 0 ; i < original_opp_num ; ++i ){
          if (opps_positionS[i] == character_position - map_width - 1){
            opps_positionS[i] = -2;
            break;
          }
        }
        num_opps--;
        score1++;

      }
      else if ( map[character_position - map_width - 1 - map_width - 1] == opp  ){
        map[character_position - map_width - 1 - map_width - 1] = ' ';
        for ( i = 0 ; i < original_opp_num ; ++i ){
          if (opps_positionS[i] == character_position - map_width - 1 - map_width - 1){
            opps_positionS[i] = -2;
            break;
          }
        }
        num_opps--;
        score1++;
        opps_positionS[num_opps] = -2;
      }
      else if ( map[character_position - map_width - 1 - map_width - 1 - map_width - 1] == opp){
          map[character_position - map_width - 1 - map_width - 1 - map_width - 1] = ' ';
          for ( i = 0 ; i < original_opp_num ; ++i ){
            if (opps_positionS[i] == character_position - map_width - 1 - map_width - 1 - map_width - 1){
              opps_positionS[i] = -2;
              break;
            }
          }
          num_opps--;
          score1++;
      }
    }
    else if ( map[character_position - map_width - 1] == ' ' && map[character_position - map_width - 1 - map_width - 1] == ' ' && map[character_position - map_width - 1 - map_width - 1 - map_width - 1] == ' '){
      new_bullet->position = character_position - map_width - 1 - map_width - 1 - map_width - 1;
    }
  }
  else if(side == move_keys[1]){
    if ( map[character_position + map_width + 1] == opp || map[character_position + map_width + 1 + map_width + 1] == opp || map[character_position + map_width + 1 + map_width + 1 + map_width + 1] == opp){
        Mix_PlayChannel(-1, effect, 0);

        if ( map[character_position + map_width + 1] == opp){
        map[character_position + map_width + 1] =' ';

        for ( i = 0 ; i < original_opp_num ; ++i ){
          if (opps_positionS[i] == character_position + map_width + 1){
            opps_positionS[i] = -2;
            break;
          }
        }

        num_opps--;
        score1++;

      }
      else if ( map[character_position + map_width + 1 + map_width + 1] == opp  ){
        map[character_position + map_width + 1 + map_width + 1] = ' ';

        for ( i = 0 ; i < original_opp_num ; ++i ){
          if (opps_positionS[i] == character_position + map_width + 1 + map_width + 1){
            opps_positionS[i] = -2;
            break;
          }
        }

        num_opps--;
        score1++;
      }
      else if ( map[character_position + map_width + 1 + map_width + 1 + map_width + 1] == opp){
          map[character_position + map_width + 1 + map_width + 1 + map_width + 1] = ' ';
          for ( i = 0 ; i < original_opp_num ; ++i ){
            if (opps_positionS[i] == character_position + map_width + 1 + map_width + 1 + map_width + 1){
              opps_positionS[i] = -2;
              break;
            }
          }
          num_opps--;
          score1++;
      }
    }
    else if ( map[character_position + map_width + 1] == ' ' && map[character_position + map_width + 1 + map_width + 1] == ' ' && map[character_position + map_width + 1 + map_width + 1 +map_width + 1] == ' '){
        new_bullet->position = character_position + map_width + 1  + map_width + 1 + map_width + 1;
    }

  }
  else if(side == move_keys[2]){
    if ( map[character_position - 1] == opp || map[character_position - 2] == opp || map[character_position - 3] == opp){
        Mix_PlayChannel(-1, effect, 0);

        if ( map[character_position - 1] == opp){
        map[character_position - 1] = ' ';
        for ( i = 0 ; i < original_opp_num ; ++i ){
          if (opps_positionS[i] == character_position - 1){
            opps_positionS[i] = -2;
            break;
          }
        }
        num_opps--;
        score1++;
      }
      else if ( map[character_position - 2] == opp  ){
        map[character_position - 2] = ' ';
        for ( i = 0 ; i < original_opp_num ; ++i ){
          if (opps_positionS[i] == character_position - 2){
            opps_positionS[i] = -2;
            break;
          }
        }
        num_opps--;
        score1++;
      }
      else if ( map[character_position - 3] == opp){
          map[character_position - 3]  = ' ';
          for ( i = 0 ; i < original_opp_num ; ++i ){
            if (opps_positionS[i] == character_position - 3){
              opps_positionS[i] = -2;
              break;
            }
          }
          num_opps--;
          score1++;
      }
    }
    else if ( map[character_position - 1] == ' ' && map[character_position - 2] == ' ' && map[character_position - 3] == ' '){
        new_bullet->position = character_position - 3;
    }
  }
  else if(side == move_keys[3]){
    if ( map[character_position + 1] == opp || map[character_position + 2] == opp || map[character_position + 3] == opp){
        Mix_PlayChannel(-1, effect, 0);

        if ( map[character_position + 1] == opp){
        map[character_position + 1] = ' ';
        for ( i = 0 ; i < original_opp_num ; ++i ){
          if (opps_positionS[i] == character_position + 1){
            opps_positionS[i] = -2;
            break;
          }
        }
        num_opps--;
        score1++;
      }
      else if ( map[character_position + 2] == opp  ){
        map[character_position + 2] = ' ';
        for ( i = 0 ; i < original_opp_num ; ++i ){
          if (opps_positionS[i] == character_position + 2){
            opps_positionS[i] = -2;
            break;
          }
        }
        num_opps--;
        score1++;
      }
      else if ( map[character_position + 3] == opp){
          map[character_position + 3]  = ' ';
          for ( i = 0 ; i < original_opp_num ; ++i ){
            if (opps_positionS[i] == character_position + 3){
              opps_positionS[i] = -2;
              break;
            }
          }
          num_opps--;
          score1++;
      }
    }
    else if ( map[character_position + 1] == ' ' && map[character_position + 2] == ' ' && map[character_position + 3] == ' '){
        new_bullet->position = character_position + 3;
    }
  }
  if ( new_bullet -> position != -1){
    new_bullet->previous_pos = character_position;
    // bullet_counter++;
      Mix_PlayChannel(-1, effect, 0);
    return new_bullet;
  }
  else {
    return NULL;
  }
}




void update_bullet(struct Bullet *current_bullet){
  int height = map_width+1, width = map_height, i;

    Mix_Chunk *effect = Mix_LoadWAV(effect_address);

  if(map[current_bullet->position] == ' '){

    map[current_bullet->position] = bullet;
    map[current_bullet->previous_pos] = ' ';
    current_bullet->previous_pos = current_bullet->position;

    if(current_bullet->side == move_keys[0]){
      current_bullet->position = current_bullet->position - map_width - 1;
    }
    else if(current_bullet->side == move_keys[1]){
      current_bullet->position = current_bullet->position + map_width + 1;
    }
    else if(current_bullet->side == move_keys[2]){
      current_bullet->position = current_bullet->position - 1;
    }
    else if(current_bullet->side == move_keys[3]){
      current_bullet->position = current_bullet->position + 1;
    }
  }
  else if(map[current_bullet->position] == deathblock){
    map[current_bullet->previous_pos] = ' ';
    map[current_bullet->position] = ' ';
    current_bullet->position = -1;
    score1++;
  }
  else if(map[current_bullet->position] == solidblock){
    map[current_bullet->previous_pos] = ' ';
    current_bullet->position = -1;
  }
  else if(map[current_bullet->position] == wall){
    map[current_bullet->previous_pos] = ' ';
    current_bullet->position = -1;
  }
  else if(map[current_bullet->position] == moveblock){
    map[current_bullet->previous_pos] = ' ';
    current_bullet->position = -1;
  }
  else if(map[current_bullet->position] == target){
    map[current_bullet->previous_pos] = ' ';
    current_bullet->position = -1;
  }
  else if(map[current_bullet->position] == object){
    map[current_bullet->previous_pos] = ' ';
    current_bullet->position = -1;
  }
  else if(map[current_bullet->position] == bullet){
    map[current_bullet->previous_pos] = ' ';
    current_bullet->position = -1;
  }
  else if(map[current_bullet->position] == opp){
    map[current_bullet->previous_pos] = ' ';
    map[current_bullet->position] = ' ';
    current_bullet->position = -1;
    for ( i = 0 ; i < original_opp_num ; ++i ){
      if (opps_positionS[i] == current_bullet->position){
        opps_positionS[i] = -2;
        break;
      }
    }
    num_opps--;
    score1++;
  }
  else if(map[current_bullet->position] == character){
    map[current_bullet->previous_pos] = ' ';
    current_bullet->position = -1;

    if(current_bullet->side == move_keys[1]){//HEADSHOT
      hp1 = hp1 - 50;
    }
    else{
      hp1 = hp1 - 20;
    }
  }
  else if(map[current_bullet->position] == rpoint){
    map[current_bullet->previous_pos] = ' ';
    current_bullet->position = -1;
  }

}

void update_raindb(int *raindbs_pos,int number){
  int height = map_width+1, width = map_height,i,j;
  for(i=0;i<number;i++){

    if ( raindbs_pos[i] < 0 ){
      continue;
    }

    if (map[raindbs_pos[i] + height] == ' ') {
        map[raindbs_pos[i] + height] = deathblock;
        map[raindbs_pos[i]] = ' ';
        raindbs_pos[i] += height;
    }
    else if(map[raindbs_pos[i] + height] == character) {
        map[raindbs_pos[i] + height] = deathblock;
        map[raindbs_pos[i]] = ' ';
        raindbs_pos += height;
        hp1 = 0;
    }
    else if(map[raindbs_pos[i] + height] == opp) {
        map[raindbs_pos[i] + height] = deathblock;
        map[raindbs_pos[i]] = ' ';
        raindbs_pos[i] += height;
        for ( j = 0 ; j < original_opp_num ; ++j ){
          if (opps_positionS[j] == raindbs_pos[i] + height){
            opps_positionS[j] = -2;
            break;
          }
        }
        num_opps--;
    }
    else if(map[raindbs_pos[i] + height] == rpoint){
      if(map[raindbs_pos[i] + height + height] == ' '){
        map[raindbs_pos[i]] = ' ';
        map[raindbs_pos[i] + height + height] == deathblock;
        raindbs_pos[i] = raindbs_pos[i] + 2*height;
      }
    }
    else if(map[raindbs_pos[i] + height] == bullet){

        map[raindbs_pos[i]] = ' ';
        map[raindbs_pos[i] + height] == ' ';

        score1++;

        raindbs_pos[i] = -1;
    }
  }
}


void gravity(int gravity_state,char gravity_side,int* positions){//moveblock solidblock
  int i;
  if(gravity_state == 0){
    return;
  }
  for(i=1;i<positions[0];i++){
    if(gravity_side == move_keys[0]){
      if(map[positions[i] - map_width - 1] == ' '){
        map[positions[i] - map_width - 1] = map[positions[i]];
        map[positions[i]] = ' ';
        positions[i] = positions[i] - map_width - 1;
      }
      else if(map[positions[i] - map_width - 1] == moveblock && map[positions[i] - map_width - 1 - map_width - 1] == ' '){
        map[positions[i] - map_width - 1] = map[positions[i]];
        map[positions[i] - map_width - 1 - map_width - 1] = moveblock;
        map[positions[i]] = ' ';
        positions[i] = positions[i] - map_width - 1;
      }
    }
    else if(gravity_side == move_keys[1]){
      if(map[positions[i] + map_width + 1] == ' '){

        map[positions[i] + map_width + 1] = map[positions[i]];
        map[positions[i]] = ' ';
        positions[i] = positions[i] + map_width + 1;

      }
      else if(map[positions[i] + map_width + 1] == moveblock && map[positions[i] + map_width + 1 + map_width + 1] == ' '){
        map[positions[i] + map_width + 1] = map[positions[i]];
        map[positions[i] + map_width + 1 + map_width + 1] = moveblock;
        map[positions[i]] = ' ';
        positions[i] = positions[i] + map_width + 1;

      }
    }
    else if(gravity_side == move_keys[2]){
      if(map[positions[i] - 1] == ' '){
        map[positions[i] - 1] = map[positions[i]];
        map[positions[i]] = ' ';
        positions[i] = positions[i] - 1;
      }
      else if(map[positions[i] - 1] == moveblock && map[positions[i] - 2] == ' '){
        map[positions[i]  - 1] = map[positions[i]];
        map[positions[i] - 2] = moveblock;
        map[positions[i]] = ' ';
        positions[i] = positions[i] - 1;
      }
    }
    else if(gravity_side == move_keys[3]){
      if(map[positions[i] + 1] == ' '){
        map[positions[i] + 1] = map[positions[i]];
        map[positions[i]] = ' ';
        map[positions[i]] += 1;
      }
      else if(map[positions[i] + 1] == moveblock && map[positions[i] + 2] == ' '){
        map[positions[i] + 1] = map[positions[i]];
        map[positions[i] + 2] = moveblock;
        map[positions[i]] = ' ';
        map[positions[i]] += 1;
      }
    }
  }
}

int *find_gravity_objs(char shape1,char shape2,char shape3){
  int i,obj_counter = 0;
  int * temp_pos ;

  for(i=0;i<(map_width+1)*map_height;i++){
    if(map[i] == shape1 || map[i] == shape2 || map[i] == shape3){
      obj_counter++;
    }
  }

  temp_pos = (int *)malloc(sizeof(int)*(obj_counter+1));
  temp_pos[0] = obj_counter; // first element of array is its number of positions
  obj_counter = 1;
  for(i=0;i<(map_width+1)*map_height;i++){
    if(map[i] == shape1 || map[i] == shape2 || map[i] == shape3){
      temp_pos[obj_counter] = i;
      obj_counter++;
    }
  }
  return temp_pos;
}
