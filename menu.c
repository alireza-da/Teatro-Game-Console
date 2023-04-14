#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <errno.h>
#include "functions.h"
#include "varsandincs.h"
#define SDL_MAIN_HANDLED


/// GLOBAL MENU VARIABLES

char *menu_options[5] = {"         - I n s t a l l -        ", "           - G a m e s -          ", "        - P r o f i l e s -       "
                         , "- C o n s o l e  S e t t i n g s -", "            - E x i t -           "};

int cursor_x = 4 , cursor_y = 2;

int height = 13, width = 39;


int color_set_state = 0;
int music_set_state = 0;
int reftime_set_state = 0;

char music_address[] = {"Music/Lines of Code.mp3"};
char effect_address[] = {"Music/selectsound.wav"};



/// A FUNCTION FOR SETTING THE POSITION OF THE CURSOR

void SetPosition (int X, int Y) {

    HANDLE Screen;
    Screen = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position={X, Y};

    SetConsoleCursorPosition(Screen, Position);
}


/// A FUNCTION TO HIDE THE CONSOLE CURSOR
void hidecursor ( void ) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}


/// A FUNCTION TO SHOW THE CONSOLE CURSOR
void showcursor ( void ) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
}


/// A FUNCTION FOR CLEARING THE SCREEN

void clear( void ) {

    COORD topLeft  = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);

    FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written );

    FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
            screen.dwSize.X * screen.dwSize.Y, topLeft, &written);

    SetConsoleCursorPosition(console, topLeft);
}

/// SETS COLOR BACK TO DEFAULT COLOR

void setconsoleThemeDefault ( void ){


    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x00);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED );

}

/// HIGHLIGHT PRINTING
void highlight_option(int index, char **texts, int x, int y, int number_of_lines )
{
    int i;

    for (i = 0; i < number_of_lines; i++, y = y + 2) {
        SetPosition(x, y);
        if (i == index) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);
            printf("%s\n", texts[i]);
            setconsoleThemeDefault();
        } else {
            printf("%s\n", texts[i]);
        }

    }

}



/// PRINT MENU

void print_menu ( char ** texts, int x, int y, int height, int width, int index){

    int i, j;
    int text_x = x, text_y = y;

    // DRAWING THE BOX
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
    SetPosition(x, y);
    printf("%c", 201);
    for ( i = 1 ; i < width -2 ; ++i ){
        printf("%c", 205);
    }
    printf("%c\n",187);
    ++y;
    for ( i = 1 ; i < height - 1 ; ++i,++y ){
        SetPosition(x, y);
        printf("%c", 186);
        for ( j = 1 ; j < width -2 ; ++j ){
            printf("%c", ' ');
        }
        printf("%c\n",186);
    }
    SetPosition(x, y);
    printf("%c", 200);
    for ( j = 1 ; j < width -2 ; ++j ){
        printf("%c", 205);
    }
    printf("%c\n",188);
    setconsoleThemeDefault();

    // PRINTING THE TEXTS

    highlight_option(index, texts, text_x + 2 , text_y + 2, 5);

    SetPosition(x, y);

}


/// INSTALL FUNCTION

