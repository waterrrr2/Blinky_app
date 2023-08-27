/** @file   level_select.c
    @author C. Papple, K. Lai
    @date   20 Oct 2021
    @brief  This module implements the level selection aspect of the game
*/

#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "level_select.h"
#include <string.h>
#include "../fonts/font5x7_1.h"

/* Initialization */

uint8_t level_select_init(void)
{
   level = MIN_LEVEL;
   return level;
}

/* Increments level variable by one until max level */

void level_select_up (void)
{
	if(level <= MIN_LEVEL) {
	    level = MIN_LEVEL;
	} else {
		level --;
	}	
}
	
/* Decreases level variable by 1 until min level */	
	
void level_select_down (void)
{
	if(level >= MAX_LEVEL) {
	   level = MAX_LEVEL;
	} else {
		level ++;
	}
}

/* Uses tinygl to display the level */

void lv_display(uint8_t cur_level)
{
    switch(cur_level)
    {
    default:
    case 1:
        tinygl_text ("LV1");
        break;
    
    case 2:
        tinygl_text ("LV2");
        break;
    
    case 3:
        tinygl_text ("LV3");
        break;
    }     
}

