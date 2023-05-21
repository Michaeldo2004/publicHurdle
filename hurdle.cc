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
  hurdle_state_.SetError("");
  if (hurdle_state_.isActive()) {
    if (hurdle_state_.GetGuesses().size() ==
        0) {                       // empty vector -> adds something
      hurdle_state_.AddGuess("");  // YOU WANT TO PUSH BACK THE KEY INTO THE
                                   // VECTOR NOT AN EMPTY STRING
    }
    int index = hurdle_state_.GetGuesses().size() - 1;
    std::string current_word = hurdle_state_.GetGuesses().at(index);
    if (hurdle_state_.GetGuesses().at(index).size() <
        5) {  // if guess is less then 5 then adds letter in
      hurdle_state_.GetGuesses()[index] = current_word + key;
    }
  }
}

void HurdleGame::WordSubmitted() {
  hurdle_state_.SetError("");
  if (!hurdle_state_.isActive()) {
    return;
  } else {  // YOU DONT NEED TO DO THIS ELSE STATEMENT AT ALL!! delete lines 39
            // - 62
    std::string color = "";
    int index = hurdle_state_.GetGuesses().size() - 1;
    if (hurdle_state_.GetGuesses().at(index).size() == 5) {
      if (hurdlewords_.IsGuessValid(hurdle_state_.GetGuesses().at(
              index))) {  // valid guess -> adds colors
        color = hurdle_state_.ColorCheck(hurdle_state_.GetGuesses().at(index),
                                         hurdle_state_.GetHurdle());
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
      /* example of what i did


 if (hurdlewords_.IsGuessValid(hurdle_state_.GetKey())) { // THE "key" is a
 string where i was tracking the current guess

  hurdle_state_.Status();
  hurdle_state_.Colors();
  hurdle_state_.ClearKey();
  hurdle_state_.SetErrorMessage("");
 } else {
  hurdle_state_.SetErrorMessage("Your word is not valid.");
 }




   */
      hurdle_state_.SetError("Needs more letters!");
      return;
    }
  }
}
void HurdleGame::LetterDeleted() {
  // YOU CAN SIMPLIFY THIS
  // 1) Do a conditional to check the current word. if the word size is 0 then
  // give error message else set the error message to an empty string, and then
  // use the .pop_back() to remove a character from that string
  hurdle_state_.SetError("");
  if (hurdle_state_.isActive()) {
    if (hurdle_state_.GetGuesses()
            .at(hurdle_state_.GetGuesses().size() - 1)
            .size() == 0) {
      hurdle_state_.SetError("There are no words to delete.");
    } else {
      hurdle_state_.SetError("");
      hurdle_state_.GetGuesses()
          .at(hurdle_state_.GetGuesses().size() - 1)
          .pop_back();
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