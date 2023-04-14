#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "functions.h"
#include "varsandincs.h"

#define MAX 10000

int *opps_positionS;
int original_opp_num = 0;

char **frames;
// 7 = opp reach target // 3 = character reach target
int color_state;// performance
int music_state = 1;
// PUT RPOINTS INSIDE
//

int game_engine( void ) {

    hidecursor();
    win1_state = 0;win2_state = 0;hp1 = 100;num_opps = 0;score1=0;score2=0, original_opp_num = 0;

    srand(time(NULL));

    put_rpoints(rpoint,NumberOfrpoints);


    frames = ( char ** )malloc(sizeof(char *) * 6);
    double gametime = game_time;
    double previousTime;
    double currentTime;
    double tempTime;
    int pause_state = 0; // if 0 it means the game hasn't been paused if 1 the game has been paused
    double elapsedTime;
    double current_fps = 0.0;
    double lag;
    int temp_counter = 0;
    int c1 = 0, i = 0, numberofhp = 0, frame = 0,highlighted_option = 0, order = 0, j = 0, c2 = 0, rain_frame = 0, counter_frame = 0, k = 0;
    int *raindbs_positions = (int *)malloc(sizeof(int)*MAX);
    raindbs_positions = put_raindb(raindb);

    char *resume_menu_options[4] = {"   - R e s u m e -   ","  - R e s t a r t -  ","   - R e p l a y -   ","     - E x i t -     "};

    for ( i = 0 ; i < 6 ; ++i ){
        frames[i] = (char *)malloc(sizeof(char) * ((map_height + 1) * (map_width + 1)));
    }
    i = 0;
    score1 = 0;
    score2 = 0;

    Mix_Chunk *lose = Mix_LoadWAV("Music/lose.wav");
    Mix_Chunk *win = Mix_LoadWAV("Music/win.wav");

    //including gravity if exist
    if(gravity_state == 1){
      gravity_object_posS = find_gravity_objs(gravity_obj1,gravity_obj2,gravity_obj3);
      //gravity(gravity_side,gravity_object_posS);
    }
    //check if colored-rendering is possible

    if ( color_set_state == 0 ){

        if ( map_height * map_width <= 450 ){
            color_state = 1;
        }

        else {
            color_state = 0;
        }
    }


    for(i=0;i<(map_height+1)*(map_width+1);i++){
        if(map[i] == character){
            character_position = i;
        }
        if(map[i] == opp && opp != '\0'){
            opp_position = i;
            num_opps++;
        }
    }



    opps_positionS = (int *)malloc(sizeof(int)*num_opps);
    bot_moves = (char *)malloc(sizeof(char)*num_opps);

    original_opp_num = num_opps;

    num_opps = 0 ;
    for(i=0;i<map_height*(map_width+1);i++){
        if(map[i] == opp){
            opp_position = i;
            opps_positionS[num_opps] = opp_position;
            // printf("bot position : %d\n",opps_positionS[num_opps]);
            num_opps++;
        }
    }

    // Sleep(1000



    previousTime = clock();
    tempTime = previousTime;
    lag = 0.0;


    int counter = 0;

    /// FIRST RENDER
    clear();
    switch (color_state) {
      case 1:
        if ( reftime_set_state == 0){
            refresh_time = 300;
        }
        print_mapp();
        break;
      case 0:
          if ( reftime_set_state == 0){
              refresh_time = 175;
          }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
        printf("%s",map);
        break;
    }


    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
    SetPosition(4, 3 + map_height);
    printf("HP1: ");
    if ( hp1/10 > 5 ){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 34);
    }
    else if ( hp1/10 > 2 && hp1/10 <=5 ){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 102);
    }
    else if ( hp1/10 >= 0 && hp1/10 <=2 ){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 68);
    }
    for ( numberofhp =  0 ; numberofhp <= hp1/10 ; ++numberofhp ){
        printf(" ");
    }

    setconsoleThemeDefault();

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
    SetPosition(4, 5 + map_height);
    printf("N M E Z: ");

    for ( i =  0 ; i < num_opps ; ++i ){

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),opp_color*17);
        putchar(' ');
        setconsoleThemeDefault();
        putchar(' ');

    }

    setconsoleThemeDefault();

    if ( color_state == 0 ){
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    else{
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
    }

    SetPosition(5 + map_width , 2);
    printf("Time: %.2f",gametime);


    if ( color_state == 0 ){
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    }
    else{
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
    }

    SetPosition(5 + map_width , 4);
    printf("FPS: 0");


    //////////////////////////// MAIN LOOP
    while(1) {


      // START OF A NEW FRAME

      currentTime = clock();
      elapsedTime = currentTime - previousTime;
      previousTime = currentTime;
      if ( pause_state == 0){
          lag+=elapsedTime;
      }

      // c1 = '\0';


        /// INIT OF THE LOOP
        if(kbhit()) {

            c1 = getch();
            if ( c1 != attack_key && c1!= put_key && c1 != '\0'){
              move = c1;
            }

            if(move == 27){//pause menu


              clear();
              SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_LIGHTCYAN);
              print_border(4,2,24,9);
              highlight_option(highlighted_option,resume_menu_options,  5, 3, 4);
              while ( 1 ) {


                  order = getch();

                  if(order == 72){

                      // Up arrow key
                      //case 72:

                          // Playing the sound effect;
                          //Mix_PlayChannel(-1, effect, 0);

                          --highlighted_option;
                          if (highlighted_option < 0) {
                              highlighted_option = 3;
                          }
                          print_border(4 , 2, 24, 9);
                          highlight_option(highlighted_option, resume_menu_options,  5, 3, 4);
                    }
                    if(order == 80){
                          // Down arrow key
                      //case 80:

                          // Playing the sound effect;
                          //Mix_PlayChannel(-1, effect, 0);

                          ++highlighted_option;
                          if (highlighted_option > 3) {
                              highlighted_option = 0;
                          }
                          print_border(4 , 2, 24, 9);
                          highlight_option(highlighted_option, resume_menu_options,  5, 3, 4);
                    }
                    if(order == 13){
                          // ENTER
                      //case 13:

                          // Playing the sound effect;
                          //Mix_PlayChannel(-1, effect, 0);



                          if (highlighted_option == 0) {//resume


                              clear();

                              pause_state = 1;

                              break;
                          }
                          else if(highlighted_option == 1){//restart
                            NumberOfrpoints = 0;
                            rpointScore = 0;
                            raindb = 0;
                            gravity_state = 0;
                            game_time = 0;

                              return games_func();
                          }

                          else if(highlighted_option == 2){//replay
                              int playbk_spd = 0;
                                clear();
                                SetPosition(4,3);
                              SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_LIGHTCYAN);
                              printf("Playback Speed : ");
                              scanf("%d",&playbk_spd);
                              replay(frames, playbk_spd);

                              clear();

                              pause_state = 1;

                              c1 = 27;

                              break;

                          }
                          else if(highlighted_option == 3){//exit
                            NumberOfrpoints = 0;
                            rpointScore = 0;
                            raindb = 0;
                            gravity_state = 0;
                            game_time = 0;
                            clear();
                            return menu();
                          }

                      }

               }
            }
        }

        //
        // printf("move : %d",move);
        // printf("key");
        // Sleep(1000);

        if ( pause_state == 1){

          pause_state = 2;
          // printf("Just after entering the result : %f",gametime);
          // Sleep(1500);
          continue;

        }


        // Check the time to see if it has been a second to determine the current FPS

        if ( pause_state == 0 ){
          if ( currentTime - tempTime >=1000 ){

              current_fps = frame;
              frame = 0;
              tempTime = clock();

          }



          /// UPDATE LOOP
          counter = 0;
          while(lag >= refresh_time){

              lag-=refresh_time;
              gametime-=refresh_time/1000;
              if ( gametime <= 0 ){

                  clear();
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);
                  SetPosition(4, 3);
                  printf("TIME IS UP!\n");


                  Sleep(2200);


                  clear();


                  // setconsoleThemeDefault();



                  if ( score1 > score2 ){

                    if ( global_loginstate == 1){
                      update_highscore(User,score1);
                      // print_border(4,3,35,5);
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
                      SetPosition(8,4);
                      printf("%s ",User);
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
                      printf("%c",'W');
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                      printf(" ");
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                      printf("%c",'I');
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                      printf(" ");
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
                      printf("%c",'N');
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                      printf(" ");
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                      printf("%c",'S');
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                      printf(" ");
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_LIGHTCYAN);
                      printf("%c",'!');
                      SetPosition(6,5);
                      printf("By gaining higher score.");
                      Mix_PlayChannel(-1, win, 0);
                      Sleep(3200);
                    }

                    else{

                      // print_border(4,3,30,5);
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
                      SetPosition(8,4);
                      printf("G U E S T  ",User);
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
                      printf("%c",'W');
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                      printf(" ");
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                      printf("%c",'I');
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                      printf(" ");
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
                      printf("%c",'N');
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                      printf(" ");
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                      printf("%c",'S');
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                      printf(" ");
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_LIGHTCYAN);
                      printf("%c",'!');
                      SetPosition(7,6);
                      printf("By gaining higher score.");
                      Mix_PlayChannel(-1, win, 0);
                      Sleep(3200);
                    }
                  }
                  else if(score2 > score1){
                      if ( global_loginstate ==1 ){
                          update_highscore(User,score1);
                      }
                    clear();
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);
                    SetPosition(4, 3);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    printf("Enemy's Team ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
                    printf("%c",'W');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    printf("%c",'O');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
                    printf("%c",'N');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");
                    /*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    printf("%c",'S');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");*/
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_LIGHTCYAN);
                    printf("%c",'!');
                    SetPosition(4,5);
                    printf("Enemy's Team earn more score");
                    Mix_PlayChannel(-1, lose, 0);

                    setconsoleThemeDefault();

                    Sleep(3200);

                  }

                  ///Here we should decide who one based on score and add scores
                  NumberOfrpoints = 0;
                  rpointScore = 0;
                  raindb = 0;
                  gravity_state = 0;
                  game_time = 0;
                  return menu() ;



              }


              // Update Player
              if ((c1 == attack_key || c1 == put_key) && c1 !='\0'){
                input_update(c1,raindbs_positions);

              }

              else{

                  input_update(move,raindbs_positions);

              }


              // Update A.I.
              for ( i = 0 ; i < num_opps ; ++i ){
                if ( opps_positionS[i] != -2 ){
                  if ( bot_moves[i] == move_keys[0] || bot_moves[i] == move_keys[1] || bot_moves[i] == move_keys[2] || bot_moves[i] == move_keys[3]){
                    c2 = ai_shoot(1,opps_positionS[i],character,bot_moves[i]);

                    if ( c2 == -1){

                      bot_moves[i] = ai(1, opps_positionS[i], opp_target);

                    }

                    else{
                      struct Bullet *tmp = (struct Bullet *)malloc(sizeof(struct Bullet));
                      tmp = put_bullet(opps_positionS[i],bot_moves[i]);
                      if ( tmp == NULL ){
                        bot_moves[i] = ai(1, opps_positionS[i], opp_target);
                      }
                      else{
                        Ammo[bullet_counter] = tmp;
                        update_bullet(Ammo[bullet_counter] );
                        bullet_counter++;

                      }
                    }
                  }
                  else{

                    bot_moves[i] = ai(1, opps_positionS[i], opp_target);

                  }
                }
              }
              if ( original_opp_num > 0 ){

                update_ai(bot_moves);

              }



              if (win2_state == 7){
                  if ( global_loginstate == 1){
                      update_highscore(User,score1);
                  }
                clear();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);
                SetPosition(4, 3);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                printf("Enemy's Team ");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
                printf("%c",'W');
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                printf(" ");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                printf("%c",'O');
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                printf(" ");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
                printf("%c",'N');
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                printf(" ");
                /*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                printf("%c",'S');
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                printf(" ");*/
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_LIGHTCYAN);
                printf("%c",'!');
                SetPosition(4,5);
                printf("They reached their target");

                Mix_PlayChannel(-1, lose, 0);

                setconsoleThemeDefault();

                Sleep(3200);
                NumberOfrpoints = 0;
                rpointScore = 0;
                raindb = 0;
                gravity_state = 0;
                game_time = 0;

                ///
                return menu();
              }

              else if(win1_state == 3){
                clear();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);

                SetPosition(4, 3);
                if(global_loginstate == 1){
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
                  printf("%s ",User);
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
                  printf("%c",'W');
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                  printf(" ");
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                  printf("%c",'O');
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                  printf(" ");
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
                  printf("%c",'N');
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                  printf(" ");
                  /*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                  printf("%c",'S');
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                  printf(" ");*/
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_LIGHTCYAN);
                  printf("%c",'!');
                  SetPosition(4,5);
                  printf("%s reached their target",User);
                  setconsoleThemeDefault();
                  Mix_PlayChannel(-1, win, 0);
                    update_highscore(User,score1);
                }

                else {
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_LIGHTCYAN);
                  printf("Guest ");
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
                  printf("%c",'W');
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                  printf(" ");
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                  printf("%c",'O');
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                  printf(" ");
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
                  printf("%c",'N');
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                  printf(" ");
                  /*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                  printf("%c",'S');
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                  printf(" ");*/
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_LIGHTCYAN);
                  printf("%c",'!');
                  SetPosition(4,5);
                  printf("Guest reached their target");
                  Mix_PlayChannel(-1, win, 0);
                  setconsoleThemeDefault();
                }

                Sleep(3200);
                ///
                NumberOfrpoints = 0;
                rpointScore = 0;
                raindb = 0;
                gravity_state = 0;
                game_time = 0;
                return menu();
              }



              else if ( hp1 <= 0 ){

                  clear();
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);
                  SetPosition(4, 3);
                  if(global_loginstate == 1){
                      update_highscore(User,score1);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    printf("Enemy's Team ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
                    printf("%c",'W');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    printf("%c",'O');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
                    printf("%c",'N');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");
                    /*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    printf("%c",'S');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");*/
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_LIGHTCYAN);
                    printf("%c",'!');
                    SetPosition(4,5);
                    printf("%s DIED!!!",User);
                    Mix_PlayChannel(-1, lose, 0);
                    setconsoleThemeDefault();
                  }

                  else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    printf("Enemy's Team ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
                    printf("%c",'W');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    printf("%c",'O');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
                    printf("%c",'N');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");
                    /*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    printf("%c",'S');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");*/
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_LIGHTCYAN);
                    printf("%c",'!');
                    SetPosition(4,5);
                    printf("Guest DIED");
                    Mix_PlayChannel(-1, lose, 0);
                    setconsoleThemeDefault();
                  }

                  Sleep(3200);
                  NumberOfrpoints = 0;
                  rpointScore = 0;
                  raindb = 0;
                  gravity_state = 0;
                  game_time = 0;
                  ///
                  return menu();
                }

              else if ( num_opps == 0  && original_opp_num > 0){


                  clear();
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);
                  SetPosition(4, 3);
                  if(global_loginstate == 1){
                      update_highscore(User,score1);
                    printf("%s ",User);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
                    printf("%c",'W');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    printf("%c",'O');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
                    printf("%c",'N');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");
                    /*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    printf("%c",'S');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");*/
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_LIGHTCYAN);
                    printf("%c",'!');
                    SetPosition(4,5);
                    printf("Enemy's team DIED!!!");
                    Mix_PlayChannel(-1, win, 0);
                    setconsoleThemeDefault();
                  }

                  else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_LIGHTCYAN);
                    printf("Guest ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
                    printf("%c",'W');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    printf("%c",'O');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
                    printf("%c",'N');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");
                    /*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    printf("%c",'S');
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_BLACK);
                    printf(" ");*/
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_LIGHTCYAN);
                    printf("%c",'!');
                    SetPosition(4,5);
                    printf("Enemy's team DIED!!!");
                    Mix_PlayChannel(-1, win, 0);
                    setconsoleThemeDefault();
                  }

                  Sleep(3200);
                  ///
                  NumberOfrpoints = 0;
                  rpointScore = 0;
                  raindb = 0;
                  gravity_state = 0;
                  game_time = 0;

                  return menu();

              }
              else if ( hp1 == 0 && num_opps == 0 && original_opp_num>0 ){

                  if ( global_loginstate == 1){
                      update_highscore(User,score1);
                  }

                  clear();
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG_AQUA);
                  SetPosition(4, 3);
                  printf("Both Players Died");
                  SetPosition(4, 5);
                  printf("ITS A DRAW!");

                  setconsoleThemeDefault();

                  Sleep(3200);
                  ///
                  NumberOfrpoints = 0;
                  rpointScore = 0;
                  raindb = 0;
                  gravity_state = 0;
                  game_time = 0;

                  return menu();


              }
              counter += 1;
              clear();


          }

        }


        /// RENDERING
        //print the map if any update has been made
        if ( counter > 0 ) {
            if(rain_frame >= (map_height-2)){
              for(i=0;i<raindb;i++){
                map[raindbs_positions[i]] = ' ';
                map[raindbs_positions[i]] = ' ';
              }
              rain_frame = 0;
              raindbs_positions = put_raindb(raindb);
            }
            switch (color_state) {
              case 1:
                print_mapp();
                break;
              case 0:
                //SetPosition(4,2);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
                printf("%s",map);
                break;
            }


            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
            SetPosition(4, 3 + map_height);
            printf("HP1: ");
            if ( hp1/10 > 5 ){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 34);
            }
            else if ( hp1/10 > 2 && hp1/10 <=5 ){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 102);
            }
            else if ( hp1/10 >= 0 && hp1/10 <=2 ){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 68);
            }
            for ( numberofhp =  0 ; numberofhp <= hp1/10 ; ++numberofhp ){
                putchar(' ');
            }

            setconsoleThemeDefault();

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
            SetPosition(4,  5+ map_height);
            printf("N M E Z: ");

            for ( i =  0 ; i < num_opps ; ++i ){

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),opp_color*17);
                putchar(' ');
                setconsoleThemeDefault();
                putchar(' ');

            }

            setconsoleThemeDefault();

            if ( color_state == 0 ){
              SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            else{
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
            }
            SetPosition(5 + map_width , 2);
            printf("Time: %.2f",gametime);


            if ( color_state == 0 ){
              SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            }
            else{
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTCYAN);
            }
            SetPosition(5 + map_width , 4);
            printf("FPS: %.1f",current_fps);

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),character_color);
            SetPosition(5 + map_width , 6);
            printf("Player Score:%d",score1);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),opp_color);
            SetPosition(5 + map_width , 7);
            printf("Bot Score:%d",score2);

            SetPosition(5 + map_width, 9);

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FG_LIGHTCYAN);

            ++frame;
            rain_frame++;
            if ( counter_frame < 6 ){
//                char * tmp = (char *)malloc(sizeof(char) * ((map_height + 1)*(map_width + 1)));
//                tmp = map;
//                printf("ladfa");
                strcpy(frames[counter_frame],map);
//                printf("After ");
//                Sleep(1000);
                ++counter_frame;
//                temp_counter += (sizeof(char) * ((map_height + 1)*(map_width + 1)));
            }
            else if ( counter_frame >= 6 ){
                for (k = 0 ; k < 5; ++k){
//                    char * tmp = (char *)malloc(sizeof(char) * ((map_height + 1)*(map_width + 1)));
                    strcpy(frames[k],frames[k+1]);
                }
//                char * tmp1 = (char *)malloc(sizeof(char) * ((map_height + 1)*(map_width + 1)));
//                tmp1 = map;
                strcpy(frames[k],map);
//                printf("pointer : %p\n",frames[k]);
//                Sleep(2000);
            }
        }


        if ( pause_state == 2 ){
          SetPosition(5 + map_width, 9);
          pause_state = 0;

        }

    }
    return 0;
}
