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
    hurdle_state_.SetError("");
    if (hurdle_state_.GetGuess().length() < 5) {
      hurdle_state_.GetGuess() += key;
      hurdle_state_.SetError("");
    } else {
      hurdle_state_.SetError("Cannot enter letter!");
    }
  }
}

void HurdleGame::WordSubmitted() {
  if (hurdle_state_.isActive()) {
    hurdle_state_.SetError("");
    std::string color = "";
    if (hurdle_state_.GetGuess().size() == 5) {
      if (hurdlewords_.IsGuessValid(hurdle_state_.GetGuess())) {
        hurdle_state_.SetError("");
        for (int i = 0; i < 5; i++) {
          if (hurdle_state_.GetGuess().at(i) ==
              hurdle_state_.GetHurdle().at(i)) {
            color += "G";
          } else if (std::find(hurdle_state_.GetHurdle().begin(),
                               hurdle_state_.GetHurdle().end(),
                               hurdle_state_.GetGuess().at(i)) ==
                     hurdle_state_.GetHurdle().end()) {
            color += "B";
          } else {
            color += "Y";
          }
        }
        hurdle_state_.AddColor(color);
        hurdle_state_.AddGuess(hurdle_state_.GetGuess());

      } else {
        hurdle_state_.SetError("Invalid Word.");
        return;
      }
    } else {
      hurdle_state_.SetError("Needs more letters!");
      return;
    }
  }
}
void HurdleGame::LetterDeleted() {
  if (hurdle_state_.isActive()) {
    hurdle_state_.SetError("");
    if (hurdle_state_.GetGuess().length() >= 1) {
      hurdle_state_.SetGuess(hurdle_state_.GetGuess().substr(
          0, hurdle_state_.GetGuess().length() - 1));
      hurdle_state_.SetError("");
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