int install ( void ) {


    int i, j, x = cursor_x, y = cursor_y;
    char c;

    clear();


    // DRAWING THE BOX
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
    SetPosition(x, y);
    printf("%c", 201);
    for ( i = 1 ; i < width -2 ; ++i ){
        printf("%c", 205);
    }
    printf("%c\n",187);
    ++y;
    for ( i = 1 ; i < 7 - 1 ; ++i,++y ){
        SetPosition(x, y);
        printf("%c", 186);
        for ( j = 1 ; j < width -2 ; ++j ){
            printf("%c", ' ');
        }
        printf("%c\n",186);
    }
    SetPosition(x, y);
    printf("%c", 200);
    for ( j = 1 ; j < width -2 ; ++j ){
        printf("%c", 205);
    }
    printf("%c\n",188);
    setconsoleThemeDefault();

    // PRINTING THE TEXT AND WAITING FOR INPUT (GAME NAME)
//    SetPosition(x, y + 2);
//    printf("Press ESC to go back");

    showcursor();
    SetPosition(cursor_x + 1 , cursor_y + 1);

    printf("Enter the Game's Name : ");

    SetPosition(cursor_x + 4, cursor_y + 3);
    scanf("%s",&gamename);

    c = getchar();

    // GETTING THE DIR

    if ( c == '\n' ){

        clear();

        x = cursor_x;
        y = cursor_y;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
        SetPosition(x, y);
        printf("%c", 201);
        for ( i = 1 ; i < width -2 ; ++i ){
            printf("%c", 205);
        }
        printf("%c\n",187);
        ++y;
        for ( i = 1 ; i < 7 - 1 ; ++i,++y ){
            SetPosition(x, y);
            printf("%c", 186);
            for ( j = 1 ; j < width -2 ; ++j ){
                printf("%c", ' ');
            }
            printf("%c\n",186);
        }
        SetPosition(x, y);
        printf("%c", 200);
        for ( j = 1 ; j < width -2 ; ++j ){
            printf("%c", 205);
        }
        printf("%c\n",188);
        setconsoleThemeDefault();


        showcursor();
        SetPosition(cursor_x + 1 , cursor_y + 1);

        printf("Enter the Game's Directory : ");

        SetPosition(cursor_x + 4, cursor_y + 3);
        scanf("%s",&directories);


        // Making the address of the files and installing them



        strcpy(map_file_name,"map-") ;

        strcat(map_file_name,gamename);

        strcat(map_file_name, ".txt");

        install_map(map_file_name, directories);

        strcpy(rule_file_name, "game-") ;

        strcat(rule_file_name, gamename);

        strcat(rule_file_name, ".txt");

        install_rules(rule_file_name, directories);


        // ADDING THE GAME TO THE LIST

        FILE * game_list;

        game_list = fopen("game-list.txt","a");

        fputs(gamename, game_list);

        fputc('\n', game_list);


        fclose(game_list);


        hidecursor();

        clear();

        SetPosition(cursor_x, cursor_y + 3);

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);

        printf("Your game was installed successfully.");

        Sleep(3000);

        return menu();
    }

}


/// GAMES SEGMENT

