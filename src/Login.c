#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "functions.h"
#include "varsandincs.h"
#define TRUE 1

struct Profile{
  char *username;
  char *password;
  char *loginstate;
  char *max_score;
};

///Global Username//
char User[30];
int global_loginstate;
////////////////////


///////////////////

int login(char *username,char *password){//return 1 if us and ps both are correct | return 0 if only username is correct | return -1 if both user and pass are wrong

  strcpy(password,encode(password));
  int c,result;
  FILE *profile;
  char tmp_user[10],tmp_pass[10];
  char dir[60] =  "Profiles/";
  char usrname[30];
  strcpy(usrname,username);
  strcat(dir,usrname);
  strcat(dir,".txt");
  profile = fopen(dir,"r");

  if(profile == NULL){//incorrect username
    result = -1;
    return result;
  }
  fscanf(profile,"Username:%s\n",tmp_user);
  fscanf(profile,"Password:%s\n",tmp_pass);
  fclose(profile);

  if(strcmp(tmp_user,username) == 0 && strcmp(tmp_pass,password) == 0){
    result = 1;
    return result;
  }
  else if(strcmp(tmp_user,username) == 0 && strcmp(tmp_pass,password) != 0){
    result = 0;
    return result;
  }
}

int login_ui(){

  char *options[3] = {"   - L o g i n -   ","- R e g i s t e r -","    - S k i p -    "};
  int highlighted_option = 0;
  char username[40],password[40];
  struct Profile *temp = (struct Profile*)malloc(sizeof(struct Profile));
  int c,order,login_result, i;


  Mix_Music *background = Mix_LoadMUS(music_address);
  Mix_Chunk *effect = Mix_LoadWAV(effect_address);

  clear();

  // Printing the login menu and getting order
  print_border(4 , 2, 24, 9);
  highlight_option(highlighted_option, options,  6, 4, 3);
  printf_curr_prf2();

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
                print_border(4 , 2, 24, 9);
                highlight_option(highlighted_option, options,  6, 4, 3);
                break;

                // Down arrow key
            case 80:

                // Playing the sound effect;
                Mix_PlayChannel(-1, effect, 0);

                ++highlighted_option;
                if (highlighted_option > 2) {
                    highlighted_option = 0;
                }
                print_border(4 , 2, 24, 9);
                highlight_option(highlighted_option, options,  6, 4, 3);
                break;

                // ENTER
            case 13:

                // Playing the sound effect;
                Mix_PlayChannel(-1, effect, 0);


                // USER HAS CHOSEN TO LOGIN
                if (highlighted_option == 0) {

                    // Getting the username and password
                    clear();
                    print_border(4, 2, 39, 7);
                    SetPosition(5, 3);
                    showcursor();
                    printf("Your Username:");
                    SetPosition(7, 5);
//                    scanf("%s",&username);
                    i = 0;
                    while ((c=getchar())!='\n'){
                        username[i] = c;
                        ++i;
                    }
                    username[i] = '\0';
                    clear();
                    print_border(4, 2, 39, 7);
                    SetPosition(5, 3);
                    printf("Your Password:");
                    SetPosition(7, 5);
//                    scanf("%s",&password);
                    i = 0;
                    while ((c=getchar())!='\n'){
                        password[i] = c;
                        ++i;
                    }
                    password[i] = '\0';

                    i = 0;

                    login_result = login(username,password);

                    switch (login_result){

                        case -1:
                            clear();
                            hidecursor();
                            SetPosition(4,3);
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
                            printf("Invalid Username\n");
                            Sleep(1500);
                            setconsoleThemeDefault();
                            return login_ui();
                            break;

                        case 0:
                            clear();
                            hidecursor();
                            SetPosition(4,3);
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
                            printf("Invalid Password\n");
                            Sleep(1500);
                            setconsoleThemeDefault();
                            return login_ui();
                            break;

                        case 1:
                            clear();
                            hidecursor();
                            SetPosition(4,3);
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);
                            printf("Login successfull\n");
                            strcpy(User,username);
                            update_loginstate(username,1);
                            global_loginstate = 1;
                            Sleep(1500);
                            setconsoleThemeDefault();
                            return menu();
                            break;

                    }

                }

                // USER HAS CHOSEN REGISTER
                else if (highlighted_option == 1) {

                    // Getting the username and password
                    clear();
                    print_border(4, 2, 39, 7);
                    SetPosition(5, 3);
                    showcursor();
                    printf("Your Username:");
                    SetPosition(7, 5);
//                    scanf("%s",&username);
                    i = 0;
                    while ((c=getchar())!='\n'){
                        username[i] = c;
                        ++i;
                    }
                    username[i] = '\0';
                    clear();
                    print_border(4, 2, 39, 7);
                    SetPosition(5, 3);
                    printf("Your Password:");
                    SetPosition(7, 5);
//                    scanf("%s",&password);
                    i = 0;
                    while ((c=getchar())!='\n'){
                        password[i] = c;
                        ++i;
                    }
                    password[i] = '\0';

                    i = 0;

                    // Updating the list and login status
                    temp = registering(username,password);
                    writeProfiles(temp);
                    update_loginstate(username,1);
                    global_loginstate = 1;
                    strcpy(User,username);

                    hidecursor();
                    clear();
                    SetPosition(4, 3);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);
                    printf("Your profile has been Registered on Teatro.\n");
                    Sleep(1500);

                    return menu();
                }

                // USER HAS CHOSEN TO SKIP
                else if (highlighted_option == 2) {

                    return menu();

                }
                break;

        }
    }


}


