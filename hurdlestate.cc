#include "hurdlestate.h"


HurdleState::HurdleState(const std::string& hurdle) {
  secret_hurdle_ = hurdle;
  error_ = "";
  game_status_ = "active";
}
void HurdleState::AddColor(const std::string& color) {
  colors_.push_back(color);
}

void HurdleState::AddGuess(const std::string& guess) {
  guesses_.push_back(guess);
}
