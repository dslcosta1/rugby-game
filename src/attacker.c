// Standard headers
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "attacker.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

// Global Variables
int TURN_ATTACKER = 0;
int LAST_DIRECTION_MOVED_ATTACKER = 0;
int COIN = -1;
position_t LAST_POSITION_ATTACKER = {-1, -1};
position_t INICIAL_POSITION_ATTACKER = {-1, -1};
position_t POSITION_DEFENDER_SPY = {-1, -1};

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy)
{
  direction_t direction_list[10] = {DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_DOWN_LEFT, DIR_DOWN_RIGHT, DIR_UP_LEFT, DIR_UP_RIGHT, DIR_DOWN_RIGHT, DIR_UP_RIGHT};
  int mov;
  TURN_ATTACKER++;
  srand(time(0));

  //Save the initial position
  if ((int)INICIAL_POSITION_ATTACKER.i == -1)
  {
    INICIAL_POSITION_ATTACKER.i = attacker_position.i;
    INICIAL_POSITION_ATTACKER.j = attacker_position.j;
    COIN = rand() % 2;
  }

  // Hit a barrier - need to move to another direction
  if (equal_positions(LAST_POSITION_ATTACKER, attacker_position))
  {
    mov = rand() % 10;
    while (mov == LAST_DIRECTION_MOVED_ATTACKER)
    {
      mov = rand() % 10;
    }
    LAST_DIRECTION_MOVED_ATTACKER = mov;
    return direction_list[mov];
  }

  LAST_POSITION_ATTACKER = attacker_position;

  if (TURN_ATTACKER < (int)INICIAL_POSITION_ATTACKER.i + 2)
  {
    // Main strategy before the SPY
    mov = 8 + COIN;
    LAST_DIRECTION_MOVED_ATTACKER = mov;
    return direction_list[mov];
  }
  else
  {
    //Use SPY
    if ((int)POSITION_DEFENDER_SPY.i == -1)
    {
      POSITION_DEFENDER_SPY = get_spy_position(defender_spy);
      COIN = (COIN + 1) % 2;
    }

    if ((int)POSITION_DEFENDER_SPY.j <= (int)attacker_position.j)
    {
      mov = 3;
    }
    else
    {
      mov = 8 + COIN;
    }

    mov = rand() % 4 == 0;
    LAST_DIRECTION_MOVED_ATTACKER = mov;
    return direction_list[mov];
  }

  mov = 3;
  LAST_DIRECTION_MOVED_ATTACKER = mov;
  return direction_list[mov];
}

/*----------------------------------------------------------------------------*/