int games_func ( void ) {

    int i, order, number_of_games = 0;
    char c;
    char ** games;

    // Setting the audio files

    Mix_Music *background = Mix_LoadMUS(music_address);
    Mix_Chunk *effect = Mix_LoadWAV(effect_address);

    clear();

    // Counting the lines to draw the appropriate box

    FILE * game_list;

    game_list = fopen("game-list.txt","r");

    while((c=fgetc(game_list))!=EOF){
        if ( c == '\n' ){
            ++number_of_games;
        }
    }


    // Initializing the games array ( 50 char space for each slot )

    games = ( char ** ) malloc ( sizeof( char * ) * number_of_games);

    for ( i = 0 ; i < number_of_games ; ++i ){
        games[i] = ( char * ) malloc ( sizeof( char ) * 50 );
    }


    // Saving the game names on the array

    fseek(game_list, 0, SEEK_SET);

    i = 0;

    while (fscanf(game_list, "%s\n", games[i])!=EOF){
        ++i;
    }

    --i;


    fclose(game_list);

    // Drawing the appropriate box

    int x = cursor_x, y = cursor_y, j;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
    SetPosition(x, y);
    printf("%c", 201);
    for ( i = 1 ; i < width -2 ; ++i ){
        printf("%c", 205);
    }
    printf("%c\n",187);
    ++y;
    for ( i = 1 ; i < ( 2 * number_of_games + 1) - 1 ; ++i,++y ){
        SetPosition(x, y);
        printf("%c", 186);
        for ( j = 1 ; j < width -2 ; ++j ){
            printf("%c", ' ');
        }
        printf("%c\n",186);
    }
    SetPosition(x, y);
    printf("%c", 200);
    for ( j = 1 ; j < width -2 ; ++j ){
        printf("%c", 205);
    }
    printf("%c\n",188);
    setconsoleThemeDefault();

    // Printing the menu and getting input

    order = 0;

    hidecursor();

    highlight_option(order, games, cursor_x + 1, cursor_y + 1, number_of_games);


    // main input loop

    while ( 1 ) {

        switch (getch()) {

            // Up arrow key
            case 72:

                // Playing the sound effect;
                Mix_PlayChannel(-1, effect, 0);

                --order;
                if (order < 0) {
                    order = number_of_games - 1;
                }

                // DRAW THE BOX AND TEXTS AGAIN

                clear();

                x = cursor_x;
                y = cursor_y;

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
                SetPosition(x, y);
                printf("%c", 201);
                for (i = 1; i < width - 2; ++i) {
                    printf("%c", 205);
                }
                printf("%c\n", 187);
                ++y;
                for (i = 1; i < (2 * number_of_games + 1) - 1; ++i, ++y) {
                    SetPosition(x, y);
                    printf("%c", 186);
                    for (j = 1; j < width - 2; ++j) {
                        printf("%c", ' ');
                    }
                    printf("%c\n", 186);
                }
                SetPosition(x, y);
                printf("%c", 200);
                for (j = 1; j < width - 2; ++j) {
                    printf("%c", 205);
                }
                printf("%c\n", 188);
                setconsoleThemeDefault();

                highlight_option(order, games, cursor_x + 1, cursor_y + 1, number_of_games);


                break;

                // Down arrow key
            case 80:

                // Playing the sound effect;
                Mix_PlayChannel(-1, effect, 0);

                ++order;
                if (order > number_of_games - 1) {
                    order = 0;
                }

                // DRAW THE BOX AND TEXTS AGAIN

                clear();

                x = cursor_x;
                y = cursor_y;

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
                SetPosition(x, y);
                printf("%c", 201);
                for (i = 1; i < width - 2; ++i) {
                    printf("%c", 205);
                }
                printf("%c\n", 187);
                ++y;
                for (i = 1; i < (2 * number_of_games + 1) - 1; ++i, ++y) {
                    SetPosition(x, y);
                    printf("%c", 186);
                    for (j = 1; j < width - 2; ++j) {
                        printf("%c", ' ');
                    }
                    printf("%c\n", 186);
                }
                SetPosition(x, y);
                printf("%c", 200);
                for (j = 1; j < width - 2; ++j) {
                    printf("%c", 205);
                }
                printf("%c\n", 188);
                setconsoleThemeDefault();

                highlight_option(order, games, cursor_x + 1, cursor_y + 1, number_of_games);

                break;

                // ENTER
            case 13:

                // Finding the game and setting the names

                strcpy(gamename, games[order]);

                // Map file
                strcpy(map_file_name,"map-");
                strcat(map_file_name,gamename);
                strcat(map_file_name,".txt");

                // Rule file
                strcpy(rule_file_name,"game-");
                strcat(rule_file_name,gamename);
                strcat(rule_file_name,".txt");

                strcpy(directories,"Games/");
                strcat(directories,gamename);

                clear();


                // Read the map and rule files
                // printf("%s %s\n",map_file_name,rule_file_name);
                // Sleep(2000);
                read_map(map_file_name, directories);
                // printf("%s\n",map);
                // Sleep(2000);
                read_rules(rule_file_name, directories);





                clear();

                /////////
                /// HERE THE GAME SHOULD BE RUN
                ////////


                game_engine();
                NumberOfrpoints = 0;
                rpointScore = 0;
                raindb = 0;
                gravity_state = 0;
                game_time = 0;
                return 0;


        }

    }
}


