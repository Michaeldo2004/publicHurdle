#include "hurdle.h"

using std::string;

std::string HurdleGame::ColorCheck(
    const std::string& guess,
    const std::string& answer) {  // returns the colors to put onto the board
  std::string colors = "BBBBB";
  for (int i = 0; i < 5; i++) {
    if (guess[i] == answer[i]) {
      colors[i] = 'G';
    } else if (std::find(answer.begin(), answer.end(), guess.at(i)) !=
               answer.end()) {
      colors[i] = 'Y';
    }
  }
  return colors;
}
void HurdleGame::NewHurdle() {
  hurdle_state_ = HurdleState(hurdlewords_.GetRandomHurdle());
}

void HurdleGame::LetterEntered(char key) {
   if (hurdle_state_.inActive()) {
    return;
  }
  hurdle_state_.SetError("");
  std::vector<std::string>& guessed_hurdles_ = hurdle_state_.GetGuesses();
  if (guessed_hurdles_.size() == 0) {
    guessed_hurdles_.push_back("");
  }
  int guess_index_ = guessed_hurdles_.size() - 1;
  std::string guess = guessed_hurdles_[guess_index_];

  if (guess.length() != 5) {
    guessed_hurdles_[guess_index_] = guess + key;
  }
}


void HurdleGame::WordSubmitted() {
  std::vector<std::string>& list = hurdle_state_.GetGuesses();
  // no guessed words, OR, game is not running
  if (hurdle_state_.inActive()) {
    return;  // return nothing
  }
  // clear errors
  hurdle_state_.SetError("");
  // create index to track which guess is current
  int index = list.size() - 1;
  std::string guess = list.at(index);
  // check for errors with the current guess
  if (guess.length() < 5) {
    hurdle_state_.SetError("Word is too short");
    return;
  } else if (!hurdlewords_.IsGuessValid(
                 guess)) {  // error somewhere with these three lines
    hurdle_state_.SetError("Invalid Word");
    return;
  }
  // assign colors
  std::string colors = ColorCheck(guess, hurdle_state_.GetHurdle());
  hurdle_state_.GetColor().push_back(colors);
  if (colors == "GGGGG") {
    hurdle_state_.SetStatus("win");
  } else if (list.size() == 6) {
    hurdle_state_.SetStatus("lose");
  }
  
  // add empty guess if game is active
  if (!hurdle_state_.inActive()) {
    list.push_back("");
  }
}

void HurdleGame::LetterDeleted() {
  if (hurdle_state_.inActive()) {  // inactive or empty then fails
    return;
  }
  std::string guess = hurdle_state_.GetGuesses()[hurdle_state_.GetGuesses().size() - 1];
  if (guess.length() == 0) {
    hurdle_state_.SetError("Your word is empty!");
    return;
  } else {
    guess.pop_back();
    hurdle_state_.GetGuesses()[hurdle_state_.GetGuesses().size() - 1] = guess;

  }
}

crow::json::wvalue HurdleGame::JsonFromHurdleState() {
  crow::json::wvalue hurdle_state_json({});

  hurdle_state_json["answer"] = hurdle_state_.GetHurdle();
  hurdle_state_json["boardColors"] = hurdle_state_.GetColor();
  hurdle_state_json["guessedWords"] = hurdle_state_.GetGuesses();
  hurdle_state_json["gameStatus"] = hurdle_state_.GetStatus();
  hurdle_state_json["errorMessage"] = hurdle_state_.GetError();

  return hurdle_state_json;
}