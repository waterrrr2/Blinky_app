/** @file   player_loc.h
    @author C. Papple, K. Lai
    @date   20 Oct 2021
    @brief  This module implements the movement and display aspect of the player
*/

#ifndef PLAYER_LOC_H
#define PLAYER_LOC_H

#include "navswitch.h"
#include "system.h"
#include "ledmat.h"

#define MAX_LOC 6
#define MIN_LOC 0
#define PLAYER_COL 4
#define START_LOC 3

uint8_t player_loc;

uint8_t location;

uint8_t player_init(void);

/* Moves the player pixel upwards */

void player_loc_up(void);

/* Moves the player pixel downwards */

void player_loc_down(void);

/* Displays the current player location pixel */

void player_display(int player_loc);

#endif
