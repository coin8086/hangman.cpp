#ifndef __GUESSLETTER_H__
#define __GUESSLETTER_H__

#include <sstream>
#include "Guess.h"

/**
 * A Guess that represents guessing a letter for the current Hangman game
 */
class GuessLetter : public Guess {
public:
  GuessLetter(char guess) {
    _guess = guess;
  }

  //NOTE: C++11 override
  void makeGuess(HangmanGame & game) override {
    game.guessLetter(_guess);
  }

  //NOTE: C++11 override
  string toString() const override {
    stringstream ss;
    ss <<  "GuessLetter[" << _guess << "]";
    return ss.str();
  }

private:
  char _guess;
};

#endif
