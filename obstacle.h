/** @file   obstacle.h
    @author C. Papple, K. Lai
    @date   20 Oct 2021
    @brief  This module implements the display and collision checking aspect of the obstacles
*/

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "system.h"
#include "ledmat.h"
#include "display.h"
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define max_row 5
#define min_row 0
#define max_col 7
#define min_col 0
#define obs_start 0
#define obs_final 4

uint8_t obs_current;

uint8_t pos;

uint8_t gap;

uint8_t rand_val;

uint8_t collided;

uint8_t score;

void obs_init(void);

/*takes an uint8_t value as level, reducing the number of gap pixels
according to the difficulty*/

void obs_level(uint8_t level);

/*displays the obsticles, dims a certain number of pixels to create a gap*/

void obs_on(void);

/*moves the obsticle foward, randomises the position of the gap when reached
the end of the display*/

void obs_move(void);

/* Checks if the player has collided with the obstacle */

uint8_t check_collision (void);

void obstacle_task_init (uint8_t level);

/* Driver for the obstacle display */ 

void obstacle_task (void);

#endif