int cons_setting ( void ){


    char *main_opts[3] = { " - G r a p h i c s - ","    - M u s i c -    ", " - R e f   T i m e - "};
    clear();
    int highlighted_option = 0, i, temp;

    Mix_Music *background = Mix_LoadMUS(music_address);
    Mix_Chunk *effect = Mix_LoadWAV(effect_address);


    print_border(4 , 2, 26, 9);
    highlight_option(highlighted_option, main_opts,  6, 4, 3);

    while ( 1 ) {

        switch (getch()) {

            // Up arrow key
            case 72:

                // Playing the sound effect;
                Mix_PlayChannel(-1, effect, 0);

                --highlighted_option;
                if (highlighted_option < 0) {
                    highlighted_option = 2;
                }
                print_border(4 , 2, 26, 9);
                highlight_option(highlighted_option, main_opts,  6, 4, 3);
                break;

                // Down arrow key
            case 80:

                // Playing the sound effect;
                Mix_PlayChannel(-1, effect, 0);

                ++highlighted_option;
                if (highlighted_option > 2) {
                    highlighted_option = 0;
                }
                print_border(4 , 2, 26, 9);
                highlight_option(highlighted_option, main_opts,  6, 4, 3);
                break;

                // ENTER
            case 13:

                // Playing the sound effect;
                Mix_PlayChannel(-1, effect, 0);


                //// IF GRAPHICS IS CHOSEN
                if ( highlighted_option == 0 ){

                    clear();
                    highlighted_option = 0;

                    /// GRAPHICS MENU

                    color_set_state = 1;


                    print_border(4 , 2, 28, 3);

                    SetPosition(7, 3);
                    printf("Graphics : ");
                    if ( highlighted_option == 0 ){
                        SetPosition(17, 3);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);
                        printf(" HIGH ");
                        SetPosition(23, 3);
                        setconsoleThemeDefault();

                        printf(" LOW ");
                        setconsoleThemeDefault();

                    }
                    while ( 1 ) {

                        switch (getch()) {

                            // Up arrow key
                            case 77:

                                // Playing the sound effect;
                                Mix_PlayChannel(-1, effect, 0);

                                ++highlighted_option;
                                if (highlighted_option > 1) {
                                    highlighted_option = 0;
                                    color_state = 0;
                                }
                                print_border(4 , 2, 28, 3);

                                SetPosition(7, 3);
                                printf("Graphics : ");

                                setconsoleThemeDefault();
                                SetPosition(17, 3);
                                printf(" HIGH ");
                                setconsoleThemeDefault();

                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);
                                SetPosition(23, 3);
                                printf(" LOW ");

                                setconsoleThemeDefault();
                                break;

                                // Down arrow key
                            case 75:

                                // Playing the sound effect;
                                Mix_PlayChannel(-1, effect, 0);

                                --highlighted_option;
                                if (highlighted_option < 0) {
                                    highlighted_option = 1;
                                    color_state = 1;
                                }
                                print_border(4 , 2, 28, 3);

                                SetPosition(7, 3);
                                printf("Graphics : ");

                                SetPosition(17, 3);
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);
                                printf(" HIGH ");
                                setconsoleThemeDefault();

                                SetPosition(23, 3);
                                printf(" LOW ");

                                setconsoleThemeDefault();
                                break;

                                // ENTER
                            case 27:


                                if ( highlighted_option == 0 ){
                                    color_state = 1;
                                }
                                else if ( highlighted_option == 1){
                                    color_state = 0;
                                }


                                return menu();
                        }
                    }
                }


                /// MUSIC MENU

                else if ( highlighted_option == 1 ){

                    clear();
                    highlighted_option = 0;

                    /// MUSIC MENU

                    music_set_state = 1;


                    print_border(4 , 2, 28, 3);

                    SetPosition(7, 3);
                    printf("Music : ");
                    if ( highlighted_option == 0 ){
                        SetPosition(17, 3);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);
                        printf("  ON  ");
                        SetPosition(23, 3);
                        setconsoleThemeDefault();

                        printf(" OFF ");
                        setconsoleThemeDefault();

                    }
                    while ( 1 ) {

                        switch (getch()) {

                            // Up arrow key
                            case 77:

                                // Playing the sound effect;
                                Mix_PlayChannel(-1, effect, 0);

                                --highlighted_option;
                                if (highlighted_option > 1) {
                                    highlighted_option = 0;
                                    music_set_state = 0;

//                                    Mix_HaltMusic();
                                }
                                print_border(4 , 2, 28, 3);

                                SetPosition(7, 3);
                                printf("Music : ");

                                setconsoleThemeDefault();
                                SetPosition(17, 3);
                                printf("  ON  ");
                                setconsoleThemeDefault();

                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);
                                SetPosition(23, 3);
                                printf(" OFF ");

                                Mix_FadeOutMusic(200);

                                setconsoleThemeDefault();
                                break;

                                // Down arrow key
                            case 75:

                                // Playing the sound effect;
                                Mix_PlayChannel(-1, effect, 0);

                                ++highlighted_option;
                                if (highlighted_option < 0) {
                                    highlighted_option = 1;
                                    color_state = 1;

                                }
                                print_border(4 , 2, 28, 3);

                                SetPosition(7, 3);
                                printf("Music : ");

                                SetPosition(17, 3);
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);
                                printf("  ON  ");
                                Mix_FadeInMusic(background,-1,200);
                                setconsoleThemeDefault();

                                SetPosition(23, 3);
                                printf(" OFF ");

                                setconsoleThemeDefault();
                                break;

                                // ENTER
                            case 27:

                                return menu();
                        }
                    }
                }


                // IF refresh time is set
                else if ( highlighted_option == 2 ){


                    reftime_set_state = 1;

                    clear();

                    print_border(4 , 2, 28, 3);

                    SetPosition(7, 3);
                    printf("Refresh Time : ");

                    scanf("%d",&temp);

                    refresh_time = temp;

                    return menu();

                }

                break;

            case 27:

                return menu();

                break;
        }
    }








}

