// Standard headers
#include <stdio.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

// CONSTS
int DEFENDER_USE_SPY_MOMENT = 2;
int MAX_VERTICAL_CRAB_STEPS = 2;

// State
static int turns = 0;
static direction_t current_direction;
static bool vertical_crab = true;
static int current_vertical_crab_steps = 0;

bool is_direction_equals_defender(direction_t direction_1, direction_t direction_2){
  return (direction_1.i == direction_2.i && direction_1.j == direction_2.j);
}

direction_t inverse_direction_vertical(direction_t direction){
  if(is_direction_equals_defender(direction, (direction_t) DIR_UP)) return (direction_t) DIR_DOWN;
  return (direction_t) DIR_UP;
}

/**
 * Choose the best defender's direction to reach attacker
 *  based on both positions (attacker and defender)
 */
direction_t get_best_defender_direction_by_positions(position_t defender_position, position_t attacker_position){
  if (attacker_position.j < defender_position.j) return (direction_t) DIR_DOWN;
  if (attacker_position.j > defender_position.j) return (direction_t) DIR_UP;
  return (direction_t) DIR_LEFT;
}

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy) {

  direction_t chosen_direction;

  // Normal cases
  if(vertical_crab && current_vertical_crab_steps == MAX_VERTICAL_CRAB_STEPS) { // Time to change directions
    current_vertical_crab_steps = 0;
    chosen_direction = inverse_direction_vertical(current_direction);
  } else { // Keep crabing
    current_vertical_crab_steps += 1;
    chosen_direction = current_direction;
  }

  // Spy cases
  if(turns == DEFENDER_USE_SPY_MOMENT){ // Use spy based on const
    vertical_crab = false; // Get "smart" and disable crab strategy
    position_t attacker_position = get_spy_position(attacker_spy);
    chosen_direction = get_best_defender_direction_by_positions(defender_position, attacker_position);
  }

  // Update state
  turns += 1;

  return chosen_direction;
}

/*----------------------------------------------------------------------------*/
