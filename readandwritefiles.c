#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "functions.h"
#include "varsandincs.h"


/// GLOBAL VARIABLES

// FILE VARS
char gamename[MAX_NAME_SIZE]; // NAME OF THE GAME
char map_name[MAX_NAME_SIZE] = "" ;  // THE NAME OF THE MAP
char map_color[MAX_NAME_SIZE] = "" ; // COLOR OF THE MAP
char map_file_name[MAX_NAME_SIZE] = ""; // A NAME FOR THE TEXT FILE OF THE MAP
char rule_file_name[MAX_NAME_SIZE] = "" ; // A NAME FOR THE TEXT FILE OF THE RULESr
char *map; // THE MAP ITSELF
char directories[100]; // THE DIRECTORY
int map_width; // MAP HEIGHT AND WIDTH
int map_height;
double refresh_time; // REFRESH TIME

// GAME VARS ( with default values )
int background_color = 0; //bg color changes in range (0,7)

char solidblock ='\0' ;
int solidblock_color = 128;

char deathblock = '\0' ;
int death_blk_color = 192;

char moveblock = '\0' ;
int moveblock_color = 224;



char rpoint ='\0' ;
int rpoint_color = 15;
int NumberOfrpoints = 0;
int rpointScore = 0;

char wall = '\0' ;
int wall_color = 11;

char move_keys[4] = {'\0','\0','\0','\0'}; //up, down, left, right

char character ='\0' ;
int character_color = 10;

double game_time = 0;

char target = '\0';
int target_color = 160;

char object = '\0' ;
int object_color = 9;

char opp = '\0' ;
int opp_color = 13;
char opp_target ;
int num_opps = 0;

char pause_key = 27;

char bullet = '\0' ;
int bullet_color = 12;

char attack_key = '\0';

char put_key = '\0' ;
char put_obj = '\0';
int put_limit = 0;

int raindb = 0;

int gravity_state = 0;
char gravity_side;
char gravity_obj1,gravity_obj2,gravity_obj3;
char exit_key ;










// READ MAP FUNCTION (READS THE MAP AND COPIES IN THE CHAR POINTER) // and the name after the map and the color after the name

void read_map ( char * map_file_name, char * directory ){

    char c;
    int i, index;
    char temp[1000];

    // Forming the address for reading

    strcpy( temp, directory);
    strcat( temp, "/");
    strcat(  temp, map_file_name );

    // reading the file

    FILE *map_file;
    map_file = fopen(temp, "r");

    fscanf(map_file, "%dx%d", &map_width, &map_height);

    // initializing the map'
    // printf("before allocating");
    map = ( char * )malloc(sizeof( char ) * ((map_width + 1 ) *   (map_height + 1)));


    while ((c=fgetc(map_file))!= '\n' ){
        ;
    }

    // parsing the map

    index = 0;

    for ( i = 1; i < map_height + 1 ; ++i ){

        while ((c=fgetc(map_file))!='\n' && c != EOF ){
            // putchar(c);
            map[index] = c;
            ++index;
        }


            map[index] = c;
            // putchar(c);
            ++index;

    }

    map[index] = '\0';

    // printf("%s",map);
    // printf("done the thing");
    // Sleep(1000);

    // reading the map name and the color and the refresh time

    fscanf(map_file, "%s\n",&map_name);
    fscanf(map_file, "%s\n",&map_color);
    fscanf(map_file, "%d\n",&refresh_time);

    fclose(map_file);


}


// PRINT MAP

void print_map ( char * mapstr , char * mapname, char * mapcolor ){


    /// Change the color

    /// Change the name of the console to map name

    // if the map name hasn't been set
    if ( mapname == "" ){
        ;
    }
    else if ( mapname != ""){
        SetConsoleTitle(map_name);
    }

    /// Prints the map


}



// INSTALL MAP FUNCTION (COPIES THE MAP TEXT FILE INSIDE THE ASSIGNED DIRECTORY)

