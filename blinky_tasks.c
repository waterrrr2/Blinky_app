/** @file   blinky_tasks.c
    @author C. Papple, K. Lai
    @date   20 Oct 2021
    @brief  This module implements most of the logic associated with button pressing
*/

#include "blinky_tasks.h"
#include "uint8toa.h"
#include "navswitch.h"
#include "ledmat.h"
#include "pacer.h"
#include "obstacle.h"
#include "level_select.h"
#include "../fonts/font3x5_1.h"
#include "player_loc.h"
#include <string.h>

/* Initializes the core part of the game */
void blinky_init(void)
{
    system_init ();
    
    pacer_init(LEVEL_TASK_RATE);

    tinygl_init (DISPLAY_TASK_RATE);
    tinygl_font_set (&font3x5_1);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_speed_set (TEXT_SPEED);
    
    navswitch_init ();
    
    player_init(); 

    state = STATE_MENU;
}

/* Constantly updates the display */
   

void display_task (__unused__ void *data)
{   
    tinygl_update (); 
}

/* A Driver for the play_loc module */
   
void player_task (__unused__ void *data)
{
    switch (state)
    {
    case STATE_INGAME:
        player_display(player_loc);
        break;

    default:
        break;
    }
    
}

/* Implements what happens when the navswitch is used */
   
void navswitch_task (__unused__ void *data)
{
    if(navswitch_push_event_p(NAVSWITCH_PUSH)) {
        switch (state)
        {
        case STATE_IDEL:
            state = STATE_PREGAME;
              
            break;
            
        case STATE_LV_SELECT:
            obstacle_task_init(level);
            state = STATE_PLAYING;
            break;  

        case STATE_POSTGAME:
            state = STATE_PREGAME;
            break;
        
        default:
            break;  
        }
    }

    if(navswitch_down_p(NAVSWITCH_SOUTH)) {
        switch (state)
        {
        case STATE_INGAME:
            /* moves player to the left */
            player_loc_up();
            break;

        default:
            break; 
        } 
    }

    if(navswitch_down_p(NAVSWITCH_NORTH)) {
        switch (state)
        {
        case STATE_INGAME:
            /* moves player to the right */
            player_loc_down();
            break;

        default:
            break; 
        } 
    }

    if(navswitch_push_event_p(NAVSWITCH_EAST)) {
        switch (state)
        {
        case STATE_LV_SELECT:
            level_select_up();
            lv_display(level);
            break;

        default:
            break; 
        }
    }
    
    if(navswitch_push_event_p(NAVSWITCH_WEST)) {
        switch (state)
        {
        case STATE_LV_SELECT:
            level_select_down();
            lv_display(level);
            break;
        default:
            break; 
        }
    }

    /* Constantly updating the state of the navswitch */

    navswitch_update();
}

/*Implements what to display depending on the state of the game */

void game_task (__unused__ void *data)
{
    switch (state)
    {
    case STATE_MENU:
        state = STATE_IDEL;
        tinygl_text ("BLINKY BY K.LAI AND C.PAPPLE");
        break;

    case STATE_PREGAME:
        str = score_string;
        strcpy (str, "SCORE ");
        player_loc = START_LOC; 
        state = STATE_LV_SELECT;
        level_select_up();
        lv_display(level);
        break;

    case STATE_PLAYING:
        state = STATE_INGAME;
        break;
    
    case STATE_INGAME:
        tinygl_clear ();
        obstacle_task();
        if(check_collision()) {
            state = STATE_OVER;
        }
        break;

    case STATE_OVER:
        state = STATE_POSTGAME;
        while (*str)
        str++;
        uint8toa(score, str, 0);
        while (*str)
            str++;
        tinygl_clear ();
        tinygl_text (score_string);
        break;

    default:
        break;
    }
}


