#include "hurdlestate.h"

HurdleState::HurdleState(const std::string& hurdle) {
  secret_hurdle_ = hurdle;
  guesses_ = {};
  current_guess_ = "";
  colors_ = {};
  error_ = "";
}
void HurdleState::AddColor(const std::string& color) {
  colors_.push_back(color);
}

void HurdleState::AddGuess(const std::string& guess) {
  guesses_.push_back(guess);
}

std::string HurdleState::ColorCheck(const std::string& guess,
                                    const std::string& answer) {
  std::string colors = "";
  for (int i = 0; i <= 5; i++) {
    if (guess.at(i) == answer.at(i)) {
      colors += "G";
    } else if (std::find(answer.begin(), answer.end(), guess.at(i)) ==
               answer.end()) {
      colors += "B";
    } else {
      colors += "Y";
    }
  }
  return colors;
}
