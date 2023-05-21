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
    if (hurdle_state_.GetGuesses().size() == 0) { //empty vector -> adds something
      hurdle_state_.AddGuess("");
    }
    if (hurdle_state_.GetGuesses()
            .at(hurdle_state_.GetGuesses().size() - 1)
            .length() < 5) {  //if guess is less then 5 then adds letter in
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
    if (hurdle_state_.GetGuesses()
            .at(hurdle_state_.GetGuesses().size() - 1)
            .length() == 5) {
      if (hurdlewords_.IsGuessValid(hurdle_state_.GetGuesses().at(
              hurdle_state_.GetGuesses().size() - 1))) {
        for (int i = 0; i < 5; i++) {
          if (hurdle_state_.GetGuesses()
                  .at(hurdle_state_.GetGuesses().size() - 1)
                  .at(i) == hurdle_state_.GetHurdle().at(i)) {
            color += "G";
          } else if (std::find(hurdle_state_.GetHurdle().begin(),
                               hurdle_state_.GetHurdle().end(),
                               hurdle_state_.GetGuesses()
                                   .at(hurdle_state_.GetGuesses().size() - 1)
                                   .at(i)) == hurdle_state_.GetHurdle().end()) {
            color += "B";
          } else {
            color += "Y";
          }
        }
        hurdle_state_.AddColor(color); //adds color to colorboard
        if (color == "GGGGG") {  //winchecker
          hurdle_state_.SetStatus("win");
        }
        if (hurdle_state_.GetGuesses().size() == 6 &&  //lose checker
            hurdle_state_.GetStatus() != "win") {
          hurdle_state_.SetStatus("lose");
        } else {
          hurdle_state_.AddGuess("");  //adds new guess if not 5 guesses yet
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
}
void HurdleGame::LetterDeleted() {
  if (hurdle_state_.isActive()) {
    if (hurdle_state_.GetGuess().length() >= 1) {
      hurdle_state_.SetGuess(hurdle_state_.GetGuess().substr(
          0, hurdle_state_.GetGuess().length() - 1));
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