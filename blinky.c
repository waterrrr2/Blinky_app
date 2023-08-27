/** @file   blinky.c
    @author C. Papple, K. Lai
    @date   20 Oct 2021
    @brief  An obstacle avoiding game with different difficulty levels

    @defgroup blinky An obstacle avoiding game with three different difficulty
*/

#include "system.h"
#include "blinky_tasks.h"
#include "task.h"

/* 
    An obstacle avoiding game, player will have to avoid obstacles to accumulate a score.
    There are three different difficulties/levels, each increment in difficulty will reduce 
    the size of the gap of which the player can pass through.
    The score is determined by the number of obstacles avoided and the level of difficulty.
*/

int main (void)
{
    
    /*Set up Tasks to scheduler*/
    task_t tasks[] =
    {   
        {.func = display_task, .period = TASK_RATE / DISPLAY_TASK_RATE, 
        .data = 0},
        {.func = player_task, .period = TASK_RATE / PLAYER_TASK_RATE,
        .data = 0}, 
        {.func = navswitch_task, .period = TASK_RATE / BUTTON_TASK_RATE,
         .data = 0},
        {.func = game_task, .period = TASK_RATE / GAME_TASK_RATE,
        .data = 0}, 
          
    };
    
    /*Initialisation*/
    blinky_init();
    
    /*Run Game*/
    task_schedule (tasks, ARRAY_SIZE (tasks));
    return 0;
}