/// MENU (ARROW KEY HANDLER)

int menu ( void ){

    // Setting the audio files

    Mix_Music *background = Mix_LoadMUS(music_address);
    Mix_Chunk *effect = Mix_LoadWAV(effect_address);




    //////////////////////
    int order = 0;
    clear();
    hidecursor();


    print_menu(menu_options, cursor_x, cursor_y, height, width, order);
    printf_curr_prf1();

    // MAIN LOOP (GETTING INPUT FROM THE USER USING ARROW KEYS)

    while ( 1 ) {

        switch (getch()){

            // Up arrow key
            case 72:

                // Playing the sound effect;
                Mix_PlayChannel(-1, effect , 0);

                --order;
                if ( order < 0 ){
                    order = 4;
                }
                print_menu(menu_options, cursor_x, cursor_y, height, width, order);
                break;

            // Down arrow key
            case 80:

                // Playing the sound effect;
                Mix_PlayChannel(-1, effect , 0);

                ++order;
                if ( order > 4){
                    order = 0;
                }
                print_menu(menu_options, cursor_x, cursor_y, height, width, order);
                break;

            // ENTER
            case 13:

                // Playing the sound effect;
                Mix_PlayChannel(-1, effect , 0);


                // USER HAS CHOSEN INSTALL
                if ( order == 0 ){
                    return install();
                }

                // USER HAS CHOSEN GAMES
                else if ( order == 1){
                    return games_func();
                }

                // USER HAS CHOSEN PROFILES
                else if ( order == 2){

                    return profiles();

                }

                // USER HAS CHOSEN CONSOLE SETTING
                else if ( order == 3){
                    return cons_setting();
                }

                // USER HAS CHOSEN EXIT
                else if ( order == 4){
                  if(global_loginstate == 1){


                    update_loginstate(User,0);

                  }

                  exit(0);

                }
                break;

        }
    }


}



/// MAIN OF TEATRO

int main ( void ) {

    // INITIALIZING THE AUDIO CHANNELS

    SDL_SetMainReady();
    SDL_Init(SDL_INIT_AUDIO );

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    // Setting the audio files

    Mix_Music *noise = Mix_LoadMUS("Music/TV-static-sound-effects.mp3");
    Mix_Music *background = Mix_LoadMUS(music_address);
    Mix_Chunk *effect = Mix_LoadWAV(effect_address);



    // PRINTING
    clear();

// Printing intro
    hidecursor();
    print_logo();
    hidecursor();
    login_ui();
    SetConsoleTitle("Teatro");


    // CLOSING AUDIO CHANNELS

    Mix_CloseAudio();
    SDL_Quit();

    // SHOWING THE CURSOR AGAIN

    showcursor();


    return 0;


}
