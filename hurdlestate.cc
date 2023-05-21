#include "hurdlestate.h"

HurdleState::HurdleState(const std::string& hurdle) {
  secret_hurdle_ = hurdle;
  guesses_ = {""};
  current_guess_ = "";
  game_status_ = "active";
  colors_ = {""};
  error_ = "";
  
}