void install_map ( char * mapfile, char * dir ){

    char c;
    char temp[100];
    char new_name[100] = "Games/";

    strcat(new_name, gamename);

    CreateDirectoryA(new_name,NULL);

    strcat(new_name, "/");

    strcpy(temp, dir);

    strcat(new_name, mapfile);

    strcat(temp, mapfile);

    // READING FROM THE MAP FILE AND WRITING INTO THE NEW FILE
    FILE * map_file;
    FILE * new_file;

    map_file = fopen(temp, "r");
    new_file = fopen(new_name, "w");

    while ((c=fgetc(map_file))!=EOF){
        fputc(c, new_file);
    }

    fclose(new_file);
    fclose(map_file);

}


// READ RULES FUNCTION ( READS THE RULE FILE AND UPDATES THE VARIABLES )
void read_rules ( char *rulefile, char *dir){

    char c;
    int i, index;
    int temp_num = 0;
    char temp[1000];
    char var_name[100];



    // Forming the address for reading

    strcpy( temp, directories);
    strcat( temp, "/");
    strcat(  temp, rulefile );


    // Opening the file

    FILE * rule_file;

    rule_file = fopen(temp, "r");

    // Parsing the data

    while (fscanf(rule_file, "%s",&temp)!=EOF){

        // making the name of the variable
        for ( i = 0 ; temp[i] != '=' ; ++i ){
            var_name[i] = temp[i];
        }

        var_name[i] = '\0';
        ++i;


        if ( strcmp(var_name, "solidblock") == 0 ){

            solidblock = temp[i];
            if ( temp[i + 1] == ',' ){
                temp_num = 0;
                i = i + 2;
                while(temp[i] != '\0' ){
                    temp_num = temp_num * 10 + ( temp[i] - '0' );
                    ++i;
                }
                solidblock_color = temp_num;
            }

        }

        else if(strcmp(var_name,"gravity") == 0){
          gravity_state = 0;
          while(temp[i] >= '0' && temp[i] <= '9'){
            gravity_state = gravity_state*10 + (temp[i] - '0');
            i++;
          }
          i++;
          gravity_side = temp[i];
          i+=2;
          gravity_obj1 = temp[i];
          i+=2;
          gravity_obj2 = temp[i];
          i+=2;
          gravity_obj3 = temp[i];
        }

        else if ( strcmp(var_name, "deathblock") == 0){
            deathblock = temp[i];
            if ( temp[i + 1] == ',' ){
                temp_num = 0;
                i = i + 2;
                while(temp[i] != '\0' ){
                    temp_num = temp_num * 10 + ( temp[i] - '0' );
                    ++i;
                }
                death_blk_color = temp_num;
            }

        }

        else if ( strcmp(var_name, "moveblock") == 0){
            moveblock = temp[i];
            if ( temp[i + 1] == ',' ){
                temp_num = 0;
                i = i + 2;
                while(temp[i] != '\0' ){
                    temp_num = temp_num * 10 + ( temp[i] - '0' );
                    ++i;
                }
                moveblock_color = temp_num;
            }

        }

        else if ( strcmp(var_name, "rpoint") == 0){
            rpoint = temp[i];
            i = i + 2;
            rpointScore = 0;
            while (temp[i] >= '0' && temp[i] <= '9' ){
                rpointScore = rpointScore * 10 + temp[i] - '0';
                ++i;
            }
            ++i;
            NumberOfrpoints = 0;
            while (temp[i] >= '0' && temp[i] <= '9' ){
                NumberOfrpoints = NumberOfrpoints * 10 + temp[i] - '0';
                ++i;
            }
//            ++i;
            if ( temp[i] == ',' ){
                temp_num = 0;
                ++i;
                while(temp[i] != '\0' ){
                    temp_num = temp_num * 10 + ( temp[i] - '0' );
                    ++i;
                }
                rpoint_color = temp_num;
            }


        }

        else if ( strcmp(var_name, "wall") == 0){
            wall = temp[i];
//            ++i;
            if ( temp[i + 1] == ',' ){
                temp_num = 0;
                i = i + 2;
                while(temp[i] != '\0' ){
                    temp_num = temp_num * 10 + ( temp[i] - '0' );
                    ++i;
                }
                wall_color = temp_num;
            }

        }

        else if ( strcmp(var_name, "up") == 0){
            move_keys[0] = temp[i];
        }

        else if ( strcmp(var_name, "down") == 0){
            move_keys[1] = temp[i];
        }

        else if ( strcmp(var_name, "left") == 0){
            move_keys[2] = temp[i];
        }

        else if ( strcmp(var_name, "right") == 0){
            move_keys[3] = temp[i];
        }

        else if ( strcmp(var_name,"bullet")== 0){
            bullet = temp[i];
//            ++i;
            if ( temp[i + 1] == ',' ){
                temp_num = 0;
                i = i + 2;
                while(temp[i] != '\0' ){
                    temp_num = temp_num * 10 + ( temp[i] - '0' );
                    ++i;
                }
                bullet_color = temp_num;
            }

        }

        else if ( strcmp(var_name, "character") == 0){
            character = temp[i];
//            ++i;
            if ( temp[i + 1] == ',' ){
                temp_num = 0;
                i = i + 2;
                while(temp[i] != '\0' ){
                    temp_num = temp_num * 10 + ( temp[i] - '0' );
                    ++i;
                }
                character_color = temp_num;
            }

        }

        else if ( strcmp(var_name, "time") == 0){
            game_time = 0;
            while (temp[i] >= '0' && temp[i] <= '9' ){
                game_time = game_time * 10 + temp[i] - '0';
                ++i;
            }
        }

        else if ( strcmp(var_name, "target") == 0){
            target = temp[i];
//            ++i;
            if ( temp[i + 1] == ',' ){
                temp_num = 0;
                i = i + 2;
                while(temp[i] != '\0' ){
                    temp_num = temp_num * 10 + ( temp[i] - '0' );
                    ++i;
                }
                target_color = temp_num;
            }

        }

        else if ( strcmp(var_name, "object") == 0){
            object = temp[i];
//            ++i;
            if ( temp[i + 1] == ',' ){
                temp_num = 0;
                i = i + 2;
                while(temp[i] != '\0' ){
                    temp_num = temp_num * 10 + ( temp[i] - '0' );
                    ++i;
                }
                object_color = temp_num;
            }

        }

        else if ( strcmp(var_name, "opp") == 0){
            opp = temp[i];
            i = i + 2;
            opp_target = temp[i];
//            ++i;
            if ( temp[i + 1] == ',' ){
                temp_num = 0;
                i = i + 2;
                while(temp[i] != '\0' ){
                    temp_num = temp_num * 10 + ( temp[i] - '0' );
                    ++i;
                }
                opp_color = temp_num;
            }

        }

        else if ( strcmp(var_name, "attack") == 0){
            attack_key = temp[i];
        }

        else if ( strcmp(var_name, "put") == 0){
            put_key = temp[i];
            i = i + 2;
            put_obj = temp[i];
            i = i + 2;
            put_limit = 0;
            while (temp[i] >= '0' && temp[i] <= '9' ){
                put_limit = put_limit * 10 + temp[i] - '0';
                ++i;
            }
        }

        else if ( strcmp(var_name, "raindb") == 0){
            raindb = 0;
            while(temp[i] >= '0' && temp[i] <= '9'){
              raindb = raindb * 10 + ( temp[i] - '0');
              ++i;
            }
        }

        else if ( strcmp(var_name, "Exit") == 0){
            exit_key = temp[i];
        }
    }



    fclose(rule_file);
    /*printf("%c %c\n",solidblock,moveblock);
    Sleep(2000);*/

}

// INSTALL RULES FUNCTION (COPIES THE RULES TEXT FILE INSIDE THE ASSIGNED DIRECTORY)

void install_rules ( char *rulefile, char *dir ){


    char c;
    char temp[100];
    char new_name[100] = "Games/";

    strcat(new_name, gamename);

    CreateDirectoryA(new_name,NULL);

    strcat(new_name, "/");

    strcpy(temp, dir);

    strcat(new_name, rulefile);

    strcat(temp, rulefile);

    // READING FROM THE RULES FILE AND WRITING INTO THE NEW FILE
    FILE * rule_file;
    FILE * new_file;

    rule_file = fopen(temp, "r");
    new_file = fopen(new_name, "w");

    while ((c=fgetc(rule_file))!=EOF){
        fputc(c, new_file);
    }

    fclose(new_file);
    fclose(rule_file);


}
