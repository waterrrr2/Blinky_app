/** @file   level_select.h
    @author C. Papple, K. Lai
    @date   20 Oct 2021
    @brief  This module implements the level selection aspect of the game
*/

#ifndef LEVEL_SELECT_H
#define LEVEL_SELECT_H

#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"

#define MIN_LEVEL 1
#define MAX_LEVEL 3

uint8_t level;

uint8_t set_level;

uint8_t cur_level;

uint8_t level_select_init(void);

/* Increases the level of the game */

void level_select_up (void);

/* Decreases the level of the game */

void level_select_down (void);

/* Handels the display of the levels in level seletion screen*/

void lv_display(uint8_t cur_level);

#endif

