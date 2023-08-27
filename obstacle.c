/** @file   obstacle.c
    @author C. Papple, K. Lai
    @date   20 Oct 2021
    @brief  This module implements the display and collision checking aspect of the obstacles
*/

#include "obstacle.h"
#include "system.h"
#include "ledmat.h"
#include "player_loc.h"
#include "level_select.h"
#include "display.h"
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

/* Initialization */

void obs_init(void)
{
    srand(time(NULL));
    obs_current = obs_start;
    rand_val = 5;
    gap = 3;
    score = 0;
}

/* Sets up Gap sizes based on selected difficuly */

void obs_level(uint8_t level)
{
    switch(level)
    {
    default:
    case 1:
        rand_val = 5;
        gap = 3;
        break;
    
    case 2:
        rand_val = 6;
        gap = 2;
        break;
    case 3:
        rand_val = 7;
        gap = 1;
        break;
    }
}

/* Displays the obstacle */

void obs_on(void)
{
    for (uint8_t i = min_col; i < max_col; i++){
        display_pixel_set(obs_current,i,1);
    }
    
    for (uint8_t i = pos; i < pos+gap; i++){
        display_pixel_set(obs_current,i,0);
    }
    display_update();
}

/* Moves the obstacle closer to the character
and makes a new obstacle once the old one reaches the end */

void obs_move(void)
{   
    if(obs_current == obs_final) {
        obs_current = obs_start;
        pos = rand()%rand_val;
    } else {
        obs_current ++;
    }
}

/* Checks if the player and obstacle collided */

uint8_t check_collision (void)
{
	collided = 0;
	if(obs_current == PLAYER_COL)
	{
        /* Checking if the player is within the gap */
		if((player_loc < pos) || (player_loc >= pos + gap)) {
			collided = 1;
		} else {
			collided = 0;
            /* updates score, incremented by number of obstacles multiplied by the difficulty */
			score += 1*level;
		}
	}
    return collided;
}

void obstacle_task_init (uint8_t level)
{
    obs_init ();
    obs_level(level);
}

void obstacle_task (void)
{
    obs_on();
    obs_move();
}
