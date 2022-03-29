// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

// Global Variables
//#define TURN_DEFENDER       (int) 0;
int TURN_DEFENDER = 0;
int LAST_DIRECTION_MOVED_DEFENDER = -1;
position_t LAST_POSITION_DEFENDER = {-1, -1};
position_t INICIAL_POSITION_DEFENDER = {-1, -1};
position_t POSITION_ATTACKER_SPY = {-1, -1};

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy)
{
  direction_t direction_list[10] = {DIR_UP, DIR_DOWN, DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_DOWN_LEFT, DIR_DOWN_RIGHT, DIR_UP_LEFT, DIR_UP_RIGHT};
  int mov;
  TURN_DEFENDER++;
  srand(time(0));

  //Save the initial position
  if ((int)INICIAL_POSITION_DEFENDER.i == -1)
  {
    INICIAL_POSITION_DEFENDER.i = defender_position.i;
    INICIAL_POSITION_DEFENDER.j = defender_position.j;
  }

  // Hit a barrier - need to move to another direction
  if (equal_positions(LAST_POSITION_DEFENDER, defender_position))
  {
    mov = rand() % 10;
    while (mov == LAST_DIRECTION_MOVED_DEFENDER)
    {
      mov = rand() % 10;
    }
    LAST_DIRECTION_MOVED_DEFENDER = mov;
    return direction_list[mov];
  }

  LAST_POSITION_DEFENDER = defender_position;

  if (TURN_DEFENDER < ((int)INICIAL_POSITION_DEFENDER.j) / 2 + 1)
  {
    // Main strategy before the SPY

    if (abs((int)defender_position.j - (int)INICIAL_POSITION_DEFENDER.j) < 2)
    {
      mov = 4;
      LAST_DIRECTION_MOVED_DEFENDER = mov;
      return direction_list[mov];
    }
    else
    {
      mov = rand() % 4 == 0;
      LAST_DIRECTION_MOVED_DEFENDER = mov;
      return direction_list[mov];
    }
  }
  else
  {
    //Use SPY
    if ((int)POSITION_ATTACKER_SPY.i == -1)
    {
      POSITION_ATTACKER_SPY = get_spy_position(attacker_spy);
    }

    direction_t direction_list_spy[4] = {DIR_UP, DIR_UP, DIR_DOWN, DIR_DOWN};

    if ((int)POSITION_ATTACKER_SPY.i > (int)defender_position.i)
    {
      direction_list_spy[2] = direction_list_spy[1];
    }

    if ((int)POSITION_ATTACKER_SPY.i < (int)defender_position.i)
    {
      direction_list_spy[1] = direction_list_spy[2];
    }

    mov = rand() % 4 == 0;
    LAST_DIRECTION_MOVED_DEFENDER = mov;
    return direction_list_spy[mov];
  }

  mov = 4;
  LAST_DIRECTION_MOVED_DEFENDER = mov;
  return direction_list[mov];
}

/*----------------------------------------------------------------------------*/
