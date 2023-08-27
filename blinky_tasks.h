/** @file   blinky_tasks.h
    @author C. Papple, K. Lai
    @date   20 Oct 2021
    @brief  This module implements most of the logic associated with button pressing
*/

#ifndef BLINKY_TASKS_H
#define BLINKY_TASKS_H

#include "uint8toa.h"
#include "navswitch.h"
#include "ledmat.h"
#include "pacer.h"
#include "obstacle.h"
#include "level_select.h"
#include "../fonts/font3x5_1.h"
#include "player_loc.h"
#include <string.h>

#define PLAYER_TASK_RATE  200
#define OBSTACLE_TASK_RATE 2
#define LEVEL_TASK_RATE 50
#define DISPLAY_TASK_RATE 250
#define BUTTON_TASK_RATE  5
#define GAME_TASK_RATE 2
#define TEXT_SPEED 20


typedef enum {STATE_MENU,STATE_IDEL,STATE_LV_SELECT,STATE_PREGAME,STATE_INGAME,
               STATE_PLAYING,STATE_OVER,STATE_POSTGAME} state_t;
state_t state;

char score_string[44];

char *str;

void blinky_init(void);

void display_task (__unused__ void *data);

void player_task (__unused__ void *data);

void navswitch_task (__unused__ void *data);

void game_task (__unused__ void *data);

#endif