void print_border(int pos_X,int pos_Y,int width,int height){
    int i, j;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
    SetPosition(pos_X, pos_Y);
    printf("%c", 201);
    for ( i = 1 ; i < width -2 ; ++i ){
        printf("%c", 205);
    }
    printf("%c\n",187);
    ++pos_Y;
    for ( i = 1 ; i < height - 1 ; ++i,++pos_Y ){
        SetPosition(pos_X, pos_Y);
        printf("%c", 186);
        for ( j = 1 ; j < width -2 ; ++j ){
            printf("%c", ' ');
        }
        printf("%c\n",186);
    }
    SetPosition(pos_X, pos_Y);
    printf("%c", 200);
    for ( j = 1 ; j < width -2 ; ++j ){
        printf("%c", 205);
    }
    printf("%c\n",188);
    setconsoleThemeDefault();
}



// FUNCTION FOR PROFILES
int profiles( void ){

    char *options[] = {" - P r o f i l e  M a n a g e m e n t - ","     - S e a r c h  P r o f i l e -     "};
    int highlighted_option = 0;
    char username[30];
    struct Profile *temp = (struct Profile*)malloc(sizeof(struct Profile));
    int i, c;


    Mix_Music *background = Mix_LoadMUS(music_address);
    Mix_Chunk *effect = Mix_LoadWAV(effect_address);

    clear();

    // Printing the login menu and getting order
    print_border(4 , 2, 46, 7);
    highlight_option(highlighted_option, options,  6, 4, 2);
    printf_curr_prf3();


    while (1) {


        switch (getch()){

            // Up arrow key
            case 72:

                // Playing the sound effect;
                Mix_PlayChannel(-1, effect, 0);

                --highlighted_option;
                if (highlighted_option < 0) {
                    highlighted_option = 1;
                }
                print_border(4 , 2, 46, 7);
                highlight_option(highlighted_option, options,  6, 4, 2);
                break;

                // Down arrow key
            case 80:

                // Playing the sound effect;
                Mix_PlayChannel(-1, effect, 0);

                ++highlighted_option;
                if (highlighted_option > 1) {
                    highlighted_option = 0;
                }
                print_border(4 , 2, 46, 7);
                highlight_option(highlighted_option, options,  6, 4, 2);
                break;


            case 13:

                // Playing the sound effect;
                Mix_PlayChannel(-1, effect, 0);


                // USER HAS CHOSEN TO PROFILE MANAGEMENT
                if (highlighted_option == 0) {

                    return login_ui();

                }

                // USER HAS CHOSEN SEARCH
                else if (highlighted_option == 1) {

                    clear();
                    print_border(4, 2, 39, 7);
                    SetPosition(5, 3);
                    showcursor();
                    printf("Your Username:");
                    SetPosition(7, 5);
                    i = 0;
                    while ((c=getchar())!='\n'){
                        username[i] = c;
                        ++i;
                    }
                    username[i] = '\0';

                    temp = search_public(username);
                    clear();
                    show_profile(temp);
                    SetPosition(4, 8);
                    printf("Press Enter to go back.");
                    while(getch()!=13){
                        ;
                    }

                    return menu();

                }

        }
    }



}
