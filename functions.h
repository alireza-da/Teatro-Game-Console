//////// HEADER FOR FUNCTIONS
struct Bullet{
  int position;
  int previous_pos;
  char side;
};
/// SCREEN FUNCTIONS & CURSOR FUNCTIONS///
void clear( void );
void SetPosition (int X, int Y);
void hidecursor( void );
void showcursor ( void );
void setconsoleThemeDefault ( void );
void fontsize(int a, int b);
void print_border(int pos_X,int pos_Y,int width,int height);
//////////////////////////////////////////
//// FILE AND INSTALL FUNCTIONS //////////////////////////////////
void read_map ( char * map_file_name, char * directory );
void read_rules ( char *rulefile, char *dir);
void print_map ( char * mapstr , char * mapname, char * mapcolor );
void install_map ( char * mapfile, char * dir );
void install_rules ( char *rulefile, char *dir );
int install ( void );
///////////////////////////////////////////////////////////////////
//// INTRO AND MENU FUNCTIONS////////////////////////////////////////////////////
void highlight_option(int index, char **texts, int x, int y, int number_of_lines);
void print_menu ( char ** texts, int x, int y, int height, int width, int index );
int cons_setting ( void );
void print_logo();
void white_snow();
int menu ( void );
int games_func ( void );
////////////////////////////////////////////////////////
//Profile creation functions////////////////////////////
struct Profile* registering(char *username,char *password);
void writeProfiles(struct Profile* profile);
void profile_maker();
////////////////////////////////////////////////////////
//Encode & Decode functions
char *encode(char *text);
char *decode(char *text);
///////////////////////////////////////////
//Profile Loaders Functions////////////////////////////////
void show_profile(struct Profile* profile);
struct Profile* search_public(char *username);
///////////////////////////////////////////////////////////
//Login function that appear after intro
int login(char *username,char *password);
int login_ui();
void printf_curr_prf1 ( void );
void printf_curr_prf2 ( void );
void printf_curr_prf3 ( void );
void update_highscore(char *username,int score);
void update_loginstate(char *username,int loginstate);
int profiles( void );
///////////////////////////////////////////////////////////
//Game Engine//////////////////////////////////////////////
void print_mapp();
int * put_raindb(int number);
void put_rpoints(char shape,int number);
void input_update( char c1, int *raindbs_positions);
void update_character(char move,int put);
void update_bullet(struct Bullet *current_bullet);
void update_ai(char *move);
void update_raindb(int *raindbs_pos,int number);
int game_engine( void );
void replay ( char ** frames, int speed);
struct Bullet * put_bullet(int character_position,char side);
void gravity(int gravity_state,char gravity_side,int* positions);
int *find_gravity_objs(char shape1,char shape2,char shape3);
///////////////////////////////////////////////////////////
///A.I. Functions//////////////////////////////////////////
int ai(int ai_difficulty, int starting_index, char opp_target);
int ai_shoot (int ai_difficulty, int starting_index, char opp_target, char side);
