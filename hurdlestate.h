#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "hurdlewords.h"

#ifndef HURDLESTATE_H
#define HURDLESTATE_H

class HurdleState {
 public:

  HurdleState(const std::string& secret_hurdle);

  std::string GetHurdle() const { return secret_hurdle_; }
  std::vector<std::string> GetColor() const { return colors_; }
  std::vector<std::string> GetGuesses() const { return guesses_; }
  std::string GetGuess() const { return current_guess_; }
  std::string GetStatus() const { return game_status_; }
  std::string GetError() const { return error_; }
  void SetHurdle(const std::string& hurdle) { secret_hurdle_ = hurdle; }
  void SetGuess(const std::string& guess) { current_guess_ = guess; }
  void SetGuesses(const std::vector<std::string>& guesses) { guesses_ = guesses; }
  void SetColor(const std::vector<std::string>& color) { colors_ = color; }
  void SetStatus(const std::string& status) { game_status_ = status; }
  void SetError(const std::string& error) { error_ = error; }

  bool isActive() { return game_status_ == "active"; }
  void AddColor(const std::string& color);
  void AddGuess(const std::string& guess);
  std::string ColorCheck(const std::string& guess, const std::string& answer);

 private:
  std::string secret_hurdle_ = "answer";
  std::vector<std::string> guesses_;
  std::string current_guess_;
  std::string game_status_ = "active";
  std::vector<std::string> colors_;
  std::string error_;
};

#endif  // HURDLESTATE_H