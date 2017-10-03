#ifndef __GUESSINGSTRATEGER_H__
#define __GUESSINGSTRATEGER_H__

#include <memory>
#include "HangmanGame.h"
#include "Guess.h"

using std::shared_ptr;

/**
 * A strategy for generating guesses given the current state of a Hangman game.
 */
class GuessingStrategy {
public:
  //NOTE: C++11 shared_ptr
  virtual shared_ptr<Guess> nextGuess(const HangmanGame & game) = 0;

  virtual string toString() const = 0;
};

#endif
