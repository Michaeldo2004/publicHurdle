#include "hurdle.h"

using std::string;

void HurdleGame::NewHurdle() {
  std::vector<std::string> empty = {};
  hurdle_state_.SetHurdle(hurdlewords_.GetRandomHurdle());
  hurdle_state_.GetGuesses().clear();
  hurdle_state_.SetGuesses(empty);
  hurdle_state_.SetColor(empty);
  hurdle_state_.SetStatus("active");
  hurdle_state_.SetError("");
  JsonFromHurdleState();
}
void HurdleGame::LetterEntered(char key) {
  if (hurdle_state_.isActive()) {
    if (hurdle_state_.GetGuesses().size() ==
        0) {  // empty vector -> adds something
      hurdle_state_.AddGuess("");
    }
    if (hurdle_state_.GetGuesses()
            .at(hurdle_state_.GetGuesses().size() - 1)
            .length() < 5) {  // if guess is less then 5 then adds letter in
      hurdle_state_.GetGuesses().at(hurdle_state_.GetGuesses().size() - 1) +=
          key;
    } else {
      hurdle_state_.SetError("Cannot enter letter!");
    }
  }
}

void HurdleGame::WordSubmitted() {
  if (hurdle_state_.isActive()) {
    hurdle_state_.SetError("");
    std::string color = "";
    int index = hurdle_state_.GetGuesses().size() - 1;
    if (hurdle_state_.GetGuesses().at(index).length() == 5) {
      if (hurdlewords_.IsGuessValid(hurdle_state_.GetGuesses().at(
              index))) {  // valid guess -> adds colors
        color = hurdle_state_.ColorCheck(hurdle_state_.GetGuesses().at(index),
                                         hurdle_state_.GetHurdle());
      }
      hurdle_state_.GetColor().push_back(color);  // adds color to colorboard
      if (color == "GGGGG") {                     // winchecker
        hurdle_state_.SetStatus("win");
      }
      if (hurdle_state_.GetGuesses().size() == 6) {  // lose checker
        hurdle_state_.SetStatus("lose");
      }
      if (hurdle_state_.isActive()) {
        hurdle_state_.AddGuess("");  // adds new guess if active
      }
    } else {
      hurdle_state_.SetError("Invalid Word.");
      return;
    }
  } else {
    hurdle_state_.SetError("Needs more letters!");
    return;
  }
}
void HurdleGame::LetterDeleted() {
  if (hurdle_state_.isActive()) {
    if (hurdle_state_.GetGuesses()
                .at(hurdle_state_.GetGuesses().size() - 1)
                .length() >= 1 &&
        hurdle_state_.GetGuesses().size() < 1) {
      std::string lastword =
          hurdle_state_.GetGuesses().at(hurdle_state_.GetGuesses().size() - 1);
      hurdle_state_.SetGuess(lastword.substr(0, lastword.length() - 1));
    } else {
      hurdle_state_.SetError("There are no words to delete.");
    }
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