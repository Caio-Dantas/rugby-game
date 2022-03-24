// Standard headers
#include <stdio.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "attacker.h"

// CONSTS
int ATTACKER_USE_SPY_MOMENT = 2;

// State
static position_t previous_attacker_position;
static int turns = 0;
static direction_t current_direction;

bool is_position_equals(position_t position_1, position_t position_2){
  return (position_1.i == position_2.i && position_1.j == position_2.j);
}

bool is_direction_equals_attacker(direction_t direction_1, direction_t direction_2){
  return (direction_1.i == direction_2.i && direction_1.j == direction_2.j);
}

/**
 * Choose the best attacker's direction to avoid defender
 *  based on both positions (attacker and defender)
 */
direction_t get_best_attacker_direction_by_positions(position_t attacker_position, position_t defender_position){
  if (attacker_position.j < defender_position.j) return (direction_t) DIR_DOWN_RIGHT;
  return (direction_t) DIR_UP_RIGHT;
}

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {

  direction_t chosen_direction;

  // Normal cases
  if (turns == 0){ // Go right on first turn
    chosen_direction = (direction_t) DIR_RIGHT;
  } else { // Always keep up and right
    chosen_direction = (direction_t) DIR_UP_RIGHT;
  }

  // Corner cases --> Cases when we found a corner
  if(is_position_equals(previous_attacker_position, attacker_position)){
    if(is_direction_equals_attacker(current_direction, (direction_t) DIR_UP_RIGHT)){ // We can't go up and right
      chosen_direction = (direction_t) DIR_DOWN_RIGHT;
    } else { // Always up and right
      chosen_direction = (direction_t) DIR_UP_RIGHT;
    }
  }

  // Spy cases
  if(turns == ATTACKER_USE_SPY_MOMENT){ // Use spy based on const
    position_t defender_position = get_spy_position(defender_spy);
    chosen_direction = get_best_attacker_direction_by_positions(attacker_position, defender_position);
  }

  // Update state
  previous_attacker_position = attacker_position;
  turns += 1;
  current_direction = chosen_direction;

  return chosen_direction;
}

/*----------------------------------------------------------------------------*/
