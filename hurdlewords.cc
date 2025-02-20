#include "hurdlewords.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

HurdleWords::HurdleWords(const std::string& valid_hurdles_filename,
                         const std::string& valid_guesses_filename) {
  // Read from the file containing all valid secret
  // hurdles, and insert them into the valid_hurdles_ vector.
  std::ifstream hurdles_file(valid_hurdles_filename);
  std::string word;
  while (hurdles_file >> word) {
    valid_hurdles_.push_back(word);
  }

  // Read from the file containing all valid guesses,
  // and insert them into the valid_guesses_ set.
  std::ifstream guesses_file(valid_guesses_filename);
  while (guesses_file >> word) {
    valid_guesses_.insert(word);
  }
  // Use the current time as a seed for the random number generator.
  srand(time(nullptr));
}

bool HurdleWords::IsGuessValid(const std::string& word) const {
  if (std::find(valid_guesses_.begin(), valid_guesses_.end(), word) !=
      valid_guesses_.end()) {
    return true;
  } else {
    return false;
  }
}

const std::string& HurdleWords::GetRandomHurdle() const {
  int i = rand() % valid_hurdles_.size();
  return valid_hurdles_.at(i);
}