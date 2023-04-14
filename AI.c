#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "functions.h"
#include "varsandincs.h"
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10000
#define DEFAULT -2
#define NONE -1
#define ON 1
#define OFF 0

// INIT OF THE QUEUE ( FRONTIER )

int frontier[MAX];
int rear = -1 , frontier_size = 0;



void put ( int x ) {

    if ( frontier_size == MAX ){
        printf("the queue is full\n");
    }
    else {
        rear+=1;
        frontier[rear] = x;
        frontier_size+=1;
    }
}

int get ( void ) {
    int i,a, temp[MAX], j;

    if ( frontier_size == 0){
//        printf("the queue is empty\n");
        return -1 ;
    }
    else{
        a = frontier[0];
        for ( i = 1, j = 0 ; i < frontier_size ; ++i, ++j ){
            temp[j] = frontier[i];
        }
        for ( i = 0 ; i < j ; ++i ){
            frontier[i] = temp[i];
        }
        rear-=1;
        frontier_size-=1;
        return a;
    }
}

// END OF FRONTIER INITIALIZATION


void neigh ( int a[], int pos ){

    int i;
//    if ( map[pos] == 'T' ){
//        if ( pos == index_tp_1 ){
//            a[0] = index_tp_2 + 1;
//            a[1] = index_tp_2 - height;
//            a[2] = index_tp_2 - 1;
//            a[3] = index_tp_2 + height;
//        }
//        else {
//            a[0] = index_tp_1 + 1;
//            a[1] = index_tp_1 - height;
//            a[2] = index_tp_1 - 1;
//            a[3] = index_tp_1 + height;
//        }
//    }

        a[0] = pos + 1;
        a[1] = pos - map_width - 1;
        a[2] = pos - 1;
        a[3] = pos + map_width + 1;



}

void xy_finder(int xy[], int index ){

    int x, y, current_index;



    for ( x = 0 ; x < map_width ; ++x ){
        for ( y = 0 ; y < map_height ; ++y){
            current_index = ( y * map_height) + x;
            if ( current_index == index ){
                xy[0] = x;
                xy[1] = y;
                break;
            }
        }
    }
}

int abs( int x ) {
    if (x < 0) {
        return -x;
    }
    else {
        return x;
    }
}



// AI FUNCTION ( USING RANDOM DIRECTIONS IN EASY MODE / BREADTH SEARCH IN NORMAL MODE ) RETURNS -1 IN CASE OF ERROR

