////// HEADER FOR VARIABLES AND INCLUDES AND PREPROCESSORS


/// PREPROCESSORS

// MISC PREPROCESSOR
#define MAX_NAME_SIZE 50

// COLOR PREPROCESSORS ( purple green blue red yellow aqua bg )
#define BG_AQUA 176
#define FG_BLACK 0
#define FG_LIGHTCYAN 11

// SDL2 PREPROCESSORS
#define SDL_MAIN_HANDLED


///////////////////////

/// INCLUDES

// SDL 2 INCLUDES
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

// MISC
#include <time.h>

///////////////////////

/// VARIABLES

// MISC
extern char music_address[]; // the address for the background music
extern char effect_address[]; // the address for the effect sound

// RULE AND MAP VARIABLES ( FILE )
extern char map_name[MAX_NAME_SIZE];  // the name of the map
extern char map_file_name[MAX_NAME_SIZE]; // a name for the text file of the map
extern char rule_file_name[MAX_NAME_SIZE] ; // a name for the text file of the rules
extern char *map; // the map itself
extern char directories[100]; // the directory
extern int map_width; // map height and width
extern int map_height;
extern char map_color[MAX_NAME_SIZE]; // color of the map
extern char gamename[MAX_NAME_SIZE]; // name of the game
extern double refresh_time; // refresh time



// GAME VARIABLES
extern char solidblock;
extern char deathblock;
extern char moveblock;
extern char rpoint;
extern int NumberOfrpoints;
extern int rpointScore;
extern char wall;
extern char move_keys[4]; //up, down, left, right
extern char character;
extern double game_time;
extern char target;
extern char object;
extern char opp;
extern char opp_target;
extern char attack_key;
extern char put_key;
extern char put_obj;
extern int put_limit;
extern int raindb;
extern char exit_key;
extern int background_color;
extern int solidblock_color;
extern int death_blk_color;
extern int moveblock_color;
extern int rpoint_color;
extern int wall_color;
extern int character_color;
extern int target_color;
extern int reftime_set_state;
extern int object_color;
extern int opp_color;
extern int num_opps;
extern int *opps_positionS;
extern int bullet_color;
extern int hp1;
extern int bullet_position;
extern int bullet_counter;
extern char bullet;
extern struct Bullet *Ammo[100];
extern char move;
extern int color_set_state;
extern int music_set_state;
extern char *bot_moves;
extern int gravity_state;
extern char gravity_side;
extern char gravity_obj1,gravity_obj2,gravity_obj3;
extern int *opps_positionS;
extern int *gravity_object_posS;
extern int original_opp_num;
extern int color_state;
extern int music_state;
extern char **frames;
//////////////////////

//Profile's varilables
extern char User[30];
extern int global_loginstate;
//////////////////////

//update & refresh var /////////
extern int character_position;
extern int opp_position;
extern int win1_state;
extern int win2_state;
extern int score1;
extern int score2;
////////////////////////////////
