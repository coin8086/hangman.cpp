#ifndef __GUESS_H__
#define __GUESS_H__

#include <string>
#include "HangmanGame.h"

using std::string;

/**
 * Common interface for GuessWord and GuessLetter
 */
class Guess {
public:
  /**
   * Applies the current guess to the specified game.
   */
  virtual void makeGuess(HangmanGame & game) = 0;

  virtual string toString() const = 0;
};

#endif