int ai(int ai_difficulty, int starting_index, char opp_target){

    int come_from[100000];
    int path[MAX];
    int neighbors[4], x_y[2], dirs[4];
    int i, j, blk_count, current, goal, current_ratio, temp,  x1, x2, y1, y2, next_block, state ;

    // SETTING THE COME_FROM ARRAY TO DEFAULT
    for ( i = 0 ; i < 100000 ; ++i ){
        come_from[i] = DEFAULT;
    }

    // SETTING THE DIRECTION ARRAY
    dirs[0] = move_keys[2];
    dirs[1] = move_keys[0];
    dirs[2] = move_keys[3];
    dirs[3] = move_keys[1];

    blk_count = 0;
    goal = NONE;
    state = ON;

    // EASY MODE
    if ( ai_difficulty == 0 ){
        srand(time(NULL));
        next_block = dirs[rand() % ( (3 - 0 + 1) + 0 )];
        return next_block;
    }

    //DIFFICULT MODE
    else if ( ai_difficulty == 1 ){

        // REINITIALIZING THE QUEUE
        frontier_size = 0;
        rear = -1;
        //

        put(starting_index);
        come_from[starting_index] = NONE;

        while ( blk_count <= 100 ){
            current = get();
            if ( state == ON ){}
            neigh(neighbors, current);
            for ( i = 0 ; i < 4 ; ++i ) {
                if ( come_from[neighbors[i]] == DEFAULT ){
                    blk_count+=1;
                }
                if ( come_from[neighbors[i]] == DEFAULT && map[neighbors[i]] != solidblock && map[neighbors[i]]!= wall && map[neighbors[i]] != deathblock && map[neighbors[i]] != bullet && map[neighbors[i]] != opp  && map[neighbors[i]]!=object ) {
                    put(neighbors[i]);
                    come_from[neighbors[i]]= current;
                }
                if ( goal == NONE && ( map[neighbors[i]] == opp_target )  ){
                    goal = neighbors[i];
                       current_ratio = 5 / (abs( x1 - x2 ) + abs( y1 - y2 ));
                }
                else if ( map[neighbors[i]] == opp_target ){

                       temp = 5 / (abs( x1 - x2 ) + abs( y1 - y2 ));

                   if ( temp > current_ratio ){
                       current_ratio = temp;
                       goal = neighbors[i];
                   }
                }
            }
            state = OFF;
        }
        if ( goal == NONE ){
            while ( (map_height * map_width) != 0 ){
                current = get();
                neigh(neighbors, current);
                for ( i = 0 ; i < 4 ; ++i ) {
                    if ( come_from[neighbors[i]] == DEFAULT ){
                        blk_count+=1;
                    }
                    if ( come_from[neighbors[i]] == DEFAULT && map[neighbors[i]] != solidblock && map[neighbors[i]]!= wall && map[neighbors[i]] != deathblock && map[neighbors[i]] != bullet && map[neighbors[i]] != opp && map[neighbors[i]]!=object){
                        put(neighbors[i]);
                        come_from[neighbors[i]]= current;
                    }
                    if ( map[neighbors[i]] == opp_target ){
                        goal = neighbors[i];
                        break;
                    }
                }
                if ( goal != NONE ){
                    break;
                }
            }
        }
        i = goal;
        j = 0;
        path[j] = i;
        ++j;
        while ( come_from[i] != NONE ){
            path[j] = come_from[i];
            ++j;
            i = come_from[i];
        }

        next_block = path[ j - 2 ];


        if ( next_block == starting_index + 1) {
            return move_keys[3];
        }
        else if ( next_block == starting_index - 1) {
            return move_keys[2];
        }
        else if ( next_block == starting_index - map_width - 1 ) {
            return move_keys[0];
        }
        else if ( next_block == starting_index + map_width + 1 ) {
            return move_keys[1];
        }
        else {
            return -1;
        }

    }
}



/// AI FOR SHOOTING (RETURNS -1 IF IT SHOULDN'T SHOOT)
int ai_shoot (int ai_difficulty, int starting_index, char targ, char side){

    // when state is 0 it shouldn't shoot
    int state = 0;
    int index = starting_index;


    //Difficult
    if ( ai_difficulty == 1 ){

        // Check above
        if ( side == move_keys[0] ){
          index = starting_index - map_width - 1;
          while(map[index] == ' ' || map[index] == targ){
              if (map[index] == opp ){
                  break;
              }
              else if ( map[index] == targ){
                  return attack_key;
              }

              else{
                  index = index - map_width - 1;
              }
          }

          return -1;
        }



        //Check below
        else if ( side == move_keys[1]){
          index = starting_index + map_width + 1;
          while(map[index] == ' ' || map[index] == targ){
              if (map[index] == opp ){
                  break;
              }
              else if ( map[index] == targ){
                  return attack_key;
              }

              else{
                  index = index + map_width + 1;
              }
          }
          return -1;
        }



        //Check left
        else if ( side == move_keys[2]){
          index = starting_index - 1;
          while(map[index] == ' ' || map[index] == targ ){
              if (map[index] == opp ){
                  break;
              }
               else if ( map[index] == targ){
                  return attack_key;
              }

              else{
                  index = index - 1;
              }
          }
          return -1;
        }



        //Check right
        else if ( side == move_keys[3]){
          index = starting_index + 1;
          while(map[index] == ' ' || map[index] == targ){
              if (map[index] == opp ){
                  break;
              }
              else if ( map[index] == targ){
                  return attack_key;
              }

              else{
                  index = index + 1;
              }
          }

          return -1;
        }
    }


    //EASY

    else if ( ai_difficulty == 0){

        srand(time(NULL));

        return move_keys[rand() % ( (3 - 0 + 1) + 0 )];
    }

}
