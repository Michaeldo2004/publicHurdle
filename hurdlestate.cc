#include "hurdlestate.h"

HurdleState::HurdleState(const std::string& hurdle) {
  secret_hurdle_ = hurdle;
  guesses_ = {};
  current_guess_ = "";
  game_status_ = "active";
  colors_ = {};
  error_ = "";
  counter_ = 0;
}
void HurdleState::AddColor(const std::string& color) {
  if (color == "GGGGG") {
    game_status_ = "win";
  }
  colors_.push_back(color);
}

void HurdleState::AddGuess(const std::string& guess, int c) {
  guesses_.at(c) = guess;
  if (guesses_.size() >= 5 && game_status_ != "win" || guesses_.size() < 0) {
    game_status_ = "lose";
  }
}