/** @file   player_loc.c
    @author C. Papple, K. Lai
    @date   20 Oct 2021
    @brief  This module implements the movement and display aspect of the player
*/

#include "player_loc.h"
#include "navswitch.h"
#include "system.h"
#include "ledmat.h"

/* Initialization*/

uint8_t player_init(void)
{
    player_loc = START_LOC;
    return player_loc;  
}

/* Increases player location variable
by one unless at maximum location */

void player_loc_up(void)
{
    if (player_loc != MAX_LOC) {
        player_loc ++;
    } else {
        player_loc = MAX_LOC;
    }
} 

/* Increases player location variable
by one unless at maximum location */

void player_loc_down(void)
{
    if (player_loc != MIN_LOC) {
        player_loc --;
    } else {
        player_loc = MIN_LOC;
    } 
}  

/* Generates a bitmap pased off the 
players location */

void player_display(int player_loc)
{
    location = (0|BIT(player_loc));
    ledmat_display_column (location, PLAYER_COL);
}
