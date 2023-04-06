#include <string>
#include <vector>

#include "hurdlewords.h"
#include "hurdlestate.h"
#include "server_utils/crow_all.h"

#ifndef HURDLE_H
#define HURDLE_H

class HurdleGame {
 public:
  HurdleGame(HurdleWords words)
      : hurdlewords_(words), hurdle_state_(words.GetRandomHurdle()) {}

  // Called by the Hurdle frontend when the user clicks "Next Hurdle".
  void NewHurdle();
  // Called by the Hurdle frontend when the user enters a letter.
  void LetterEntered(char key);
  // Called by the Hurdle frontend when the user submits a guess.
  void WordSubmitted();
  // Called by the Hurdle frontend when the presses backspace.
  void LetterDeleted();
  // JsonFromHurdleState returns a JSON object representing the Hurdle state.
  // This is used to send the game state to the Hurdle Frontend in a readable
  // format.
  crow::json::wvalue JsonFromHurdleState();

 private:
  HurdleState hurdle_state_;
  HurdleWords hurdlewords_;
};

#endif  // HURDLE_H
