#include "hurdle.h"

using std::string;

std::string HurdleGame::ColorCheck(const std::string& guess,
                                   const std::string& hurd) {
  std::string colorsString = "BBBBB";  // default as BBBBB then changed
  for (int i = 0; i < 5; i++) {
    if (guess[i] == hurd[i]) {  // check if equal
      colorsString[i] = 'G';
    } else if (std::find(hurd.begin(), hurd.end(),
                         hurd.at(i)) !=  // if it exists then Y
               hurd.end()) {
      colorsString[i] = 'Y';
    }
  }
  return colorsString;
}
void HurdleGame::NewHurdle() {
  hurdle_state_ = HurdleState(
      hurdlewords_.GetRandomHurdle());  // creates new hurdlestateobject
                                        // (already cleaned)
}

void HurdleGame::LetterEntered(char key) {
  if (hurdle_state_.inActive()) {  // game not on ->dont run
    return;
  }
  hurdle_state_.SetError("");  // errorclean
  std::vector<std::string>& guesslist = hurdle_state_.GetGuesses();
  if (guesslist.size() == 0) {  // empty vector -> make space for key
    guesslist.push_back("");
  }
  int index = guesslist.size() - 1;  // too lazy so index
  std::string guess = guesslist[index];

  if (guess.length() != 5) {
    guesslist[index] = guess + key;  // concatenation bc not 5
  }
}

void HurdleGame::WordSubmitted() {
  std::vector<std::string>& list = hurdle_state_.GetGuesses();
  if (hurdle_state_.inActive()) {
    return;  // stop running
  }
  hurdle_state_.SetError("");
  int index = list.size() - 1;  // too azy to write it all out
  std::string guess = list.at(index);
  if (guess.length() < 5) {  // lengthchecker
    hurdle_state_.SetError("short word");
    return;
  } else if (!hurdlewords_.IsGuessValid(
                 guess)) {  // valid word or not else error
    hurdle_state_.SetError("invalid word");
    return;
  }
  // assign colors
  std::string colors =
      ColorCheck(guess, hurdle_state_.GetHurdle());  // gets 5string color
  hurdle_state_.GetColor().push_back(colors);        // push to colorboard
  if (colors == "GGGGG") {                           // winchecker
    hurdle_state_.SetStatus("win");
  } else if (list.size() == 6) {
    hurdle_state_.SetStatus("lose");  // losechecker
  }

  if (!hurdle_state_.inActive()) {  // make space for next word
    list.push_back("");
  }
}

void HurdleGame::LetterDeleted() {
  if (hurdle_state_.inActive()) {  // game end so no run
    return;
  }
  std::string guess =
      hurdle_state_.GetGuesses()[hurdle_state_.GetGuesses().size() -
                                 1];  // create guess to not type it all out
  if (guess.length() == 0) {          // word checker
    hurdle_state_.SetError("empty word");
    return;
  } else {
    guess.pop_back();  // take out last word
    hurdle_state_.GetGuesses()[hurdle_state_.GetGuesses().size() - 1] =
        guess;  // replace it put it aback in
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